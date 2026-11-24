#pragma once

#include "pic/grid/Grid.hpp"
#include "pic/grid/Field.hpp"
#include "pic/particles/ParticleSpecies.hpp"

#include <cstddef>
#include <vector>

namespace pic {

class SimulationState {
public:
    Grid grid;
    std::vector<ParticleSpecies> species;
    Field field;

    double time = 0.0;
    std::size_t step = 0;

    SimulationState(
        Grid grid,
        std::vector<ParticleSpecies> species
    );

    bool isValid() const;
};

}