cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

project(wasm-qt-demo VERSION 1.0)

find_package(Qt6 REQUIRED COMPONENTS Core5Compat Gui OpenGLWidgets Widgets)

qt_standard_project_setup()

qt_add_executable(${PROJECT_NAME}
    src/app.cc
    src/mywindow.cc
    src/mainwindow.cc
    ## header file in the same directory can be find out automatically
    ## otherwise it must be include explicitly for qt moc procedure
    # src/mywindow.h
    # src/mainwindow.h
    resources/myresources.qrc
)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

if (EMSCRIPTEN)
    target_link_libraries(${PROJECT_NAME} PRIVATE png-mt)
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt::Core
    Qt::Core5Compat
    Qt::Gui
    Qt::OpenGLWidgets
    Qt::Widgets
)
