#include "Player.h"

Player::Player() {
	fov = 60;
	radius = 3;
	circle.setFillColor(Color::Yellow);
	circle.setRadius(radius);
	circle.setOrigin(radius, radius);
	setPosition(Vector2f(400, 300));

	wsk.setFillColor(Color::Red);
	wsk.setSize(Vector2f(1, radius));
}

Player::~Player() {

}

void Player::setPosition(Vector2f pos) {
	position = pos;
	circle.setPosition(position);
	wsk.setPosition(position);
}

void Player::move(Vector2f mov) {
	circle.move(mov);
	wsk.move(mov);
	position = circle.getPosition();
	for (auto& it : ray_vec) {
		it.update(position);
	}
}

void Player::setRotation(float rad) {
	float deg = rad * (180 / 3.1415);
	circle.setRotation(deg);
	wsk.setRotation(deg+30);
	for (auto& it : ray_vec) {
		it.setRotation(deg);
	}
}

Vector2f Player::getPosition() {
	return position;
}

float Player::getRotation() {
	return circle.getRotation();
}

void Player::draw(RenderTarget& renderTarget, RenderStates renderStates) const {
	for (auto& it : ray_vec) {
		renderTarget.draw(it, renderStates);
	}
	renderTarget.draw(circle, renderStates);
	renderTarget.draw(wsk, renderStates);
}
