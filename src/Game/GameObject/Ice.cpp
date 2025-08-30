#include "Ice.h"
#include "../../Renderer/Sprite.h"
#include "../../Resources/ResourceManager.h"

Ice::Ice(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer)
	: IGameObject(EObjectType::Ice, position, size, rotation, layer)
	, m_Sprite(ResourceManager::getSprite("ice"))
	, m_blockOffSets{
					glm::vec2(0, m_size.y / 2.f),
					glm::vec2(m_size.x / 2.f, m_size.y / 2.f),
					glm::vec2(0, 0),
					glm::vec2(m_size.x / 2.f, 0),
	}
{
}

void Ice::render() const
{
	renderIce(EIceLocation::TopLeft);
	renderIce(EIceLocation::TopRight);
	renderIce(EIceLocation::BottomLeft);
	renderIce(EIceLocation::BottomRight);
}

void Ice::renderIce(const EIceLocation eBrickLovation) const
{
	m_Sprite->render(m_position + m_blockOffSets[static_cast<size_t>(eBrickLovation)], m_size / 2.f, m_rotation, m_layer);
}