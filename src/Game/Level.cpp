#include "Level.h"

#include "GameObject/BrickWall.h"
#include "../Resources/ResourceManager.h"

#define BLOCK_SIZE 16

std::shared_ptr<IGameObject> createGameObjectFromDescription(const char description, const glm::vec2& position, const glm::vec2& size, const float rotation)
{
	switch (description)
	{
	case '0':
		return std::make_shared<BrickWall>(ResourceManager::getSprite("brickWall_right"), position, size, rotation);
		break;
	case '1':
		return std::make_shared<BrickWall>(ResourceManager::getSprite("brickWall_bottom"), position, size, rotation);
		break;
	case '2':
		return std::make_shared<BrickWall>(ResourceManager::getSprite("brickWall_left"), position, size, rotation);
		break;
	case '3':
		return std::make_shared<BrickWall>(ResourceManager::getSprite("brickWall_top"), position, size, rotation);
		break;
	case '4':
		return std::make_shared<BrickWall>(ResourceManager::getSprite("brickWall"), position, size, rotation);
		break;
	case 'G':
		return std::make_shared<BrickWall>(ResourceManager::getSprite("brickWall_BottomLeft"), position, size, rotation);
		break;
	case 'H':
		return std::make_shared<BrickWall>(ResourceManager::getSprite("brickWall_BottomRight"), position, size, rotation);
		break;
	case 'I':
		return std::make_shared<BrickWall>(ResourceManager::getSprite("brickWall_TopLeft"), position, size, rotation);
		break;
	case 'J':
		return std::make_shared<BrickWall>(ResourceManager::getSprite("brickWall_TopRight"), position, size, rotation);
		break;
	case 'D':
		return nullptr;
		break;
	default:
		std::cerr << "Unknown GameObject descriptoin! " << description << std::endl;
		return nullptr;
		break;
	}
	return nullptr;
}

Level::Level(const std::vector<std::string> levelDescription)
{
	if (levelDescription.empty())
	{
		std::cerr << "Level is empty!" << std::endl;
	}

	m_widht = levelDescription[0].length();
	m_height = levelDescription.size();
	m_mapObject.reserve(m_widht * m_height);

	unsigned int currentBottomOffset{static_cast<unsigned int>(BLOCK_SIZE * (m_height - 1))};

	for (const auto& currentRow : levelDescription)
	{
		unsigned int currentLeftOffset{ 0 };
		for (const auto currentElement : currentRow)
		{
			m_mapObject.emplace_back(createGameObjectFromDescription(currentElement, glm::vec2(currentLeftOffset, currentBottomOffset), glm::vec2(BLOCK_SIZE, BLOCK_SIZE), 0.f));
			currentLeftOffset += BLOCK_SIZE;
		}

		currentBottomOffset -= BLOCK_SIZE;
	}
}

void Level::render() const
{
	for (const auto currentObject : m_mapObject)
	{
		if (currentObject)
		{
			currentObject->render();
		}
	}
}


void Level::update(const uint64_t delta)
{
	for (const auto currentObject : m_mapObject)
	{
		if (currentObject)
		{
			currentObject->update(delta);
		}
	}
}