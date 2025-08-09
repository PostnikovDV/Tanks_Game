#pragma once

#include "IGameObject.h"
#include <memory>
#include <array>

namespace RenderEngine
{
	class Sprite;
}

class BetonWall : public IGameObject
{
public:
	enum class EBetonWallType
	{
		All,
		Top,
		Bottom,
		Left,
		Right,
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight
	};

	enum class EBlockState
	{
		Enabled = 0,
		Destroyed
	};

	enum class EBetonLocation
	{
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight
	};

	BetonWall(EBetonWallType blockType, const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer);

	void render() const override;
private:
	void renderBeton(const EBetonLocation eBetonLoñation) const;

	std::array<EBlockState, 4> m_CurrentBlockState;
	std::shared_ptr<RenderEngine::Sprite> m_Sprite;

	std::array<glm::vec2, 4> m_blockOffSets;
};
