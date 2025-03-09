#include "SpriteAnimator.h"
#include "Sprite.h"
#include <iostream>

namespace RenderEngine
{
	SpriteAnimator::SpriteAnimator(std::shared_ptr<Sprite> pSprite) : m_Sprite(std::move(pSprite)), m_currentFrameDuration(m_Sprite->getFrameDuration(0))
	{
	}


	void SpriteAnimator::update(const size_t delta)
	{
		m_currentAnimationTime += delta;

		while (m_currentAnimationTime >= m_currentFrameDuration)
		{
			m_currentAnimationTime -= m_currentFrameDuration;
			++m_currentFrame;
			if (m_currentFrame == m_Sprite->getFramesCount())
			{
				m_currentFrame = 0;
			}
			m_currentFrameDuration = m_Sprite->getFrameDuration(m_currentFrame);
		}
	}
}