DESTDIR = bin
OBJECTS_DIR = bin/.obj
MOC_DIR = bin/.moc
RCC_DIR = bin/.rcc

HEADERS += src/main/abstraction/synthpro.h \
    src/main/abstraction/module.h \
    src/main/abstraction/port.h \
    src/main/abstraction/sequencer.h \
    src/main/control/csynthpro.h \
    src/main/presentation/psynthpro.h \
    src/main/factory/synthprofactory.h \
    src/main/factory/qtfactory.h \
    src/main/abstraction/outport.h \
    src/main/abstraction/filter.h \
    src/main/abstraction/filterdummy.h \
    src/main/abstraction/filterincrement.h \
    src/main/abstraction/inport.h \
    src/main/abstraction/vco.h \
    src/main/abstraction/wavegenerator.h \
    src/main/abstraction/wavegeneratordummy.h \
    src/main/abstraction/wavegeneratorsquare.h \
    src/main/abstraction/buffer.h

SOURCES += src/main/abstraction/synthpro.cpp \
    src/main/abstraction/module.cpp \
    src/main/abstraction/port.cpp \
    src/main/abstraction/sequencer.cpp \
    src/main/control/csynthpro.cpp \
    src/main/presentation/psynthpro.cpp \
    src/main/main.cpp \
    src/main/factory/qtfactory.cpp \
    src/main/abstraction/outport.cpp \
    src/main/abstraction/filterdummy.cpp \
    src/main/abstraction/filterincrement.cpp \
    src/main/abstraction/inport.cpp \
    src/main/abstraction/vco.cpp \
    src/main/abstraction/wavegeneratordummy.cpp \
    src/main/abstraction/wavegeneratorsquare.cpp \
    src/main/abstraction/buffer.cpp

INCLUDEPATH += src/main/

RESOURCES += \
    src/resources/SynthPro.qrc
