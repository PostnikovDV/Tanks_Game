#pragma once

#include "IGameObject.h"
#include <memory>
#include <array>

#include "../../Renderer/SpriteAnimator.h"

namespace RenderEngine
{
	class Sprite;
}

class Water : public IGameObject
{
public:

	enum class EWaterLocation
	{
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight
	};

	Water(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer);

	void render() const override;
	void update(const double delta) override;

private:
	void renderWater(const EWaterLocation eBetonLovation) const;

	std::shared_ptr<RenderEngine::Sprite> m_pSprite;

	RenderEngine::SpriteAnimator m_spriteAnimator;

	std::array<glm::vec2, 4> m_blockOffSets;
};
