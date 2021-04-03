/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "game.h"
#include "ResourceManager.h"
#include "sprite_renderer.h"
#include "game_object.h"
#include <windows.h>

// Game-related State data
SpriteRenderer  *Renderer;
GameObject      *Player;
const unsigned int maxDir = 260;

Game::Game(unsigned int width, unsigned int height)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{
}

Game::~Game()
{
    delete Renderer;
    delete Player;
}

void Game::Init()
{
    try
    {
        char currentDir[maxDir];
        GetCurrentDirectoryA(maxDir, currentDir);
        // load shaders
        std::string vsFile1 = "/src/Utility/shaders/sprite.vs";
        std::string frsFile1 = "/src/Utility/shaders/sprite.frs";
        ResourceManager::LoadShader(currentDir + vsFile1, currentDir + frsFile1, "", "sprite");
        // configure shaders
        glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width), static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
        ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
        ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
        // set render-specific controls
        Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
        // load textures
        char imageFile[maxDir];
        std::strncpy(imageFile, currentDir, maxDir - 1);
        std::strncat(imageFile, "/Resources/imgs/background.jpg", maxDir - strlen(imageFile) - 1);
        ResourceManager::LoadTexture(imageFile, false, "background");
        std::strncpy(imageFile, currentDir, maxDir - 1);
        std::strncat(imageFile, "/Resources/imgs/awesomeface.png", maxDir - strlen(imageFile) - 1);
        ResourceManager::LoadTexture(imageFile, true, "face");
        std::strncpy(imageFile, currentDir, maxDir - 1);
        std::strncat(imageFile, "/Resources/imgs/block.png", maxDir - strlen(imageFile) - 1);
        ResourceManager::LoadTexture(imageFile, false, "block");
        std::strncpy(imageFile, currentDir, maxDir - 1);
        std::strncat(imageFile, "/Resources/imgs/block_solid.png", maxDir - strlen(imageFile) - 1);
        ResourceManager::LoadTexture(imageFile, false, "block_solid");
        std::strncpy(imageFile, currentDir, maxDir - 1);
        std::strncat(imageFile, "/Resources/imgs/paddle.png", maxDir - strlen(imageFile) - 1);
        ResourceManager::LoadTexture(imageFile, true, "paddle");
        // load levels
        char levelFile[maxDir];
        std::strncpy(levelFile, currentDir, maxDir - 1);
        std::strncat(levelFile, "/src/Utility/levels/one.lvl", maxDir - strlen(imageFile) - 1);
        GameLevel one; one.Load(levelFile, this->Width, this->Height / 2);
        std::strncpy(levelFile, currentDir, maxDir - 1);
        std::strncat(levelFile, "/src/Utility/levels/two.lvl", maxDir - strlen(imageFile) - 1);
        GameLevel two; two.Load(levelFile, this->Width, this->Height / 2);
        std::strncpy(levelFile, currentDir, maxDir - 1);
        std::strncat(levelFile, "/src/Utility/levels/three.lvl", maxDir - strlen(imageFile) - 1);
        GameLevel three; three.Load(levelFile, this->Width, this->Height / 2);
        std::strncpy(levelFile, currentDir, maxDir - 1);
        std::strncat(levelFile, "/src/Utility/levels/four.lvl", maxDir - strlen(imageFile) - 1);
        GameLevel four; four.Load(levelFile, this->Width, this->Height / 2);
        this->Levels.push_back(one);
        this->Levels.push_back(two);
        this->Levels.push_back(three);
        this->Levels.push_back(four);
        this->Level = 0;
        // configure game objects
        glm::vec2 playerPos = glm::vec2(this->Width / 2.0f - PLAYER_SIZE.x / 2.0f, this->Height - PLAYER_SIZE.y);
        Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));
    }
    catch (const std::exception& e)
    {
        int a = 1;
    }    
}

void Game::Update(float dt)
{

}

void Game::ProcessInput(float dt)
{
    if (this->State == GAME_ACTIVE)
    {
        float velocity = PLAYER_VELOCITY * dt;
        // move playerboard
        if (this->Keys[GLFW_KEY_A])
        {
            if (Player->Position.x >= 0.0f)
                Player->Position.x -= velocity;
        }
        if (this->Keys[GLFW_KEY_D])
        {
            if (Player->Position.x <= this->Width - Player->Size.x)
                Player->Position.x += velocity;
        }
    }
}

void Game::Render()
{
    if (this->State == GAME_ACTIVE)
    {
        // draw background
        Renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0.0f, 0.0f), glm::vec2(this->Width, this->Height), 0.0f);
        // draw level
        this->Levels[this->Level].Draw(*Renderer);
        // draw player
        Player->Draw(*Renderer);
    }
}