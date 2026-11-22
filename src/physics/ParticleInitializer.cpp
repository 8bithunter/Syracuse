#include "pic/physics/ParticleInitializer.hpp"

#include <cmath>
#include <stdexcept>

#include "pic/core/Constants.hpp"

namespace pic {

// initializes seed
ParticleInitializer::ParticleInitializer(std::uint64_t seed)
    : rng(seed)
{
}

// builds and returns a complete ParticleSpecies object
ParticleSpecies ParticleInitializer::initialize(
    const SpeciesConfig& config,
    const Grid& grid
) {
    if (config.numParticles == 0) { // prevent initializing an empty species
        throw std::invalid_argument(
            "Species must contain at least one particle."
        );
    }

    // construct the species container with physical properties from the config
    ParticleSpecies species(
        config.name,
        config.charge,
        config.mass,
        config.macroWeight
    );

    // allocate memory for x and v
    species.x.resize(config.numParticles);
    species.v.resize(config.numParticles);

    // populate initial positions and velocities based on config distrubutions
    initializePositions(species, config, grid);
    initializeVelocities(species, config);

    return species;
}

// distributes macroparticles across domain
void ParticleInitializer::initializePositions(
    ParticleSpecies& species,
    const SpeciesConfig& config,
    const Grid& grid
) {
    switch (config.spatialDistribution) {

        // uniform distribution [min, max)
        case SpatialDistribution::Uniform: {
            std::uniform_real_distribution<double> distribution(
                grid.minPosition,
                grid.maxPosition()
            );

            for (std::size_t i = 0; i < species.size(); ++i) {
                species.x[i] = distribution(rng);
            }

            break;
        }
    }
}

// assigns initial velocities to each macroparticle based on plasma temperature and drift
void ParticleInitializer::initializeVelocities(
    ParticleSpecies& species,
    const SpeciesConfig& config
) {
    switch (config.velocityDistribution) {

        // Maxwell-Boltzmann distribution
        // thermal velocity standard dev: v_th = sqrt(k_B * T / m)
        case VelocityDistribution::Maxwellian: {
            const double sigma = std::sqrt(
                constants::boltzmannConstant
                * config.temperature
                / config.mass
            );

            // Sample from a Gaussian centered at bulk driftVelocity with spread sigma
            std::normal_distribution<double> distribution(
                config.driftVelocity,
                sigma
            );

            for (std::size_t i = 0; i < species.size(); ++i) {
                species.v[i] = distribution(rng);
            }

            break;
        }

        // Placeholder for future profiles
        case VelocityDistribution::Uniform:
            throw std::logic_error(
                "Uniform velocity initialization not implemented yet."
            );
    }
}

}