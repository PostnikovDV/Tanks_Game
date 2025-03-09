#pragma once
#include "IGameObject.h"
#include <memory>

namespace RenderEngine
{
	class Sprite;
}


class BrickWall : public IGameObject
{
public:

	BrickWall(const std::shared_ptr<RenderEngine::Sprite> pSprite, const glm::vec2& position, const glm::vec2& size, const float rotation);

	void render() const override;
	void update(const uint64_t) override;

private:
	std::shared_ptr<RenderEngine::Sprite> m_currentSprite;

};