#include "Scene.h"

Scene::Scene() {
}

Scene::Scene(int width, int height, int amount) {
	windowWidth = width;
	windowHeight = height;
	rayAmount = amount;
	offset = windowWidth / rayAmount;
	for (int i = 0; i < rayAmount; i++) {
		RectangleShape shape;
		shape.setPosition(Vector2f(offset * i, windowHeight/2));
		shape.setFillColor(Color(0,255,0));
		shape.setSize(Vector2f(offset, 100));
		walls.push_back(shape);
	}

}

Scene::~Scene() {
}

void Scene::renderScene() {

	float projectionDistance = 0.5f * 4 / tan((0.5f * fovVertical) * (3.1415 / 180));

	for (int i = 0; i < rayAmount; i++) {

		float rayDir = fov * (floor(0.5f * windowWidth) - i) / (windowWidth - 1);
		float rayPosition = 0.5f * tan(rayDir * (3.1415 / 180)) / tan((0.5f * fov) * (3.1415 / 180));
		float height = round(windowHeight * projectionDistance / (lengths.at(i) * (cos(rayDir * (3.1415/180)))));

		walls.at(i).setSize(Vector2f(offset, height));
		walls.at(i).setPosition(offset*i, 0.5f * (windowHeight - height));

		float color = 255 * (1 - lengths.at(i) / renderDistance);
		if (lengths.at(i) > renderDistance) color = 0;
		walls.at(i).setFillColor(Color(0, color, 0));
	}

	lengths.clear();
}

void Scene::draw(RenderTarget& renderTarget, RenderStates renderStates) const {
	for (auto& it : walls) {
		renderTarget.draw(it, renderStates);
	}
}
