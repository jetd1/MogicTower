cmake_minimum_required(VERSION 3.6)
project(MogicTower)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast")

set(SOURCE_FILES
    damage.cpp
    damage.h
    debug.cpp
    debug.h
    eval.cpp
    eval.h
    graph.cpp
    graph.h
    helpers.h
    init.cpp
    init.h
    main.cpp
    mogic.h
    mogicTower.cpp
    mogicTower.h
    README.md
    routine.cpp
    routine.h
    search.cpp
    search.h
    trans.cpp
    trans.h)

add_executable(MogicTower ${SOURCE_FILES})