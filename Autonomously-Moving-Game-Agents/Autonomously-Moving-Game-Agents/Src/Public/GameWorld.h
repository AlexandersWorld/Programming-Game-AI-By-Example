#pragma once
#include <iostream>
#include <vector>
#include "Vehicle.h"
#include <cmath>

struct SVector2D
{
    float x, y;

    // Constructor
    SVector2D(float x = 0, float y = 0) : x(x), y(y) {}

    // Dot product with another vector
    float Dot(const SVector2D& target) const
    {
        return x * target.x + y * target.y;
    }

    // Normalize the vector (make it unit length)
    void Normalize()
    {
        float length = std::sqrt(x * x + y * y);

        if (length > 0.000001f) // Avoid division by zero
        {
            x /= length;
            y /= length;
        }
    }

    // Helper function to get the length/magnitude
    float Length() const
    {
        return std::sqrt(x * x + y * y);
    }

    // Helper function to get squared length (faster, no sqrt)
    float LengthSquared() const
    {
        return x * x + y * y;
    }

    // Alternative: Returns a normalized copy without modifying the original
    SVector2D Normalized() const
    {
        SVector2D result = *this;
        result.Normalize();
        return result;
    }

    // Static method to calculate squared distance between two vectors
    static float DistanceSquared(const SVector2D& v1, const SVector2D& v2)
    {
        float dx = v1.x - v2.x;
        float dy = v1.y - v2.y;
        return dx * dx + dy * dy;
    }

    // Static method to calculate distance between two vectors
    static float Distance(const SVector2D& v1, const SVector2D& v2)
    {
        return std::sqrt(DistanceSquared(v1, v2));
    }

    // Operator overloads for vector arithmetic
    SVector2D operator-(const SVector2D& other) const
    {
        return SVector2D(x - other.x, y - other.y);
    }

    SVector2D operator+(const SVector2D& other) const
    {
        return SVector2D(x + other.x, y + other.y);
    }

    SVector2D operator*(float scalar) const
    {
        return SVector2D(x * scalar, y * scalar);
    }

    // Note: There's a bug in your Flee function - you can't add a scalar to a vector
    // MaxSpeed should multiply the normalized vector, not be added to it
};

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
