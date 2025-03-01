#include <iostream>
#include "AnimatedSprite.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace RenderEngine
{
	AnimatedSprite::AnimatedSprite(
		std::shared_ptr<Texture2D> pTexture
		, std::string initialSubTexture
		, std::shared_ptr<ShaderProgram> pShaderProgram
		, const glm::vec2& position
		, const glm::vec2& size
		, const float rotation)
		: Sprite(std::move(pTexture), std::move(initialSubTexture), std::move(pShaderProgram), position, size, rotation)
	{

	}

	void AnimatedSprite::insertState(std::string state, std::vector<std::pair<std::string, uint64_t>> subTextureDuration)
	{
		m_statesMap.emplace(std::move(state), std::move(subTextureDuration));
	}
	
	void AnimatedSprite::render() const
	{
		if (m_dirty)
		{
			const auto subTexture = m_pTexture->getSubTexture(m_pCurrentAnimationDurations->second[m_currentFrame].first);

			const GLfloat textCoords[]
			{
				subTexture.leftBottomUV.x, subTexture.leftBottomUV.y,
				subTexture.leftBottomUV.x, subTexture.rightTopUV.y,
				subTexture.rightTopUV.x, subTexture.rightTopUV.y,
				subTexture.rightTopUV.x, subTexture.leftBottomUV.y,
			};

			m_textureCoordsBuffer.update(textCoords, sizeof(textCoords));
			m_textureCoordsBuffer.unbind();

			m_dirty = false;
		}
		Sprite::render();
	}

	void AnimatedSprite::update(const uint64_t delta)
	{
		if (m_pCurrentAnimationDurations != m_statesMap.end())
		{
			m_currentAnimationTime += delta;
		}

		while (m_currentAnimationTime >= m_pCurrentAnimationDurations->second[m_currentFrame].second)
		{
			m_currentAnimationTime -= m_pCurrentAnimationDurations->second[m_currentFrame].second;
			++m_currentFrame;
			m_dirty = true;

			if (m_currentFrame == m_pCurrentAnimationDurations->second.size())
			{
				m_currentFrame = 0;
			}
		}
	}

	void AnimatedSprite::setState(const std::string& newState)
	{
		const auto it = m_statesMap.find(newState);

		if (it == m_statesMap.end())
		{
			std::cout << "Can't find animation state: " << newState << std::endl;
			return;
		}

		if (m_pCurrentAnimationDurations != it)
		{
			m_currentFrame = 0;
			m_currentAnimationTime = 0;
			m_pCurrentAnimationDurations = it;
			m_dirty = true;
		}
	}

}