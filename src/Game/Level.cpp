#include "Level.h"
#include "GameObject/BrickWall.h"
#include "GameObject/BetonWall.h"
#include "GameObject/Tree.h"
#include "GameObject/Ice.h"
#include "GameObject/Water.h"
#include "GameObject/Eagle.h"
#include "GameObject/Border.h"
#include <algorithm>

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

Level::Level(const std::vector<std::string>& levelDescription)
{
	if (levelDescription.empty())
	{
		std::cerr << "Level is empty!" << std::endl;
	}

	m_playerRespawn_1 = { BLOCK_SIZE * (m_widthBlock / 2 - 1), BLOCK_SIZE / 2 };
	m_playerRespawn_2 = { BLOCK_SIZE * (m_widthBlock / 2 + 3), BLOCK_SIZE / 2 };
	
	m_enemyRespawn_1 = { BLOCK_SIZE, BLOCK_SIZE * m_heightBlock - BLOCK_SIZE / 2 };
	m_enemyRespawn_2 = { BLOCK_SIZE * (m_widthBlock / 2 + 1), BLOCK_SIZE * m_heightBlock - BLOCK_SIZE / 2};
	m_enemyRespawn_3 = { BLOCK_SIZE * m_widthBlock, BLOCK_SIZE * m_heightBlock - BLOCK_SIZE / 2 };

	m_widthBlock = levelDescription[0].length();
	m_heightBlock = levelDescription.size();

	m_widthPixels = static_cast<unsigned int>(m_widthBlock * BLOCK_SIZE);
	m_heightPixels = static_cast<unsigned int>(m_heightBlock * BLOCK_SIZE);

	m_levelObjects.reserve(m_widthBlock * m_heightBlock + 4);

	unsigned int currentBottomOffset{static_cast<unsigned int>(BLOCK_SIZE * (m_heightBlock - 1)) + BLOCK_SIZE / 2};

	for (const auto& currentRow : levelDescription)
	{
		unsigned int currentLeftOffset{ BLOCK_SIZE };
		for (const auto currentElement : currentRow)
		{
			switch (currentElement)
			{
			case 'K':
				m_playerRespawn_1 = { currentLeftOffset, currentBottomOffset };
				m_levelObjects.emplace_back(nullptr);
				break;
			case 'L':
				m_playerRespawn_2 = { currentLeftOffset, currentBottomOffset };
				m_levelObjects.emplace_back(nullptr);
				break;
			case 'M':
				m_enemyRespawn_1 = { currentLeftOffset, currentBottomOffset };
				m_levelObjects.emplace_back(nullptr);
				break;
			case 'N':
				m_enemyRespawn_2 = { currentLeftOffset, currentBottomOffset };
				m_levelObjects.emplace_back(nullptr);
				break;
			case 'O':
				m_enemyRespawn_3 = { currentLeftOffset, currentBottomOffset };
				m_levelObjects.emplace_back(nullptr);
				break;
			default:
				m_levelObjects.emplace_back(createGameObjectFromDescription(currentElement, glm::vec2(currentLeftOffset, currentBottomOffset), glm::vec2(BLOCK_SIZE, BLOCK_SIZE), 0.f));
				break;
			}
			currentLeftOffset += BLOCK_SIZE;
		}

		currentBottomOffset -= BLOCK_SIZE;
	}

	// Bottom border
	m_levelObjects.emplace_back(std::make_shared<Border>(glm::vec2(BLOCK_SIZE, 0.f), glm::vec2(m_widthBlock * BLOCK_SIZE,BLOCK_SIZE / 2), 0.f, 0.f));

	// Top border
	m_levelObjects.emplace_back(std::make_shared<Border>(glm::vec2(BLOCK_SIZE, m_heightPixels + BLOCK_SIZE / 2), glm::vec2(m_widthBlock * BLOCK_SIZE, BLOCK_SIZE / 2), 0.f, 0.f));

	// Left border
	m_levelObjects.emplace_back(std::make_shared<Border>(glm::vec2(0, 0), glm::vec2( BLOCK_SIZE, (m_heightBlock + 1) * BLOCK_SIZE), 0.f, 0.f));

	// Right border
	m_levelObjects.emplace_back(std::make_shared<Border>(glm::vec2((m_widthBlock + 1) * BLOCK_SIZE, 0), glm::vec2(2 * BLOCK_SIZE, (m_heightBlock + 1) * BLOCK_SIZE), 0.f, 0.f));
}

void Level::render() const
{
	for (const auto currentObject : m_levelObjects)
	{
		if (currentObject)
		{
			currentObject->render();
		}
	}
}

void Level::update(const double delta)
{
	for (const auto currentObject : m_levelObjects)
	{
		if (currentObject)
		{
			currentObject->update(delta);
		}
	}
}

size_t Level::getLevelWidth() const
{
	return (m_widthBlock + 3) * BLOCK_SIZE;
}

size_t Level::getLevelHight() const
{
	return (m_heightBlock + 1) * BLOCK_SIZE;
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

std::vector<std::shared_ptr<IGameObject>> Level::getObjectInArea(const glm::vec2& bottomLeft, const glm::vec2& topRight) const
{
	std::vector<std::shared_ptr<IGameObject>> output;
	output.reserve(9);

	glm::vec2 bottomLeftConverted(std::clamp(bottomLeft.x - BLOCK_SIZE, 0.f, static_cast<float>(m_widthPixels))
								, std::clamp(m_heightPixels - bottomLeft.y + BLOCK_SIZE / 2, 0.f, static_cast<float>(m_heightPixels)));
	glm::vec2 topRightConverted(std::clamp(topRight.x - BLOCK_SIZE, 0.f, static_cast<float>(m_widthPixels))
								, std::clamp(m_heightPixels - topRight.y + BLOCK_SIZE / 2, 0.f, static_cast<float>(m_heightPixels)));

	size_t startX = static_cast<size_t>(floor(bottomLeftConverted.x / BLOCK_SIZE));
	size_t endX = static_cast<size_t>(ceil(topRightConverted.x / BLOCK_SIZE));

	size_t startY = static_cast<size_t>(floor(topRightConverted.y / BLOCK_SIZE));
	size_t endY = static_cast<size_t>(ceil(bottomLeftConverted.y / BLOCK_SIZE));

	for (size_t currentColumn = startX; currentColumn < endX; ++currentColumn)
	{
		for (size_t currentRow = startY; currentRow < endY; ++currentRow)
		{
			auto& currentObject = m_levelObjects[currentRow * m_widthBlock + currentColumn];
			if (currentObject)
			{
				output.push_back(currentObject);
			}
		}
	}
	const auto levelObjectSize = m_levelObjects.size();
	if (endX >= m_widthBlock)
		output.push_back(m_levelObjects[levelObjectSize - 1]);
	if (startX <= 1)
		output.push_back(m_levelObjects[levelObjectSize - 2]);
	if (endY >= m_heightBlock)
		output.push_back(m_levelObjects[levelObjectSize - 4]);
	if (startY <= 1)
		output.push_back(m_levelObjects[levelObjectSize - 3]);

	return output;
}