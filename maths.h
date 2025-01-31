#ifndef _MATH
#define _MATH
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define PI 3.141592653589793

struct vec3f
{
  float x, y, z;
};
typedef struct vec3f vec3f;

struct mat4
{
  float m[16];
};
typedef struct mat4 mat4;

void printMat4(const mat4 matrix);
mat4 identityMat4();
mat4 mat4Multiply(mat4 mat1, mat4 mat2);
mat4 mat4Rotate(mat4 matrix, float theta, vec3f axis);
mat4 orthoMat4(float left, float right, float bottom, float top, float near, float far);
mat4 perspectiveMat4(float fov, float aspectRatio, float near, float far);
mat4 translateMat4(mat4 matrix, vec3f vector);
mat4 lookMat4(vec3f cameraPos, vec3f cameraTarget, vec3f cameraUp);
vec3f vec3fSubtract(vec3f vec1, vec3f vec2);
vec3f vec3fAdd(vec3f vec1, vec3f vec2);
vec3f vec3fNormalize(vec3f vector);
vec3f vec3fCross(vec3f vec1, vec3f vec2);
float vec3fLength(vec3f* vector);
float vec3fDot(vec3f vec1, vec3f vec2);

float radians(float degrees);

#endif 

