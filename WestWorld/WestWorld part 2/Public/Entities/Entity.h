#pragma once

#include "../Game/BaseGameEntity.h"


class Telegram;

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
