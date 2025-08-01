cmake_minimum_required(VERSION 3.5)

project(QT5_multithread_progress LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets)

add_executable(QT5_multithread_progress
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    worker.cpp
    worker.h
)

target_link_libraries(QT5_multithread_progress Qt5::Widgets)
