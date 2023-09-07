import math


class TorqueController(object):
    def Calculate(self, info):
        if info.NewTimeStep:
            targetTorque = 100.0 * info.ModelObject.UnitsConversionFactor("FF.LL")
            info.Value = targetTorque / (1.0 + math.exp(-info.SimulationTime))
