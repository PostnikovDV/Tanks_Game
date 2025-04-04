#include "Sprite.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Renderer.h"

namespace RenderEngine
{
	Sprite::Sprite(
		std::shared_ptr<Texture2D> pTexture
		, std::string initialSubTexture
		, std::shared_ptr<ShaderProgram> pShaderProgram
		) : m_pTexture(std::move(pTexture))
		, m_pShaderProgram(std::move(pShaderProgram))
		, m_lastFrameId(0)
	{
		const GLfloat vertexCoords[]
		{
			0.f, 0.f,
			0.f, 1.f,
			1.f, 1.f,
			1.f, 0.f,
		};

		auto subTexture = m_pTexture->getSubTexture(std::move(initialSubTexture));

		const GLfloat textCoords[]
		{
			subTexture.leftBottomUV.x, subTexture.leftBottomUV.y,
			subTexture.leftBottomUV.x, subTexture.rightTopUV.y,
			subTexture.rightTopUV.x, subTexture.rightTopUV.y,
			subTexture.rightTopUV.x, subTexture.leftBottomUV.y,

		};

		const GLint indices[]
		{
			0, 1, 2,
			2, 3, 0
		};

		m_vertexArray.bind();

		m_vertexCoordsBuffer.init(vertexCoords, sizeof(vertexCoords));
		VertexBufferLayout vertexCoordsLayout;
		vertexCoordsLayout.addElementLayout(2, false);
		m_vertexArray.addBuffer(m_vertexCoordsBuffer, vertexCoordsLayout);

		m_textureCoordsBuffer.init(textCoords, sizeof(textCoords));
		VertexBufferLayout textureCoordsLayout;
		textureCoordsLayout.addElementLayout(2, false);
		m_vertexArray.addBuffer(m_textureCoordsBuffer, textureCoordsLayout);


		m_indexBuffer.init(indices, 6);


		m_vertexArray.unbind();
		m_indexBuffer.unbind();
	}

	Sprite::~Sprite()
	{
	}

	void Sprite::render(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer, const size_t frameId) const
	{
		if (m_lastFrameId != frameId)
		{
			m_lastFrameId = frameId;
			const FrameDescription& currentFrameDescr{ m_framesDescriptions[frameId] };

			const GLfloat textCoords[]
			{
				currentFrameDescr.leftBottomUV.x, currentFrameDescr.leftBottomUV.y,
				currentFrameDescr.leftBottomUV.x, currentFrameDescr.rightTopUV.y,
				currentFrameDescr.rightTopUV.x, currentFrameDescr.rightTopUV.y,
				currentFrameDescr.rightTopUV.x, currentFrameDescr.leftBottomUV.y,
			};

			m_textureCoordsBuffer.update(textCoords, sizeof(textCoords));
		}

		m_pShaderProgram->use();

		glm::mat4 model(1.f);
		model = glm::translate(model, glm::vec3(position, 0.f));
		model = glm::translate(model, glm::vec3(-0.5 * size.x, -0.5 * size.y, 0.f));
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.f, 0.f, 1.f));
		model = glm::translate(model, glm::vec3(0.5 * size.x, 0.5 * size.y, 0.f));
		model = glm::scale(model, glm::vec3(size, 1.f));

		m_pShaderProgram->setMatrix4("modelMat", model);
		m_pShaderProgram->setFloat("layer", layer);

		glActiveTexture(GL_TEXTURE0);
		m_pTexture->bind();
	
		Renderer::draw(m_vertexArray, m_indexBuffer,*m_pShaderProgram);

	}

	double Sprite::getFrameDuration(const size_t frameId) const
	{
		return m_framesDescriptions[frameId].duration;
	}
	size_t Sprite::getFramesCount() const
	{
		return m_framesDescriptions.size();
	}

	void Sprite::insertFrames(std::vector<FrameDescription> framesDescription)
	{
		m_framesDescriptions = std::move(framesDescription);
	}
}