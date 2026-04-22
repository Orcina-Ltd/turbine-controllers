#pragma once

struct ActuatorState
{
    double x;
    double xdot;
    double xdotdot;
};

class Actuator
{
public:
    Actuator(double omega, double gamma, double dt);
    ActuatorState output(double input);
private:
    double omega;
    double gamma;
    double dt;
    ActuatorState prevState;
    double uprev;
    double g;
    double f;
};
