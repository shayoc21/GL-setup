#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include "maths.h"
#include "render.h"
#include "object.h"

float vertices[120] = 
{
  //FRONT
  -0.5f,-0.5f, 0.5f,    0.0f, 0.0f, //BL
   0.5f,-0.5f, 0.5f,    1.0f, 0.0f, //BR
  -0.5f, 0.5f, 0.5f,    0.0f, 1.0f, //TL
   0.5f, 0.5f, 0.5f,    1.0f, 1.0f, //TR

  //BACK 
  -0.5f,-0.5f,-0.5f,    0.0f, 0.0f, //BL
   0.5f,-0.5f,-0.5f,    1.0f, 0.0f, //BR
  -0.5f, 0.5f,-0.5f,    0.0f, 1.0f, //TL
   0.5f, 0.5f,-0.5f,    1.0f, 1.0f, //TR

  //LEFT
  -0.5f,-0.5f,-0.5f,    0.0f, 0.0f, //BL
  -0.5f,-0.5f, 0.5f,    1.0f, 0.0f, //BR
  -0.5f, 0.5f,-0.5f,    0.0f, 1.0f, //TL
  -0.5f, 0.5f, 0.5f,    1.0f, 1.0f, //TR

  //RIGHT
   0.5f,-0.5f, 0.5f,    0.0f, 0.0f, //BL
   0.5f,-0.5f,-0.5f,    1.0f, 0.0f, //BR
   0.5f, 0.5f, 0.5f,    0.0f, 1.0f, //TL
   0.5f, 0.5f,-0.5f,    1.0f, 1.0f, //TR

  //TOP
  -0.5f, 0.5f,-0.5f,    0.0f, 0.0f, //BL
   0.5f, 0.5f,-0.5f,    1.0f, 0.0f, //BR
  -0.5f, 0.5f, 0.5f,    0.0f, 1.0f, //TL
   0.5f, 0.5f, 0.5f,    1.0f, 1.0f, //TR

  //BOTTOM
  -0.5f,-0.5f,-0.5f,    0.0f, 0.0f, //BL
   0.5f,-0.5f,-0.5f,    1.0f, 0.0f, //BR
  -0.5f,-0.5f, 0.5f,    0.0f, 1.0f, //TL
   0.5f,-0.5f, 0.5f,    1.0f, 1.0f //TR
};

unsigned int indices[36]  = 
{
    // Front Face
    0, 1, 2, 2, 1, 3,
    // Back Face
    4, 5, 6, 6, 5, 7,
    // Left Face
    8, 9, 10, 10, 9, 11,
    // Right Face
    12, 13, 14, 14, 13, 15,
    // Top Face
    16, 17, 18, 18, 17, 19,
    // Bottom Face
    20, 21, 22, 22, 21, 23
};

struct camera
{
  vec3f cameraPos;
  vec3f cameraFront;
  vec3f cameraUp;
  vec3f cameraRight;
  float yaw;
  float pitch;
};
typedef struct camera camera;
camera playerCam;

float xsens = 0.45f;
float ysens = 0.45f;

struct 
{
  GLFWwindow* window;
} session;

int pPressed = 0;

enum
{
  WIREFRAME = GL_LINE,
  FILL = GL_FILL
} wireframe;

void errorCallback(int error, const char* description)
{
  fprintf(stderr, "ERROR: %s\n", description);
}

void frameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}

void getInput(GLFWwindow* window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, 1);
  }
  if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && !pPressed)
  {
    pPressed = 1;
    wireframe = (wireframe == FILL) ? WIREFRAME : FILL;
    glPolygonMode(GL_FRONT_AND_BACK, wireframe);
  }
  if (glfwGetKey(window, GLFW_KEY_P) == GLFW_RELEASE)
  {
    pPressed = 0;
  }
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
  {
    playerCam.cameraPos.x += 0.05f * playerCam.cameraFront.x;
    playerCam.cameraPos.y += 0.05f * playerCam.cameraFront.y;
    playerCam.cameraPos.z += 0.05f * playerCam.cameraFront.z;
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
  {
    playerCam.cameraPos.x -= 0.05f * playerCam.cameraFront.x;
    playerCam.cameraPos.y -= 0.05f * playerCam.cameraFront.y;
    playerCam.cameraPos.z -= 0.05f * playerCam.cameraFront.z;
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
  {
    playerCam.cameraPos.x += 0.05f * playerCam.cameraRight.x;
    playerCam.cameraPos.y += 0.05f * playerCam.cameraRight.y;
    playerCam.cameraPos.z += 0.05f * playerCam.cameraRight.z;
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
  {
    playerCam.cameraPos.x -= 0.05f * playerCam.cameraRight.x;
    playerCam.cameraPos.y -= 0.05f * playerCam.cameraRight.y;
    playerCam.cameraPos.z -= 0.05f * playerCam.cameraRight.z;
  }
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
  {
    playerCam.cameraPos.x += 0.05f * playerCam.cameraUp.x;
    playerCam.cameraPos.y += 0.05f * playerCam.cameraUp.y;
    playerCam.cameraPos.z += 0.05f * playerCam.cameraUp.z;
  }
  if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
  {
    playerCam.cameraPos.x -= 0.05f * playerCam.cameraUp.x;
    playerCam.cameraPos.y -= 0.05f * playerCam.cameraUp.y;
    playerCam.cameraPos.z -= 0.05f * playerCam.cameraUp.z;
  }
  if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
  {
    playerCam.yaw -= xsens;
  }
  if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
  {
    playerCam.yaw += xsens;
  }
  if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && playerCam.pitch < 80.0f)
  {
    playerCam.pitch += ysens;
  }
  if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && playerCam.pitch > -80.0f)
  {
    playerCam.pitch -= ysens;
  }
}

