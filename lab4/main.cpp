#include <iostream>
#include "./src/Controller/ShapeController.h"

using namespace std;

int main()
{
    ShapeController shapeController;
    string dataShape;
    while (getline(cin, dataShape))
    {
        if (dataShape.empty())
        {
            continue;
        }

        shapeController.ConstructShape(dataShape);
    }

    if (shapeController.GetMaxAreaShape() == nullptr)
    {
        return 0;
    }

    cout << "Shape with max area:\n" << shapeController.GetMaxAreaShape()->ToString() << endl;
    cout << "Shape with min perimeter:\n" << shapeController.GetMinPerimeterShape()->ToString() << endl;

    shapeController.DrawShapes();

    return 0;
}