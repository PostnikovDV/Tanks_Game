#include "ResourceManager.h"
#include "../Renderer/ShaderProgram.h"
#include "../Renderer/Texture2D.h"
#include "../Renderer/Sprite.h"
#include <sstream>
#include <fstream>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"

#include <rapidjson/document.h>
#include <rapidjson/error/en.h>


ResourceManager::ShaderProgramsMap ResourceManager::m_shaderPrograms;
ResourceManager::TexturesMap ResourceManager::m_textures;
ResourceManager::SpritesMap ResourceManager::m_sprites;
std::string ResourceManager::m_path;
std::vector<std::vector<std::string>> ResourceManager::m_levels;

void ResourceManager::unloadAllResources()
{
	m_shaderPrograms.clear();
	m_textures.clear();
	m_sprites.clear();
}

void ResourceManager::setExecutablePath(const std::string& executablePath)
{
	size_t found = executablePath.find_last_of("/\\");//ищем последний слеш
	m_path = executablePath.substr(0, found);
}

std::string ResourceManager::getFileString(const std::string& relativeFilePath)
{
	std::ifstream f;
	f.open(m_path + "/" + relativeFilePath.c_str(), std::ios::in | std::ios::binary);
	if (!f.is_open())
	{
		std::cerr << "Failed to open file: " << relativeFilePath << std::endl;
		return std::string{};
	}

	std::stringstream buffer;
	buffer << f.rdbuf();
	return buffer.str();
}

std::shared_ptr<RenderEngine::ShaderProgram> ResourceManager::loadShaders(const std::string& shaderName
	, const std::string& vertexPath, const std::string& fragmentPath)
{
	std::string vertexString = getFileString(vertexPath);
	if (vertexString.empty())
	{
		std::cerr << "No vertex shader!" << std::endl;
		return nullptr;
	}

	std::string fragmentString = getFileString(fragmentPath);
	if (fragmentString.empty())
	{
		std::cerr << "No fragment shader!" << std::endl;
		return nullptr;
	}

	std::shared_ptr<RenderEngine::ShaderProgram>& newShader =
		m_shaderPrograms.emplace(shaderName, std::make_shared<RenderEngine::ShaderProgram>
		(vertexString, fragmentString)).first->second;

	if (newShader->isCompiled())
	{
		return newShader;
	}
	
	std::cerr << "Can't load shader program: \n"
		<< "Vertex: " << vertexPath << "\n"
		<< "Fragment: " << fragmentPath << std::endl;
	return nullptr;
}

std::shared_ptr<RenderEngine::ShaderProgram> ResourceManager::getShaderProgram(const std::string& shaderName)
{
	ShaderProgramsMap::const_iterator it = m_shaderPrograms.find(shaderName);
	if (it != m_shaderPrograms.end())
	{
		return it->second;
	}

	std::cerr << "Can't find the shader program: " << shaderName << std::endl;
	return nullptr;
}

std::shared_ptr<RenderEngine::Texture2D> ResourceManager::loadTexture(const std::string& textureName, const std::string& texturePath)
{
	int channels{ 0 };
	int width{ 0 };
	int height{ 0 };

	stbi_set_flip_vertically_on_load(true);
	unsigned char* pixels = stbi_load(std::string(m_path + "/" + texturePath).c_str(), &width, &height, &channels, 0);

	if (!pixels)
	{
		std::cerr << "Can't load image: " << texturePath << std::endl;
		return nullptr;
	}

	std::shared_ptr<RenderEngine::Texture2D> newTextures = m_textures.emplace(textureName,
		std::make_shared<RenderEngine::Texture2D>(width, height, pixels, channels, GL_NEAREST, GL_CLAMP_TO_EDGE)).first->second;

	stbi_image_free(pixels);
	return newTextures;
}

std::shared_ptr<RenderEngine::Texture2D> ResourceManager::getTexture(const std::string& textureName)
{
	TexturesMap::const_iterator it = m_textures.find(textureName);
	if (it != m_textures.end())
	{
		return it->second;
	}

	std::cerr << "Can't find the texture: " << textureName << std::endl;
	return nullptr;
}

std::shared_ptr<RenderEngine::Sprite> ResourceManager::loadSprite(const std::string& spriteName
	, const std::string& textureName
	, const std::string& shaderName
	, const std::string subTextureName)
{
	const auto pTexture = getTexture(textureName);
	if (!pTexture)
	{
		std::cerr << "Can't find the texture: " << textureName <<"for the sprite: " << spriteName << std::endl;
	}

	const auto pShader = getShaderProgram(shaderName);
	if (!pShader)
	{
		std::cerr << "Can't find the shader: " << shaderName << "for the sprite: " << spriteName << std::endl;
	}

	std::shared_ptr<RenderEngine::Sprite> newSprite = m_sprites.emplace(spriteName,
		std::make_shared<RenderEngine::Sprite>(
												pTexture
												, subTextureName
												, pShader
	)).first->second;

	return newSprite;
}

std::shared_ptr<RenderEngine::Sprite>  ResourceManager::getSprite(const std::string& spriteName)
{
	SpritesMap::const_iterator it = m_sprites.find(spriteName);
	if (it != m_sprites.end())
	{
		return it->second;
	}

	std::cerr << "Can't find the sprite: " << spriteName << std::endl;
	return nullptr;
}

