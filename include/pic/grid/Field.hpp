#pragma once

#include <vector>
#include <cstddef>
#include <algorithm>

namespace pic {

struct Field {
    // Grid quantities
    std::vector<double> chargeDensity; // rho (C/m^3)
    std::vector<double> potential;     // phi (V)
    std::vector<double> electricField; // Ex (V/m)

    void resize(std::size_t numNodes) {
        chargeDensity.resize(numNodes);
        potential.resize(numNodes);
        electricField.resize(numNodes);
    }

    void clear() {
        std::fill(chargeDensity.begin(), chargeDensity.end(), 0.0);
        std::fill(potential.begin(), potential.end(), 0.0);
        std::fill(electricField.begin(), electricField.end(), 0.0);
    }

    bool isValid(std::size_t expectedNodes) const {
        return chargeDensity.size() == expectedNodes
            && potential.size() == expectedNodes
            && electricField.size() == expectedNodes;
    }
};

}