#pragma once

#include <string>
#include <iostream>
#include <memory>
#include "../Shapes/IShape.h"
#include "../Shapes/LineSegment/CLineSegment.h"
#include "../Shapes/Circle/CCircle.h"
#include "../Shapes/Rectangle/CRectangle.h"
#include "../Shapes/Triangle/CTriangle.h"

class ShapeFactory
{
public:
    static std::shared_ptr <IShape> CreateShape(const string &line);

private:
    static std::shared_ptr <CLineSegment> CreateLineSegment(istringstream &input);

    static std::shared_ptr <CRectangle> CreateRectangle(istringstream &input);

    static std::shared_ptr <CTriangle> CreateTriangle(istringstream &input);

    static std::shared_ptr <CCircle> CreateCircle(istringstream &input);
};
