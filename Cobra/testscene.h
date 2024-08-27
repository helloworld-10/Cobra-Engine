#pragma once
#include "Scene.h"
#include "MeshBuilder.h"
#include "Renderer.h"
class testscene : public Scene {
	virtual void start() override;
	virtual void update() override;
	virtual void close() override;
private:
	Renderer renderer;
	Model model;
};