add_executable(${PROJECT_NAME} main.cpp ${GLAD_SOURCE})

add_library(SRC_LIB STATIC
        shader.cpp
        cube.cpp
        texture.cpp
        )

target_include_directories(SRC_LIB PUBLIC ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(${PROJECT_NAME} PUBLIC SRC_LIB)
