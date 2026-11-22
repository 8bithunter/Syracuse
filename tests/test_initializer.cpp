#include "test_utils.hpp"

#include "pic/physics/ParticleInitializer.hpp"
#include "pic/core/Constants.hpp"

#include <cmath>
#include <vector>

void testInitializer() {
    
    // create a grid
    pic::Grid grid(10.0, 100);

    // create a species configuration
    pic::SpeciesConfig config;

    config.name = "electrons";
    config.charge = pic::constants::elementaryCharge;
    config.mass = pic::constants::electronMass;
    config.macroWeight = 1.0e10;

    config.numParticles = 100000;

    config.spatialDistribution = pic::SpatialDistribution::Uniform;
    config.velocityDistribution = pic::VelocityDistribution::Maxwellian;

    config.temperature = 1.0e5;
    config.driftVelocity = 0.0;

    // initialize particles
    pic::ParticleInitializer initializer(12345);

    pic::ParticleSpecies electrons = initializer.initialize(config, grid);

    // check particle grid
    test::check(
        electrons.size() == config.numParticles,
        "Initializer creates correct number of particles"
    );

    test::check(
        electrons.isValid(),
        "Initialized particles have matching sizes"
    );

    // check particle positions
    bool positionsValid = true;

    for (double x : electrons.x) {
        if (x < grid.minPosition || x >= grid.maxPosition()) {
            positionsValid = false;
            break;
        }
    }

    test::check(
        positionsValid,
        "All particles within bounds"
    );

    // check that velocities are finite
    bool velocitiesFinite = true;

    for (double v : electrons.v) {
        if (!std::isfinite(v)) {
            velocitiesFinite = false;
            break;
        }
    }

    test::check(
        velocitiesFinite,
        "All initialized velocities are finite"
    );

    // calculate average velocity
    double meanVelocity = 0.0;

    for (double v : electrons.v) {
        meanVelocity += v;
    }
    meanVelocity /= electrons.size();

    test::checkNear(
        meanVelocity,
        config.driftVelocity,
        0.05 * std::sqrt(
            pic::constants::boltzmannConstant * 
            config.temperature / config.mass
        ),
        "Maxwellian velocities have approximately correct mean"
    );

    // calculate velocity variance
    double variance = 0.0;

    for (double v : electrons.v) {
        double difference = v - meanVelocity;
        variance += difference * difference;
    }

    variance /= electrons.size();

    double expectedVariance = 
        pic::constants::boltzmannConstant * 
        config.temperature / config.mass;

    test::checkNear(
        variance,
        expectedVariance,
        0.05 * expectedVariance,
        "Maxwellian velocities have approximately equal correct variance"
    );

    // check reproducibility with the same seed
    pic::ParticleInitializer initializer2(12345);

    pic::ParticleSpecies electrons2 = 
        initializer2.initialize(config, grid);

    bool reproducible = true;

    for (std::size_t i = 0; i < electrons.size(); i++) {
        if (electrons.x[i] != electrons2.x[i] ||
            electrons.v[i] != electrons2.v[i]) {
            reproducible = false;
            break;
        }
    }

    test::check(
        reproducible,
        "Same random seed produces idential initialization"
    );
}