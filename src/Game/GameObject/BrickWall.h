#pragma once
#include "IGameObject.h"
#include <memory>
#include <array>

namespace RenderEngine
{
	class Sprite;
}


class BrickWall : public IGameObject
{
public:

	enum class EBrickWallType
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

	enum class EBrickState
	{
		All = 0,
		TopLeft,
		TopRight,
		Top,
		BottomLeft,
		Left,
		TopRight_BottomLeft,
		Top_BottomLeft,
		BottomRight,
		TopLeft_BottomRight,
		Right,
		Top_BottomRight,
		Bottom,
		TopLeft_Bottom,
		TopRight_Bottom,
		Destroyed
	};

	enum class EBrickLocation
	{
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight
	};

	BrickWall(EBrickWallType blockType, const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer);

	void render() const override;
private:
	void renderBrick(const EBrickLocation eBrickLovation) const;

	std::array<EBrickState, 4> m_CurrentBrickState;
	std::array<std::shared_ptr<RenderEngine::Sprite>, 15> m_Sprites;

	std::array<glm::vec2, 4> m_blockOffSets;
};