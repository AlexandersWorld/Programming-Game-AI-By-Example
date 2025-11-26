#pragma once

#include "BaseGameEntity.h"
#include "Telegram.h"


class Entity : public BaseGameEntity
{
public:
    Entity(int id) : BaseGameEntity(id) {}

    void Update() override
    {
        // Will be filled later in the book
    }

    void DispatchMessage(Telegram msg);
};
