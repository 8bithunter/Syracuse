#include "pic/physics/ChargeDeposition.hpp"

#include <cmath>
#include <stdexcept>
#include <algorithm>
#include <cstddef>

namespace pic {

void ChargeDeposition::deposit(
    const Grid& grid,
    const std::vector<ParticleSpecies>& species,
    Field& field,
    double transverseArea
) const {
    const std::size_t numNodes = grid.numNodes();

    // validate
    if (numNodes == 0 || 
        !std::isfinite(grid.dx) ||
        grid.dx <= 0.0) {
        throw std::invalid_argument("Invalid grid");
    }

    if (!field.isValid(numNodes)) {
        throw std::invalid_argument("Field dimensions do not match grid");
    }

    if (!std::isfinite(transverseArea) || transverseArea <= 0.0) {
        throw std::invalid_argument("Transverse area must be positive and finite");
    }

    // clear density
    std::fill(
        field.chargeDensity.begin(),
        field.chargeDensity.end(),
        0.0
    );

    const double cellVolume = transverseArea * grid.dx;

    for (const ParticleSpecies& s : species) {
        if (!s.isValid()) {
            throw std::invalid_argument("Particle species has mismatched arrays");
        }

        if (!std::isfinite(s.charge) ||
            !std::isfinite(s.macroWeight)) {
            throw std::invalid_argument("Particle charge and weight must be finite");
        }

        if (s.macroWeight <= 0.0) {
            throw std::invalid_argument("Macroparticle weight must be positive.");
        }

        const double particleCharge = s.charge * s.macroWeight;

        if (!std::isfinite(particleCharge)) {
            throw std::invalid_argument("Macroparticle charge is not finite");
        }

        for (double x : s.x) {
            if (!std::isfinite(x)) {
                throw std::invalid_argument("Particle position must be finite");
            }

            const double gridPosition = (x - grid.minPosition) / grid.dx;

            if (!std::isfinite(gridPosition)) {
                throw std::invalid_argument("Particle grid position is not finite.");
            }

            if (gridPosition < 0.0 || 
                gridPosition >= static_cast<double>(numNodes)) {
                throw std::out_of_range("Particle position is outside the grid domain");
            }

            const std::size_t left = static_cast<std::size_t>(std::floor(gridPosition));

            const double fraction = gridPosition - std::floor(gridPosition);

            const std::size_t right = (left + 1) % numNodes;

            const double leftWeight = 1.0 - fraction;
            const double rightWeight = fraction;

            field.chargeDensity[left] += particleCharge * leftWeight / cellVolume;
            field.chargeDensity[right] += particleCharge * rightWeight / cellVolume;
        }
    }
}

}