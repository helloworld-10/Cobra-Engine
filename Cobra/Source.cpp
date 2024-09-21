#pragma once
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Vertex.h"

#include "Mesh.h"
#include "MeshBuilder.h"
#include "Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Model.h"
#include "Renderer.h"
#include "Application.h"
#include "testscene.h"
#include "Scene.h"
#include "Component.h"
int main(void)
{

    Application::start();
    testscene test;
    Application::addScene(&test);
    Application::run();
    Application::closeWindow();
    

    return 0;
}