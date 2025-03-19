#include "Level.h"
#include "GameObject/BrickWall.h"
#include "GameObject/BetonWall.h"
#include "GameObject/Tree.h"
#include "GameObject/Ice.h"
#include "GameObject/Water.h"
#include "GameObject/Eagle.h"

#define BLOCK_SIZE 16

std::shared_ptr<IGameObject> createGameObjectFromDescription(const char description, const glm::vec2& position, const glm::vec2& size, const float rotation)
{
	switch (description)
	{
	case '0':
		return std::make_shared<BrickWall>(BrickWall::EBrickWallType::Right, position, size, rotation, 0.f);
		break;
	case '1':
		return std::make_shared<BrickWall>(BrickWall::EBrickWallType::Bottom, position, size, rotation, 0.f);
		break;
	case '2':
		return std::make_shared<BrickWall>(BrickWall::EBrickWallType::Left, position, size, rotation, 0.f);
		break;
	case '3':
		return std::make_shared<BrickWall>(BrickWall::EBrickWallType::Top, position, size, rotation, 0.f);
		break;
	case '4':
		return std::make_shared<BrickWall>(BrickWall::EBrickWallType::All, position, size, rotation, 0.f);
		break;
	case '5':
		return std::make_shared<BetonWall>(BetonWall::EBetonWallType::Right, position, size, rotation, 0.f);
		break;
	case '6':
		return std::make_shared<BetonWall>(BetonWall::EBetonWallType::Bottom, position, size, rotation, 0.f);
		break;
	case '7':
		return std::make_shared<BetonWall>(BetonWall::EBetonWallType::Left, position, size, rotation, 0.f);
		break;
	case '8':
		return std::make_shared<BetonWall>(BetonWall::EBetonWallType::Top, position, size, rotation, 0.f);
		break;
	case '9':
		return std::make_shared<BetonWall>(BetonWall::EBetonWallType::All, position, size, rotation, 0.f);
		break;
	case 'A':
		return std::make_shared<Water>(position, size, rotation, 0.f);
		break;
	case 'B':
		return std::make_shared<Tree>(position, size, rotation, 1.f);
		break;
	case 'E':
		return std::make_shared<Eagle>(position, size, rotation, 0.f);
		break;
	case 'C':
		return std::make_shared<Ice>(position, size, rotation, -1.f);
		break;
	case 'G':
		return std::make_shared<BrickWall>(BrickWall::EBrickWallType::BottomLeft, position, size, rotation, 0.f);
		break;
	case 'H':
		return std::make_shared<BrickWall>(BrickWall::EBrickWallType::BottomRight, position, size, rotation, 0.f);
		break;
	case 'I':
		return std::make_shared<BrickWall>(BrickWall::EBrickWallType::TopLeft, position, size, rotation, 0.f);
		break;
	case 'J':
		return std::make_shared<BrickWall>(BrickWall::EBrickWallType::TopRight, position, size, rotation, 0.f);
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

	m_width = levelDescription[0].length();
	m_height = levelDescription.size();
	m_mapObject.reserve(m_width * m_height);

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