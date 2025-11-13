#include "BaseGameEntity.h"
#include "EntityManager.h"

void EntityManager::RegisterEntity(BaseGameEntity* NewEntity, int ID)
{
	m_EntityMap.insert({ID, NewEntity});
}

BaseGameEntity* EntityManager::GetEntityByID(int ID) const
{
	auto it = m_EntityMap.find(ID);

	if (it != m_EntityMap.end())
	{
		return it->second;
	}

	return nullptr;
}

void EntityManager::RemoveEntity(BaseGameEntity* pEntity)
{
	for (auto it = m_EntityMap.begin(); it != m_EntityMap.end();)
	{
		if (it->second == pEntity)
		{
			it = m_EntityMap.erase(it);
		}
		else
		{
			++it;
		}
	}
}

EntityManager* EntityManager::Instance()
{
	static EntityManager instance;

	return &instance;
}