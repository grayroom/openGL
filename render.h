#pragma once

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


unsigned int initShader(const GLchar* vertexShaderSource, const GLchar* fragmentShaderSource);
void checkShaderCompile(const unsigned int vertexShader);
void checkShaderProgram(const unsigned int shaderProgram);

unsigned int renderWithVAO(const float* vertices, const unsigned int* indices, const int verticeSize, const int indiceSize);
unsigned int renderWithVBO(const float* vertices);