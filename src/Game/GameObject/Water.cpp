#include "Water.h"
#include "../../Renderer/Sprite.h"
#include "../../Resources/ResourceManager.h"

Water::Water(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer)
	: IGameObject(EObjectType::Water, position, size, rotation, layer)
	, m_pSprite(ResourceManager::getSprite("water"))
	, m_spriteAnimator(m_pSprite)
	, m_blockOffSets{
					glm::vec2(0, m_size.y / 2.f),
					glm::vec2(m_size.x / 2.f, m_size.y / 2.f),
					glm::vec2(0, 0),
					glm::vec2(m_size.x / 2.f, 0),
	}
{
	m_colliders.emplace_back(glm::vec2(0), size);
}

void Water::render() const
{
	renderWater(EWaterLocation::TopLeft);
	renderWater(EWaterLocation::TopRight);
	renderWater(EWaterLocation::BottomLeft);
	renderWater(EWaterLocation::BottomRight);
}

void Water::update(const double delta)
{
	m_spriteAnimator.update(delta);
}

void Water::renderWater(const EWaterLocation eBrickLovation) const
{
	m_pSprite->render(m_position + m_blockOffSets[static_cast<size_t>(eBrickLovation)], m_size / 2.f, m_rotation, m_spriteAnimator.getCurrentFrame(), m_layer);
}

bool Water::collides(const EObjectType objectType)
{
	return objectType != EObjectType::Bullet;
}