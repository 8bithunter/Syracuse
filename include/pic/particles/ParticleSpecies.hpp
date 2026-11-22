
#pragma once

#include <vector>
#include <string>
#include <cstddef>
#include <cmath>
#include <stdexcept>
#include <utility>

namespace pic {

struct ParticleSpecies {

    // Identification
    std::string name;

    // Physical properties
    double charge;
    double mass;
    double macroWeight;

    // Particle data (SoA)
    std::vector<double> x;
    std::vector<double> v;

    ParticleSpecies(
        std::string name,
        double charge,
        double mass,
        double macroWeight
    )
        : name(std::move(name)),
          charge(charge),
          mass(mass),
          macroWeight(macroWeight)
    {
        if (this->name.empty())
            throw std::invalid_argument("Species name cannot be empty.");

        if (!std::isfinite(charge))
            throw std::invalid_argument("Species charge must be finite.");

        if (!std::isfinite(mass) || mass <= 0.0)
            throw std::invalid_argument("Species mass must be finite and positive.");

        if (!std::isfinite(macroWeight) || macroWeight <= 0.0)
            throw std::invalid_argument("Macro weight must be finite and positive.");
    }

    std::size_t size() const {
        return x.size();
    }

    bool isValid() const {
        return x.size() == v.size();
    }
};

}
