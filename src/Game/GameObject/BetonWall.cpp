#include "BetonWall.h"
#include "../../Renderer/Sprite.h"
#include "../../Resources/ResourceManager.h"

BetonWall::BetonWall(EBetonWallType blockType, const glm::vec2& position, const glm::vec2& size, const float rotation)
	: IGameObject(position, size, rotation)
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
		break;
	case EBetonWallType::Top:
		m_CurrentBlockState[static_cast<size_t>(EBetonLocation::TopLeft)] = EBlockState::Enabled;
		m_CurrentBlockState[static_cast<size_t>(EBetonLocation::TopRight)] = EBlockState::Enabled;
		break;
	case EBetonWallType::Bottom:
		m_CurrentBlockState[static_cast<size_t>(EBetonLocation::BottomLeft)] = EBlockState::Enabled;
		m_CurrentBlockState[static_cast<size_t>(EBetonLocation::BottomRight)] = EBlockState::Enabled;
		break;
	case EBetonWallType::Left:
		m_CurrentBlockState[static_cast<size_t>(EBetonLocation::TopLeft)] = EBlockState::Enabled;
		m_CurrentBlockState[static_cast<size_t>(EBetonLocation::BottomLeft)] = EBlockState::Enabled;
		break;
	case EBetonWallType::Right:
		m_CurrentBlockState[static_cast<size_t>(EBetonLocation::TopRight)] = EBlockState::Enabled;
		m_CurrentBlockState[static_cast<size_t>(EBetonLocation::BottomRight)] = EBlockState::Enabled;
		break;
	case EBetonWallType::TopLeft:
		m_CurrentBlockState[static_cast<size_t>(EBetonLocation::TopLeft)] = EBlockState::Enabled;
		break;
	case EBetonWallType::TopRight:
		m_CurrentBlockState[static_cast<size_t>(EBetonLocation::TopRight)] = EBlockState::Enabled;
		break;
	case EBetonWallType::BottomLeft:
		m_CurrentBlockState[static_cast<size_t>(EBetonLocation::BottomLeft)] = EBlockState::Enabled;
		break;
	case EBetonWallType::BottomRight:
		m_CurrentBlockState[static_cast<size_t>(EBetonLocation::BottomRight)] = EBlockState::Enabled;
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

void BetonWall::update(const uint64_t)
{

}

void BetonWall::renderBeton(const EBetonLocation eBrickLovation) const
{
	const EBlockState state = m_CurrentBlockState[static_cast<size_t>(eBrickLovation)];
	if (state != EBlockState::Destroyed)
	{
		m_Sprite->render(m_position + m_blockOffSets[static_cast<size_t>(eBrickLovation)], m_size / 2.f, m_rotation);
	}
}