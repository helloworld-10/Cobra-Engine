#include "testscene.h"

void testscene::start()
{
    const std::string fname = "blank.png";
    const std::string objname = "C:\\Users\\Rajit\\source\\repos\\Cobra\\Cobra\\dragon.txt";
    MeshComponent m = MeshBuilder::loadFromObj(&objname, &fname);


    
    
    
    
    TransformComponent t;
    t.position = { 0,-5,0 };
    t.scale = { 2,2,2 };

    CameraComponent camera;
    camera.position = glm::vec3(0, 10.0, 10);
    camera.camFront = glm::vec3(0.0, 0.0, -1.0);
    camera.camUp = glm::vec3(0.0, 1.0, 0.0);
    camera.projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    PointLightComponent p;
    p.attenuation = { 1,0.14,.07 };
    p.color = { 0.894, 0.721, 0.043 };

    RigidBodyComponent rb;
    rb.mass = 0.01;


    std::shared_ptr<MeshComponent> mp = std::make_shared<MeshComponent>(m);

    DirectionalLightComponent d;
    d.color = { 0,0,1 };
    d.direction = { 0.5,0.5,0 };
    manager.registerComponent<MeshComponent, TransformComponent, CameraComponent,DirectionalLightComponent,PointLightComponent,RigidBodyComponent>(m,t,camera,d,p,rb);
    manager.addComponent<MeshComponent>(1, mp);
    manager.addComponent<TransformComponent>(1, std::make_shared<TransformComponent>(t));
    manager.addComponent<RigidBodyComponent>(1, std::make_shared<RigidBodyComponent>(rb));
    manager.addComponent<CameraComponent>(0, std::make_shared<CameraComponent>(camera));


    manager.addComponent<DirectionalLightComponent>(2, std::make_shared<DirectionalLightComponent>(d));
    /*for (int i = 4; i < 10; i++) {
        manager.addComponent<MeshComponent>(i, mp);
        TransformComponent lt;
        lt.position = { 10 * i,5,0 };
        lt.scale = { 1,1,1 };
        manager.addComponent<TransformComponent>(i, std::make_shared<TransformComponent>(lt));
    }*/
    manager.addComponent<PointLightComponent>(4, std::make_shared<PointLightComponent>(p));
    manager.addComponent<TransformComponent>(4, std::make_shared<TransformComponent>(t));


    
    behaviors.push_back(&renderer);
    behaviors.push_back(&controller);
    behaviors.push_back(&physics);
    for (Behavior* behavior : behaviors) {
        behavior->init();
    }
   
}

void testscene::update()
{
    for (Behavior* behavior : behaviors) {
        
        behavior->update(&manager);
        
    }
    
    
}

void testscene::close()
{
}
