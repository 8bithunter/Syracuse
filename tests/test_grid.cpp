#include "test_utils.hpp"
#include "pic/grid/Grid.hpp"

#include <cmath>
#include <stdexcept>

void testGrid() {
    // Create a grid with length 10 and 100 cells.
    pic::Grid grid(10.0, 100);

    // Check number of cells.
    test::check(
        grid.numCells == 100,
        "Grid has correct number of cells"
    );

    // check cell spacing
    test::checkNear(
        grid.dx,
        0.1,
        1e-12,
        "Grid has correct cell spacing"
    );

    // check node positions
    test::checkNear(
        grid.nodePosition(0),
        0.0,
        1e-12,
        "First node is at the origin"
    );

    test::checkNear(
        grid.nodePosition(50),
        5.0,
        1e-12,
        "Middle node has correct position"
    );

    test::checkNear(
        grid.nodePosition(99),
        9.9,
        1e-12,
        "Last node has correct position"
    );

    // invalid constructor args
    test::checkThrows(
        [] { pic::Grid grid(10.0, 0); },
        "Grid rejects 0 cells"
    );

    test::checkThrows(
        [] { pic::Grid grid(-10.0, 100); },
        "Grid rejects negative length"
    );

    test::checkThrows(
        [] { pic::Grid grid(0.0, 100); },
        "Grid rejects zero length"
    );
}