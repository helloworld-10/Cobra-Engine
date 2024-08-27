#include "Application.h"
#include <iostream>

static GLFWwindow* window;
static Scene* scene;
void Application::start()
{

    /* Initialize the library */
    if (!glfwInit()) {
        return;
    }
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(2520, 1680, "Cobra", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);


}

void Application::addScene(Scene* newScene)
{
    scene = newScene;
    scene->start();
}

Scene* Application::swapScene(Scene* newScene)
{
    Scene* out = scene;
    scene->close();
    scene = newScene;
    
	return out;
}

Scene* Application::getScene()
{
	return scene;
	
}

void Application::run()
{
    while (!glfwWindowShouldClose(window))
    {
        scene->update();
    }
}

void Application::closeWindow() {
    scene->close();
    glfwTerminate();
}
