#include "Tank.h"
#include "Bullet.h"
#include "../../Renderer/Sprite.h"
#include "../../Resources/ResourceManager.h"
#include "../../Physics/PhysicsEngine.h"


Tank::Tank(
	const double maxVelocity
	, const glm::vec2& position
	, const glm::vec2& size
	, const float layer)
	: IGameObject(EObjectType::Tank, position, size, 0.f, layer)
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
	, m_pCurrentBullet(std::make_shared<Bullet>(0.1, m_position + m_size / 4.f, m_size / 2.f, layer))
	, m_maxVelocity(maxVelocity)
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

	m_reloadTimer.setCallback([&]()
		{
			m_readyToShot = true;
			m_reloadTimer.start(1000);
		}
	);

	m_colliders.emplace_back(glm::vec2(0), m_size);

	Physics::PhysicsEngine::addDynamicGameObject(m_pCurrentBullet);
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
			m_pSpriteShield->render(m_position, m_size, m_rotation, m_layer + 0.01f, m_spriteAnimatorShield.getCurrentFrame());

		if (m_pCurrentBullet->isActive())
			m_pCurrentBullet->render();
	}
}

void Tank::setOrientation(const EOrientation orient)
{
	m_eOrientation = orient;

	switch (m_eOrientation)
	{
	case Tank::EOrientation::Top:
		m_direction.x = 0.f;
		m_direction.y = 1.f;
		break;
	case Tank::EOrientation::Bottom:
		m_direction.x = 0.f;
		m_direction.y = -1.f;
		break;
	case Tank::EOrientation::Left:
		m_direction.x = -1.f;
		m_direction.y = 0.f;
		break;
	case Tank::EOrientation::Right:
		m_direction.x = 1.f;
		m_direction.y = 0.f;
		break;
	default:
		break;
	}
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
		if (m_velocity > 0)
		{
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
		m_reloadTimer.update(delta);
	}
}

double Tank::getMaxVelocity()
{
	return m_maxVelocity;
}

void Tank::setVelocity(const double velocity)
{
	if (!m_isSpawning)
	{
		m_velocity = velocity;
	}
}

void Tank::fire()
{
	if(m_readyToShot && !m_pCurrentBullet->isActive() && !m_isSpawning)
	{
		m_pCurrentBullet->fire(m_position + m_size / 4.f + m_size * m_direction / 4.f, m_direction);
		m_readyToShot = false;
	}
}