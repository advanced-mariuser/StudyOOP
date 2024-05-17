#pragma once

#include "ISolidShape.h"

class CBaseShape : public ISolidShape
{
public:
    std::string ToString() const override;

private:
    virtual std::string AdvancedInfo() const = 0;
};