#pragma once
class Window {
public:
	static void initWindow(int height, int width, const char* name);
	static void getWindow();
	static void getKeyPressed();
	static void pollEvents();
	static void shouldClose();

};