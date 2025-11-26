#pragma once
#include "BaseGameEntity.h"

template<class T>
class State
{

public:
	virtual ~State() {}

	virtual void Execute(T* t) = 0;
	virtual void Enter(T* t) = 0;
	virtual void Exit(T* t) = 0;
};