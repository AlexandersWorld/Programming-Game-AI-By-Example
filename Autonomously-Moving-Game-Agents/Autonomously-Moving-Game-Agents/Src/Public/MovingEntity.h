


class MovingEntity : public BaseGameEntity
{
public:
    
protected:
    SVector2D m_vVelocity;
    
    SVector2D m_vHeading;
    
    SVector2D m_vSide;
    
    double m_dMass;
    
    double m_dMaxSpeed;
    
    double m_dMaxForce;
    
    double m_dMaxTurnRate;
private:
    
};
