#pragma once

#include "IGameObject.h"
#include <memory>
#include <array>

namespace RenderEngine
{
	class Sprite;
}

class Ice : public IGameObject
{
public:

	enum class EIceLocation
	{
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight
	};

	Ice(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer);

	void render() const override;
	void update(const uint64_t) override;

private:
	void renderIce(const EIceLocation eBetonLovation) const;

	std::shared_ptr<RenderEngine::Sprite> m_Sprite;

	std::array<glm::vec2, 4> m_blockOffSets;
};
