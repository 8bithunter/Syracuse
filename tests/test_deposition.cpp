#include "test_utils.hpp"

#include "pic/physics/ChargeDeposition.hpp"

#include <vector>
#include <cmath>

void testDeposition() {
    constexpr double area = 1.0;

    pic::Grid grid(10.0, 10);

    pic::ChargeDeposition deposition;

    // test particle exactly on grid node
    pic::ParticleSpecies particle1(
        "test",
        2.0,
        1.0,
        1.0
    );

    particle1.x = {3.0};
    particle1.v = {0.0};

    std::vector<pic::ParticleSpecies> species1 = {particle1};

    pic::Field field1;
    field1.resize(grid.numNodes());

    deposition.deposit(grid, species1, field1, area);

    test::checkNear(
        field1.chargeDensity[3],
        2.0,
        1e-12,
        "Particle on a node deposits all charge there"
    );

    bool onlyNodeThreeHasCharge = true;

    for (std::size_t i = 0; i < grid.numNodes(); ++i) {
        double expected = (i == 3) ? 2.0 : 0.0;

        if (std::abs(field1.chargeDensity[i] - expected) > 1e-12) {
            onlyNodeThreeHasCharge = false;
            break;
        }
    }

    test::check(
        onlyNodeThreeHasCharge,
        "Particle deposits charge only at its grid node"
    );

    // test particle halfway between two nodes

    pic::ParticleSpecies particle2(
        "test2",
        2.0,
        1.0,
        1.0
    );

    particle2.x = {3.5};
    particle2.v = {0.0};

    std::vector<pic::ParticleSpecies> species2 = {particle2};

    pic::Field field2;
    field2.resize(grid.numNodes());

    deposition.deposit(grid, species2, field2, area);

    test::checkNear(
        field2.chargeDensity[3],
        1.0,
        1e-12,
        "Halfway particle deposits half of its charge to the left node"
    );

    test::checkNear(
        field2.chargeDensity[4],
        1.0,
        1e-12,
        "Halfway particle deposits half of its charge to the right node"
    );

    // periodic boundary tests

    pic::ParticleSpecies particle3(
        "test3",
        2.0,
        1.0,
        1.0
    );

    particle3.x = {9.5};
    particle3.v = {0.0};

    std::vector<pic::ParticleSpecies> species3 = {particle3};

    pic::Field field3;
    field3.resize(grid.numNodes());

    deposition.deposit(grid, species3, field3, area);

    test::checkNear(
        field3.chargeDensity[9],
        1.0,
        1e-12,
        "Periodic particle deposits half charge at final node"
    );

    test::checkNear(
        field3.chargeDensity[0],
        1.0,
        1e-12,
        "Periodic particle deposits half charge at first node"
    );

    // charge conservation

    double totalCharge = 0.0;

    for (double rho : field3.chargeDensity) {
        totalCharge += rho * area * grid.dx;
    }

    test::checkNear(
        totalCharge,
        2.0,
        1e-12,
        "Charge deposition conserves total charge"
    );
}