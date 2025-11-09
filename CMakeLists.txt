cmake_minimum_required(VERSION 3.16)
project(GravitySim)

# C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include headers
include_directories(include)

# --- SFML MANUAL SETUP ---
# Adjust these paths if your SFML folder is somewhere else
set(SFML_DIR "C:/SFML")
include_directories(${SFML_DIR}/include)
link_directories(${SFML_DIR}/lib)

# --- Source files ---
add_executable(GravitySim src/main.cpp)
add_executable(BinarySystem src/BinarySystem.cpp)
add_executable(ThreeBodySystem src/ThreeBodySystem.cpp)
add_executable(SunEarth src/SunEarth.cpp)


# --- Link SFML libraries ---
# (Debug builds usually use the -d variants)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_libraries(GravitySim
        sfml-graphics-d
        sfml-window-d
        sfml-system-d
    )
else()
    target_link_libraries(GravitySim
        sfml-graphics
        sfml-window
        sfml-system
    )
endif()

# --- Copy SFML DLLs automatically (optional but helpful) ---
add_custom_command(TARGET GravitySim POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${SFML_DIR}/bin"
        "$<TARGET_FILE_DIR:GravitySim>"
)
