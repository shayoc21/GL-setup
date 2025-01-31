#ifndef _OBJECT
#define _OBJECT

#include "render.h"
#include "camera.h"

struct object
{
	mat4* model;
	renderer* r;
	float* vertices;
	unsigned int* indices;
	int vertexCount;
	int indexCount;
	int STATIONARY;
};
typedef struct object object;

void objectInit(object* obj, const char* shaderPath, const char* texturePath,
								float* vertices, unsigned int* indices, int vertexCount, int indexCount,
								 mat4* model, int stationary);
void objectDraw(object* obj, mat4 proj);
void objectDestroy(object* obj);
void objectRotate(object* obj);
void objectTranslate(object* obj);

#endif
