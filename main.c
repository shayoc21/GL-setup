#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include "maths.h"
#include "render.h"
#include "object.h"
#include "camera.h"

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

float xsens = 0.45f;
float ysens = 0.45f;

struct 
{
  GLFWwindow* window;
} session;

int pPressed = 0;
int oPressed = 0;

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

		printf("-- PRINTING DIAGNOSTICS --\n\
						 - POS =  %f, %f, %f 	  - \n\
						 - DIR =  %f, %f, %f    - \n\
						--------------------------\n", 
						currentCamera->position.x, currentCamera->position.y, currentCamera->position.z,
						currentCamera->direction.x, currentCamera->direction.y, currentCamera->direction.z); 
		printf("Front: (%f, %f, %f)\n", currentCamera->front.x, currentCamera->front.y, currentCamera->front.z);
		printf("Right: (%f, %f, %f)\n", currentCamera->right.x, currentCamera->right.y, currentCamera->right.z);
		printf("Up: (%f, %f, %f)\n", currentCamera->up.x, currentCamera->up.y, currentCamera->up.z);	
  }
  if (glfwGetKey(window, GLFW_KEY_P) == GLFW_RELEASE)
  {
    pPressed = 0;
  }
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
  {
		currentCamera->position.x += 0.05f * currentCamera->front.x;
		currentCamera->position.y += 0.05f * currentCamera->front.y;
		currentCamera->position.z += 0.05f * currentCamera->front.z;
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
  {
		currentCamera->position.x -= 0.05f * currentCamera->front.x;
		currentCamera->position.y -= 0.05f * currentCamera->front.y;
		currentCamera->position.z -= 0.05f * currentCamera->front.z;
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
  {
		currentCamera->position.x += 0.05f * currentCamera->right.x;
		currentCamera->position.y += 0.05f * currentCamera->right.y;
		currentCamera->position.z += 0.05f * currentCamera->right.z;
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
  {
		currentCamera->position.x -= 0.05f * currentCamera->right.x;
		currentCamera->position.y -= 0.05f * currentCamera->right.y;
		currentCamera->position.z -= 0.05f * currentCamera->right.z;
  }
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
  {
		currentCamera->position.x += 0.05f * currentCamera->up.x;
		currentCamera->position.y += 0.05f * currentCamera->up.y;
		currentCamera->position.z += 0.05f * currentCamera->up.z;
  }
  if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
  {
		currentCamera->position.x -= 0.05f * currentCamera->up.x;
		currentCamera->position.y -= 0.05f * currentCamera->up.y;
		currentCamera->position.z -= 0.05f * currentCamera->up.z;
  }
  if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
  {
    currentCamera->yaw -= xsens;
  }
  if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
  {
    currentCamera->yaw += xsens;
  }
  if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && currentCamera->pitch < 80.0f)
  {
    currentCamera->pitch += ysens;
  }
  if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && currentCamera->pitch > -80.0f)
  {
    currentCamera->pitch -= ysens;
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

int main(int argc, char** argv)
{
  if (!glInit())
  {
    printf("--CLOSING PROGRAM--");
    return 0;
  }
	
	Camera camera = {0};
	currentCamera = &camera;
	
	vec3f position = {3.0f, 0.0f,  0.0f};
	vec3f direction = {0.0f, 0.0f, -1.0f};
	vec3f up = {0.0f, 1.0f, 0.0f};
	cameraInit(currentCamera, position, direction, 60.0f);

	Camera camera2 = {0};
	currentCamera = &camera2;
	cameraInit(currentCamera, position, direction, 60.0f);
	currentCamera = &camera;

	mat4 model = {0};
	mat4 model2 = {0};
	mat4 model3 = {0};
	object* cubeOne;
	cubeOne = (object*)malloc(sizeof(object));
	objectInit(cubeOne, "shaders/shaderSource.glsl", 
						 "textures/tex.jpg", vertices, indices,
						 120, 36, &model, 1);
	object* cubeTwo;
	cubeTwo = (object*)malloc(sizeof(object));
	objectInit(cubeTwo, "shaders/shaderSource.glsl",
						 "textures/tex.png", vertices, indices,
						 120, 36, &model2, 1);
	object* cubeThree;
	cubeThree = (object*)malloc(sizeof(object));
	objectInit(cubeThree, "shaders/shaderSource.glsl",
						 "textures/tex.png", vertices, indices,
						 120, 36, &model3, 0);

  while (!glfwWindowShouldClose(session.window))
  {

    // --   INPUT HANDLING   -- //

    getInput(session.window);
		if (glfwGetKey(session.window, GLFW_KEY_O) == GLFW_PRESS && !oPressed)
		{
			currentCamera = (currentCamera == &camera) ? &camera2 : &camera;
			oPressed = 1;
		}
		if (glfwGetKey(session.window, GLFW_KEY_O) == GLFW_RELEASE)
		{
			oPressed = 0;
		}

    // --       RENDER       -- //

    currentCamera->right = vec3fNormalize(vec3fCross(currentCamera->front, up));
    vec3f direction;
    direction.x = cos(radians(currentCamera->yaw)) * cos(radians(currentCamera->pitch));
    direction.y = sin(radians(currentCamera->pitch));
    direction.z = sin(radians(currentCamera->yaw)) * cos(radians(currentCamera->pitch));
    currentCamera->front = vec3fNormalize(direction);
		currentCamera->up = vec3fCross(currentCamera->front, currentCamera->right);
		currentCamera->up.x = -currentCamera->up.x;
		currentCamera->up.y = -currentCamera->up.y;
		currentCamera->up.z = -currentCamera->up.z;
		currentCamera->up = vec3fNormalize(currentCamera->up);

		currentCamera->view = lookMat4(currentCamera->position, 
																	 vec3fAdd(currentCamera->position, currentCamera->front),
																	 currentCamera->up);

    model = identityMat4();
    vec3f axis = {0.5f, 1.0f, 0.0f};
    model = mat4Rotate(model, radians(50.0f), axis);
		vec3f t = {1.0f, 1.0f, 10.0f};
		model2 = mat4Rotate(model2, radians(70.0f), axis);
		model2 = mat4Multiply(translateMat4(model2, t), model2);

		vec3f objectPos = 
		{
			currentCamera->position.x + currentCamera->front.x*5.0f,
			currentCamera->position.y + currentCamera->front.y*5.0f,
			currentCamera->position.z + currentCamera->front.z*5.0f
		};
		model3 = translateMat4(model3, objectPos);

    renderClear();
    objectDraw(cubeOne, currentCamera->projection);
		objectDraw(cubeTwo, currentCamera->projection);
		objectDraw(cubeThree, currentCamera->projection);

    // --    SWAP BUFFERS    -- //

    glfwSwapBuffers(session.window);
    glfwPollEvents();
  }
	objectDestroy(cubeOne);
	objectDestroy(cubeTwo);
	objectDestroy(cubeThree);
  glfwTerminate();
  return 1;
}  
