cmake_minimum_required(VERSION 3.10)
project(IQ)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(IQ
        buttons.cpp
        buttons.h
        config.h
        CreateWindows.cpp
        CreateWindows.h
        EventHandler.cpp
        EventHandler.h
        gameEngine.cpp
        gameEngine.h
        gamePresenter.cpp
        gamePresenter.h
        main.cpp)

target_link_libraries(IQ -lSDL2)
