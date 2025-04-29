#pragma once
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Ray : public Drawable {
public:
	Ray(float length, Vector2f pos);
	~Ray();
	RectangleShape shape;
	void update(Vector2f position);
	void setRotation(float rot);
	void setLength(float length);
	float primaryRotation;

private:
	virtual void draw(RenderTarget& renderTarget, RenderStates renderStates) const;
};

