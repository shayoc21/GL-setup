# OPENGL SETUP
## Boilerplate setup for Open-GL in C.

The goal of this project is to help me get through the boring and sometimes complex OpenGL setup.
---
This project:
	- Creates a window using GLFW
	- Uses GLEW to load GL functions
	- Uses my entirely custom math "library", rather than something like cglm
	- Uses a "renderer" struct and functions to abstract the raw GL function calls
	- Has an "object" struct for creating multiple objects, with different shaders, vertices, etc.
	- Allows for both "stationary" and "camerabound" objects, for objects that stay in place, and follow the camera's movement respectively
	- Has a "camera" struct to allow for multiple cameras

Right now it is hardly readable, uses a lot of janky hardcoding, and some not-so-well designed math functions.
This will all improve though.
TODO:
	- Fully custom .obj file loader, for blender models
	- Basic lighting engine
	- Clean up code, massively
	- Fix indentation
	- Add some inline documentation // though not really necessary as this is relatively simple, it's still good practice
