cmake_minimum_required(VERSION 3.20)
project(easygl)

set(CMAKE_CXX_STANDARD 17)

find_package(glad REQUIRED)
find_package(glm REQUIRED)

include_directories(include)
add_library(${PROJECT_NAME}
    src/buffer.cpp
    src/framebuffer.cpp
    src/program.cpp
    src/shader.cpp
    src/vertex_layout.cpp
    src/utils.cpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC glad::glad glm::glm)