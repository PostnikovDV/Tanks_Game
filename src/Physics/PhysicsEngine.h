#pragma once
#include <unordered_set>
#include <memory>
#include <glm/vec2.hpp>

class IGameObject;
class Level;

namespace Physics
{
struct AABB
{
	AABB(const glm::vec2 _botomLeft, const glm::vec2 _topRight) : botomLeft(_botomLeft), topRight(_topRight) {}
	glm::vec2 botomLeft;
	glm::vec2 topRight;
};

class PhysicsEngine
{
public:
	PhysicsEngine() = delete;
	~PhysicsEngine() = delete;

	PhysicsEngine(PhysicsEngine&&) = delete;
	PhysicsEngine(const PhysicsEngine&) = delete;
	PhysicsEngine& operator = (const PhysicsEngine&) = delete;
	PhysicsEngine& operator = (PhysicsEngine&&) = delete;

	static void init();
	static void terminate();

	static void update(const double delta);
	static void addDynamicGameObject(std::shared_ptr<IGameObject> gameObject);
	static void setCurrentLevel(std::shared_ptr<Level> currentLevel);
private:
	static std::unordered_set<std::shared_ptr<IGameObject>> m_dynamicObject;
	static std::shared_ptr<Level> m_currentLevel;

	static bool hasIntersection(const std::vector<AABB>& colliders1, const glm::vec2& posittion1
								, const std::vector<AABB>& colliders2, const glm::vec2& posittion2);
};
} //namespace Physics
