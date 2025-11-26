#include "../../Public//Messages/MessageDispatcher.h"
#include "../../Public/Entities/Entity.h"
#include "../../Public/Entities/EntityManager.h"
#include "../../Public/Utils/Clock.h"


void MessageDispatcher::Discharge(Entity* pReceiver, const Telegram& msg)
{
	pReceiver->DispatchMessage(msg);
}

void MessageDispatcher::DispatchMessage(double delay, int sender, int receiver, int msg, void* ExtraInfo)
{
	Entity* pReceiver = EntityMgr->GetEntityFromID(receiver);
	
	Telegram telegram(0, sender, receiver, msg, ExtraInfo);
	
	if (delay <= 0)
	{
		Discharge(pReceiver, telegram);
	}
}

void MessageDispatcher::DispatchDelayedMessages()
{
	double CurrentTime = Clock->GetCurrentTime();
	
	while (PriorityQ.begin()->DispatchTime < CurrentTime && PriorityQ.begin()->DispatchTime > 0)
	{
		Telegram telegram = *PriorityQ.begin();
		Entity pReciever = EntityMgr->GetEntityByID(telegram.Reciever);
		
		Discharge(pReciever, telegram);
		
		PriorityQ.erase(PriorityQ.begin());
	}
}

MessageDispatcher* MessageDispatcher::Instance()
{
	static MessageDispatcher instance;

	return &instance;
}
