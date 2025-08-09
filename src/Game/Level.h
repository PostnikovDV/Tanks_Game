#pragma once
#include <iostream>
#include <vector>
#include <glm/vec2.hpp>

class IGameObject;

class Level
{
public:
	static constexpr unsigned int BLOCK_SIZE = 16;

	Level(const std::vector<std::string>& levelDescription);
	void render() const;
	void update(const double delta);

	size_t getLevelWidth() const;

	size_t getLevelHight() const;

	enum class ETypeRespawn
	{
		player1,
		player2,
		enemy1,
		enemy2,
		enemy3
	};

	const glm::ivec2& getPlayerRespawn(ETypeRespawn respawnType);

	const glm::ivec2& getPlayerRespawn1() { return m_playerRespawn_1; }
	const glm::ivec2& getPlayerRespawn2() { return m_playerRespawn_2; }
	const glm::ivec2& getEnemyRespawn1() { return m_enemyRespawn_1; }
	const glm::ivec2& getEnemyRespawn2() { return m_enemyRespawn_2; }
	const glm::ivec2& getEnemyRespawn3() { return m_enemyRespawn_3; }
	std::vector<std::shared_ptr<IGameObject>> getObjectInArea(const glm::vec2& bottomLeft, const glm::vec2& topRight) const;
private:
	size_t m_widthBlock{ 0 };
	size_t m_heightBlock{ 0 };
	unsigned int m_widthPixels{ 0 };
	unsigned int m_heightPixels{ 0 };

	glm::ivec2 m_playerRespawn_1;
	glm::ivec2 m_playerRespawn_2;
	glm::ivec2 m_enemyRespawn_1;
	glm::ivec2 m_enemyRespawn_2;
	glm::ivec2 m_enemyRespawn_3;

	std::vector<std::shared_ptr<IGameObject>> m_levelObjects;
};