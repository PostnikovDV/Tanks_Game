#include "Eagle.h"
#include "../../Renderer/Sprite.h"
#include "../../Resources/ResourceManager.h"

Eagle::Eagle(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer)
	: IGameObject(position, size, rotation, layer)
	, m_currentState(EEagleState::Alive)
	, m_Sprites{
				ResourceManager::getSprite("eagle")
				, ResourceManager::getSprite("eagle_dead"),
	}
{
	m_colliders.emplace_back(glm::vec2(0), size);
}

void Eagle::render() const
{
	m_Sprites[static_cast<size_t>(m_currentState)]->render(m_position, m_size, m_rotation, m_layer);
}

void Eagle::update(const double delta)
{
}