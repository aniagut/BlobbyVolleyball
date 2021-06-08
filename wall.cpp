#include "wall.h"
#include <Box2D/box2d.h>

void setWall(int pos_x, int pos_y, int width, int height) {
	b2PolygonShape shape;
	shape.SetAsBox(width / scale, height / scale);

	b2BodyDef bodyDef;
	bodyDef.position.Set(pos_x / scale, pos_y / scale);

	b2Body* wallBody = world.CreateBody(&bodyDef);
	wallBody->CreateFixture(&shape, 1);
}