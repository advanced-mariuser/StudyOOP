#include "CBaseShape.h"

using namespace std;

string CBaseShape::ToString() const
{
    std::stringstream output;
    output << "Area: " << GetArea() << std::endl;
    output << "Perimeter: " << GetPerimeter() << std::endl;
    output << "OutlineColor: " << std::hex << std::setw(6) << std::setfill('0') << GetOutlineColor() << std::endl;
    output << "FillColor: " << std::hex << std::setw(6) << std::setfill('0') << GetFillColor() << std::endl
    AdvancedInfo();

    return output.str();
}