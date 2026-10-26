TEMPLATE = app
TARGET = TP2POOCartas

QT += core gui widgets
CONFIG += c++17
CONFIG -= console
CONFIG -= app_bundle

msvc: QMAKE_CXXFLAGS += /utf-8

# Carpeta del proyecto: permite encontrar config.txt y partidas/ aunque Qt Creator
# compile en otra carpeta (ver RutasAplicacion).
DEFINES += RUTA_PROYECTO=\\\"$$PWD\\\"

INCLUDEPATH += modelo persistencia aplicacion ui

SOURCES += \
    modelo/agua.cpp \
    modelo/elemento.cpp \
    modelo/elementomixto.cpp \
    modelo/elementosmixtos.cpp \
    modelo/fabricaelementos.cpp \
    modelo/fabricaia.cpp \
    modelo/fuego.cpp \
    modelo/iaaleatoria.cpp \
    modelo/iaestrategica.cpp \
    modelo/iajugador.cpp \
    modelo/jugador.cpp \
    modelo/par.cpp \
    modelo/partida.cpp \
    modelo/resultadoataque.cpp \
    modelo/superia.cpp \
    modelo/tabladanio.cpp \
    modelo/tierra.cpp \
    modelo/tipoelemento.cpp \
    persistencia/configuracion.cpp \
    persistencia/lectorconfiguracion.cpp \
    persistencia/repositoriopartidas.cpp \
    aplicacion/fabricapartida.cpp \
    aplicacion/gestorpartidas.cpp \
    aplicacion/rutasaplicacion.cpp \
    ui/cartaelemento.cpp \
    ui/dialogofin.cpp \
    ui/main.cpp \
    ui/ventanainicio.cpp \
    ui/ventanajuego.cpp

HEADERS += \
    modelo/agua.h \
    modelo/elemento.h \
    modelo/elementomixto.h \
    modelo/elementosmixtos.h \
    modelo/fabricaelementos.h \
    modelo/fabricaia.h \
    modelo/fuego.h \
    modelo/ia.h \
    modelo/iaaleatoria.h \
    modelo/iaestrategica.h \
    modelo/iajugador.h \
    modelo/idelemento.h \
    modelo/idia.h \
    modelo/jugador.h \
    modelo/par.h \
    modelo/partida.h \
    modelo/resultadoataque.h \
    modelo/superia.h \
    modelo/tabladanio.h \
    modelo/tierra.h \
    modelo/tipoelemento.h \
    persistencia/configuracion.h \
    persistencia/estadoguardado.h \
    persistencia/lectorconfiguracion.h \
    persistencia/repositoriopartidas.h \
    aplicacion/fabricapartida.h \
    aplicacion/gestorpartidas.h \
    aplicacion/rutasaplicacion.h \
    ui/cartaelemento.h \
    ui/dialogofin.h \
    ui/ventanainicio.h \
    ui/ventanajuego.h

OTHER_FILES += config.txt
