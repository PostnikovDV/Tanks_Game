#include "Game.h"
#include <iostream>
#include "../Resources/ResourceManager.h"
#include "../Renderer/ShaderProgram.h"
#include "../Resources/ResourceManager.h"
#include "../Renderer/Texture2D.h"
#include "../Renderer/Sprite.h"
#include "../Renderer/AnimatedSprite.h"


#include "GameObject/Tank.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Level.h"


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

void Game::update(const uint64_t delta)
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
            m_pTank->move(true);
        }
        else if (m_keys[GLFW_KEY_A])
        {
            m_pTank->setOrientation(Tank::EOrientation::Left);
            m_pTank->move(true);
        }
        else if (m_keys[GLFW_KEY_D])
        {
            m_pTank->setOrientation(Tank::EOrientation::Right);
            m_pTank->move(true);
        }
        else if (m_keys[GLFW_KEY_S])
        {
            m_pTank->setOrientation(Tank::EOrientation::Bottom);
            m_pTank->move(true);
        }
        else
        {
            m_pTank->move(false);
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

    auto pTextureAtlas = ResourceManager::getTexture("mapTextureAtlas");

    if (!pTextureAtlas)
    {
        std::cerr << "Can't find texture Atlas: " << "mapTextureAtlas" << std::endl;
        return false;
    }

    auto pTanksTextureAtlas = ResourceManager::getTexture("tanksTextureAtlas");

    if (!pTanksTextureAtlas)
    {
        std::cerr << "Can't find texture Atlas: " << "tanksTextureAtlas" << std::endl;
        return false;
    }

    glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(m_windowSize.x), 0.f, static_cast<float>(m_windowSize.y), -100.f, 100.f);

    pSpriteShaderProgram->use();
    pSpriteShaderProgram->setInt("tex", 0);
    pSpriteShaderProgram->setMatrix4("projectionMat", projectionMatrix);

    auto pTankAnimatedSprite = ResourceManager::getAnimatedSprite("tankAnimatedSprite");

    if (!pTankAnimatedSprite)
    {
        std::cerr << "Can't find animated sprite: " << "pTankAnimatedSprite" << std::endl;
        return false;
    }

    m_pTank = std::make_unique<Tank>(pTankAnimatedSprite, 0.0000001f, glm::vec2(0.f, 0.f), glm::vec2(16.f, 16.f));
    m_level = std::make_unique<Level>(ResourceManager::getLevels()[0]);

    return true;
}