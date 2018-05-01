#pragma once
#include "Brick.h"
#include "Block.h"
class Ball
{
private: 
	bool collisionX(float, float, float, float, float, float, float, float);
	bool collisionY(float, float, float, float, float, float, float, float);
public:
	float x;
	float y;
	float widthheight;
	float velx;
	float vely;
	float red;
	float green;
	float blue;
	bool left;
	bool right;
	bool up;
	bool down;
	bool collisionX(Brick b);
	bool collisionY(Brick b);
	bool collisionX(Block b);
	bool collisionY(Block b);
	Ball();
	~Ball();

};

