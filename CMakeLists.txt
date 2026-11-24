cmake_minimum_required(VERSION 3.24)

project(Syracuse
    VERSION 0.1.0
    DESCRIPTION "3D Particle-In-Cell Plasma Simulator"
    LANGUAGES C CXX
)

# C++ Standard

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build Options

option(SYRACUSE_BUILD_TESTS "Build unit tests" OFF)

include(FetchContent)

# GLFW

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(glfw)

# GLM

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.1
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(glm)

# Glad

FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG v2.0.8
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(glad)

add_subdirectory(
    ${glad_SOURCE_DIR}/cmake
    ${glad_BINARY_DIR}/cmake
)

glad_add_library(glad_gl_core_33
    REPRODUCIBLE
    API gl:core=3.3
)

# Dear ImGui

FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.92.6-docking
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(imgui)

add_library(imgui STATIC
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
)

target_link_libraries(imgui PUBLIC glfw)

# Syracuse executable

# ----------------------------------------------------------
# Syracuse Core Library
# ----------------------------------------------------------

add_library(pic_core STATIC
    src/core/Simulation.cpp
    src/core/SimulationConfig.cpp

    src/particles/ParticleSpecies.cpp

    src/grid/Grid.cpp

    src/physics/ParticleInitializer.cpp
    src/physics/ChargeDeposition.cpp
    src/physics/ElectrostaticFieldSolver.cpp
    src/physics/FieldInterpolator.cpp
    src/physics/ParticlePusher.cpp
    src/physics/LeapfrogIntegrator.cpp
    src/core/SimulationState.cpp
)

target_include_directories(pic_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# ----------------------------------------------------------
# Syracuse Application
# ----------------------------------------------------------

add_executable(Syracuse
    app/main.cpp
)

target_link_libraries(Syracuse PRIVATE
    pic_core
    glfw
    glm::glm
    glad_gl_core_33
    imgui
)

# ----------------------------------------------------------
# Testing
# ----------------------------------------------------------

if(SYRACUSE_BUILD_TESTS)
    enable_testing()

    add_executable(syracuse_tests
    tests/test_main.cpp
    tests/test_grid.cpp
    tests/test_field.cpp
    tests/test_particles.cpp
    tests/test_initializer.cpp
    tests/test_simulation_state.cpp
    )

    target_include_directories(syracuse_tests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/tests
    )

    target_link_libraries(syracuse_tests PRIVATE
        pic_core
    )

    set(SYRACUSE_TEST_CASES
        grid
        field
        particles
        initializer
        simulationState
    )

    foreach(test_case IN LISTS SYRACUSE_TEST_CASES)
        add_test(
            NAME Syracuse.${test_case}
            COMMAND $<TARGET_FILE:syracuse_tests> ${test_case}
        )
    endforeach()
endif()

# ----------------------------------------------------------
# Platform specific settings
# ----------------------------------------------------------

if(MSVC)
    target_compile_options(pic_core PRIVATE /W4)
    target_compile_options(Syracuse PRIVATE /W4)

    if(SYRACUSE_BUILD_TESTS)
        target_compile_options(syracuse_tests PRIVATE /W4)
    endif()

else()
    target_compile_options(pic_core PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )

    if(SYRACUSE_BUILD_TESTS)
        target_compile_options(syracuse_tests PRIVATE
            -Wall
            -Wextra
            -Wpedantic
        )
    endif()
endif()

# ----------------------------------------------------------
# Copy assets
# ----------------------------------------------------------

add_custom_command(TARGET Syracuse POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/assets"
    "$<TARGET_FILE_DIR:Syracuse>/assets"
)