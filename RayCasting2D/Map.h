#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include <iostream>

using namespace std;
using namespace sf;

class Map : public Drawable{
public:
	Map();
	~Map();
	void generate();
	int width, height;
	int wLength, hLength;
	vector<Tile> tiles;

private:
	vector<int> map;
	RectangleShape background;
	virtual void draw(RenderTarget& renderTarget, RenderStates renderStates) const;
};

