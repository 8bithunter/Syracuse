#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include "test_utils.hpp"

// Forward declarations of your existing void test functions
void testGrid();
void testField();
void testParticles();
void testInitializer();

int main(int argc, char** argv) {
    // Map CLI names to your void test functions
    const std::unordered_map<std::string, std::function<void()>> tests = {
        {"grid",        testGrid},
        {"field",       testField},
        {"particles",   testParticles},
        {"initializer", testInitializer}
    };

    // If no arguments are passed, run all tests
    if (argc < 2) {
        for (const auto& [name, func] : tests) {
            func();
        }
        return test::summary();
    }

    // Run the specific test requested by CTest
    std::string test_name = argv[1];
    auto it = tests.find(test_name);
    if (it == tests.end()) {
        std::cerr << "Unknown test: " << test_name << "\n";
        return 1;
    }

    it->second();
    return test::summary();
}
