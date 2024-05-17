#include "ShapeController.h"
#include "../ShapeFactory/ShapeFactory.h"
#include <iostream>

using namespace std;

void ShapeController::ConstructShape(const string &line)
{
    shared_ptr <IShape> shape = ShapeFactory::CreateShape(line);

    if (shape == nullptr)
    {
        cout << "Failed to create this shape" << endl;
        return;
    }

    m_shapes.emplace_back(shape);
}

shared_ptr <IShape> ShapeController::GetMaxAreaShape() const
{
    if (m_shapes.empty())
    {
        return nullptr;
    }

    auto maxAreaShape = *max_element(
            m_shapes.begin(), m_shapes.end(),
            [](const auto &a, const auto &b)
            { return a->GetArea() < b->GetArea(); });

    return maxAreaShape;
}

shared_ptr <IShape> ShapeController::GetMinPerimeterShape() const
{
    if (m_shapes.empty())
    {
        return nullptr;
    }

    auto minPerimeterShape = *min_element(
            m_shapes.begin(), m_shapes.end(),
            [](const auto &a, const auto &b)
            { return a->GetPerimeter() < b->GetPerimeter(); });

    return minPerimeterShape;
}

//почему функция реализует создание и открытие окна
void ShapeController::DrawShapes()
{
    auto window = make_shared<sf::RenderWindow>(
            sf::VideoMode(WIDTH_WINDOW, HEIGHT_WINDOW),
            NAME_WINDOW);

    m_canvas = make_shared<CCanvas>(window);

    while (window->isOpen())
    {
        sf::Event event{};
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window->close();
            }
        }

        window->clear(sf::Color::White);

        for (auto const &shape: m_shapes)
        {
            shape->Draw(m_canvas);
        }

        window->display();
    }
}