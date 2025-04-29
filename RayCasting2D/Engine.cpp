#include "Engine.h"

Engine::Engine(RenderWindow &win, int width, int height) {
	screenWidth = width;
	screenHeight = height;
	window = &win;
	window->create(VideoMode(screenWidth, screenHeight), "Raycasting 2D", Style::Close);
	window->setFramerateLimit(fps);

	map.generate();
	Vector2f pos;
	for (auto& it : map.tiles) {
		if (it.type == SPAWN) {
			pos = it.getPosition();
			break;
		}
	}
	player.setPosition(Vector2f(pos.x + 0.5 * map.wLength, pos.y + 0.5 * map.hLength));

	Scene s(screenWidth, screenHeight, rayAmount);
	scene = s;
}

Engine::~Engine() {

}

void Engine::run() {
	createRays(rayAmount);
	Clock clock;
	Time timeSinceLastUpdate = Time::Zero;
	while (window->isOpen()) {
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame) {
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			update(timePerFrame);
		}
		render();
	}
}

void Engine::update(Time deltaTime) {
	// Player movement
	Vector2f movement(0, 0);
	if (isForward) {
		movement.x += player.playerSpeed * cos((player.getRotation() + 120) * (3.1415/180));
		movement.y += -player.playerSpeed * -sin((player.getRotation() + 120) * (3.1415 / 180));
	}
	if (isBack) {
		movement.x += player.playerSpeed * cos((player.getRotation() - 60) * (3.1415 / 180));
		movement.y += -player.playerSpeed * -sin((player.getRotation() - 60) * (3.1415 / 180));
	}
	if (isLeft) {
		movement.x += player.playerSpeed * cos((player.getRotation() + 30) * (3.1415 / 180));
		movement.y += -player.playerSpeed * -sin((player.getRotation() + 30) * (3.1415 / 180));
	}
	if (isRight) {
		movement.x += player.playerSpeed * cos((player.getRotation() - 150) * (3.1415 / 180));
		movement.y += -player.playerSpeed * -sin((player.getRotation() - 150) * (3.1415 / 180));
	}

	player.move(movement * deltaTime.asSeconds());
	calculateLengthOfRay();
	scene.renderScene();
}

void Engine::processEvents() {
	Event event;
	if (window->pollEvent(event)) {
		switch (event.type) {
		case Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;
		case Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;
		case Event::MouseButtonPressed:
			handlePlayerInput(event.key.code, true);
			break;
		case Event::MouseButtonReleased:
			handlePlayerInput(event.key.code, false);
			break;
		case Event::MouseMoved:
			rotatePlayer(event.mouseMove);
			break;
		case Event::Closed:
			window->close();
			break;
		}
	}
}

void Engine::handlePlayerInput(Keyboard::Key key, bool isPressed) {
	if (key == Keyboard::Escape && isPressed == true)
		window->close();
	if (key == Keyboard::W)
		isForward = isPressed;
	if (key == Keyboard::A)
		isLeft = isPressed;
	if (key == Keyboard::S)
		isBack = isPressed;
	if (key == Keyboard::D)
		isRight = isPressed;
}

void Engine::render() {
	window->clear();
	window->draw(scene);
	window->draw(map);
	window->draw(player);
	window->display();
}

void Engine::calculateLengthOfRay() {
	for (auto& it : player.ray_vec) {

		Vector2f startPos = player.getPosition();
		Vector2f rayDir(cos(degToRad(it.shape.getRotation() + 90 )), sin(degToRad(it.shape.getRotation() + 90)));
		Vector2f currentCell(floor(startPos.x / map.wLength), floor(startPos.y / map.hLength));
		float length = 0;
		Vector2f lengthRay(0,0);
		Vector2f stepSize(map.wLength * sqrt(1 + (rayDir.y / rayDir.x) * (rayDir.y / rayDir.x)), 
			map.hLength * sqrt(1 + (rayDir.x / rayDir.y) * (rayDir.x / rayDir.y)));
		Vector2f step(0, 0);

		if (rayDir.x < 0) {
			step.x = -1;
			lengthRay.x = (startPos.x / map.wLength - currentCell.x) * stepSize.x;
		}
		else {
			step.x = 1;
			lengthRay.x = (1 + currentCell.x - startPos.x / map.wLength) * stepSize.x;
		}
		if (rayDir.y < 0) {
			step.y = -1;
			lengthRay.y = (startPos.y / map.hLength - currentCell.y) * stepSize.y;
		}
		else {
			step.y = 1;
			lengthRay.y = (1 + currentCell.y - startPos.y / map.hLength) * stepSize.y;
		}

		bool tileFound = false;
		while (!tileFound && length < 500.f) {
			if (lengthRay.x < lengthRay.y) {
				currentCell.x += step.x;
				length = lengthRay.x;
				lengthRay.x += stepSize.x;
			}
			else {
				currentCell.y += step.y;
				length = lengthRay.y;
				lengthRay.y += stepSize.y;
			}
			if(currentCell.x >= 0 && currentCell.x < map.width && currentCell.y >= 0 && currentCell.y < map.height)
				if (map.tiles.at(currentCell.y * map.width + currentCell.x).type != NONE 
					&& map.tiles.at(currentCell.y * map.width + currentCell.x).type != SPAWN)
					tileFound = true;
		}
		it.setLength(length);
		scene.lengths.push_back(length);
	}
}

void Engine::rotatePlayer(Event::MouseMoveEvent e) {
	player.setRotation(e.x/100.f);
}

void Engine::createRays(int amount) {
	float recAngle = player.fov / amount;
	for (int i = 0; i < amount; i++) {
		Ray ray(rayLength, player.getPosition());
		ray.shape.setRotation(recAngle * i);
		ray.primaryRotation = recAngle * i;
		player.ray_vec.push_back(ray);
	}
}

float Engine::degToRad(float deg) {
	return deg * (3.1415 / 180);
}
