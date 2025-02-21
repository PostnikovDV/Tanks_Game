#pragma once
#include <array>
#include <external/glm/vec2.hpp>
#include <memory>

class Tank;

class Game
{
public:
	Game(const glm::ivec2& windowSize);

	~Game();

	void render();
	void update(const uint64_t delta);
	void setKey(const int key, const int action);
	bool init();

private:
	std::array<bool, 349> m_keys;

	enum class EGameState
	{
		Active,
		Pause
	};


	glm::ivec2 m_windowSize;
	EGameState m_ECurrentGameState{ EGameState::Active };

	std::unique_ptr<Tank> m_pTank;
};