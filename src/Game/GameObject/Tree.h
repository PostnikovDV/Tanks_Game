#pragma once

#include "IGameObject.h"
#include <memory>
#include <array>

namespace RenderEngine
{
	class Sprite;
}

class Tree : public IGameObject
{
public:

	enum class ETreeLocation
	{
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight
	};

	Tree(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer);

	void render() const override;
private:
	void renderTree(const ETreeLocation eBetonLovation) const;

	std::shared_ptr<RenderEngine::Sprite> m_Sprite;

	std::array<glm::vec2, 4> m_blockOffSets;
};
