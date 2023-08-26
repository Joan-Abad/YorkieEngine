cmake_minimum_required(VERSION 3.12)

project(YorkieEngine)

set(CMAKE_CXX_STANDARD 17)

#Compile options and configurations
set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Custom" CACHE STRING "" FORCE)

# Add all files 
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/YorkieEngine/src/*.cpp")
file(GLOB_RECURSE HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/YorkieEngine/include/*.h")

#Removes the ALL_BUILD and ZERO_CHECK projects
#set(CMAKE_SUPPRESS_REGENERATION true)

#Set directories 
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<CONFIG>/$<PLATFORM_ID>/${CMAKE_VS_PLATFORM_NAME})

# Create the DLL
add_library(YorkieEngine SHARED ${SOURCES} ${HEADERS})

# Set include directories
target_include_directories(YorkieEngine 
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/YorkieEngine/include
    ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/entt/src
    ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/glm
    ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/glfw/include															
)

# Link your game engine target with GLFW
target_link_libraries(YorkieEngine ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/glfw/lib/glfw3.lib)

# Find and link OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(YorkieEngine OpenGL::GL)

target_compile_definitions(YorkieEngine PRIVATE YENGINE_EXPORT)

# Add a custom command to copy the GLFW DLL to the binary directory
add_custom_command(TARGET YorkieEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
        "$ENV{E}/Projects/SandboxAppTest/Dependencies/YorkieEngine/lib/"
    COMMENT "Copying YorkieEngine files..."
)
