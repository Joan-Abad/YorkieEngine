cmake_minimum_required(VERSION 3.12)

project(YorkieEngine)

set(CMAKE_CXX_STANDARD 17)

# Add all files 
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/YorkieEngine/src/*.cpp")
file(GLOB_RECURSE HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/YorkieEngine/include/*.h")

#Removes the ALL_BUILD and ZERO_CHECK projects
#set(CMAKE_SUPPRESS_REGENERATION true)

# Create the DLL
add_library(YorkieEngine SHARED ${SOURCES} ${HEADERS})

# Set include directories
target_include_directories(YorkieEngine 
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/YorkieEngine/include
    ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/entt/src
    ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/glm
    ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/glfw/include
)

# Link your game engine target with GLFW
target_link_libraries(YorkieEngine ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/glfw/lib/glfw3.lib)

# Find and link OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(YorkieEngine OpenGL::GL)

target_compile_definitions(YorkieEngine PRIVATE YENGINE_EXPORT)

