set(SRCS
        1_sonar_sweep.cpp
        2_dive.cpp
        3_binary_diagnostic.cpp
        4_giant_squid.cpp
        5_hydrothermal_venture.cpp
        6_lanternfish.cpp
        7_whales.cpp
        )
# Add Catch2 Definition
include(Catch)

# Create Executables
foreach (SRC ${SRCS})
    get_filename_component(BIN ${SRC} NAME_WE) # Grab Filename w/o path and extension
    add_executable(${BIN} ${SRC} main.cpp) # Catch main should be its own file to avoid recompilation
    target_link_libraries(${BIN} PRIVATE CONAN_PKG::catch2 CONAN_PKG::fmt)
    catch_discover_tests(${BIN})
endforeach ()