std::shared_ptr<RenderEngine::Texture2D> ResourceManager::loadTextureAtlas(
																	std::string textureName
																	, std::string texturePath
																	, std::vector<std::string> subTextures
																	, const unsigned int subTextureWidth
																	, const unsigned int subTextureHeight)
{
	auto pTexture = loadTexture(std::move(textureName), std::move(texturePath));

	if (pTexture)
	{
		const unsigned int textureWidth = pTexture->getWidth();
		const unsigned int textureHeight = pTexture->getHeight();
		
		unsigned int currentSubTextureOffsetX = 0;
		unsigned int currentSubTextureOffsetY = textureHeight;

		for (auto& currentSubTextureName : subTextures)
		{
			glm::vec2 leftBottomUV(static_cast<float>(currentSubTextureOffsetX + 0.01f) / textureWidth
								 , static_cast<float>(currentSubTextureOffsetY - subTextureHeight + 0.01f) / textureHeight);

			glm::vec2 rightTopUV(static_cast<float>(currentSubTextureOffsetX + subTextureWidth - 0.01f) / textureWidth
				, static_cast<float>(currentSubTextureOffsetY - 0.01f) / textureHeight);

			pTexture->addSubTexture2D(std::move(currentSubTextureName), leftBottomUV, rightTopUV);

			currentSubTextureOffsetX += subTextureWidth;

			if (currentSubTextureOffsetX >= textureWidth)
			{
				currentSubTextureOffsetX = 0;
				currentSubTextureOffsetY -= subTextureHeight;
			}
		}
	}

	return pTexture;
}

bool ResourceManager::loadJsonResources(const std::string jsonPath)
{
	std::string jsonString = getFileString(jsonPath);

	if (jsonString.empty())
	{
		std::cerr << "No JSON resource file" << std::endl;
		return false;
	}

	rapidjson::Document document;

	rapidjson::ParseResult parseResult = document.Parse(jsonString.c_str());

	if (!parseResult)
	{
		std::cerr << "JSON parse error " << rapidjson::GetParseError_En(parseResult.Code()) <<"(" << parseResult.Offset() << ")" << std::endl;
		std::cerr << "In JSON file: " << jsonPath << std::endl;
		return false;
	}

	auto shaderList = document.FindMember("shaders");

	if (shaderList != document.MemberEnd())
	{
		for (const auto& currentShader : shaderList->value.GetArray())
		{
			const std::string name = currentShader["name"].GetString();
			const std::string filePathV = currentShader["filepath_v"].GetString();
			const std::string filePathF = currentShader["filepath_f"].GetString();

			loadShaders(name, filePathV, filePathF);
		}
	}

	auto textureAtlases = document.FindMember("textureAtlases");

	if (textureAtlases != document.MemberEnd())
	{
		for (const auto& currentTextureAtlas : textureAtlases->value.GetArray())
		{
			const std::string name = currentTextureAtlas["name"].GetString();
			const std::string filePath = currentTextureAtlas["filepath"].GetString();
			const unsigned int subTextureWidth = currentTextureAtlas["subTextureWidth"].GetUint();
			const unsigned int subTextureHeight = currentTextureAtlas["subTextureHeight"].GetUint();
		
			const auto subTexturesArray = currentTextureAtlas["subTextures"].GetArray();

			std::vector<std::string> subTextures;
			subTextures.reserve(subTexturesArray.Size());

			for (const auto& currentSubTexture : subTexturesArray)
			{
				subTextures.emplace_back(currentSubTexture.GetString());
			}
			loadTextureAtlas(name, filePath, std::move(subTextures), subTextureWidth, subTextureHeight);
		}
	}


	auto sprites = document.FindMember("sprites");

	if (sprites != document.MemberEnd())
	{
		for (const auto& currentSprite : sprites->value.GetArray())
		{
			const std::string name = currentSprite["name"].GetString();
			const std::string textureAtlas = currentSprite["textureAtlas"].GetString();
			const std::string shader = currentSprite["shader"].GetString();
			const std::string initialSubTexture = currentSprite["initialSubTexture"].GetString();

			auto pSprite = loadSprite(name, textureAtlas, shader, initialSubTexture);

			if (!pSprite)
			{
				continue;
			}

			auto frames = currentSprite.FindMember("frames");

			if (frames != currentSprite.MemberEnd())
			{
				const auto framesArray = currentSprite["frames"].GetArray();

				std::vector<RenderEngine::Sprite::FrameDescription> frameDescriptions;
				frameDescriptions.reserve(framesArray.Size());

				for (const auto& currentFrame : framesArray)
				{
					std::string subTexture = currentFrame["subTexture"].GetString();
					const uint64_t duration = currentFrame["duration"].GetUint();

					const auto& pTextureAtlas = getTexture(textureAtlas);
					const auto& psubTexture = pTextureAtlas->getSubTexture(subTexture);
					frameDescriptions.emplace_back(psubTexture.leftBottomUV, psubTexture.rightTopUV, duration);
				}
				pSprite->insertFrames(std::move(frameDescriptions));
			}
		}

	}

	auto levelsIt = document.FindMember("levels");

	if (levelsIt != document.MemberEnd())
	{
		for (const auto& currentLevel : levelsIt->value.GetArray())
		{
			const auto descriptionArray = currentLevel["description"].GetArray();

			std::vector<std::string> levelRows;
			levelRows.reserve(descriptionArray.Size());
			size_t maxLenght{ 0 };
			for (const auto& currentRow : descriptionArray)
			{
				levelRows.emplace_back(currentRow.GetString());
				if (maxLenght < levelRows.back().length())
				{
					maxLenght = levelRows.back().length();
				}
			}

			for (auto& currentRow : levelRows)
			{
				while (currentRow.length() < maxLenght)
				{
					currentRow.append("D");
				}
				
			}
			m_levels.emplace_back(std::move(levelRows));
		}
	}

	return true;
}
