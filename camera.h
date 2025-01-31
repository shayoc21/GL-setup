#ifndef _CAMERA
#define _CAMERA

#include "maths.h"

struct Camera
{
	mat4 view;
	mat4 projection;
	vec3f position;
	vec3f direction;
	vec3f front;
	vec3f right;
	vec3f up;
	float fov;
	float yaw;
	float pitch;
};
typedef struct Camera Camera;

extern Camera* currentCamera;
void cameraInit(Camera* camera, vec3f position, vec3f direction, float fov);

#endif

