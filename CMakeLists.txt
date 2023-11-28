cmake_minimum_required(VERSION 3.20)

project(CPP_Assignment_05)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
  add_compile_options(/permissive-)
endif()

if(XCODE)
  # Enable building of universal MacOS executable (works both on Intel 
  # and ARM based Mac's). Requires Xcode 12.2 or newer.
  #set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64" CACHE STRING "" FORCE)
endif()  

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(3rd-party)
add_subdirectory(particle)
