#include "PhysicsEngine.h"
#include "../Game/GameObject/IGameObject.h"

std::unordered_set<std::shared_ptr<IGameObject>> PhysicsEngine::m_dynamicObject;

void PhysicsEngine::init()
{

}

void PhysicsEngine::terminate()
{
	m_dynamicObject.clear();
}

void PhysicsEngine::update(const double delta)
{
	for (auto& currentObject : m_dynamicObject)
	{
		const auto velocity = currentObject->getCurrentVelocity();
		if (velocity > 0)
		{
			currentObject->getCurrentPosition() += currentObject->getCurrentDirection() * static_cast<float>(delta * velocity);
		}
	}
}

void PhysicsEngine::addDynamicGameObject(std::shared_ptr<IGameObject> gameObject)
{
	m_dynamicObject.insert(std::move(gameObject));
}