cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(main src/main.cpp
        src/main.cpp
        src/headers/PlayerController.h
        src/headers/PlayerController.h
        src/headers/Projectile.h
        src/headers/RPG.h
        src/headers/Invader.h
        src/headers/Shield.h
        src/headers/Game.h
        src/headers/DefaultInvader.h
        src/headers/RareInvader.h
        src/RareInvader.cpp
        src/DefaultInvader.cpp
        src/Shield.cpp
        src/Invader.cpp
        src/RPG.cpp
        src/Game.cpp
        src/Player.cpp
        src/headers/constants.h
        src/InvaderBullet.cpp
        src/PlayerBullet.cpp
        src/headers/View.h
        src/View.cpp
        src/Projectile.cpp
        src/Bullet.cpp
        src/Bullet.cpp
        src/Bullet.cpp
        src/PlayerController.cpp
        src/headers/ActionHandler.h
        src/ActionHandler.cpp
        src/headers/directions.h
        src/headers/ShieldComponent.h
        src/headers/PowerUp.h
        src/headers/PowerUpTypes.h
        src/headers/ScatterBullet.h
)
target_link_libraries(main PRIVATE sfml-graphics)
target_compile_features(main PRIVATE cxx_std_17)

if (WIN32)
    add_custom_command(
            TARGET main
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:main>
            VERBATIM)
endif ()
