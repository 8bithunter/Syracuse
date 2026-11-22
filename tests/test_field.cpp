#include "test_utils.hpp"
#include "pic/grid/Field.hpp"

void testField() {

    pic::Field field;

    field.resize(100);

    test::check(
        field.chargeDensity.size() == 100,
        "Charge density has correct size"
    );

    test::check(
        field.potential.size() == 100,
        "Potential has correct size"
    );

    test::check(
        field.electricField.size() == 100,
        "Electric field has correct size"
    );

    test::check(
        field.isValid(100),
        "Field is valid for 100 nodes"
    );

    test::check(
        !field.isValid(50),
        "Field rejects incorrect expected size"
    );

    // set some vals
    field.chargeDensity[0] = 5.0;
    field.potential[0] = 10.0;
    field.electricField[0] = 15.0;

    // clear everything
    field.clear();

    test::checkNear(
        field.chargeDensity[0],
        0.0,
        1e-12,
        "Clear resets charge density"
    );

    test::checkNear(
        field.potential[0],
        0.0,
        1e-12,
        "Clear resets potential"
    );

    test::checkNear(
        field.electricField[0],
        0.0,
        1e-12,
        "Clear resets electric field"
    );
}