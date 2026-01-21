struct Params
{
    // physics
    double Friction;
    double Mass;
    double MaxSpeed;

    // timing
    double TimeStep;

    Params()
    {
        Friction = -0.8;   // negative = deceleration
        Mass = 1.0;
        MaxSpeed = 150.0;
        TimeStep = 0.1;
    }
};

extern Params Prm;
