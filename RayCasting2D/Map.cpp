#include "Map.h"

Map::Map() {
	width = 32, height = 16;
	wLength = 8, hLength = 8;
	map = {
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,
		1,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,
		1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,
		1,0,0,0,1,1,1,0,0,0,1,1,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,0,0,1,1,
		1,0,0,0,1,1,1,0,0,0,1,1,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,0,0,1,1,
		1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
	};
	background.setPosition(Vector2f(0, 0));
	background.setFillColor(Color::Black);
	background.setSize(Vector2f(width * wLength, height * hLength));
}

Map::~Map() {
}

void Map::generate() {
	for (int i = 0; i < width * height; i++) {
		Tile tile;
		float x = (i % width) * wLength, y = floor(i / width) * hLength;
		if (map[i] == 1) {
			tile.setPosition(Vector2f(x, y));
			tile.setSize(Vector2f(wLength -1 , hLength -1));
			tile.changeType(BRICK);
		}
		else if (map[i] == 2) {
			tile.setPosition(Vector2f(x, y));
			tile.changeType(SPAWN);
		}
		else
			tile.changeType(NONE);
		tiles.push_back(tile);
	}
}

void Map::draw(RenderTarget& renderTarget, RenderStates renderStates) const {
	renderTarget.draw(background, renderStates);
	for (auto& it : tiles) {
		if(it.type != NONE)
			renderTarget.draw(it, renderStates);
	}
}
