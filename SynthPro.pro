DESTDIR = bin
OBJECTS_DIR = bin/.obj
MOC_DIR = bin/.moc
RCC_DIR = bin/.rcc
UI_DIR = bin /.ui

HEADERS += src/main/abstraction/synthpro.h \
    src/main/abstraction/module.h \
    src/main/abstraction/port.h \
    src/main/abstraction/sequencer.h \
    src/main/control/csynthpro.h \
    src/main/presentation/psynthpro.h \
    src/main/factory/synthprofactory.h \
    src/main/factory/qtfactory.h \
    src/main/abstraction/outport.h \
    src/main/abstraction/inport.h \
    src/main/abstraction/vco.h
SOURCES += src/main/abstraction/synthpro.cpp \
    src/main/abstraction/module.cpp \
    src/main/abstraction/port.cpp \
    src/main/abstraction/sequencer.cpp \
    src/main/control/csynthpro.cpp \
    src/main/presentation/psynthpro.cpp \
    src/main/main.cpp \
    src/main/factory/qtfactory.cpp \
    src/main/abstraction/outport.cpp \
    src/main/abstraction/inport.cpp \
    src/main/abstraction/vco.cpp
INCLUDEPATH += src/main/
