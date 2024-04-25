cmake_minimum_required(VERSION 3.0.0)
project(sinop VERSION 0.1.0 LANGUAGES C CXX)

set(SOURCES
    main.cpp
    FlightSimulator.cpp
    Interpreter.cpp
    Renderer.cpp
    Texture.cpp
)

set(HEADERS
    FlightSimulator.h
    helperfunctions.h
    Interpreter.h
    Renderer.h
    RenderMath.h
    Texture.h)

find_package(PNG REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(${PNG_INCLUDE_DIR})
include_directories(${OpenGL_INCLUDE_DIR})

add_executable(sinop main.cpp ${SOURCES} ${HEADERS})
target_link_libraries(sinop ${PNG_LIBRARY} ${OpenGL_LIBRARY})
target_link_libraries(sinop
    GL
    GLU
    glut
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)