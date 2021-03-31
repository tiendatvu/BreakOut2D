/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "sprite_renderer.h"

SpriteRenderer::SpriteRenderer(Shader &inShader)
{
    this->shader = inShader;
    this->initRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
    glDeleteVertexArrays(1, &this->quadVAO);
}

void SpriteRenderer::DrawSprite(Texture2D &texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color)
{
    // prepare transformations
    this->shader.Use();
    glm::mat4 model = glm::mat4(1.0f);
    // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)
    model = glm::translate(model, glm::vec3(position, 0.0f));
    // move the origin of rotation to center of the quad
    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // (2)
    // then rotate
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    // move origin back
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // (1)
    // last scale
    model = glm::scale(model, glm::vec3(size, 1.0f));

    // Theo thứ tự nhân ma trận:
    // 1. scale
    // 2. rotate
    // 3. translate
    // Ta thấy có 2 hàm translate xen giữa. Do hiện tại, ta đang định nghĩa gốc 0 ở tại vị trí top-left của 1 <quad>
    // -> cần đưa gốc 0 về vị trí tâm của hình vuông <quad> để rotate cho ra kết quả chính xác
    // -> translate sang trái (0.5, 0.5) theo 2 chiều (x,y)
    // -> sau khi rotate thành công, ta lại đưa gốc 0 về vị trí top-left của hình vuông <quad>
    // -> thực hiện translate như bình thường
    this->shader.SetMatrix4("model", model);
    // render textured quad
    this->shader.SetVector3f("spriteColor", color);

    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void SpriteRenderer::initRenderData()
{
    // configure VAO/VBO
    unsigned int VBO;
    float vertices[] = {
        // Bình thường, ta quen với việc xác định vertices với gốc tọa độ 0 tại tâm của hình vuông <quad>
        // nên ta thường có định nghĩa position của các vertex và texture coordinate để render ra hình texure tương đôi khác nhau
        // ví dụ:
        // // positions          // texture coords
        //  0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
        //  0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
        // -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
        // -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 

        // Nhưng trong trường hợp này, gốc tọa độ của vertex và texture là giống nhau (cùng tại top-left của hình vuông <quad>)
        // nên giá trị của chúng PHẢI giống nhau như bên dưới
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}