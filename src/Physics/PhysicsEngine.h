#pragma once
#include <unordered_set>
#include <memory>

class IGameObject;

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
private:
	static std::unordered_set<std::shared_ptr<IGameObject>> m_dynamicObject;
};