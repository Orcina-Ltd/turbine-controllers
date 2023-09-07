import math


class PitchController(object):
    def Calculate(self, info):

        amp, omega = math.pi, math.pi / 10.0
        scale = (0.25, 0.5, 1.0)

        if info.NewTimeStep:
            for i in range(info.ModelObject.BladeCount):
                t = info.SimulationTime - info.Model.simulationStartTime
                info.StructValue[i].Value = scale[i] * amp * math.sin(omega * t)
                info.StructValue[i].Velocity = (
                    omega * scale[i] * amp * math.cos(omega * t)
                )
                info.StructValue[i].Acceleration = (
                    -(omega**2) * scale[i] * amp * math.sin(omega * t)
                )
