#include "Border.h"
#include "../../Renderer/Sprite.h"
#include "../../Resources/ResourceManager.h"

Border::Border(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer)
	: IGameObject(EObjectType::Border, position, size, rotation, layer)
	, m_Sprite(ResourceManager::getSprite("border"))
{
	m_colliders.emplace_back(glm::vec2(0), size);
}

void Border::render() const
{
	m_Sprite->render(m_position, m_size, m_rotation, m_layer);
}