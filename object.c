#include "object.h"

void objectInit(object* obj,
								const char* shaderPath,
								const char* texturePath,
								float* vertices, 
								unsigned int* indices, 
								int vertexCount, 
								int indexCount,
								mat4* view,
								mat4* model)
{
	obj->vertexCount = vertexCount;
	obj->indexCount = indexCount;
	obj->vertices = (float*)malloc(vertexCount*sizeof(float));
	obj->indices = (unsigned int*)malloc(indexCount*sizeof(unsigned int));

	obj->r = (renderer*)malloc(sizeof(renderer));
	renderInit(obj->r, shaderPath, texturePath, vertexCount, indexCount, vertices, indices);
	
	obj->view = view;
	obj->model = model;
}

void objectDraw(object* obj, mat4 proj)
{
	glUseProgram(obj->r->shaderProgram);
	int modelLocation = glGetUniformLocation(obj->r->shaderProgram, "model");
	int viewLocation = glGetUniformLocation(obj->r->shaderProgram, "view");
	int projectionLocation = glGetUniformLocation(obj->r->shaderProgram, "projection");
	glUniformMatrix4fv(viewLocation, 1, GL_TRUE, obj->view->m);
	glUniformMatrix4fv(modelLocation, 1, GL_TRUE, obj->model->m);
	glUniformMatrix4fv(projectionLocation, 1, GL_TRUE, proj.m);
	renderDraw(obj->r, obj->indexCount);
}

void objectDestroy(object* obj)
{
	free(obj->vertices);
	free(obj->indices);
	free(obj->r);
	renderDestroy(obj->r);
}
	
