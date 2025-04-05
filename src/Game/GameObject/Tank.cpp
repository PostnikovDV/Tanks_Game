#include "Tank.h"
#include "../../Renderer/Sprite.h"
#include "../../Resources/ResourceManager.h"


Tank::Tank(
	const double velocity
	, const glm::vec2& position
	, const glm::vec2& size
	, const float layer)
	: IGameObject(position, size, 0.f, layer)
	, m_pSpriteTop(ResourceManager::getSprite("tankSpriteTop"))
	, m_pSpriteBottom(ResourceManager::getSprite("tankSpriteBottom"))
	, m_pSpriteLeft(ResourceManager::getSprite("tankSpriteLeft"))
	, m_pSpriteRight(ResourceManager::getSprite("tankSpriteRight"))
	, m_spriteAnimatorTop(m_pSpriteTop)
	, m_spriteAnimatorBottom(m_pSpriteBottom)
	, m_spriteAnimatorLeft(m_pSpriteLeft)
	, m_spriteAnimatorRight(m_pSpriteRight)
	, m_pSpriteRespawn(ResourceManager::getSprite("respawn"))
	, m_pSpriteShield(ResourceManager::getSprite("shield"))
	, m_spriteAnimatorRespawn(m_pSpriteRespawn)
	, m_spriteAnimatorShield(m_pSpriteShield)
	, m_velocity(velocity)
	, m_moveOffset(glm::vec2(0.f, 1.f))
	, m_isSpawning(true)
	, m_hasShield(false)
{
	m_spawnTimer.setCallback([&]()
		{
			m_isSpawning = false;
			m_hasShield = true;
			m_shieldTimer.start(2000); // 2 sec shield
		}
	);
	m_spawnTimer.start(1500);

	m_shieldTimer.setCallback([&]()
		{
			m_hasShield = false;
		}
	);
}

void Tank::render() const
{
	if (m_isSpawning)
	{
		m_pSpriteRespawn->render(m_position, m_size, m_rotation, m_layer, m_spriteAnimatorRespawn.getCurrentFrame());
	}
	else
	{
		switch (m_eOrientation)
		{
		case Tank::EOrientation::Top:
			m_pSpriteTop->render(m_position, m_size, m_rotation, m_layer, m_spriteAnimatorTop.getCurrentFrame());
			break;
		case Tank::EOrientation::Bottom:
			m_pSpriteBottom->render(m_position, m_size, m_rotation, m_layer, m_spriteAnimatorBottom.getCurrentFrame());
			break;
		case Tank::EOrientation::Left:
			m_pSpriteLeft->render(m_position, m_size, m_rotation, m_layer, m_spriteAnimatorLeft.getCurrentFrame());
			break;
		case Tank::EOrientation::Right:
			m_pSpriteRight->render(m_position, m_size, m_rotation, m_layer, m_spriteAnimatorRight.getCurrentFrame());
			break;
		default:
			break;
		}
		if (m_hasShield)
		{
			m_pSpriteShield->render(m_position, m_size, m_rotation, m_layer, m_spriteAnimatorShield.getCurrentFrame());
		}
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

void Tank::update(const double delta)
{

	if (m_isSpawning)
	{
		m_spriteAnimatorRespawn.update(delta);
		m_spawnTimer.update(delta);
	}

	else
	{
		if (m_hasShield)
		{
			m_spriteAnimatorShield.update(delta);
			m_shieldTimer.update(delta);
		}
		if (m_move)
		{
			m_position.x += static_cast<float>(delta * m_velocity * m_moveOffset.x);
			m_position.y += static_cast<float>(delta * m_velocity * m_moveOffset.y);

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
}