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

add_executable(Syracuse
    app/main.cpp
    include/pic/core/Simulation.hpp
    include/pic/core/SimulationState.hpp
    include/pic/core/SimulationConfig.hpp
    include/pic/core/Constants.hpp
    include/pic/particles/ParticleSpecies.hpp
    include/pic/grid/Grid.hpp
    include/pic/grid/Field.hpp
    include/pic/physics/ParticleInitializer.hpp
    include/pic/physics/ChargeDeposition.hpp
    include/pic/physics/FieldSolver.hpp
    include/pic/physics/FieldInterpolator.hpp
    include/pic/physics/ParticlePusher.hpp
    include/pic/physics/LeapfrogIntegrator.hpp
    src/core/Simulation.cpp
    src/particles/ParticleSpecies.cpp
    src/grid/Grid.cpp
    src/physics/ParticleInitializer.cpp
    src/physics/ChargeDeposition.cpp
    src/physics/FieldSolver.cpp
    src/physics/FieldInterpolator.cpp
    src/physics/ParticlePusher.cpp
    src/physics/LeapfrogIntegrator.cpp
    tests/test_deposition.cpp
    tests/test_field_solver.cpp
    tests/test_interpolation.cpp
    tests/test_simulation.cpp
)

target_include_directories(Syracuse PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Syracuse PRIVATE
    glfw
    glm::glm
    glad_gl_core_33
    imgui
)

# Platform specific settings

if(MSVC)
    target_compile_options(Syracuse PRIVATE /W4)
else()
    target_compile_options(Syracuse PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()

add_custom_command(TARGET Syracuse POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/assets"
    "$<TARGET_FILE_DIR:Syracuse>/assets"
)