#include "Ray.h"

Ray::Ray(float length, Vector2f pos) {
	shape.setFillColor(Color::White);
	shape.setPosition(pos);
	shape.setOrigin(0, 1);
	shape.setSize(Vector2f(2, length));
}

Ray::~Ray()  {

}

void Ray::update(Vector2f position) {
	shape.setPosition(position);
}

void Ray::setRotation(float rot) {
	shape.setRotation(rot + primaryRotation);
}

void Ray::setLength(float length) {
	shape.setSize(Vector2f(1, length));
}

void Ray::draw(RenderTarget& renderTarget, RenderStates renderStates) const {
	//renderTarget.draw(shape, renderStates);
}
