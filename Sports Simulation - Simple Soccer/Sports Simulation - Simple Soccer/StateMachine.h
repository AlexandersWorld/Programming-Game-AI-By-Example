#pragma once

#include "State.h"

template <class EntityType>
class StateMachine
{
private:
	EntityType* m_pOwner;

	State<EntityType>* m_pCurrentState;
	State<EntityType>* m_pPreviousState;
	State<EntityType>* m_pGlobalState;

public:
	StateMachine(EntityType* owner)
		: m_pOwner(owner),
		m_pCurrentState(nullptr),
		m_pPreviousState(nullptr),
		m_pGlobalState(nullptr)
	{
	}

	void Update()
	{
		if (m_pGlobalState)
			m_pGlobalState->Execute(m_pOwner);

		if (m_pCurrentState)
			m_pCurrentState->Execute(m_pOwner);
	}

	void ChangeState(State<EntityType>* newState)
	{
		m_pPreviousState = m_pCurrentState;

		if (m_pCurrentState)
			m_pCurrentState->Exit(m_pOwner);

		m_pCurrentState = newState;

		if (m_pCurrentState)
			m_pCurrentState->Enter(m_pOwner);
	}

	void RevertToPreviousState()
	{
		ChangeState(m_pPreviousState);
	}
};
