TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

unix:!macx {
	INCLUDEPATH += /usr/local/include/SDL2
	LIBS += -LC:/usr/local/lib -lSDL2
}

SOURCES += main.cpp \
    control.cpp \
    figures.cpp \
    gamefield.cpp \
    output.cpp \
    score.cpp

OTHER_FILES += \
    tetris.pro.user

HEADERS += \
    control.h \
    fig_source.h \
    figures.h \
    gamefield.h \
    number_source.h \
    output.h \
    score.h

