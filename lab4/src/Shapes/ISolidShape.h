#pragma once
#include "IShape.h"

class ISolidShape : public IShape
{
public:
    ISolidShape(uint32_t outlineColor,uint32_t fillColor)
            :IShape(outlineColor)
            ,m_fillColor(fillColor)
    {}

    virtual uint32_t GetFillColor() const = 0;

protected:
    uint32_t m_fillColor = 0;
};