#include "MessageDispatcher.h"
#include "Entity.h"
#include "EntityManager.h"

void MessageDispatcher::Discharge(Entity* pReceiver, const Telegram& msg)
{
	pReceiver->DispatchMessage(msg);
}

void MessageDispatcher::DispatchMessage(double delay, int sender, int receiver, int msg, void* ExtraInfo)
{
	BaseGameEntity* pReceiver = EntityManager::Instance()->GetEntityByID(receiver);
}

void MessageDispatcher::DispatchDelayedMessages()
{
}

MessageDispatcher* MessageDispatcher::Instance()
{
	static MessageDispatcher instance;

	return &instance;
}
