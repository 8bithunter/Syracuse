# Syracuse

A particle-in-cell plasma physics simulator made from scratch built for learning, experimentation and curiosity.

Syracuse is an educational and experimental project to explore plasma physics, numerical simulation, scientific computing, and computer graphics by building a particle-in-cell (PIC) plasma simulator from the ground up.

Syracuse is named after the birthplace of [Archimedes](https://en.wikipedia.org/wiki/Archimedes) who established the science of hydrostatics, serving as inspiration for our project as our philosophy revolves around using math to understand physical phenomena from first principles much like Archimedes' work.

**Status: Early development.** The project is currently in the planning and foundational stages, with plans to
1. Understand the relevant physics and mathematics.
2. Derive or study the numerical methods required.
3. Implement them against known solutions.
4. Optimize the implementation.
5. Visualize the results.
6. Document what we learn.

We wanted to build something that would force us to learn plasma physics, numerical methods, performance optimization, scientific validation and error analysis, while also developing our skills in C++ programming, GPU/graphical computation, rendering, and mathematical modelling.

## What is the goal?
The long-term goal is to build a PIC simulator that can be used in two complementary ways:

### Graphically
Provide an interactive visualization of the simulation, allowing us to observe things like:
- Particle motion
- Electric and magnetic fields
- Charge density
- Plasma behaviour
- Energy distributions
- Boundary interactions

### Numerically
Allow simulations to be configured and run without relying on the graphical interface, making it possible to:
- Run simulations through the command line
- Collect numerical results
- Compare results against analytical or established numerical solutions (validation)
- Investigate the effects of changing physical parameters
- Study the accuracy of the numerical methods

### Scientific Accuracay
Although Syracuse is primarily a learning project, we want the physics to be as accurate as possible. Therefore, we plan to validate our simulations against problems with known solutions wherever possible.

This includes testing:
- Numerical integration
- Particle motion
- Field calculations
- Conservation laws
- Boundary conditions
- Numerical stability
- Convergence with increasing resolution
- Energy and momentum behaviour
- Other analytically solvable or well-established test problems

## Technology
The project is currently being developed primarily with **C++** for simulation and numerical computation, **OpenGL** for rendering, **Git** for version control

## Roadmap
The project is still at an early stage
### Foundations
- [ ] Establish C++ project structure and build system
- [ ] Establish OpenGL Rendering framework
- [ ] Implement basic particle representation
- [ ] Implement basic visualization
- [ ] Develop initial numerical integration methods
- [ ] Establish testing framework

### Plasma Physics
- [ ] Implement particle motion
- [ ] Implement charge deposition
- [ ] Implement field calculation
- [ ] Implement field interpolation
- [ ] Implement electromagnetic particle updates
- [ ] Introduce appropriate boundary conditions

### Validation
- [ ] Develop analytical test cases
- [ ] Compare numerical and analytical solutions
- [ ] Test convergence and numerical stability
- [ ] Investigate conservation of physical quantities
- [ ] Document numerical errors and limitations

### Performance
- [ ] Profile simulation bottlenecks
- [ ] Optimize CPU implementation
- [ ] Investigate parallel computation
- [ ] Explore GPU-based computation

### Exploration
- [ ] Build interactive simulation controls
- [ ] Run controlled plasma experiments
- [ ] Explore increasingly realistic configurations
- [ ] Compare results with establish physical behaviour

## Long-term vision
Syracuse is intended to be a deep learning tool for ourselves, where we can follow a physical problem from formulation, through numerical approximation and implementation, all the way to visualization and validation.
