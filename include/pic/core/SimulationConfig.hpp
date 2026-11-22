
#pragma once

#include <string>
#include <vector>
#include <cstddef>
#include <cstdint>
#include <cassert>

namespace pic {

// Initial particle distribution
enum class SpatialDistribution {
    Uniform
};

enum class VelocityDistribution {
    Maxwellian,
    Uniform,
    // TwoStream 
    // can add more later
};

// Configuration for one particle species
struct SpeciesConfig {

    // Identification
    std::string name;

    // Physical properties
    double charge;          // C
    double mass;            // kg
    double macroWeight;     // Physical particles per computational particle

    // Particle initialization
    std::size_t numParticles;

    SpatialDistribution spatialDistribution;
    VelocityDistribution velocityDistribution;

    double temperature;     // K
    double driftVelocity;   // m/s
};

// Global simulation configuration
struct SimulationConfig {

    // Spatial domain
    double domainLength;
    std::size_t numCells;

    // Simulation timing
    double timeStep;
    std::uint64_t numSteps;

    // Initial plasma conditions
    std::vector<SpeciesConfig> species;

    // Reproducibility
    std::uint64_t randomSeed;

    bool isValid() const;
};

}
