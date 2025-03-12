#include "Tank.h"
#include "../../Renderer/Sprite.h"
#include "../../Resources/ResourceManager.h"


Tank::Tank(
	const float velocity
	, const glm::vec2& position
	, const glm::vec2& size)
	: IGameObject(position, size, 0.f)
	, m_pSpriteTop(ResourceManager::getSprite("tankSpriteTop"))
	, m_pSpriteBottom(ResourceManager::getSprite("tankSpriteBottom"))
	, m_pSpriteLeft(ResourceManager::getSprite("tankSpriteLeft"))
	, m_pSpriteRight(ResourceManager::getSprite("tankSpriteRight"))
	, m_spriteAnimatorTop(m_pSpriteTop)
	, m_spriteAnimatorBottom(m_pSpriteBottom)
	, m_spriteAnimatorLeft(m_pSpriteLeft)
	, m_spriteAnimatorRight(m_pSpriteRight)
	, m_velocity(velocity)
	, m_moveOffset(glm::vec2(0.f, 1.f))
{
}

void Tank::render() const
{
	switch (m_eOrientation)
	{
	case Tank::EOrientation::Top:
		m_pSpriteTop->render(m_position, m_size, m_rotation, m_spriteAnimatorTop.getCurrentFrame());
		break;
	case Tank::EOrientation::Bottom:
		m_pSpriteBottom->render(m_position, m_size, m_rotation, m_spriteAnimatorBottom.getCurrentFrame());
		break;
	case Tank::EOrientation::Left:
		m_pSpriteLeft->render(m_position, m_size, m_rotation, m_spriteAnimatorLeft.getCurrentFrame());
		break;
	case Tank::EOrientation::Right:
		m_pSpriteRight->render(m_position, m_size, m_rotation, m_spriteAnimatorRight.getCurrentFrame());
		break;
	default:
		break;
	}
}

void Tank::setOrientation(const EOrientation orient)
{
	m_eOrientation = orient;

	switch (m_eOrientation)
	{
	case Tank::EOrientation::Top:
		m_moveOffset.x = 0.f;
		m_moveOffset.y = 1.f;
		break;
	case Tank::EOrientation::Bottom:
		m_moveOffset.x = 0.f;
		m_moveOffset.y = -1.f;
		break;
	case Tank::EOrientation::Left:
		m_moveOffset.x = -1.f;
		m_moveOffset.y = 0.f;
		break;
	case Tank::EOrientation::Right:
		m_moveOffset.x = 1.f;
		m_moveOffset.y = 0.f;
		break;
	default:
		break;
	}
}

void Tank::move(const bool move)
{
	m_move = move;
}

void Tank::update(const uint64_t delta)
{
	if (m_move)
	{
		m_position += delta * m_velocity * m_moveOffset;
		switch (m_eOrientation)
		{
		case Tank::EOrientation::Top:
			m_spriteAnimatorTop.update(delta);
			break;
		case Tank::EOrientation::Bottom:
			m_spriteAnimatorBottom.update(delta);
			break;
		case Tank::EOrientation::Left:
			m_spriteAnimatorLeft.update(delta);
			break;
		case Tank::EOrientation::Right:
			m_spriteAnimatorRight.update(delta);
			break;
		default:
			break;
		}
	}
}