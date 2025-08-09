#include "BetonWall.h"
#include "../../Renderer/Sprite.h"
#include "../../Resources/ResourceManager.h"

BetonWall::BetonWall(EBetonWallType blockType, const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer)
	: IGameObject(position, size, rotation, layer)
	, m_CurrentBlockState{
						EBlockState::Destroyed
						, EBlockState::Destroyed
						, EBlockState::Destroyed
						, EBlockState::Destroyed
	},
	m_blockOffSets{
					glm::vec2(0, m_size.y / 2.f),
					glm::vec2(m_size.x / 2.f, m_size.y / 2.f),
					glm::vec2(0, 0),
					glm::vec2(m_size.x / 2.f, 0),
	}
{
	m_Sprite = ResourceManager::getSprite("betonWall");


	switch (blockType)
	{
	case EBetonWallType::All:
		m_CurrentBlockState.fill(EBlockState::Enabled);
		m_colliders.emplace_back(glm::vec2(0), m_size);
		break;
	case EBetonWallType::Top:
		m_CurrentBlockState[static_cast<size_t>(EBetonLocation::TopLeft)] = EBlockState::Enabled;
		m_CurrentBlockState[static_cast<size_t>(EBetonLocation::TopRight)] = EBlockState::Enabled;
		m_colliders.emplace_back(glm::vec2(0, m_size.y / 2), m_size);
		break;
	case EBetonWallType::Bottom:
		m_CurrentBlockState[static_cast<size_t>(EBetonLocation::BottomLeft)] = EBlockState::Enabled;
		m_CurrentBlockState[static_cast<size_t>(EBetonLocation::BottomRight)] = EBlockState::Enabled;
		m_colliders.emplace_back(glm::vec2(0), glm::vec2(m_size.x, m_size.y / 2));
		break;
	case EBetonWallType::Left:
		m_CurrentBlockState[static_cast<size_t>(EBetonLocation::TopLeft)] = EBlockState::Enabled;
		m_CurrentBlockState[static_cast<size_t>(EBetonLocation::BottomLeft)] = EBlockState::Enabled;
		m_colliders.emplace_back(glm::vec2(0), glm::vec2(m_size.x / 2, m_size.y));
		break;
	case EBetonWallType::Right:
		m_CurrentBlockState[static_cast<size_t>(EBetonLocation::TopRight)] = EBlockState::Enabled;
		m_CurrentBlockState[static_cast<size_t>(EBetonLocation::BottomRight)] = EBlockState::Enabled;
		m_colliders.emplace_back(glm::vec2(m_size.x / 2, 0), m_size);
		break;
	case EBetonWallType::TopLeft:
		m_CurrentBlockState[static_cast<size_t>(EBetonLocation::TopLeft)] = EBlockState::Enabled;
		m_colliders.emplace_back(glm::vec2(0, m_size.y / 2), glm::vec2(m_size.x / 2, m_size.y));
		break;
	case EBetonWallType::TopRight:
		m_CurrentBlockState[static_cast<size_t>(EBetonLocation::TopRight)] = EBlockState::Enabled;
		m_colliders.emplace_back(glm::vec2(m_size.x / 2, m_size.y / 2), m_size);
		break;
	case EBetonWallType::BottomLeft:
		m_CurrentBlockState[static_cast<size_t>(EBetonLocation::BottomLeft)] = EBlockState::Enabled;
		m_colliders.emplace_back(glm::vec2(0), glm::vec2(m_size.x / 2, m_size.y / 2));
		break;
	case EBetonWallType::BottomRight:
		m_CurrentBlockState[static_cast<size_t>(EBetonLocation::BottomRight)] = EBlockState::Enabled;
		m_colliders.emplace_back(glm::vec2(m_size.x / 2, 0), glm::vec2(m_size.x, m_size.y / 2));
		break;

	default:
		break;
	}
}

void BetonWall::render() const
{
	renderBeton(EBetonLocation::TopLeft);
	renderBeton(EBetonLocation::TopRight);
	renderBeton(EBetonLocation::BottomLeft);
	renderBeton(EBetonLocation::BottomRight);
}

void BetonWall::renderBeton(const EBetonLocation eBrickLo�ation) const
{
	const EBlockState state = m_CurrentBlockState[static_cast<size_t>(eBrickLo�ation)];
	if (state != EBlockState::Destroyed)
	{
		m_Sprite->render(m_position + m_blockOffSets[static_cast<size_t>(eBrickLo�ation)], m_size / 2.f, m_rotation, m_layer);
	}
}