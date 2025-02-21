#pragma once

#include <glad/glad.h>
#include <external/glm/vec2.hpp>
#include <memory>
#include <string>
#include "Sprite.h"
#include <map>
#include <vector>

namespace RenderEngine
{

	class AnimatedSprite : public Sprite
	{
	public:
		AnimatedSprite(
			std::shared_ptr<Texture2D> pTexture
			, std::string initialSubTexture
			, const std::shared_ptr<ShaderProgram> pShaderProgram
			, const glm::vec2& position = glm::vec2(0.f)
			, const glm::vec2& size = glm::vec2(1.f)
			, const float rotation = 0
		);

		void insertState(std::string state, std::vector<std::pair<std::string, uint64_t>> subTextureDuration);

		void render() const override;

		void update(const uint64_t delta);

		void setState(const std::string& newState);

	private:
		std::map<std::string, std::vector<std::pair<std::string, uint64_t>>> m_statesMap;
		size_t m_currentFrame{ 0 };
		uint64_t m_currentAnimationTime{ 0 };
		std::map<std::string, std::vector<std::pair<std::string, uint64_t>>>::const_iterator m_pCurrentAnimationDurations{ m_statesMap.end() };
		mutable bool m_dirty{ false };

	};
}