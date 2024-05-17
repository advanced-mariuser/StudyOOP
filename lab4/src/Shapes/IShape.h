#pragma once

#include <cstdint>
#include <sstream>
#include <string>
#include <iomanip>
#include "../Canvas/ICanvasDrowable.h"

class IShape : public ICanvasDrawable
{
public:
    IShape(uint32_t outlineColor)
            : m_outlineColor(outlineColor) {}

    virtual double GetArea() const = 0;

    virtual double GetPerimeter() const = 0;

    virtual uint32_t GetOutlineColor() const = 0;

    virtual std::string ToString() const = 0;

    virtual ~IShape() = default;

protected:
    uint32_t m_outlineColor;
};