int glInit()
{
  glfwSetErrorCallback(errorCallback);
  if (!glfwInit())
  {
    printf("GLFW FAILED TO INIT\n");
    return 0;
  }
 
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
  session.window = glfwCreateWindow(800, 600, "Hello, World!", NULL, NULL);
  if (!session.window)
  {
    printf("WINDOW CREATION FAILED\n");
    return 0;
  }
  printf("WINDOW :%d\n", session.window);
  glfwMakeContextCurrent(session.window);
  
  glfwSetFramebufferSizeCallback(session.window, frameBufferSizeCallback);
  GLenum err = glewInit();
  if (err != GLEW_OK)
  {
    printf("GLEW INIT FAILED: %s\n", glewGetErrorString(err));
    return 0;
  }

  glViewport(0, 0, 800, 600);
  printf("SUCCESS!\n");
  return 1;
}

vec3f cubePositions[2] =
{
  {0.0f, 0.0f, 0.0f},
  {2.0f, 3.0f, 0.0f}
};

int main(int argc, char** argv)
{
  if (!glInit())
  {
    printf("--CLOSING PROGRAM--");
    return 0;
  }

	mat4 view = {0};
	mat4 model = {0};
	mat4 model2 = {0};
	mat4 projection = perspectiveMat4(radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	object* cubeOne;
	cubeOne = (object*)malloc(sizeof(object));
	objectInit(cubeOne, "shaders/shaderSource.glsl", 
						 "textures/tex.jpg", vertices, indices,
						 120, 36, &view, &model);
	object* cubeTwo;
	cubeTwo = (object*)malloc(sizeof(object));
	objectInit(cubeTwo, "shaders/shaderSource.glsl",
						 "textures/tex.png", vertices, indices,
						 120, 36, &view, &model2);

  playerCam.cameraPos   = (vec3f){0.0f, 0.0f, 3.0f};
  playerCam.cameraFront = (vec3f){0.0f, 0.0f, -1.0f};
  playerCam.cameraUp    = (vec3f){0.0f, 1.0f, 0.0f};
  playerCam.cameraRight = vec3fCross(playerCam.cameraFront, playerCam.cameraUp);
  playerCam.yaw = -90.0f;
  playerCam.pitch = 0.0f;

  while (!glfwWindowShouldClose(session.window))
  {

    // --   INPUT HANDLING   -- //

    getInput(session.window);

    // --       RENDER       -- //
    

    playerCam.cameraRight = vec3fCross(playerCam.cameraFront, playerCam.cameraUp);
    vec3f direction;
    direction.x = cos(radians(playerCam.yaw)) * cos(radians(playerCam.pitch));
    direction.y = sin(radians(playerCam.pitch));
    direction.z = sin(radians(playerCam.yaw)) * cos(radians(playerCam.pitch));
    playerCam.cameraFront = vec3fNormalize(direction);

    view = lookMat4(
      playerCam.cameraPos, 
      vec3fAdd(playerCam.cameraPos, playerCam.cameraFront), 
      playerCam.cameraUp);
   
    model = identityMat4();
    vec3f axis = {0.5f, 1.0f, 0.0f};
    model = mat4Rotate(model, radians(50.0f), axis);
		vec3f t = {1.0f, 1.0f, 10.0f};
		model2 = mat4Rotate(model2, radians(70.0f), axis);
		model2 = mat4Multiply(translateMat4(model2, t), model2);

    renderClear();
    objectDraw(cubeOne, projection);
		objectDraw(cubeTwo, projection);

    // --    SWAP BUFFERS    -- //

    glfwSwapBuffers(session.window);
    glfwPollEvents();
  }
	objectDestroy(cubeOne);
	objectDestroy(cubeTwo);
	free(cubeOne);
	free(cubeTwo);
  glfwTerminate();
  return 1;
}  
