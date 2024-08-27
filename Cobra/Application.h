#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Scene.h"
class Application {
public:
	static void start();
	static void addScene(Scene* newScene);
	static Scene* swapScene(Scene* newScene);
	static Scene* getScene();
	static void run();
	static void closeWindow();
};