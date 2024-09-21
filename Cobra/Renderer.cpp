#include "Renderer.h"
#include <GLFW/glfw3.h>
#include "Application.h"
#include <iostream>


float yaw = -90.0f;
float pitch = 0;
float roll = 0;
float fov = 45;
float prevChangeY = 0;
float prevChangeX = 0;
float prevScroll = 0;
void Renderer::initRenderer() {

	shader = new Shader("C:\\Users\\Rajit\\source\\repos\\Cobra\\Cobra\\vertex.glsl", "C:\\Users\\Rajit\\source\\repos\\Cobra\\Cobra\\frag.glsl");
	glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glBlendFuncSeparate(GL_SRC1_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
	glCullFace(GL_BACK);
    glClearColor(1, 0, 0, 1);
}




void Renderer::Render(ComponentManager* manager)
{
    
    findCamera(manager);
   
    std::vector<entity> entities = manager->getEntities();
    
    for (entity entity : entities) {

        if (manager->hasComponent<MeshComponent>(entity)) {
            meshes[manager->getComponent<MeshComponent>(entity)].push_back(*(manager->getComponent<TransformComponent>(entity)));
        }
        if (manager->hasComponent<PointLightComponent>(entity)) {
            lights.push_back(*manager->getComponent<PointLightComponent>(entity));
            lightTransforms.push_back(*manager->getComponent<TransformComponent>(entity));
        }
        if (manager->hasComponent<DirectionalLightComponent>(entity)) {
            sun = manager->getComponent<DirectionalLightComponent>(entity);
        }
    }

    for (const auto& mesh : meshes) {
        
        Renderer::Render(mesh.first, mesh.second);
    }
    
    meshes.clear();
    lights.clear();
    lightTransforms.clear();
    
}


void Renderer::Render(std::shared_ptr<MeshComponent> mesh, std::vector<TransformComponent> transforms)
{
    std::vector<glm::mat4> transform;
        
        for (int i = 0; i < transforms.size(); i++) {
            transform.push_back(glm::mat4(1.0));
            transform[i] = glm::scale(transform[i], transforms[i].scale);
            transform[i] = glm::translate(transform[i], transforms[i].position);
            //add rotation with quaternion
        }
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glActiveTexture(GL_TEXTURE0); // 
    
    glBindTexture(GL_TEXTURE_2D, mesh->m->texture.id);

    glBindVertexArray(mesh->m->VAO);
    
    // vertex attributes
    
    unsigned int transformbuffer;
    glGenBuffers(1, &transformbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, transformbuffer);
    glBufferData(GL_ARRAY_BUFFER, transform.size() * sizeof(glm::mat4), &transform[0], GL_STATIC_DRAW);
    std::size_t vec4Size = sizeof(glm::vec4);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(1 * vec4Size));
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size));
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size));

    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);
    glBindVertexArray(0);
    glDeleteBuffers(1, &transformbuffer);
    glBindVertexArray(mesh->m->VAO);


    (*shader).use();

    float speed = 0.2f;
    glm::vec3 right = { 1,0,0 };
    glm::vec3 up = { 0,1,0 };
    glm::vec3 forward = { 0,0,1 };
    if (Application::isKeyPressed(GLFW_KEY_W)) {

        camera->position += speed * camera->camFront;
    }
    if (Application::isKeyPressed(GLFW_KEY_A)) {
        camera->position -= speed * glm::cross(camera->camFront, camera->camUp);
    }
    if (Application::isKeyPressed(GLFW_KEY_S)) {
        camera->position -= speed * camera->camFront;
    }
    if (Application::isKeyPressed(GLFW_KEY_D)) {
        camera->position += speed * glm::cross(camera->camFront, camera->camUp);
    }
    if (Application::isKeyPressed(GLFW_KEY_LEFT_SHIFT)) {
        camera->position -= speed * up;
    }
    if (Application::isKeyPressed(GLFW_KEY_SPACE)) {
        camera->position += speed * up;
    }
    if (Application::isKeyPressed(GLFW_KEY_ESCAPE)) {
        Application::closeWindow();
    }
    camera->camFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    camera->camFront.y = sin(glm::radians(pitch));
    camera->camFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    if (Application::getXChange() != prevChangeX) {
        yaw += 0.09 * Application::getXChange();
        prevChangeX = Application::getXChange();
    }
    if (Application::getYChange() != prevChangeY) {
        pitch += 0.09 * Application::getYChange();
        prevChangeY = Application::getYChange();
    }

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    if (Application::getScrollYPos() != prevScroll) {
        fov -= (float)Application::getScrollYPos() / 20.0f;
        prevScroll = Application::getScrollYPos();
    }
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 90.0f)
        fov = 45.0f;
    camera->projection = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 1000.0f);
    camera->camFront = glm::normalize(camera->camFront);

    glm::mat4 view = glm::lookAt(camera->position, camera->position + camera->camFront, camera->camUp);
    shader->setMat4("view", view);
    shader->setMat4("projection", camera->projection);
    float lightX = sin(glfwGetTime()) * 10.0;
    float lightY = sin(glfwGetTime()) * 10.0 * cos(glfwGetTime());
    float lightZ = cos(glfwGetTime()) * 10.0;
    glm::vec3 lightPos(lightX, lightY, lightZ);
    //glm::vec3 lightColor(0.894, 0.721, 0.043);
    float r = glm::max(glm::sin(glfwGetTime()), 0.2);
    float g = glm::max(glm::cos(glfwGetTime()), 0.2);
    float b = glm::max(glm::sin(glfwGetTime()) * glm::sin(glfwGetTime()), 0.2);
    glm::vec3 lightColor(r, g, b);

    (*shader).setVec3("camPos", camera->position);
    shader->setPointLightArray("pointLights", lights,lightTransforms);
    shader->setDirLight("dirLight", *sun);
    glDrawElementsInstanced(GL_TRIANGLES, static_cast<unsigned int>(mesh->m->indices.size()), GL_UNSIGNED_INT, 0, transform.size());
    glBindVertexArray(0);
    /* Swap front and back buffers */
    glfwSwapBuffers(glfwGetCurrentContext());
    glfwPollEvents();
}

