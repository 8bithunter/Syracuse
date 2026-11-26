#pragma once

#include "pic/grid/Grid.hpp"
#include "pic/grid/Field.hpp"
#include "pic/particles/ParticleSpecies.hpp"

#include <vector>
#include <algorithm>
#include <cstddef>

namespace pic {

class ChargeDeposition {
public:
    void deposit(
        const Grid& grid,
        const std::vector<ParticleSpecies>& species,
        Field& field,
        double transverseArea = 1.0
    ) const;
};
}