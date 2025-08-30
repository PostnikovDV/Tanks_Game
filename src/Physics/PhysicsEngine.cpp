#include "PhysicsEngine.h"
#include "../Game/GameObject/IGameObject.h"
#include "../Game/Level.h"

namespace Physics
{
std::unordered_set<std::shared_ptr<IGameObject>> PhysicsEngine::m_dynamicObject;
std::shared_ptr<Level> PhysicsEngine::m_currentLevel;

void PhysicsEngine::init()
{

}

void PhysicsEngine::terminate()
{
	m_dynamicObject.clear();
	m_currentLevel.reset();
}

void PhysicsEngine::update(const double delta)
{
	for (auto& currentObject : m_dynamicObject)
	{
		const auto velocity = currentObject->getCurrentVelocity();
		if (velocity > 0)
		{
			auto& direction = currentObject->getCurrentDirection();
			auto& position = currentObject->getCurrentPosition();
			if (direction.x != 0.f)
				position = glm::vec2(position.x, static_cast<unsigned int>(position.y / 4.f + 0.5f) * 4);
			else if (direction.y != 0.f)
				position = glm::vec2(static_cast<unsigned int>(position.x / 4.f + 0.5f) * 4, position.y);

			const auto newPosition = currentObject->getCurrentPosition() + currentObject->getCurrentDirection() * static_cast<float>(delta * velocity);
			const auto& colliders = currentObject->getColliders();
			std::vector<std::shared_ptr<IGameObject>> objectsToCheck = m_currentLevel->getObjectInArea(newPosition, newPosition + currentObject->getCurrentSize());
			bool hasCollision = false;

			for (const auto& currentObjectToCheck : objectsToCheck)
			{
				const auto& objectColliders = currentObjectToCheck->getColliders();
				if (currentObjectToCheck->collides(currentObject->getObjectType()) && !objectColliders.empty())
				{
					if (hasIntersection(colliders, newPosition, objectColliders, currentObjectToCheck->getCurrentPosition()))
					{
						hasCollision = true;
						currentObjectToCheck->onCollision();
						break;
					}
				}
			}
			if (!hasCollision)
				position = newPosition;
			else
			{
				if (direction.x != 0.f)
					position = glm::vec2(static_cast<unsigned int>(position.x / 8.f + 0.5f) * 8, position.y);
				else if (direction.y != 0.f)
					position = glm::vec2(position.x, static_cast<unsigned int>(position.y / 8.f + 0.5f) * 8);

				currentObject->onCollision();
			}
		}
	}
}

void PhysicsEngine::addDynamicGameObject(std::shared_ptr<IGameObject> gameObject)
{
	m_dynamicObject.insert(std::move(gameObject));
}

void PhysicsEngine::setCurrentLevel(std::shared_ptr<Level> currentLevel)
{
	m_currentLevel.swap(currentLevel);
}

bool PhysicsEngine::hasIntersection(const std::vector<AABB>& colliders1, const glm::vec2& posittion1
					, const std::vector<AABB>& colliders2, const glm::vec2& posittion2)
{
	for (const auto& collider1 : colliders1)
	{
		const glm::vec2 currentCollider1TopRightWorld = collider1.topRight + posittion1;
		const glm::vec2 currentCollider1BottomLeftWorld = collider1.botomLeft + posittion1;
		for (const auto& collider2 : colliders2)
		{
			const glm::vec2 currentCollider2TopRightWorld = collider2.topRight + posittion2;
			const glm::vec2 currentCollider2BottomLeftWorld = collider2.botomLeft + posittion2;

			if (currentCollider1BottomLeftWorld.x >= currentCollider2TopRightWorld.x)
				continue;
			if (currentCollider1TopRightWorld.x <= currentCollider2BottomLeftWorld.x)
				continue;
			if (currentCollider1BottomLeftWorld.y >= currentCollider2TopRightWorld.y)
				continue;
			if (currentCollider1TopRightWorld.y <= currentCollider2BottomLeftWorld.y)
				continue;
			return true;
		}
	}
	return false;
}
}//namespace Physics