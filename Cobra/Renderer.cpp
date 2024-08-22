#include "Renderer.h"
#include <GLFW/glfw3.h>




void Renderer::initRenderer() {
	camera.position = glm::vec3(0, 10.0, 10);
	camera.camFront = glm::vec3(0.0, 0.0, 0.0);
	camera.camUp = glm::vec3(0.0, 1.0, 0.0);
    camera.projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	shader = new Shader("C:\\Users\\Rajit\\source\\repos\\Cobra\\Cobra\\vertex.glsl", "C:\\Users\\Rajit\\source\\repos\\Cobra\\Cobra\\frag.glsl");
	glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glBlendFuncSeparate(GL_SRC1_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
	glCullFace(GL_BACK);
    glClearColor(1, 1, 1, 1);
}


void Renderer::Render(Model model)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    std::vector<glm::mat4> transforms;
    
    for (int i = 0; i < model.t.size(); i++) {
        transforms.push_back(glm::mat4(1.0));
        transforms[i] = glm::scale(transforms[i], model.t[i].scale);
        transforms[i] = glm::translate(transforms[i], model.t[i].position);
        //add rotation with quaternion
    }
    unsigned int transformbuffer;
    glGenBuffers(1, &transformbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, transformbuffer);
    glBufferData(GL_ARRAY_BUFFER, transforms.size() * sizeof(glm::mat4), &transforms[0], GL_STATIC_DRAW);

    glActiveTexture(GL_TEXTURE0); // 
    glBindTexture(GL_TEXTURE_2D, model.m->texture.id);
    glBindVertexArray(model.m->VAO);
        // vertex attributes
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
        //glBindBuffer(GL_ARRAY_BUFFER, 0);
        
    




    (*shader).use();


    camera.position.x = sin(glfwGetTime()) * 60;
    camera.position.z = cos(glfwGetTime()) * 60;

    glm::mat4 view = glm::lookAt(camera.position, glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
    shader->setMat4("view", view);
    shader->setMat4("projection", camera.projection);
    glm::vec3 lightPos(0.0 ,10.0,5.0);
    glm::vec3 lightColor(0.5,0.1,0.1);
    (*shader).setVec3("lightPos", lightPos);
    (*shader).setVec3("camPos", camera.position);
    shader->setVec3("lightColor", lightColor);
    glDrawElementsInstanced(GL_TRIANGLES, static_cast<unsigned int>(model.m->indices.size()), GL_UNSIGNED_INT, 0,model.t.size());
    glBindVertexArray(0);
    /* Swap front and back buffers */
    glfwSwapBuffers(glfwGetCurrentContext());

    /* Poll for and process events */
    glfwPollEvents();

}
