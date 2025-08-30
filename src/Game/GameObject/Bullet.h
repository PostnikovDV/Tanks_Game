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

class Bullet : public IGameObject
{
public:
	enum class EOrientation : uint8_t
	{
		Top,
		Bottom,
		Left,
		Right
	};

	Bullet(
		const double velocity
		, const glm::vec2& position
		, const glm::vec2& size
		, const float layer
	);

	void render() const override;
	bool isActive() const { return m_isActive; }
	void fire(const glm::vec2& position, const glm::vec2& direction);
	void onCollision() override;
private:
	EOrientation m_eOrientation{ EOrientation::Top };
	std::shared_ptr<RenderEngine::Sprite> m_pSpriteTop;
	std::shared_ptr<RenderEngine::Sprite> m_pSpriteBottom;
	std::shared_ptr<RenderEngine::Sprite> m_pSpriteLeft;
	std::shared_ptr<RenderEngine::Sprite> m_pSpriteRight;
	double m_maxVelocity;

	bool m_isActive{ false }; //  находится ли снаряд в полете
};