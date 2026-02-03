struct Params
{
    // physics
    double Friction;
    double Mass;
    double MaxSpeed;
    double SupportSpotUpdateFreq;
    double Spot_CanPassScore;
    double Spot_CanScoreFromPositionScore;
    double Spot_DistFromControllingPlayerScore;
    double MaxPassingForce;
    double Spot_PassSafeStrength;
    double MaxShootingForce;
    double Spot_CanScoreStrength;
    double Spot_DistFromControllingPlayerStrength;
    int TeamSize;

    // timing
    double TimeStep;

    Params()
    {
        Friction = -0.8;   // negative = deceleration
        Mass = 1.0;
        MaxSpeed = 150.0;
        TimeStep = 0.1;
        SupportSpotUpdateFreq = 1.0;
        Spot_CanPassScore = 2.0;
        Spot_CanScoreFromPositionScore = 1.0;
        Spot_DistFromControllingPlayerScore = 200.0;
        MaxPassingForce = 30.0;
        Spot_PassSafeStrength = 10;
        MaxShootingForce = 50.0;
        Spot_CanScoreStrength = 20.0;
        Spot_DistFromControllingPlayerStrength = 40.0;
        TeamSize = 5;
    }
};

extern Params Prm;
