#ifndef WALL_H
#define WALL_H

#include <Box2D/box2d.h>

const float scale = 30.0;

b2Vec2 gravity(0.0, 9.81);
b2World world(gravity);

void setWall(int pos_x, int pos_y, int width, int height);

#endif