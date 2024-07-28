cmake_minimum_required(VERSION 3.25)
project(sfml_algorithmus)

set(CMAKE_CXX_STANDARD 20)

# Find the SFML package
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Add the executable
add_executable(sfml_algorithmus
        src/main.cpp
        src/window.cpp
)

# Include directories
target_include_directories(sfml_algorithmus PRIVATE src/include)

# Link SFML libraries
target_link_libraries(sfml_algorithmus PRIVATE sfml-graphics sfml-window sfml-system)