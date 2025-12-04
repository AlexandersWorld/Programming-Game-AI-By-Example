#include "GameWorld.h"

class Vehicle : public MovingEntity
{
private:
    
    //a pointer to the world data enabling a vehicle to access any obstacle
    //path, wall, or agent data
    GameWorld* m_pWorld;
    
    SteeringBehaviors* m_pSteering;
    
public:
    void Update(double time_elapsed);
};
