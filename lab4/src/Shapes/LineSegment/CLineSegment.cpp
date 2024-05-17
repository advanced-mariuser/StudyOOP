#include <complex>
#include "CLineSegment.h"

using namespace std;

const string CLineSegment::NAME = "line_segment";

double CLineSegment::GetArea() const
{
    return 0;
}

//устранить дублиование кода с классом Треугольник
double CLineSegment::GetPerimeter() const
{
    return sqrt(pow(m_startPoint.m_x - m_endPoint.m_x, 2) + pow(m_startPoint.m_y - m_endPoint.m_y, 2));
}

string CLineSegment::ToString() const
{
    stringstream output;
    output << "Name: " << NAME << endl;
    output << IShape::ToString();
    output << "Start point: (" << m_startPoint.m_x << ';' << m_startPoint.m_y << ')' << endl;
    output << "End point: (" << m_endPoint.m_x << ';' << m_endPoint.m_y << ')' << endl;
    output << "Length: " << GetPerimeter() << endl;

    return output.str();
}

uint32_t CLineSegment::GetOutlineColor() const
{
    return m_outlineColor;
}

CPoint CLineSegment::GetStartedPoint() const
{
    return m_startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
    return m_endPoint;
}

void CLineSegment::Draw(shared_ptr <ICanvas> canvas)
{
    canvas->DrawLine(m_startPoint, m_endPoint, m_outlineColor);
}