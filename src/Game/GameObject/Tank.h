#pragma once
#include <memory>
#include "glm/vec2.hpp"

#include "IGameObject.h"
#include "../../Renderer/SpriteAnimator.h"
#include "../../System/Timer.h"

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
		const double maxVelocity
		, const glm::vec2& position
		, const glm::vec2& size
		, const float layer
	);

	void render() const;

	void setOrientation(const EOrientation orient);
	void update(const double delta);
	double getMaxVelocity();
	void setVelocity(const double velocity) override;

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

	std::shared_ptr<RenderEngine::Sprite> m_pSpriteRespawn;
	RenderEngine::SpriteAnimator m_spriteAnimatorRespawn;

	std::shared_ptr<RenderEngine::Sprite> m_pSpriteShield;
	RenderEngine::SpriteAnimator m_spriteAnimatorShield;

	Timer m_spawnTimer;
	Timer m_shieldTimer;

	bool m_isSpawning;
	bool m_hasShield;
	double m_maxVelocity;
};