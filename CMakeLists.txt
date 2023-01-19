cmake_minimum_required(VERSION 3.24.3)
project(coal_engine 
        VERSION 1.0.0 
        DESCRIPTION "A c++ raw game engine" 
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_SUPPRESS_REGENERATION true)

#========================== ENGINE ==========================#
file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*.h)
file(GLOB_RECURSE RESOURCE_FILES res/**)
add_executable(${PROJECT_NAME} src/engine.cpp ${SOURCE_FILES} ${RESOURCE_FILES})

#========================== INCLUDES ==========================#
include_directories(src)
include_directories(vendor)
include_directories(vendor/glew/include)
include_directories(vendor/glfw/include)
include_directories(vendor/glm)
include_directories(vendor/imgui)
include_directories(vendor/stb_image)

#========================== STB IMAGE ==========================#
add_library(stb_image STATIC vendor/stb_image/stb_image.cpp vendor/stb_image/stb_image.h)
target_link_libraries(${PROJECT_NAME} stb_image)

#========================== GLEW ==========================#
set(glew-cmake_BUILD_SHARED OFF)
set(ONLY_LIBS ON)
add_subdirectory(vendor/glew)
target_link_libraries(${PROJECT_NAME} libglew_static)

#========================== GLFW ==========================#
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(vendor/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

#========================== IMGUI ==========================#
set(IMGUI_PATH vendor/imgui)
file(GLOB IMGUI_FILES
                ${IMGUI_PATH}/*.cpp ${IMGUI_PATH}/*.h 
                ${IMGUI_PATH}/backends/imgui_impl_glfw.h
                ${IMGUI_PATH}/backends/imgui_impl_glfw.cpp
                ${IMGUI_PATH}/backends/imgui_impl_opengl3.h
                ${IMGUI_PATH}/backends/imgui_impl_opengl3.cpp
)
add_library(imgui STATIC ${IMGUI_FILES})
target_link_libraries(${PROJECT_NAME} imgui)

#========================== DEFINITIONS ==========================#
add_definitions(-DGLFW_INCLUDE_NONE -DGLEW_STATIC)

if(CMAKE_BUILD_TYPE MATCHES Debug)
        target_compile_definitions(${PROJECT_NAME} PRIVATE "ENGINE_DEBUG")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
        target_compile_definitions(${PROJECT_NAME} PRIVATE "ENGINE_RELEASE")
endif()

#========================== COMMANDS ==========================#
add_custom_command(
        TARGET  ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/res/
                $<TARGET_FILE_DIR:${PROJECT_NAME}>/res/)