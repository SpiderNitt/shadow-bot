# Impedance Control

## Abstract:
The impedance of a mechanical system can be defined as the ratio of the force applied at a point to the resulting velocity at that point. Thus, impedance control is distinct from both position/velocity control and force control. Impedance control is implemented here to achieve the specified desired dynamics.
## Proposed controller
The designed controller is capable of imposing the desired behavior defined by impedance on the original complicated behavior of the end-effector.
![Block diagram](/documentation/blockDiagram.png)
## Passivity analysis
![Passivity analysis](/documentation/passivityAnalysis.png)
## Modified dynamics
![Modified dynamics](/documentation/modifiedDynamics.png)
## Results:
![Joint position](/documentation/[positionPlot.png)

![Joint velocity](/documentation/[velocityPlot.png)