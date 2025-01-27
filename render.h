#ifndef _RENDER
#define _RENDER

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include "dep/stb/stb_image.h"

struct renderer
{
  GLuint VAO;
  GLuint VBO;
  GLuint EBO;
  GLuint shaderProgram;
  GLuint texture;
};
typedef struct renderer renderer;

void renderClear();
void renderInit(renderer* r, const char* shaderPath, const char* texturePath, int vs, int is, float* vertices, unsigned int* indices);
void renderDestroy(renderer* r);
void renderDraw(renderer* renderer, int indexCount);

#endif
