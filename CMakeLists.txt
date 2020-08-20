cmake_minimum_required(VERSION 3.18)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

if(${TO_WINDOWS})
    # the name of the target operating system
    SET(CMAKE_SYSTEM_NAME Windows)

    # which compilers to use for C and C++
    SET(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc-posix)
    SET(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++-posix)
    SET(CMAKE_RC_COMPILER x86_64-w64-mingw32-windres)

    # here is the target environment located
    SET(CMAKE_FIND_ROOT_PATH  /usr/x86_64-w64-mingw32 /home/andrew/Projects/Vendor_mingw )

    # adjust the default behaviour of the FIND_XXX() commands:
    # search headers and libraries in the target environment, search
    # programs in the host environment
    set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
    set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
    set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
endif()

project(CrApp)

file(GLOB_RECURSE MY_SOURCE_FILES CONFIGURE_DEPENDS 
    source/*.cpp source/*.h)
add_executable(${PROJECT_NAME} ${MY_SOURCE_FILES})

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
#find_package(SDL2_ttf REQUIRED)
#find_package(SDL2_mixer REQUIRED)
find_package(SQLite3 REQUIRED)

if (CMAKE_SYSTEM_NAME MATCHES Windows)
    target_link_libraries(${PROJECT_NAME} PUBLIC 
        -static-libgcc -static-libstdc++ 
        SQLite::SQLite3 SDL2::Main SDL2::Image)
elseif(CMAKE_SYSTEM_NAME MATCHES Linux)
    target_link_libraries(${PROJECT_NAME} PUBLIC 
    sqlite3 SDL2::Main SDL2::Image)
endif()