#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include <cmath>

namespace test {

inline int testsPassed = 0;
inline int testsFailed = 0;

// checks whether something is true
inline void check( 
    bool condition,
    const std::string& testName
) {
    if (condition) {
        std::cout << "[PASS] " << testName << '\n';
        testsPassed++;
    } else {
        std::cerr << "[FAIL] " << testName << '\n';
        testsFailed++;
    }
}

// checks whether two floats are sufficiently close
inline void checkNear(
    double actual,
    double expected,
    double tolerance,
    const std::string& testName
) {
    check(
        std::isfinite(actual) &&
        std::abs(actual - expected) <= tolerance,
        testName
    );
}

// checks whether a function throws an exception
template <typename Function>
void checkThrows(
    Function function,
    const std::string& testName
) {
    try {
        function();
        check(false, testName);
    }
    catch (const std::exception&) {
        check(true, testName);
    }
}

inline int summary() {
    std::cout << "\n--------------------------\n";
    std::cout << "Tests passed: " << testsPassed << '\n';
    std::cout << "Tests failed: " << testsFailed << '\n';
    std::cout << "\n--------------------------\n";

    return testsFailed == 0 ? 0 : 1;
}

}