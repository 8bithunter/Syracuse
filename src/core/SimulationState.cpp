#include "pic/core/SimulationState.hpp"

#include <stdexcept>
#include <utility>
#include <cmath>

namespace pic {

SimulationState::SimulationState(
    Grid grid,
    std::vector<ParticleSpecies> species
)
    : grid(std::move(grid)),       // initialize grid
      species(std::move(species)), // initialize species
      field()                      // initialize field
{
    field.resize(this->grid.numNodes()); // (*this).grid.numNodes()
}

bool SimulationState::isValid() const {
    if (!std::isfinite(time) || time < 0.0) {
        return false;
    }

    if (grid.numNodes() == 0) {
        return false;
    }

    if (!field.isValid(grid.numNodes())) {
        return false;
    }

    for (const ParticleSpecies& s : species) { 
        if (!s.isValid()) {
            return false;
        }
    }

    return true;
}

}