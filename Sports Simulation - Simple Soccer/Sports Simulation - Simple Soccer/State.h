template <class EntityType>
class State
{
public:
    virtual ~State() = default;

    // Called when the state becomes active
    virtual void Enter(EntityType* entity) = 0;

    // Called every update tick
    virtual void Execute(EntityType* entity) = 0;

    // Called when the state is exited
    virtual void Exit(EntityType* entity) = 0;
};
