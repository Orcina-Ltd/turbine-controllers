import math


class PitchController(object):
    def Calculate(self, info):
        if info.NewTimeStep:
            maxPitch = 0.5 * math.pi
            ramp = 1.0 / (1.0 + math.exp(-info.SimulationTime + 10.0))
            info.StructValue.Value = maxPitch * ramp
            info.StructValue.Velocity = maxPitch * ramp * (1.0 - ramp)
            info.StructValue.Acceleration = (
                maxPitch * ramp * (1.0 - ramp) * (1.0 - 2.0 * ramp)
            )
