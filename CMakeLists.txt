cmake_minimum_required(VERSION 3.14)

project(my_gtk_app LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# find_package(Boost REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(ImageMagick COMPONENTS Magick++ REQUIRED)

pkg_check_modules(GTKMM4 REQUIRED gtkmm-4.0)

file(GLOB_RECURSE SOURCES "src/*.cc")
file(GLOB_RECURSE HEADERS "include/*.h")
add_executable(my_gtk_app ${SOURCES} ${HEADERS})

add_definitions(-DMAGICKCORE_QUANTUM_DEPTH=16)
add_definitions(-DMAGICKCORE_HDRI_ENABLE=1)

target_include_directories(my_gtk_app PRIVATE ${GTKMM4_INCLUDE_DIRS} ${ImageMagick_INCLUDE_DIRS} include)
target_link_libraries(my_gtk_app PRIVATE ${GTKMM4_LIBRARIES} ${ImageMagick_LIBRARIES})
target_compile_options(my_gtk_app PRIVATE ${GTKMM4_CFLAGS_OTHER})