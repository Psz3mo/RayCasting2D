#pragma once
#include <SFML\Graphics.hpp>
#include "Ray.h"
#include <iostream>

using namespace sf;
using namespace std;

class Player : public Drawable
{
public:
	Player();
	~Player();
	void setPosition(Vector2f);
	void move(Vector2f);
	void setRotation(float rad);
	Vector2f getPosition();
	float playerSpeed = 20.f;
	float getRotation();
	vector<Ray> ray_vec;
	float fov;

private:
	CircleShape circle;
	float radius;
	RectangleShape wsk;
	Vector2f position;
	virtual void draw(RenderTarget& renderTarget, RenderStates renderStates) const;
};

