#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>

using namespace std;
using namespace sf;

class Scene : public Drawable{
public:
	Scene();
	Scene(int width, int height, int amount);
	~Scene();

	void renderScene();
	vector<float> lengths;

private:
	int rayAmount;
	float offset;
	float renderDistance = 200;
	float fovVertical = 51.f;
	float fov = 60.f;
	vector<RectangleShape> walls;
	int windowWidth, windowHeight;
	virtual void draw(RenderTarget& renderTarget, RenderStates renderStates) const;
};

