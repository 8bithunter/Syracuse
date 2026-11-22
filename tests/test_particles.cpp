#include "test_utils.hpp"
#include "pic/particles/ParticleSpecies.hpp"

#include <stdexcept>

void testParticles() {

    pic::ParticleSpecies electrons(
        "electrons",
        -1.602176634e-19,
        9.1093837e-31,
        1.0e10
    );

    test::check(
        electrons.name == "electrons",
        "Particle species has correct name"
    );

    test::check(
        electrons.charge < 1,
        "Electron charge is negative"
    );

    test::check(
        electrons.mass > 0,
        "Electron mass is positive"
    );

    // add particles
    electrons.x = { 1.0, 2.0, 3.0 };
    electrons.v = { 100.0, 200.0, 300.0 };

    test::check(
        electrons.size() == 3,
        "Particle species reports correct particle count"
    );

    test::check(
        electrons.isValid(),
        "Particle species is valid when arrays match"
    );

    // introduce inconsistency
    electrons.v.pop_back();
    
    test::check(
        !electrons.isValid(),
        "Particle species rejects mismatched arrays"
    );

    // invalid mass
    test::checkThrows(
        [] {
            pic::ParticleSpecies invalid(
                "invalid",
                1.0,
                -1.0,
                1.0
            );
        },
        "Particle species rejects negative mass"
    );
}