#include "Ball.h"


bool Ball::collisionX(float Ax, float Ay, float Aw, float Ah, float Bx, float By, float Bw, float Bh)
{
	if (Ax + Aw < Bx) return false;
	else if (Ax > Bx + Bw) return false;
	if (Ay + Ah < By) return false;
	else if (Ay > By + Bh) return false;
	if ((((int)Ax + 1 == int(Bx + Bw)) || ((int)Ax == int(Bx + Bw)) || ((int)Ax == int(Bx + Bw) + 1) || ((int)Bx + 1 == int(Ax + Aw)) || ((int)Bx == int(Ax + Aw)) || ((int)Bx == int(Ax + Aw) + 1)) && (((By <= Ay + Ah) && (Ay + Ah <= By + Bh)) || ((Ay <= By + Bh) && (By + Bh <= Ay + Ah))))
		return true;
	return false;
}
bool Ball::collisionY(float Ax, float Ay, float Aw, float Ah, float Bx, float By, float Bw, float Bh)
{
	if (Ax + Aw < Bx) return false;
	else if (Ax > Bx + Bw) return false;
	if (Ay + Ah < By) return false;
	else if (Ay > By + Bh) return false;
	if ((((int)Ay + 1 == (int)(By + Bh)) || ((int)Ay == (int)(By + Bh)) || ((int)Ay == (int)(By + Bh) + 1) || ((int)By + 1 == (int)(Ay + Ah)) || ((int)By == (int)(Ay + Ah)) || ((int)By == (int)(Ay + Ah) + 1)) && (((Bx <= Ax + Aw) && (Ax + Aw <= Bx + Bw)) || ((Ax <= Bx + Bw) && (Bx + Bw <= Ax + Aw))))
		return true;
	return false;
}




bool Ball::collisionX(Brick b) {
	return collisionX(x, y, widthheight, widthheight, b.x, b.y, b.width, b.height);
}

bool Ball::collisionY(Brick b) {
	return collisionY(x, y, widthheight, widthheight, b.x, b.y, b.width, b.height);
}

bool Ball::collisionX(Block b) {
	return collisionX(x, y, widthheight, widthheight, b.x, b.y, b.width, b.height);
}

bool Ball::collisionY(Block b) {
	return collisionY(x, y, widthheight, widthheight, b.x, b.y, b.width, b.height);
}

Ball::Ball()
{
}


Ball::~Ball()
{
}
