#include "test_utils.hpp"
#include "pic/core/SimulationState.hpp"
#include "pic/core/Constants.hpp"

#include <cmath>

void testSimulationState() {
    // A state is constructed correctly
    // Field arrays are automatically sized
    // Time and step start at 0
    // A valid state passes isValid()
    // Invalid state data is caught

    pic::Grid grid(10.0, 100);

    pic::ParticleSpecies electrons(
        "electrons",
        pic::constants::elementaryCharge * -1,
        pic::constants::electronMass,
        1.0e10
    );

    electrons.x = {1.0, 2.0, 3.0};
    electrons.v = {0.0, 0.0, 0.0};

    std::vector<pic::ParticleSpecies> species;
    species.push_back(electrons);

    pic::SimulationState state(grid, species);

    test::checkNear(
        state.time,
        0.0,
        1e-12,
        "SimulationState starts time at zero"
    );

    test::check(
        state.step == 0,
        "SimulationState starts step at zero"
    );

    test::check(
        state.grid.getNumCells() == 100,
        "SimulationState contains the correct grid"
    );

    test::check(
        state.species.size() == 1,
        "SimulationState contains the correct number of species"
    );

    test::check(
        state.species[0].size() == 3,
        "SimulationState contains the correct number of particles"
    );

    test::check(
        state.field.chargeDensity.size() == 100,
        "Charge density is sized to the grid"
    );

    test::check(
        state.field.potential.size() == 100,
        "Potential is sized to the grid"
    );

    test::check(
        state.field.electricField.size() == 100,
        "Electric field is sized to the grid"
    );

    test::check(
        state.isValid(),
        "New SimulationState is valid"
    );

    state.time = -10.0;

    test::check(
        !state.isValid(),
        "SimulationState rejects negative time"
    );

    state.time = 0.0;
    state.time = std::nan("");

    test::check(
        !state.isValid(),
        "SimulationState rejects NaN time"
    );
}