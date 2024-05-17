#pragma once

#include <memory>
#include "ICanvas.h"

class ICanvasDrawable
{
public:
    //передать ссылку на ICanvas потому что не подразумевается владение внутри Draw
    virtual void Draw(std::shared_ptr <ICanvas> canvas) const  = 0;
    //посмотреть алгоритм выбора деструктора
protected:
    ~ICanvasDrawable() = default;
};