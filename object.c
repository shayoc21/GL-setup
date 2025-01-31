#include "object.h"

void objectInit(object* obj,
								const char* shaderPath,
								const char* texturePath,
								float* vertices, 
								unsigned int* indices, 
								int vertexCount, 
								int indexCount,
								mat4* model, int stationary)
{
	obj->vertexCount = vertexCount;
	obj->indexCount = indexCount;
	obj->vertices = (float*)malloc(vertexCount*sizeof(float));
	obj->indices = (unsigned int*)malloc(indexCount*sizeof(unsigned int));

	obj->r = (renderer*)malloc(sizeof(renderer));
	renderInit(obj->r, shaderPath, texturePath, vertexCount, indexCount, vertices, indices);
	
	obj->model = model;
	obj->STATIONARY = stationary;
}


void objectDraw(object* obj, mat4 proj)
{
	glUseProgram(obj->r->shaderProgram);
	int modelLocation = glGetUniformLocation(obj->r->shaderProgram, "model");
	int viewLocation = glGetUniformLocation(obj->r->shaderProgram, "view");
	int projectionLocation = glGetUniformLocation(obj->r->shaderProgram, "projection");
	glUniformMatrix4fv(viewLocation, 1, GL_TRUE, currentCamera->view.m);
	glUniformMatrix4fv(modelLocation, 1, GL_TRUE, obj->model->m);
	glUniformMatrix4fv(projectionLocation, 1, GL_TRUE, currentCamera->projection.m);

	if (!obj->STATIONARY)
	{
		vec3f objectPos = 
		{
			currentCamera->position.x + currentCamera->front.x*5.0f,
			currentCamera->position.y + currentCamera->front.y*5.0f,
			currentCamera->position.z + currentCamera->front.z*5.0f
		};
		mat4 rotationMatrix = identityMat4();
		float m[16] = 
		{
			currentCamera->right.x, currentCamera->up.x, currentCamera->front.x, 0,
			currentCamera->right.y, currentCamera->up.y, currentCamera->front.y, 0,
			currentCamera->right.z, currentCamera->up.z, currentCamera->front.z, 0,
			0.0f, 0.0f, 0.0f, 1.0f
		};
		memcpy(rotationMatrix.m, m, sizeof(m));
		mat4 mmodel = mat4Multiply(translateMat4(*obj->model, objectPos), rotationMatrix);
		glUniformMatrix4fv(modelLocation, 1, GL_TRUE, mmodel.m);
	}

	renderDraw(obj->r, obj->indexCount);
}

void objectDestroy(object* obj)
{
	free(obj->vertices);
	free(obj->indices);
	free(obj->r);
	renderDestroy(obj->r);
	free(obj);
}
