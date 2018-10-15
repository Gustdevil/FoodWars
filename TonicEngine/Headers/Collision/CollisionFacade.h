#pragma once

#include "Shape.h"
#include "Rectangle.h"
#include "Circle.h"

class CollisionFacade {
public:
    static bool detectCollision(Shape* shapeA, Shape* shapeB, Vector2D movement);
private:
    static bool detectCollision(Rectangle* recA, Rectangle* recB);
    static bool detectCollision(Circle* cirA, Circle* cirB);
    static bool detectCollision(Circle* cirA, Rectangle* recB);
};