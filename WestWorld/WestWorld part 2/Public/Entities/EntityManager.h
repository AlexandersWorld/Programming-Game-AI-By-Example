#pragma once

#include <map>

class BaseGameEntity;

class EntityManager
{
private:
    typedef std::map<int, BaseGameEntity*> EntityMap;

private:
    EntityMap m_EntityMap;

    EntityManager() {}

public:
    static EntityManager* Instance();

    void RegisterEntity(BaseGameEntity* pEntity, int ID);

    BaseGameEntity* GetEntityByID(int ID) const;

    void RemoveEntity(BaseGameEntity* pEntity);
};

#define EntityMgr EntityManager::Instance();