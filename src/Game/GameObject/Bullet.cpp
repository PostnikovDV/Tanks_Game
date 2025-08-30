#include "Bullet.h"
#include "../../Renderer/Sprite.h"
#include "../../Resources/ResourceManager.h"


Bullet::Bullet(
	const double velocity
	, const glm::vec2& position
	, const glm::vec2& size
	, const float layer)
	: IGameObject(EObjectType::Bullet, position, size, 0.f, layer)
	, m_pSpriteTop(ResourceManager::getSprite("bullet_Top"))
	, m_pSpriteBottom(ResourceManager::getSprite("bullet_Bottom"))
	, m_pSpriteLeft(ResourceManager::getSprite("bullet_Left"))
	, m_pSpriteRight(ResourceManager::getSprite("bullet_Right"))
	, m_maxVelocity(velocity)
{
	m_colliders.emplace_back(glm::vec2(0), m_size);
}

void Bullet::render() const
{
	if (m_isActive)
	{
		switch (m_eOrientation)
		{
		case EOrientation::Top:
			m_pSpriteTop->render(m_position, m_size, m_rotation, m_layer);
			break;
		case EOrientation::Bottom:
			m_pSpriteBottom->render(m_position, m_size, m_rotation, m_layer);
			break;
		case EOrientation::Left:
			m_pSpriteLeft->render(m_position, m_size, m_rotation, m_layer);
			break;
		case EOrientation::Right:
			m_pSpriteRight->render(m_position, m_size, m_rotation, m_layer);
			break;
		default:
			break;
		}
	}
}

void Bullet::fire(const glm::vec2& position, const glm::vec2& direction)
{
	m_position = position;
	m_direction = direction;
	if (m_direction.x == 0.f)
	{
		m_eOrientation = (m_direction.y > 0) ? EOrientation::Top : EOrientation::Bottom;
	}
	else
	{
		m_eOrientation = (m_direction.x > 0) ? EOrientation::Right : EOrientation::Left;
	}
	m_isActive = true;
	setVelocity(m_maxVelocity);
}

void Bullet::onCollision()
{
	setVelocity(0);
	m_isActive = false;
}