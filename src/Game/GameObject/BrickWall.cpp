#include "BrickWall.h"
#include "../../Renderer/Sprite.h"
#include "../../Resources/ResourceManager.h"

BrickWall::BrickWall(EBrickWallType blockType, const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer)
	: IGameObject(EObjectType::BrickWall, position, size, rotation, layer)
	, m_CurrentBrickState{
						EBrickState::Destroyed
						, EBrickState::Destroyed
						, EBrickState::Destroyed
						, EBrickState::Destroyed
	}, 
	m_blockOffSets{
					glm::vec2(0, m_size.y / 2.f),
					glm::vec2(m_size.x / 2.f, m_size.y / 2.f),
					glm::vec2(0, 0),
					glm::vec2(m_size.x / 2.f, 0),
	}
{
	m_Sprites[static_cast<size_t>(EBrickState::All)]					= ResourceManager::getSprite("brickWall_All");
	m_Sprites[static_cast<size_t>(EBrickState::TopLeft)]				= ResourceManager::getSprite("brickWall_TopLeft");
	m_Sprites[static_cast<size_t>(EBrickState::TopRight)]				= ResourceManager::getSprite("brickWall_TopRight");
	m_Sprites[static_cast<size_t>(EBrickState::Top)]					= ResourceManager::getSprite("brickWall_Top");
	m_Sprites[static_cast<size_t>(EBrickState::BottomLeft)]				= ResourceManager::getSprite("brickWall_BottomLeft");
	m_Sprites[static_cast<size_t>(EBrickState::Left)]					= ResourceManager::getSprite("brickWall_Left");
	m_Sprites[static_cast<size_t>(EBrickState::TopRight_BottomLeft)]	= ResourceManager::getSprite("brickWall_TopRight_BottomLeft");
	m_Sprites[static_cast<size_t>(EBrickState::Top_BottomLeft)]			= ResourceManager::getSprite("brickWall_Top_BottomLeft");
	m_Sprites[static_cast<size_t>(EBrickState::BottomRight)]			= ResourceManager::getSprite("brickWall_BottomRight");
	m_Sprites[static_cast<size_t>(EBrickState::TopLeft_BottomRight)]	= ResourceManager::getSprite("brickWall_TopLeft_BottomRight");
	m_Sprites[static_cast<size_t>(EBrickState::Right)]					= ResourceManager::getSprite("brickWall_Right");
	m_Sprites[static_cast<size_t>(EBrickState::Top_BottomRight)]		= ResourceManager::getSprite("brickWall_Top_BottomRight");
	m_Sprites[static_cast<size_t>(EBrickState::Bottom)]					= ResourceManager::getSprite("brickWall_Bottom");
	m_Sprites[static_cast<size_t>(EBrickState::TopLeft_Bottom)]			= ResourceManager::getSprite("brickWall_TopLeft_Bottom");
	m_Sprites[static_cast<size_t>(EBrickState::TopRight_Bottom)]		= ResourceManager::getSprite("brickWall_TopRight_Bottom");

	switch (blockType)
	{
	case EBrickWallType::All:
		m_CurrentBrickState.fill(EBrickState::All);
		m_colliders.emplace_back(glm::vec2(0), m_size);
		break;
	case EBrickWallType::Top:
		m_CurrentBrickState[static_cast<size_t>(EBrickLocation::TopLeft)] = EBrickState::All;
		m_CurrentBrickState[static_cast<size_t>(EBrickLocation::TopRight)] = EBrickState::All;
		m_colliders.emplace_back(glm::vec2(0, m_size.y / 2), m_size);
		break;
	case EBrickWallType::Bottom:
		m_CurrentBrickState[static_cast<size_t>(EBrickLocation::BottomLeft)] = EBrickState::All;
		m_CurrentBrickState[static_cast<size_t>(EBrickLocation::BottomRight)] = EBrickState::All;
		m_colliders.emplace_back(glm::vec2(0), glm::vec2(m_size.x, m_size.y / 2));
		break;
	case EBrickWallType::Left:
		m_CurrentBrickState[static_cast<size_t>(EBrickLocation::TopLeft)] = EBrickState::All;
		m_CurrentBrickState[static_cast<size_t>(EBrickLocation::BottomLeft)] = EBrickState::All;
		m_colliders.emplace_back(glm::vec2(0), glm::vec2(m_size.x / 2, m_size.y));
		break;
	case EBrickWallType::Right:
		m_CurrentBrickState[static_cast<size_t>(EBrickLocation::TopRight)] = EBrickState::All;
		m_CurrentBrickState[static_cast<size_t>(EBrickLocation::BottomRight)] = EBrickState::All;
		m_colliders.emplace_back(glm::vec2(m_size.x / 2, 0), m_size);
		break;
	case EBrickWallType::TopLeft:
		m_CurrentBrickState[static_cast<size_t>(EBrickLocation::TopLeft)] = EBrickState::All;
		m_colliders.emplace_back(glm::vec2(0, m_size.y / 2), glm::vec2(m_size.x / 2, m_size.y));
		break;
	case EBrickWallType::TopRight:
		m_CurrentBrickState[static_cast<size_t>(EBrickLocation::TopRight)] = EBrickState::All;
		m_colliders.emplace_back(glm::vec2(m_size.x / 2, m_size.y / 2), m_size);
		break;
	case EBrickWallType::BottomLeft:
		m_CurrentBrickState[static_cast<size_t>(EBrickLocation::BottomLeft)] = EBrickState::All;
		m_colliders.emplace_back(glm::vec2(0), glm::vec2(m_size.x / 2, m_size.y / 2));
		break;
	case EBrickWallType::BottomRight:
		m_CurrentBrickState[static_cast<size_t>(EBrickLocation::BottomRight)] = EBrickState::All;
		m_colliders.emplace_back(glm::vec2(m_size.x / 2, 0), glm::vec2(m_size.x, m_size.y / 2));
		break;

	default:
		break;
	}
}

void BrickWall::render() const
{
	renderBrick(EBrickLocation::TopLeft);
	renderBrick(EBrickLocation::TopRight);
	renderBrick(EBrickLocation::BottomLeft);
	renderBrick(EBrickLocation::BottomRight);
}

void BrickWall::renderBrick(const EBrickLocation eBrickLovation) const
{
	const EBrickState state = m_CurrentBrickState[static_cast<size_t>(eBrickLovation)];
	if (state != EBrickState::Destroyed)
	{
		m_Sprites[static_cast<size_t>(state)]->render(m_position + m_blockOffSets[static_cast<size_t>(eBrickLovation)], m_size / 2.f, m_rotation, m_layer);
	}
}