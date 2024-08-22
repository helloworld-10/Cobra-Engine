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
#include <vector>
#include "Model.h"
#include "Renderer.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(2520, 1680, "Cobra", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    
    const std::string fname = "blending_transparent_window.png";
    const std::string objname = "C:\\Users\\Rajit\\source\\repos\\Cobra\\Cobra\\cube.txt";
    Mesh* mesh = MeshBuilder::loadFromObj(&objname, &fname);
    Shader s("C:\\Users\\Rajit\\source\\repos\\Cobra\\Cobra\\vertex.glsl", "C:\\Users\\Rajit\\source\\repos\\Cobra\\Cobra\\frag.glsl");
    Model m;
    m.m = mesh;        
    /*for (int i = -4; i <4; i++) {
        for (int j = -1; j < 1; j++) {
            for (int k = -4; k < 4; k++) {
                Transform transform;
                transform.scale = { 0.7,0.7,0.7 };
                transform.position = { 14 * i,14 * k,14*j };
                m.t.push_back(transform);
            }
        }
    }*/
    Transform transform;
    transform.scale = { 2,2,2 };
    transform.position = { 0,-5,0 };
    m.t.push_back(transform);
    Renderer renderer;
    renderer.initRenderer();

    while (!glfwWindowShouldClose(window))
    {
        renderer.Render(m);   
    }
    glfwTerminate();
    return 0;
}