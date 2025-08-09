#include "Game.h"
#include <iostream>
#include "../Resources/ResourceManager.h"
#include "../Renderer/ShaderProgram.h"
#include "../Resources/ResourceManager.h"
#include "../Renderer/Texture2D.h"
#include "../Renderer/Sprite.h"

#include "GameObject/Tank.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Level.h"
#include "../Physics/PhysicsEngine.h"


Game::Game(const glm::ivec2& windowSize) : m_windowSize(windowSize)
{
	m_keys.fill(false);
}

Game::~Game()
{

}

void Game::render()
{
    if (m_pTank)
    {
        m_pTank->render();
    }

    if (m_level)
    {
        m_level->render();
    }
}

void Game::update(const double delta)
{
    if (m_level)
    {
        m_level->update(delta);
    }

    if (m_pTank)
    {
        if (m_keys[GLFW_KEY_W])
        {
            m_pTank->setOrientation(Tank::EOrientation::Top);
            m_pTank->setVelocity(m_pTank->getMaxVelocity());
        }
        else if (m_keys[GLFW_KEY_A])
        {
            m_pTank->setOrientation(Tank::EOrientation::Left);
            m_pTank->setVelocity(m_pTank->getMaxVelocity());
        }
        else if (m_keys[GLFW_KEY_D])
        {
            m_pTank->setOrientation(Tank::EOrientation::Right);
            m_pTank->setVelocity(m_pTank->getMaxVelocity());
        }
        else if (m_keys[GLFW_KEY_S])
        {
            m_pTank->setOrientation(Tank::EOrientation::Bottom);
            m_pTank->setVelocity(m_pTank->getMaxVelocity());
        }
        else
        {
            m_pTank->setVelocity(0);
        }
        m_pTank->update(delta);
    }

}

void Game::setKey(const int key, const int action)
{
	m_keys[key] = action;
}

bool Game::init()
{

    bool parseJson = ResourceManager::loadJsonResources("res/resources.json");

    if (!parseJson)
    {
        return false;
    }

    auto pSpriteShaderProgram = ResourceManager::getShaderProgram("spriteShader");

    if (!pSpriteShaderProgram)
    {
        std::cerr <<"Can't find shader program: " << "spriteShader" << std::endl;
        return false;
    }

    m_level = std::make_shared<Level>(ResourceManager::getLevels()[1]);
    m_windowSize.x = static_cast<int>(m_level->getLevelWidth());
    m_windowSize.y = static_cast<int>(m_level->getLevelHight());
    Physics::PhysicsEngine::setCurrentLevel(m_level);

    glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(m_windowSize.x), 0.f, static_cast<float>(m_windowSize.y), -100.f, 100.f);

    pSpriteShaderProgram->use();
    pSpriteShaderProgram->setInt("tex", 0);
    pSpriteShaderProgram->setMatrix4("projectionMat", projectionMatrix);

    m_pTank = std::make_shared<Tank>(
                                    0.05
                                    , m_level->getPlayerRespawn(Level::ETypeRespawn::player1)
                                    , glm::vec2(Level::BLOCK_SIZE, Level::BLOCK_SIZE)
                                    , 0.f
    );
    Physics::PhysicsEngine::addDynamicGameObject(m_pTank);

    return true;
}

size_t Game::getCurrentLevelWidth() const
{ 
    return m_level->getLevelWidth();
}
size_t Game::getCurrentLevelHeigh() const
{
    return m_level->getLevelHight();
}