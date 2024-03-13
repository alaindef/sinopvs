TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

CONFIG += opengl

LIBS += -lGL -lGLU -lglut
LIBS += -lpng


SOURCES += main.cpp \
    FlightSimulator.cpp \
    Interpreter.cpp \
    Renderer.cpp \
    Texture.cpp

SUBDIRS += \
    SinopQt.pro

DISTFILES += \
    SinopQt.pro.user

HEADERS += \
    FlightSimulator.h \
    helperfunctions.h \
    Interpreter.h \
    Renderer.h \
    RenderMath.h \
    Texture.h
