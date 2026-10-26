#include <iostream>
#include <array>


constexpr size_t rows = 100;
constexpr size_t cols = 100;

std::array<std::array<std::array<float, 3>, cols>, rows> electricGrid{};
// E_x, E_y, E_z
std::array<std::array<std::array<float, 3>, cols>, rows> magneticGrid{};
// B_x, B_y, B_z


void updateFields() { // calculate curl
    // for i in range(Rows):
        // for j in range(Cols):
            // calculate curl at every point of the new grid
            // to update all of our other vectors
}