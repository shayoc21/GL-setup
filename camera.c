#include "camera.h"

Camera* currentCamera;

void cameraInit(Camera* camera, vec3f position, vec3f direction, float fov)
{
	camera->position = position;
	camera->direction = direction;
	camera->fov = fov;
	
	camera->up = (vec3f) {0.0f, 1.0f, 0.0f};
	camera->front = vec3fNormalize(direction);
	camera->right = vec3fCross(camera->front, camera->up);
	
	camera->view = identityMat4();
	camera->projection = perspectiveMat4(radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);

	float yaw = -90.0f;
	float pitch = 0;
}
