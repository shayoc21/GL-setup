#define STB_IMAGE_IMPLEMENTATION
#include "render.h"
#include <stdio.h>

void renderClear()
{
  glClearColor(0.39f, 0.58f, 0.93f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
};

void renderInit(renderer* r, const char* shaderPath, const char* texturePath, int vs, int is, float* vertices, unsigned int* indices)
{
	
	//TEXTURES
	
  glGenTextures(1, &r->texture);
  glBindTexture(GL_TEXTURE_2D, r->texture);
  int w, h, nrChannels;
  stbi_set_flip_vertically_on_load(1);
  unsigned char* data = stbi_load(texturePath, &w, &h, &nrChannels, 0);
  if (data)
  {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
    printf("FAILED TO LOAD TEXTURE\n");
    exit(1);
  }
  
  stbi_image_free(data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glEnable(GL_DEPTH_TEST);
	
	//SHADERS

  shaderSource shaders = {0};
  parseShaders(&shaders, shaderPath);

  int compileResult;
  char infoLog[512];

  GLuint vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, (char const * const *)&shaders.vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compileResult);
  if (!compileResult)
  {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    printf("VERTEX SHADER FAILED TO COMPILE : %s\n", infoLog);
    exit(1);
  }
  GLuint fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, (char const * const *)&shaders.fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compileResult);
  if(!compileResult)
  {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    printf("FRAGMENT SHADER FAILED TO COMPILE : %s\n", infoLog);
    exit(1);
  }
  int linkResult;
  r->shaderProgram = glCreateProgram();
  glAttachShader(r->shaderProgram, vertexShader);
  glAttachShader(r->shaderProgram, fragmentShader);
  glLinkProgram(r->shaderProgram);
  glGetProgramiv(r->shaderProgram, GL_LINK_STATUS, &linkResult);
  if (!linkResult)
  {
    glGetProgramInfoLog(r->shaderProgram, 512, NULL, infoLog);
    printf("SHADER FAILED TO LINK: %s\n", infoLog);
    exit(1);
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  destroyShaderSource(&shaders);

	//VERTICES/INDICES

  glGenVertexArrays(1, &r->VAO);
  printf("VAO: %d\n", r->VAO);
  glBindVertexArray(r->VAO);

  glGenBuffers(1, &r->VBO);
  printf("VBO: %d\n", r->VBO);
  glBindBuffer(GL_ARRAY_BUFFER, r->VBO);
  glBufferData(GL_ARRAY_BUFFER, vs * sizeof(float), vertices, GL_STATIC_DRAW);

  glGenBuffers(1, &r->EBO);
  printf("EBO: %d\n", r->EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, r->EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, is * sizeof(unsigned int), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) 0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3*sizeof(float)));
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glBindVertexArray(0);

  GLenum err = glGetError();
  if (err != GL_NO_ERROR)
  {
    printf("OPENGL ERROR FUCK MY LIFE INSIDE RINIT\n");
    printf("ERROR: %d\n", err);
  }
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

void renderDraw(renderer* r, int indexCount)
{
  glUseProgram(r->shaderProgram);
  glBindTexture(GL_TEXTURE_2D, r->texture);
  glBindVertexArray(r->VAO);
  glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);

  GLenum err = glGetError();
  if (err != GL_NO_ERROR)
  {
    printf("OPENGL ERROR FUCK MY LIFE\n");
    printf("ERROR: %d\n", err);
  }
  glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);
}

void renderDestroy(renderer* r)
{
  glDeleteVertexArrays(1, &r->VAO);
  glDeleteBuffers(1, &r->VBO);
}























