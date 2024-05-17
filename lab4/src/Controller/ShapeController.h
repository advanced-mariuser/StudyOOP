#pragma once

#include <vector>
#include "../ShapeCreator/ShapeFactory.h"
#include "../Canvas/CCanvas.h"
#include <memory>

class ShapeController
{
public:
    void ConstructShape(const std::string &line);

    std::shared_ptr <IShape> GetMaxAreaShape() const;

    std::shared_ptr <IShape> GetMinPerimeterShape() const;

    void DrawShapes();

private:
    const int WIDTH_WINDOW = 900;
    const int HEIGHT_WINDOW = 900;
    const std::string NAME_WINDOW = "window";

    std::vector <shared_ptr<IShape>> m_shapes = {};
    std::shared_ptr <ICanvas> m_canvas;
};
