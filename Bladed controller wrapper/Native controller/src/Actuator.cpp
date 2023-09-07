#include "Actuator.hpp"
#include <cmath>

ActuatorState::ActuatorState(double x, double xdot, double xdotdot)
    : x(x), xdot(xdot), xdotdot(xdotdot) {}

Actuator::Actuator(double omega, double gamma, double dt)
    : omega(omega), gamma(gamma), dt(dt), prevState(0, 0, 0), uprev(0)
{
    double beta = sqrt(1 - gamma * gamma);
    g = exp(-gamma * omega * dt) * sin(beta * omega * dt) / (beta * omega);
    f = exp(-gamma * omega * dt) * (gamma * sin(beta * omega * dt) / beta + cos(beta * omega * dt));
}

ActuatorState Actuator::output(double input)
{
    double u = input;
    double omegaSqr = omega * omega;
    double gamma2Omega = 2 * gamma * omega;
    double xprev = prevState.x;
    double xdotprev = prevState.xdot;
    double udot = (u - uprev) / dt;
    ActuatorState result(
        f * xprev
        + g * xdotprev
        + (2.0 * gamma * (f - 1.0) / omega + dt - g) * udot
        + (1.0 - f) * uprev,
        -g * omegaSqr * (xprev - uprev)
        + (f - gamma2Omega * g) * xdotprev
        + (1.0 - f) * udot,
        (gamma2Omega * g - f) * omegaSqr * (xprev - uprev)
        + ((4.0 * gamma* gamma - 1.0) * omegaSqr * g - gamma2Omega * f)
        * xdotprev
        + omegaSqr * g * udot
    );
    prevState = result;
    uprev = u;
    return result;
}