void Renderer::findCamera(ComponentManager* manager){
    camera = (manager->getComponent<CameraComponent>(0));
}




//void Renderer::Render(Model model)
//{
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    
//    std::vector<glm::mat4> transforms;
//    
//    for (int i = 0; i < model.t.size(); i++) {
//        transforms.push_back(glm::mat4(1.0));
//        transforms[i] = glm::scale(transforms[i], model.t[i].scale);
//        transforms[i] = glm::translate(transforms[i], model.t[i].position);
//        //add rotation with quaternion
//    }
//
//
//    glActiveTexture(GL_TEXTURE0); // 
//    glBindTexture(GL_TEXTURE_2D, model.m->texture.id);
//    glBindVertexArray(model.m->VAO);
//        // vertex attributes
//        unsigned int transformbuffer;
//    glGenBuffers(1, &transformbuffer);
//    glBindBuffer(GL_ARRAY_BUFFER, transformbuffer);
//    glBufferData(GL_ARRAY_BUFFER, transforms.size() * sizeof(glm::mat4), &transforms[0], GL_STATIC_DRAW);
//        std::size_t vec4Size = sizeof(glm::vec4);
//        glEnableVertexAttribArray(3);
//        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
//        glEnableVertexAttribArray(4);
//        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(1 * vec4Size));
//        glEnableVertexAttribArray(5);
//        glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size));
//        glEnableVertexAttribArray(6);
//        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size));
//
//        glVertexAttribDivisor(3, 1);
//        glVertexAttribDivisor(4, 1);
//        glVertexAttribDivisor(5, 1);
//        glVertexAttribDivisor(6, 1);
//        glBindVertexArray(0);
//        glDeleteBuffers(1, &transformbuffer);
//    
//        glBindVertexArray(model.m->VAO);
//
//
//
//    (*shader).use();
//
//
//    float speed = 0.2f;
//    glm::vec3 right = { 1,0,0 };
//    glm::vec3 up = { 0,1,0 };
//    glm::vec3 forward = { 0,0,1 };
//    if (Application::isKeyPressed(GLFW_KEY_W)) {
//        
//        camera.position += speed* camera.camFront;
//    }
//    if (Application::isKeyPressed(GLFW_KEY_A)) {
//        camera.position -= speed* glm::cross(camera.camFront,camera.camUp);
//    }
//    if (Application::isKeyPressed(GLFW_KEY_S)) {
//        camera.position -= speed * camera.camFront;
//    }
//    if (Application::isKeyPressed(GLFW_KEY_D)) {
//        camera.position += speed * glm::cross(camera.camFront, camera.camUp);
//    }
//    if (Application::isKeyPressed(GLFW_KEY_LEFT_SHIFT)) {
//        camera.position -= speed * up;
//    }
//    if (Application::isKeyPressed(GLFW_KEY_SPACE)) {
//        camera.position += speed * up;
//    }
//    if (Application::isKeyPressed(GLFW_KEY_ESCAPE)) {
//        Application::closeWindow();
//    }
//    camera.camFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
//    camera.camFront.y = sin(glm::radians(pitch));
//    camera.camFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
//    if (Application::getXChange() != prevChangeX) {
//        yaw += 0.09 * Application::getXChange();
//        prevChangeX = Application::getXChange();
//    }
//    if (Application::getYChange() != prevChangeY) {
//        pitch += 0.09*Application::getYChange();
//        prevChangeY = Application::getYChange();
//    }
//
//    if (pitch > 89.0f)
//        pitch = 89.0f;
//    if (pitch < -89.0f)
//        pitch = -89.0f;
//
//    if (Application::getScrollYPos() != prevScroll) {
//        fov -= (float)Application::getScrollYPos() / 20.0f;
//        prevScroll = Application::getScrollYPos();
//    }
//    if (fov < 1.0f)
//        fov = 1.0f;
//    if (fov > 90.0f)
//        fov = 45.0f;
////std::cout << (float)Application::getYChange()<< std::endl;
//    camera.projection = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 1000.0f);
//    camera.camFront = glm::normalize(camera.camFront);
//    //camera.camRight = glm::normalize(glm::cross(camera.camUp, up));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
//    //camera.camUp = glm::normalize(glm::cross(camera.camRight, camera.camFront));
//
//
//    glm::mat4 view = glm::lookAt(camera.position, camera.position+camera.camFront, camera.camUp);
//    shader->setMat4("view", view);
//    shader->setMat4("projection", camera.projection);
//    float lightX = sin(glfwGetTime()) * 10.0;
//    float lightY = sin(glfwGetTime()) * 10.0* cos(glfwGetTime());
//    float lightZ = cos(glfwGetTime()) * 10.0;
//    glm::vec3 lightPos(lightX ,lightY, lightZ);
//    //glm::vec3 lightColor(0.894, 0.721, 0.043);
//    float r = glm::max(glm::sin(glfwGetTime()),0.2);
//    float g = glm::max(glm::cos(glfwGetTime()),0.2);
//    float b = glm::max(glm::sin(glfwGetTime()) * glm::sin(glfwGetTime()),0.2);
//    glm::vec3 lightColor(r,g,b);
//
//    (*shader).setVec3("lightPos", lightPos);
//    (*shader).setVec3("camPos", camera.position);
//    shader->setVec3("lightColor", lightColor);
//    glDrawElementsInstanced(GL_TRIANGLES, static_cast<unsigned int>(model.m->indices.size()), GL_UNSIGNED_INT, 0,model.t.size());
//    glBindVertexArray(0);
//    /* Swap front and back buffers */
//    glfwSwapBuffers(glfwGetCurrentContext());
//    glfwPollEvents();
//}
