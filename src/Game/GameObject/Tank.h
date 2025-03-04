#pragma once
#include <memory>
#include "glm/vec2.hpp"

#include "IGameObject.h"

namespace RenderEngine
{
	class AnimatedSprite;
}

class Tank : public IGameObject
{
public:
	enum class EOrientation
	{
		Top,
		Bottom,
		Left,
		Right
	};

	Tank(std::shared_ptr<RenderEngine::AnimatedSprite> sprite, const float velocity, const glm::vec2& position, const glm::vec2& size);

	void render() const;

	void setOrientation(const EOrientation orient);
	void move(const bool move);
	void update(const uint64_t delta);

private:
	EOrientation m_eOrientation{ EOrientation::Top };
	std::shared_ptr<RenderEngine::AnimatedSprite> m_pSprite;
	bool m_move{ false };
	float m_velocity;

	glm::vec2 m_moveOffset;
};