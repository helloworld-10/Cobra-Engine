#include "testscene.h"

void testscene::start()
{
    const std::string fname = "blank.png";
    const std::string objname = "C:\\Users\\Rajit\\source\\repos\\Cobra\\Cobra\\dragon.txt";
    Mesh* mesh = MeshBuilder::loadFromObj(&objname, &fname);
    Shader s("C:\\Users\\Rajit\\source\\repos\\Cobra\\Cobra\\vertex.glsl", "C:\\Users\\Rajit\\source\\repos\\Cobra\\Cobra\\frag.glsl");
    //model.m = mesh;
    //for (int i = -4; i < 4; i++) {
    //    for (int j = -1; j < 1; j++) {
    //        for (int k = -4; k < 4; k++) {
    //            Transform transform;
    //            transform.scale = { 0.7,0.7,0.7 };
    //            transform.position = { 14 * i,14 * k,14 * j };
    //            model.t.push_back(transform);
    //        }
    //    }
    //}
    Transform transform;
    transform.scale = { 2,2,2 };
    transform.position = { 0,-5,0 };
    model.t.push_back(transform);
    
    
    
    
    MeshComponent m;
    m.m = mesh;
    TransformComponent t;
    t.position = transform.position;
    t.scale = transform.scale;
    CameraComponent camera;
    camera.position = glm::vec3(0, 10.0, 10);
    camera.camFront = glm::vec3(0.0, 0.0, -1.0);
    camera.camUp = glm::vec3(0.0, 1.0, 0.0);
    camera.projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    manager.registerComponent<MeshComponent, TransformComponent, CameraComponent>(m,t,camera);
    for (const auto& elem : manager.componentID)
    {
        std::cout << elem.first << " " << elem.second << "\n";
    }
 
    manager.addComponent<MeshComponent>(1, std::make_shared<MeshComponent>(m));
    manager.addComponent<TransformComponent>(1, std::make_shared<TransformComponent>(t));
    manager.addComponent<CameraComponent>(0, std::make_shared<CameraComponent>(camera));
    renderer.initRenderer();
    
    
}

void testscene::update()
{
    
    renderer.Render(&manager);
}

void testscene::close()
{
}
