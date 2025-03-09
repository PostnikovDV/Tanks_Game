#pragma once
#include <memory>
#include "glm/vec2.hpp"

#include "IGameObject.h"
#include "../../Renderer/SpriteAnimator.h"

namespace RenderEngine
{
	class Sprite;
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

	Tank(
		std::shared_ptr<RenderEngine::Sprite> spriteTop
		, std::shared_ptr<RenderEngine::Sprite> spriteBottom
		, std::shared_ptr<RenderEngine::Sprite> spriteLeft
		, std::shared_ptr<RenderEngine::Sprite> spriteRight
		, const float velocity
		, const glm::vec2& position
		, const glm::vec2& size
	);

	void render() const;

	void setOrientation(const EOrientation orient);
	void move(const bool move);
	void update(const uint64_t delta);

private:
	EOrientation m_eOrientation{ EOrientation::Top };
	std::shared_ptr<RenderEngine::Sprite> m_pSpriteTop;
	std::shared_ptr<RenderEngine::Sprite> m_pSpriteBottom;
	std::shared_ptr<RenderEngine::Sprite> m_pSpriteLeft;
	std::shared_ptr<RenderEngine::Sprite> m_pSpriteRight;

	RenderEngine::SpriteAnimator m_spriteAnimatorTop;
	RenderEngine::SpriteAnimator m_spriteAnimatorBottom;
	RenderEngine::SpriteAnimator m_spriteAnimatorLeft;
	RenderEngine::SpriteAnimator m_spriteAnimatorRight;

	bool m_move{ false };
	float m_velocity;

	glm::vec2 m_moveOffset;
};