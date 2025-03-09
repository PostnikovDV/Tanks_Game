#pragma once
#include <memory>

namespace RenderEngine
{
	class Sprite;
	class SpriteAnimator
	{
	public:
		SpriteAnimator(std::shared_ptr<Sprite> pSprite);

		size_t getCurrentFrame() const { return m_currentFrame; }

		void update(const size_t delta);
	private:
		std::shared_ptr<Sprite> m_Sprite;
		size_t m_currentFrame{ 0 };
		uint64_t m_currentFrameDuration;
		uint64_t m_currentAnimationTime{ 0 };
	};
}