# Pruebas de consola (sin interfaz Qt): logica, configuracion y persistencia.
TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle qt

INCLUDEPATH += ../modelo ../persistencia ../aplicacion

SOURCES += pruebas.cpp \
    $$files(../modelo/*.cpp) \
    $$files(../persistencia/*.cpp) \
    ../aplicacion/fabricapartida.cpp \
    ../aplicacion/gestorpartidas.cpp
