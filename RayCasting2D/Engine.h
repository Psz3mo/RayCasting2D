#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Map.h"
#include "Scene.h"

using namespace std;
using namespace sf;

class Engine
{
public:
	Engine(RenderWindow &window,int width, int height);
	~Engine();
	void run();
	void update(Time);

private:
	float fps = 60.f;
	Time timePerFrame = seconds(1.f/fps);
	int screenWidth, screenHeight;
	RenderWindow* window;
	void processEvents();
	void handlePlayerInput(Keyboard::Key key, bool isPressed);
	void render();

	bool isForward, isBack, isLeft, isRight;
	Player player;
	void rotatePlayer(Event::MouseMoveEvent);

	int rayAmount = 200;
	float rayLength = 1000.f;
	void createRays(int amount);
	void calculateLengthOfRay();
	float degToRad(float deg);
	Map map;

	Scene scene;
};

