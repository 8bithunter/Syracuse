#pragma once

#include "pic/core/SimulationConfig.hpp"
#include "pic/particles/ParticleSpecies.hpp"
#include "pic/grid/Grid.hpp"

#include <cstdint>
#include <random>

namespace pic {

class ParticleInitializer {
public:
    explicit ParticleInitializer(std::uint64_t seed);

    ParticleSpecies initialize( // initializer creates a compile species and returns it
        const SpeciesConfig& config,
        const Grid& grid
    );

private:
    std::mt19937_64 rng;

    void initializePositions(
        ParticleSpecies& species,
        const SpeciesConfig& config,
        const Grid& grid
    );

    void initializeVelocities(
        ParticleSpecies& species,
        const SpeciesConfig& config
    );
};

}