#include "iostream"
#include "State.h"

template<class entity_type>
class StateMachine
{
private:
	entity_type* m_pOwner;

	State<entity_type>* m_pCurrentState;

	State<entity_type>* m_pPreviousState;

	State<entity_type>* m_pGlobalState;

public:
	StateMachine(entity_type* owner) : m_pOwner(owner),
		m_pCurrentState(nullptr),
		m_pPreviousState(nullptr),
		m_pGlobalState(nullptr) {}


	void SetCurrentState(State<entity_type>* s);
	void SetPreviousState(State<entity_type>* s);
	void SetGlobalState(State<entity_type>* s);

	State<entity_type>* GetCurrentState() const;
	State<entity_type>* GetPreviousState() const;
	State<entity_type>* GetGlobalState() const;

	void Update() const;

	void ChangeState(State<entity_type>* pNewState) override;
	void RevertToPreviousState() override;

	bool isInState(const State<entity_type>& st) const;
};
