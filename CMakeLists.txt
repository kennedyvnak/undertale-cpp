cmake_minimum_required(VERSION 3.24.3)
project(UndertaleCpp 
        VERSION 1.0.0 
        DESCRIPTION "A undertale copy using c++" 
        LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 20)

add_definitions(-DGLFW_INCLUDE_NONE -DGLEW_STATIC -DSTB_IMAGE_IMPLEMENTATION)

include(${CMAKE_SOURCE_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(src ${CONAN_IMGUI_ROOT}/res/bindings)

file(GLOB_RECURSE SOURCE_FILES src/*(.cpp|.h)) # source files

file(GLOB_RECURSE RESOURCE_FILES res/**)

file(GLOB_RECURSE IMGUI_GLFW_BINDINGS_FILES ${CONAN_IMGUI_ROOT}/res/bindings/imgui_impl_glfw.*) # imgui bindings
file(GLOB_RECURSE IMGUI_OPENGL3_BINDINGS_FILES ${CONAN_IMGUI_ROOT}/res/bindings/imgui_impl_opengl3.*) # imgui bindings

add_executable(${PROJECT_NAME}
               ${SOURCE_FILES}
               ${RESOURCE_FILES}
               ${IMGUI_GLFW_BINDINGS_FILES} ${IMGUI_OPENGL3_BINDINGS_FILES}
)

if(CMAKE_BUILD_TYPE MATCHES Debug)
        target_compile_definitions(${PROJECT_NAME} PRIVATE "ENGINE_DEBUG")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
        target_compile_definitions(${PROJECT_NAME} PRIVATE "ENGINE_RELEASE")
endif()

target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
