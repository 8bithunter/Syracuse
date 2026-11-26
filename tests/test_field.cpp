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

    field.resize(5);

    test::check(
        field.isValid(5),
        "Field resize creates correct array sizes"
    );

    bool initializedToZero = true;

    for (std::size_t i = 0; i < 5; ++i) {
        if (field.chargeDensity[i] != 0.0 ||
            field.potential[i] != 0.0 ||
            field.electricField[i] != 0.0) {
            initializedToZero = false;
            break;
        }
    }

    test::check(
        initializedToZero,
        "New field elements are initialized to zero"
    );

    field.chargeDensity[0] = 10.0;
    field.potential[0] = 20.0;
    field.electricField[0] = 30.0;

    field.resize(10);

    test::check(
        field.isValid(10),
        "Field can be resized to a larger size after initialization"
    );

    test::checkNear(
        field.chargeDensity[0],
        10.0,
        1e-12,
        "Resize preserves existing values"
    );

    test::checkNear(
        field.chargeDensity[9],
        0.0,
        1e-12,
        "Newly added elements are 0"
    );
}