#include "CCircle.h"
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

const string CCircle::NAME = "circle";

double CCircle::GetArea() const
{
    return M_PI * m_radius * m_radius;
}

double CCircle::GetPerimeter() const
{
    return 2 * M_PI * m_radius;
}

string CCircle::ToString() const
{
    stringstream output;
    output << "Name: " << NAME << endl;
    output << ISolidShape::ToString();
    output << "Center: (" << m_center.m_x << ';' << m_center.m_y << ')' << endl;
    output << "Radius: " << m_radius << endl;

    return output.str();
}

uint32_t CCircle::GetOutlineColor() const
{
    return m_outlineColor;
}

uint32_t CCircle::GetFillColor() const
{
    return m_fillColor;
}

CPoint CCircle::GetCenter() const
{
    return m_center;
}

double CCircle::GetRadius() const
{
    return m_radius;
}

void CCircle::Draw(shared_ptr<ICanvas> canvas)
{
    canvas->DrawCircle(m_center, m_radius, m_outlineColor);
    canvas->FillCircle(m_center, m_radius, m_fillColor);
}