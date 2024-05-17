#include "ShapeFactory.h"

using namespace std;

shared_ptr<IShape> ShapeFactory::CreateShape(const string &line)
{
    istringstream input(line);
    string nameShape;
    input >> nameShape;

    if (nameShape == CLineSegment::NAME)
    {
        return ShapeFactory::CreateLineSegment(input);
    }
    else if (nameShape == CCircle::NAME)
    {
        return ShapeFactory::CreateCircle(input);
    }
    else if (nameShape == CTriangle::NAME)
    {
        return ShapeFactory::CreateTriangle(input);
    }
    else if (nameShape == CRectangle::NAME)
    {
        return ShapeFactory::CreateRectangle(input);
    }

    return nullptr;
}

shared_ptr<CLineSegment> ShapeFactory::CreateLineSegment(istringstream &iss)
{
    double startX, startY, endX, endY;
    if (!(iss >> startX >> endX >> startY >> endY))
    {
        cout << "Invalid line segment coordinates" << endl;
        return nullptr;
    }

    CPoint startPoint = {startX, endX};
    CPoint endPoint = {startY, endY};

    uint32_t outlineColor;
    if (!(iss >> hex >> outlineColor))
    {
        cout << "Invalid color value" << endl;
        return nullptr;
    }

    return make_shared<CLineSegment>(startPoint, endPoint, outlineColor);
}

shared_ptr<CCircle> ShapeFactory::CreateCircle(istringstream &iss)
{
    double centerX, centerY, radius;
    if (!(iss >> centerX >> centerY >> radius))
    {
        cout << "Invalid circle coordinates or sizes" << endl;
        return nullptr;
    }

    CPoint center = {centerX, centerY};

    uint32_t outlineColor, fillColor;
    if (!(iss >> hex >> outlineColor >> fillColor))
    {
        cout << "Invalid color values" << endl;
        return nullptr;
    }

    return make_shared<CCircle>(center, radius, outlineColor, fillColor);
}

shared_ptr<CRectangle> ShapeFactory::CreateRectangle(istringstream &iss)
{
    double leftTopX, leftTopY, width, height;
    if (!(iss >> leftTopX >> leftTopY >> width >> height))
    {
        cout << "Invalid rectangle coordinates or sizes" << endl;
        return nullptr;
    }

    CPoint leftTop = {leftTopX, leftTopY};

    uint32_t outlineColor, fillColor;
    if (!(iss >> hex >> outlineColor >> fillColor))
    {
        cout << "Invalid color values" << endl;
        return nullptr;
    }

    return make_shared<CRectangle>(leftTop, width, height, outlineColor, fillColor);
}

shared_ptr<CTriangle> ShapeFactory::CreateTriangle(istringstream &iss)
{
    double top1X, top1Y;
    double top2X, top2Y;
    double top3X, top3Y;
    if (!(iss >> top1X >> top1Y >>
              top2X >> top2Y >>
              top3X >> top3Y))
    {
        cout << "Invalid triangle coordinates" << endl;
        return nullptr;
    }

    CPoint top1 = {top1X, top1Y};
    CPoint top2 = {top2X, top2Y};
    CPoint top3 = {top3X, top3Y};

    uint32_t outlineColor, fillColor;
    if (!(iss >> hex >> outlineColor >> fillColor))
    {
        cout << "Invalid color values" << endl;
        return nullptr;
    }

    return make_shared<CTriangle>(top1, top2, top3, outlineColor, fillColor);
}