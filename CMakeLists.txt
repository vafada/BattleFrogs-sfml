cmake_minimum_required(VERSION 3.16)
project(BattleFrogs-SFML LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(BattleFrogs-SFML src/main.cpp
        src/BattleFrogs.cpp
        src/BattleFrogs.h
        src/Player.cpp
        src/Player.h
        src/World.cpp
        src/World.h
        src/ForegroundObject.cpp
        src/ForegroundObject.h
        src/Door.cpp
        src/Door.h
        src/TextScreen.cpp
        src/TextScreen.h)
target_link_libraries(BattleFrogs-SFML PRIVATE sfml-graphics sfml-audio)
target_compile_features(BattleFrogs-SFML PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET BattleFrogs-SFML
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:CMakeSFMLProject>
        VERBATIM)
endif()

install(TARGETS BattleFrogs-SFML)

file(COPY graphics DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY sounds DESTINATION ${CMAKE_BINARY_DIR}/bin)

if (DEBUG)
    add_definitions(-DDEBUG=1)
endif (DEBUG)