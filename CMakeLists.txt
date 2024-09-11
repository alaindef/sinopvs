cmake_minimum_required(VERSION 3.6.0)
project(sinop VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(SOURCES
    main.cpp
    FlightSimulator.cpp
    Renderer.cpp
    Texture.cpp
    calculator.cpp
    tokengenerator.cpp
    rpngenerator.cpp
    vartable.cpp
    runprogram.cpp
    FSData.cpp
)

set(HEADERS
    FlightSimulator.h
    helperfunctions.h
    Renderer.h
    RenderMath.h
    Texture.h
    tokengenerator.h
    rpngenerator.h
    vartable.h
    calculator.h
    utils.h
    runprogram.h
    FSData.h
    )
set(OpenGL_GL_PREFERENCE GLVND)

find_package(PNG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

include_directories(${PNG_INCLUDE_DIR})
include_directories(${OpenGL_INCLUDE_DIR} ${GLFW_INCLUDE_DIRS})

add_executable(sinop main.cpp ${SOURCES} ${HEADERS})
target_link_libraries(sinop ${PNG_LIBRARY} ${OpenGL_LIBRARY})
target_link_libraries(sinop
    ${OPENGL_LIBRARIES}   # OpenGL library
    glfw                  # GLFW library
    ${GLFW_LIBRARIES}
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)