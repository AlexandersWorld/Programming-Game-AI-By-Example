#include "StateMachine.h"

template<class entity_type>
inline void StateMachine<entity_type>::SetCurrentState(State<entity_type>* s)
{
	m_pCurrentState = s;
}

template<class entity_type>
void StateMachine<entity_type>::SetPreviousState(State<entity_type>* s)
{
	m_pPreviousState = s;
}

template<class entity_type>
void StateMachine<entity_type>::SetGlobalState(State<entity_type>* s)
{
	m_pGlobalState = s;
}

template<class entity_type>
State<entity_type>* StateMachine<entity_type>::GetCurrentState() const
{
	return m_pCurrentState;
}

template<class entity_type>
State<entity_type>* StateMachine<entity_type>::GetPreviousState() const
{
	return m_pPreviousState;
}

template<class entity_type>
State<entity_type>* StateMachine<entity_type>::GetGlobalState() const
{
	return GetGlobalState;
}

template<class entity_type>
void StateMachine<entity_type>::Update() const
{
	if (m_pGlobalState) m_pGlobalState->Execute(m_pOwner);

	if (m_pCurrentState) m_pCurrentState->Execute(m_pOwner);
}

template<class entity_type>
void StateMachine<entity_type>::ChangeState(State<entity_type>* pNewState)
{
	if (!pNewState) {
		std::cerr << "<StateMachine>::ChangeState: trying to change to a null state";
		return;
	}

	SetPreviousState(m_pCurrentState);

	m_pCurrentState->Exit(m_pOwner);

	SetCurrentState(pNewState);

	m_pCurrentState->Execute(m_pOwner);
}

template<class entity_type>
void StateMachine<entity_type>::RevertToPreviousState()
{
	ChangeState(m_pPreviousState);
}

template<class entity_type>
bool StateMachine<entity_type>::isInState(const State<entity_type>& st) const
{
	return typeid(m_pCurrentState) == typeid(st);
}
