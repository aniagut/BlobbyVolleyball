#include "body.h"
#include <Box2D/box2d.h>

b2Body* defineDynamicBody(int position_x, int position_y) {
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position_x, position_y);
	b2Body* newBody = world.CreateBody(&bodyDef);
	return newBody;
}