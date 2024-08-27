#pragma once
class Scene {

public:
	virtual void start() = 0;
	virtual void update() = 0;
	virtual void close() = 0;
};