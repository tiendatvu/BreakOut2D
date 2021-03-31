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
#include <windows.h>

// Game-related State data
SpriteRenderer  *Renderer;
const unsigned int maxDir = 260;

Game::Game(unsigned int width, unsigned int height)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

Game::~Game()
{
    delete Renderer;
}

void Game::Init()
{
    char currentDir[maxDir];
    GetCurrentDirectoryA(maxDir, currentDir);
    // load shaders
    std::string vsFile1 = "/src/Utility/shaders/sprite.vs";
    std::string frsFile1 = "/src/Utility/shaders/sprite.frs";
    ResourceManager::LoadShader(currentDir + vsFile1, currentDir + frsFile1, "", "sprite");
    // configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),
        static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    // set render-specific controls
    Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
    // load textures
    char imageFile[maxDir];
    std::strncpy(imageFile, currentDir, maxDir - 1);
    std::strncat(imageFile, "/Resources/imgs/awesomeface.png", maxDir - strlen(imageFile) - 1);
    ResourceManager::LoadTexture(imageFile, true, "face");
}

void Game::Update(float dt)
{

}

void Game::ProcessInput(float dt)
{

}

void Game::Render()
{
    Renderer->DrawSprite(ResourceManager::GetTexture("face"), glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}