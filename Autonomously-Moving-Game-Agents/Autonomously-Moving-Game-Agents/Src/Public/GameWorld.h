#pragma once
#include <vector>
#include "Vehicle.h"

class GameWorld
{
private:
    // All vehicles in the world
    std::vector<Vehicle*> m_Vehicles;

    // You can add walls, obstacles, paths later
    // std::vector<Wall> m_Walls;
    // std::vector<BaseGameEntity*> m_Obstacles;

public:
    GameWorld();
    ~GameWorld();

    void Update(double time_elapsed);
    void Render();

    // Helper to create vehicles
    void AddVehicle(const SVector2D& startPos);

    // Getter for Vehicles (used by SteeringBehaviors)
    const std::vector<Vehicle*>& GetVehicles() const { return m_Vehicles; }
};
