#pragma once
#include "BaseGameEntity.h"

class Telegram;

template<class T>
class State
{

public:
	virtual ~State() {}

	virtual void Execute(T* t) = 0;
	virtual void Enter(T* t) = 0;
	virtual void Exit(T* t) = 0;
	virtual bool OnMessage(T*, const Telegram&)=0;
};
