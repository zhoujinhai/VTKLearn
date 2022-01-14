cmake_minimum_required(VERSION 2.8)

project(RenderCylinder)

set(VTK_DIR D:/VTK/VTK-8.2.0-build)
find_package(VTK REQUIRED)
message(${VTK_LIBRARIES})

include(${VTK_USE_FILE})

add_executable(${PROJECT_NAME} RenderCylinder.cpp)
target_link_libraries(${PROJECT_NAME} ${VTK_LIBRARIES})




