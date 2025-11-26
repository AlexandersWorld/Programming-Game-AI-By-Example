#pragma once

#include <set>
#include "../Messages/Telegram.h"

#include "../Entities/EntityManager.h"

class Clock;
class Entity;

class MessageDispatcher : public EntityManager
{
private:
	std::set<Telegram> PriorityQ;

	void Discharge(Entity* pReceiver, const Telegram& msg);

	MessageDispatcher()
	{
		Clock = new::Clock();
	}

	~MessageDispatcher()
	{
		delete Clock;
	}


public:
	static MessageDispatcher* Instance();

	void DispatchMessage(double delay, int sender, int receiver, int msg, void* ExtraInfo);

	void DispatchDelayedMessages();
	
	Clock* Clock;
};
