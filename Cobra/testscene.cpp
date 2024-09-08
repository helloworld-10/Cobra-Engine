#include "testscene.h"

void testscene::start()
{
    const std::string fname = "blank.png";
    const std::string objname = "C:\\Users\\Rajit\\source\\repos\\Cobra\\Cobra\\dragon.txt";
    Mesh* mesh = MeshBuilder::loadFromObj(&objname, &fname);
    Shader s("C:\\Users\\Rajit\\source\\repos\\Cobra\\Cobra\\vertex.glsl", "C:\\Users\\Rajit\\source\\repos\\Cobra\\Cobra\\frag.glsl");
    model.m = mesh;
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
    renderer.initRenderer();
}

void testscene::update()
{
    renderer.Render(model);
}

void testscene::close()
{
    delete(this);
}
