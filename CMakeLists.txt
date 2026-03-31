cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_AUTOMOC ON)

project(wasm-qt-demo VERSION 1.0)

find_package(Qt6 REQUIRED COMPONENTS Core5Compat Gui OpenGLWidgets Widgets)

qt_standard_project_setup()

qt_add_executable(${PROJECT_NAME}
    app.cc
    mywindow.cc
    mainwindow.cc
)
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt::Core
    Qt::Core5Compat
    Qt::Gui
    Qt::OpenGLWidgets
    Qt::Widgets
)
