#ifndef _OBJECT
#define _OBJECT

#include "render.h"
#include "maths.h"

struct object
{
	mat4* view;
	mat4* model;
	renderer* r;
	float* vertices;
	unsigned int* indices;
	int vertexCount;
	int indexCount;
};
typedef struct object object;

void objectInit(object* obj, const char* shaderPath, const char* texturePath,
								float* vertices, unsigned int* indices, int vertexCount, int indexCount,
								mat4* view, mat4* model);
void objectDraw(object* obj, mat4 proj);
void objectDestroy(object* obj);

#endif
