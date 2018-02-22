cmake_minimum_required (VERSION 3.1)
project (sdl-graphics)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "-Wall")
set (CMAKE_CXX_FLAGS_RELEASE "-Ofast")

find_package (PkgConfig REQUIRED)
pkg_check_modules (SDL2 sdl2)

# SDL2
if (SDL2_FOUND)
  add_definitions(-DSDL2)

  link_libraries (${SDL2_LIBRARIES})
  include_directories (PUBLIC ${SDL2_INCLUDE_DIRS})
  add_compile_options (${SDL2_CFLAGS_OTHER})
endif ()

add_subdirectory (src)
