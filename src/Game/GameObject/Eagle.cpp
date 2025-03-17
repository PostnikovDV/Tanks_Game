#include "Eagle.h"
#include "../../Renderer/Sprite.h"
#include "../../Resources/ResourceManager.h"

Eagle::Eagle(const glm::vec2& position, const glm::vec2& size, const float rotation)
	: IGameObject(position, size, rotation)
	, m_currentState(EEagleState::Alive)
	, m_Sprites{
				ResourceManager::getSprite("eagle")
				, ResourceManager::getSprite("eagle_dead"),
	}
{
}

void Eagle::render() const
{
	m_Sprites[static_cast<size_t>(m_currentState)]->render(m_position, m_size, m_rotation);
}

void Eagle::update(const uint64_t delta)
{
}