#pragma once
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

enum TilesType {
	NONE,
	BRICK,
	SPAWN
};

class Tile : public Drawable{
public:
	Tile();
	~Tile();
	void setPosition(Vector2f pos);
	Vector2f getPosition();
	void setSize(Vector2f siz);
	void changeType(TilesType typ);
	TilesType type;

private:
	Vector2f position;
	Vector2f size;
	RectangleShape rect;
	virtual void draw(RenderTarget& renderTarget, RenderStates renderStates) const;
};

