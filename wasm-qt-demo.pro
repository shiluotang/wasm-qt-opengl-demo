CONFIG += c++17
CONFIG += debug

QT += core gui core5compat widgets openglwidgets 

wasm {
    # QMAKE_LFLAGS += --use-port=sdl2
}

SOURCES = app.cc mywindow.cc
HEADERS = mywindow.h
