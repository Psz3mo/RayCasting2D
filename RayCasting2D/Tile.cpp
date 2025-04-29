#include "Tile.h"

Tile::Tile() {
	
}

Tile::~Tile() {
}

void Tile::setPosition(Vector2f pos) {
	position = pos;
	rect.setPosition(position);
}

Vector2f Tile::getPosition() {
	return position;
}

void Tile::setSize(Vector2f siz) {
	size = siz;
	rect.setSize(size);
}

void Tile::changeType(TilesType typ) {
	type = typ;
	switch (type)
	{
	case BRICK:
		rect.setFillColor(Color::Blue);
		break;
	default:
		break;
	}
}

void Tile::draw(RenderTarget& renderTarget, RenderStates renderStates) const {
	renderTarget.draw(rect, renderStates);
}
