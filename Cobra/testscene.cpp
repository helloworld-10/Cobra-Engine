#include "testscene.h"

void testscene::start()
{
    const std::string fname = "blank.png";
    const std::string objname = "C:\\Users\\Rajit\\source\\repos\\Cobra\\Cobra\\dragon.txt";
    Mesh* mesh = MeshBuilder::loadFromObj(&objname, &fname);
    Shader s("C:\\Users\\Rajit\\source\\repos\\Cobra\\Cobra\\vertex.glsl", "C:\\Users\\Rajit\\source\\repos\\Cobra\\Cobra\\frag.glsl");

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

    PointLightComponent p;
    p.attenuation = { 1,0.14,.07 };
    p.color = { 0.894, 0.721, 0.043 };

    

    DirectionalLightComponent d;
    d.color = { 0,0,1 };
    d.direction = { 0.5,0.5,0 };
    manager.registerComponent<MeshComponent, TransformComponent, CameraComponent,DirectionalLightComponent,PointLightComponent>(m,t,camera,d,p);
    //for (const auto& elem : manager.componentID)
    //{
    //    std::cout << elem.first << " " << elem.second << "\n";
    //}
 
    manager.addComponent<MeshComponent>(1, std::make_shared<MeshComponent>(m));
    manager.addComponent<TransformComponent>(1, std::make_shared<TransformComponent>(t));
    manager.addComponent<CameraComponent>(0, std::make_shared<CameraComponent>(camera));
    manager.addComponent<DirectionalLightComponent>(2, std::make_shared<DirectionalLightComponent>(d));
    for (int i = 3; i < 13; i++) {
        manager.addComponent<PointLightComponent>(i, std::make_shared<PointLightComponent>(p));
        TransformComponent lt;
        lt.position = { 10*(sin(i*0.5)),10*(cos(i*0.5)),0};
        manager.addComponent<TransformComponent>(i, std::make_shared<TransformComponent>(lt));
    }
    renderer.initRenderer();
    
    
}

void testscene::update()
{
    
    renderer.Render(&manager);
}

void testscene::close()
{
}
