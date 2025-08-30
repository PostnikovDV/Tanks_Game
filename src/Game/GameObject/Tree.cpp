#include "Tree.h"
#include "../../Renderer/Sprite.h"
#include "../../Resources/ResourceManager.h"

Tree::Tree(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer)
	: IGameObject(EObjectType::Tree, position, size, rotation, layer)
	, m_Sprite(ResourceManager::getSprite("trees"))
	, m_blockOffSets{
					glm::vec2(0, m_size.y / 2.f),
					glm::vec2(m_size.x / 2.f, m_size.y / 2.f),
					glm::vec2(0, 0),
					glm::vec2(m_size.x / 2.f, 0),
	}
{
}

void Tree::render() const
{
	renderTree(ETreeLocation::TopLeft);
	renderTree(ETreeLocation::TopRight);
	renderTree(ETreeLocation::BottomLeft);
	renderTree(ETreeLocation::BottomRight);
}

void Tree::renderTree(const ETreeLocation eBrickLovation) const
{
	m_Sprite->render(m_position + m_blockOffSets[static_cast<size_t>(eBrickLovation)], m_size / 2.f, m_rotation, m_layer);
}