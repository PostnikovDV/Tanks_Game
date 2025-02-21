#include "Game.h"
#include <iostream>
#include "../Resources/ResourceManager.h"
#include "../Renderer/ShaderProgram.h"
#include "../Resources/ResourceManager.h"
#include "../Renderer/Texture2D.h"
#include "../Renderer/Sprite.h"
#include "../Renderer/AnimatedSprite.h"


#include "Tank.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <external/glm/vec2.hpp>
#include <external/glm/mat4x4.hpp>
#include <external/glm/gtc/matrix_transform.hpp>


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

    ResourceManager::getAnimationSprite("NewAnimatedSprite")->render();
}

void Game::update(const uint64_t delta)
{
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
    ResourceManager::getAnimationSprite("NewAnimatedSprite")->update(delta);

}

void Game::setKey(const int key, const int action)
{
	m_keys[key] = action;
}

bool Game::init()
{
    auto pSpriteShaderProgram = ResourceManager::loadShaders("spriteShader", "res/shaders/vSprite.txt", "res/shaders/fSprite.txt");
    if (!pSpriteShaderProgram)
    {
        std::cerr << "Can't create shader program: " << "DefaultShader" << std::endl;
        return false;
    }

    std::vector<std::string> subTextureNames{
        "block"
        , "topBlock"
        , "bottomBlock"
        , "leftBlock"
        , "rightBlock"
        , "topLeftBlock"
        , "topRightBlock"
        , "bottomLeftBlock"
        , "bottomRightBlock"
        , "beton"
        , "topBeton"
        , "bottomBeton"
        , "leftBeton"
        , "rightBeton"
        , "topLeftBeton"
        , "topRightBeton"
        , "bottomLeftBeton"
        , "bottomRightBeton"
        , "water1"
        , "water2"
        , "water3"
        , "trees"
        , "ice"
        , "wall"
        , "eagle"
        , "deadEagle"
        , "nothing"
        , "respawn1"
        , "respawn2"
        , "respawn3"
        , "respawn4"

    };

    auto pTextureAtlas = ResourceManager::loadTextureAtlas("DefaultTextureAtlas", "res/textures/map_16x16.png", std::move(subTextureNames), 16, 16);

    auto pAnimatedSprite = ResourceManager::loadAnimationSprite("NewAnimatedSprite", "DefaultTextureAtlas", "spriteShader", 100, 100, "beton");
    pAnimatedSprite->setPosition(glm::vec2(300, 300));
    std::vector<std::pair<std::string, uint64_t>> waterState;
    waterState.emplace_back(std::make_pair<std::string, uint64_t>("water1", 1000000000));
    waterState.emplace_back(std::make_pair<std::string, uint64_t>("water2", 1000000000));
    waterState.emplace_back(std::make_pair<std::string, uint64_t>("water3", 1000000000));

    std::vector<std::pair<std::string, uint64_t>> eagleState;
    eagleState.emplace_back(std::make_pair<std::string, uint64_t>("eagle", 1000000000));
    eagleState.emplace_back(std::make_pair<std::string, uint64_t>("deadEagle", 1000000000));

    pAnimatedSprite->insertState("waterState", std::move(waterState));
    pAnimatedSprite->insertState("eagleState", std::move(eagleState));


    pAnimatedSprite->setState("waterState");

    glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(m_windowSize.x), 0.f, static_cast<float>(m_windowSize.y), -100.f, 100.f);

    pSpriteShaderProgram->use();
    pSpriteShaderProgram->setInt("tex", 0);
    pSpriteShaderProgram->setMatrix4("projectionMat", projectionMatrix);


    std::vector<std::string> tanksSubTextureNames{
        "tankTop1"
        , "tankTop2"
        , "tankLeft1"
        , "tankLeft2"
        , "tankBottom1"
        , "tankBottom2"
        , "tankRight1"
        , "tankRight2"
    };
    auto pTanksTextureAtlas = ResourceManager::loadTextureAtlas("TanksTextureAtlas", "res/textures/tanks.png", std::move(tanksSubTextureNames), 16, 16);
    
    auto pTankAnimatedSprite = ResourceManager::loadAnimationSprite("TanksAnimatedSprite", "TanksTextureAtlas", "spriteShader", 100, 100, "tankTop1");

    std::vector<std::pair<std::string, uint64_t>> tankTopState;
    tankTopState.emplace_back(std::make_pair<std::string, uint64_t>("tankTop1", 500000000));
    tankTopState.emplace_back(std::make_pair<std::string, uint64_t>("tankTop2", 500000000));

    std::vector<std::pair<std::string, uint64_t>> tankBottomState;
    tankBottomState.emplace_back(std::make_pair<std::string, uint64_t>("tankBottom1", 500000000));
    tankBottomState.emplace_back(std::make_pair<std::string, uint64_t>("tankBottom2", 500000000));

    std::vector<std::pair<std::string, uint64_t>> tankLeftState;
    tankLeftState.emplace_back(std::make_pair<std::string, uint64_t>("tankLeft1", 500000000));
    tankLeftState.emplace_back(std::make_pair<std::string, uint64_t>("tankLeft2", 500000000));

    std::vector<std::pair<std::string, uint64_t>> tankRightState;
    tankRightState.emplace_back(std::make_pair<std::string, uint64_t>("tankRight1", 500000000));
    tankRightState.emplace_back(std::make_pair<std::string, uint64_t>("tankRight2", 500000000));


    pTankAnimatedSprite->insertState("tankTopState", std::move(tankTopState));
    pTankAnimatedSprite->insertState("tankBottomState", std::move(tankBottomState));
    pTankAnimatedSprite->insertState("tankLeftState", std::move(tankLeftState));
    pTankAnimatedSprite->insertState("tankRightState", std::move(tankRightState));

    pTankAnimatedSprite->setState("tankTopState");

    m_pTank = std::make_unique<Tank>(pTankAnimatedSprite, 0.0000001f, glm::vec2(100.f, 100.f));

    return true;
}