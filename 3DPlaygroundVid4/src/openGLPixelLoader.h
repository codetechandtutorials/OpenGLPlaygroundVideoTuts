#pragma once
#include <glad/glad.h>
#include <iostream>
#include <shader.h>
#include <glm/glm.hpp>
#include "camera.h"

extern Shader* gShader;
extern Camera* gCamera;

static unsigned int cubeVAO = 0;
static unsigned int cubeVBO = 0;

void loadUpSquare() 
{
  const float vertices[] = {
    // positions         
    -0.5f, -0.5f, -0.5f, 
     0.5f, -0.5f, -0.5f, 
     0.5f,  0.5f, -0.5f, 
     0.5f,  0.5f, -0.5f, 
    -0.5f,  0.5f, -0.5f, 
    -0.5f, -0.5f, -0.5f, 

    -0.5f, -0.5f,  0.5f, 
     0.5f, -0.5f,  0.5f, 
     0.5f,  0.5f,  0.5f, 
     0.5f,  0.5f,  0.5f, 
    -0.5f,  0.5f,  0.5f, 
    -0.5f, -0.5f,  0.5f, 

    -0.5f,  0.5f,  0.5f, 
    -0.5f,  0.5f, -0.5f, 
    -0.5f, -0.5f, -0.5f, 
    -0.5f, -0.5f, -0.5f, 
    -0.5f, -0.5f,  0.5f, 
    -0.5f,  0.5f,  0.5f, 

     0.5f,  0.5f,  0.5f, 
     0.5f,  0.5f, -0.5f, 
     0.5f, -0.5f, -0.5f, 
     0.5f, -0.5f, -0.5f, 
     0.5f, -0.5f,  0.5f, 
     0.5f,  0.5f,  0.5f, 

    -0.5f, -0.5f, -0.5f, 
     0.5f, -0.5f, -0.5f, 
     0.5f, -0.5f,  0.5f, 
     0.5f, -0.5f,  0.5f, 
    -0.5f, -0.5f,  0.5f, 
    -0.5f, -0.5f, -0.5f, 

    -0.5f,  0.5f, -0.5f, 
     0.5f,  0.5f, -0.5f, 
     0.5f,  0.5f,  0.5f, 
     0.5f,  0.5f,  0.5f, 
    -0.5f,  0.5f,  0.5f, 
    -0.5f,  0.5f, -0.5f, 
  };

  /* set up an area to store vertex data */
  glGenVertexArrays(1, &cubeVAO);
  glGenBuffers(1, &cubeVBO);

  glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

  glBindVertexArray(cubeVAO);

  // position attribute
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

  //// normal attribute
  //glEnableVertexAttribArray(2);
  //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

  //// texture coord attribute
  //glEnableVertexAttribArray(1);
  //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));


  // unbind buffers
  //glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindVertexArray(0);

  std::cout << "cube Loaded to Graphics Card \n";
}

void unloadSquare()
{
  glDeleteBuffers(1, &cubeVBO);
}

void render()
{
  gCamera->updateViewMatrix(gShader);

  glBindVertexArray(cubeVAO);
  glEnableVertexAttribArray(0);
  glDrawArrays(GL_TRIANGLES, 0, 36);
  glBindVertexArray(0);
}