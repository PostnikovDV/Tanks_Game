#include "Level.h"
#include "GameObject/BrickWall.h"
#include "GameObject/BetonWall.h"
#include "GameObject/Tree.h"
#include "GameObject/Ice.h"
#include "GameObject/Water.h"
#include "GameObject/Eagle.h"
#include "GameObject/Border.h"

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

	m_playerRespawn_1 = { BLOCK_SIZE * (m_width / 2 - 1), BLOCK_SIZE / 2 };
	m_playerRespawn_2 = { BLOCK_SIZE * (m_width / 2 + 3), BLOCK_SIZE / 2 };
	
	m_enemyRespawn_1 = { BLOCK_SIZE, BLOCK_SIZE * m_height - BLOCK_SIZE / 2 };
	m_enemyRespawn_2 = { BLOCK_SIZE * (m_width / 2 + 1), BLOCK_SIZE * m_height - BLOCK_SIZE / 2};
	m_enemyRespawn_3 = { BLOCK_SIZE * m_width, BLOCK_SIZE * m_height - BLOCK_SIZE / 2 };

	m_width = levelDescription[0].length();
	m_height = levelDescription.size();
	m_mapObject.reserve(m_width * m_height + 4);

	unsigned int currentBottomOffset{static_cast<unsigned int>(BLOCK_SIZE * (m_height - 1)) + BLOCK_SIZE / 2};

	for (const auto& currentRow : levelDescription)
	{
		unsigned int currentLeftOffset{ BLOCK_SIZE };
		for (const auto currentElement : currentRow)
		{
			switch (currentElement)
			{
			case 'K':
				m_playerRespawn_1 = { currentLeftOffset, currentBottomOffset };
				break;
			case 'L':
				m_playerRespawn_2 = { currentLeftOffset, currentBottomOffset };
				break;
			case 'M':
				m_enemyRespawn_1 = { currentLeftOffset, currentBottomOffset };
				break;
			case 'N':
				m_enemyRespawn_2 = { currentLeftOffset, currentBottomOffset };
				break;
			case 'O':
				m_enemyRespawn_3 = { currentLeftOffset, currentBottomOffset };
				break;
			default:
				m_mapObject.emplace_back(createGameObjectFromDescription(currentElement, glm::vec2(currentLeftOffset, currentBottomOffset), glm::vec2(BLOCK_SIZE, BLOCK_SIZE), 0.f));
				break;
			}
			currentLeftOffset += BLOCK_SIZE;
		}

		currentBottomOffset -= BLOCK_SIZE;
	}

	// Bottom border
	m_mapObject.emplace_back(std::make_shared<Border>(glm::vec2(BLOCK_SIZE, 0.f), glm::vec2(m_width * BLOCK_SIZE,BLOCK_SIZE / 2), 0.f, 0.f));

	// Top border
	m_mapObject.emplace_back(std::make_shared<Border>(glm::vec2(BLOCK_SIZE, m_height * BLOCK_SIZE + BLOCK_SIZE / 2), glm::vec2(m_width * BLOCK_SIZE, BLOCK_SIZE / 2), 0.f, 0.f));

	// Left border
	m_mapObject.emplace_back(std::make_shared<Border>(glm::vec2(0, 0), glm::vec2( BLOCK_SIZE, (m_height + 1) * BLOCK_SIZE), 0.f, 0.f));

	// Right border
	m_mapObject.emplace_back(std::make_shared<Border>(glm::vec2((m_width + 1) * BLOCK_SIZE, 0), glm::vec2(2 * BLOCK_SIZE, (m_height + 1) * BLOCK_SIZE), 0.f, 0.f));
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

void Level::update(const double delta)
{
	for (const auto currentObject : m_mapObject)
	{
		if (currentObject)
		{
			currentObject->update(delta);
		}
	}
}

size_t  Level::getLevelWidth() const
{
	return (m_width + 3) * BLOCK_SIZE;
}

size_t  Level::getLevelHight() const
{
	return (m_height + 1) * BLOCK_SIZE;
}

const glm::ivec2& Level::getPlayerRespawn(ETypeRespawn respawnType)
{
	switch (respawnType)
	{
	case Level::ETypeRespawn::player1:
		return m_playerRespawn_1;
		break;
	case Level::ETypeRespawn::player2:
		return m_playerRespawn_2;
		break;
	case Level::ETypeRespawn::enemy1:
		return m_enemyRespawn_1;
		break;
	case Level::ETypeRespawn::enemy2:
		return m_enemyRespawn_2;
		break;
	case Level::ETypeRespawn::enemy3:
		return m_enemyRespawn_3;
		break;
	default:
		return m_playerRespawn_1;
		break;
	}
}