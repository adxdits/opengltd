#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include <GL/gl.h>
#include <iostream>

void onMouseClick(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double x, y;
        glfwGetCursorPos(window, &x, &y);
 float r = fmod((float)x, 256.0f) / 255.0f;
        float v = fmod((float)y, 256.0f) / 255.0f;
        float b = 0.0;
        glClearColor(r, v, b, 1.0);
        glfwPostEmptyEvent();
    }
}
enum class MODE
{
	MODE1,
	MODE2
};

MODE mode = MODE::MODE1;
void onMouseMove(GLFWwindow *window, double x, double y)
{
	int w , h;
	glfwGetWindowSize(window, &w, &h);
	float r = (float)x/w;
	float v = 0.0;
	float b = float(y)/h;
	glClearColor(r, v, b, 1.0);
    glfwPostEmptyEvent();
}
static const double FRAMERATE_IN_SECONDS = 1. / 30.;
static const float GL_VIEW_SIZE = 1.;
static float aspectRatio;
void onWindowResized(GLFWwindow* window,int width,int height)
{
 aspectRatio = width / (float) height;
 glViewport(0, 0, width, height);
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 if( aspectRatio > 1)
 {
 glOrtho(
 -GL_VIEW_SIZE / 2. * aspectRatio, GL_VIEW_SIZE / 2. * aspectRatio,
 -GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2., -1.0, 1.0);
 }
 else
 {
 glOrtho(
 -GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.,
 -GL_VIEW_SIZE / 2. / aspectRatio, GL_VIEW_SIZE / 2. / aspectRatio,
 -1.0,1.0);
 }
}

/* Error handling function */
void onError(int error, const char* description) {
	std::cout << "GLFW Error ("<<error<<") : " << description << std::endl;
}

int main() {
    // Initialize the library

    if (!glfwInit()) {
        return -1;
    }

    /* Callback to a function if an error is rised by GLFW */
	glfwSetErrorCallback(onError);

    // Create a windowed mode window and its OpenGL context
#ifdef __APPLE__
    // We need to explicitly ask for a 3.3 context on Mac
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
    GLFWwindow* window = glfwCreateWindow(1280, 720, "OpenGLTemplate", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

	// Intialize glad (loads the OpenGL functions)
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		return -1;
	}

	/*
	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		std::cout << "key pressed: " << key << ", " << scancode << std::endl;
	});
	*/

	/* Loop until the user closes the window */
	//glfwSetMouseButtonCallback(window, onMouseClick);
	    glfwSetCursorPosCallback(window, onMouseMove);
	while (!glfwWindowShouldClose(window))
	{
        // Rendering code

        // Clear the color buffer
        glClear(GL_COLOR_BUFFER_BIT);

        // Other rendering code...

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
		/* Get time (in second) at loop beginning */
		double startTime = glfwGetTime();

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

        // render exemple quad
        // glColor3f(1.0f, 0.0f, 0.0f);
        // glBegin(GL_QUADS);
        //     glVertex2f(-0.5f, -0.5f);
        //     glVertex2f(0.5f, -0.5f);
        //     glVertex2f(0.5f, 0.5f);
        //     glVertex2f(-0.5f, 0.5f);
        // glEnd();
        
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		/* Elapsed time computation from loop begining */
		double elapsedTime = glfwGetTime() - startTime;
		/* If to few time is spend vs our wanted FPS, we wait */
		if(elapsedTime < FRAMERATE_IN_SECONDS) 
		{
			glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS-elapsedTime);
		}
	}

    glfwTerminate();
    return 0;
}
