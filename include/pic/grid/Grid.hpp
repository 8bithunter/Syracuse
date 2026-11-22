#pragma once

#include <cassert>
#include <stdexcept>
#include <cstddef>
#include <cmath>

namespace pic {

struct Grid {
    std::size_t numCells;     // Number of spatial cells
    double length;            // Domain length (m)
    double dx;                // Grid spacing (m)
    double minPosition;       // Domain start (m)
    double transverseArea;    // For volumes (m^2)

    Grid(
        double length,
        std::size_t numCells,
        double minPosition = 0.0,
        double transverseArea = 1.0
    )
        : numCells(numCells),
          length(length),
          dx(calculateDx(length, numCells)),
          minPosition(minPosition),
          transverseArea(transverseArea)
    {
        if (numCells == 0)
            throw std::invalid_argument("Grid must have at least one cell.");

        if (!std::isfinite(length) || length <= 0.0)
            throw std::invalid_argument("Grid length must be finite and positive.");

        if (!std::isfinite(minPosition))
            throw std::invalid_argument("Grid minimum position must be finite.");

        if (!std::isfinite(transverseArea) || transverseArea <= 0.0)
            throw std::invalid_argument("Transverse area must be finite and positive.");

        assert(dx > 0.0);
    }

    double maxPosition() const {
        return minPosition + length;
    }

    std::size_t numNodes() const {
        return numCells;
    }

    // Returns spatial coordinate of node i: x_min + i * dx
    double nodePosition(std::size_t i) const {
        assert(i < numNodes() && "Node index out of bounds");
        return minPosition + static_cast<double>(i) * dx;
    }

private:
    static double calculateDx(double length, std::size_t numCells) {
        if (!std::isfinite(length) || length <= 0.0)
            throw std::invalid_argument("Invalid grid length.");

        if (numCells == 0)
            throw std::invalid_argument("Grid must have at least one cell.");

        return length / static_cast<double>(numCells);
    }
};

}