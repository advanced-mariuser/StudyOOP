#include "CRectangle.h"
#include <cmath>

using namespace std;

const string CRectangle::NAME = "rectangle";

double CRectangle::GetArea() const
{
    return m_height * m_width;
}

double CRectangle::GetPerimeter() const
{
    return (m_height + m_width) * 2;
}

string CRectangle::ToString() const
{
    //паттерн шаблонный метод (можно посмотреть видео)
    stringstream output;
    output << "Name: " << NAME << endl;
    output << ISolidShape::ToString();
    output << "Left top: (" << m_leftTop.m_x << ';' << m_leftTop.m_y << ')' << endl;
    output << "Width: " << m_width << endl;
    output << "Height: " << m_height << endl;

    return output.str();
}

uint32_t CRectangle::GetOutlineColor() const
{
    return m_outlineColor;
}

uint32_t CRectangle::GetFillColor() const
{
    return m_fillColor;
}

CPoint CRectangle::GetLeftTop() const
{
    return m_leftTop;
}

double CRectangle::GetWidth() const
{
    return m_width;
}

double CRectangle::GetHeight() const
{
    return m_height;
}

void CRectangle::Draw(shared_ptr <ICanvas> canvas)
{
    CPoint rightBottom (m_leftTop.m_x + m_width, m_leftTop.m_y + m_height);
    CPoint rightTop(rightBottom.m_x, m_leftTop.m_y);
    CPoint leftBottom(m_leftTop.m_x, rightBottom.m_y);
    vector <CPoint> points = {m_leftTop, rightTop, rightBottom, leftBottom};

    canvas->FillPolygon(points, m_outlineColor, m_fillColor);

    canvas->DrawLine(m_leftTop, rightTop, m_outlineColor);
    canvas->DrawLine(rightTop, rightBottom, m_outlineColor);
    canvas->DrawLine(rightBottom, leftBottom, m_outlineColor);
    canvas->DrawLine(leftBottom, m_leftTop, m_outlineColor);
}