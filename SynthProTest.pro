CONFIG += qtestlib

DESTDIR = bin/test
OBJECTS_DIR = bin/test/.obj
MOC_DIR = bin/test/.moc
RCC_DIR = bin/test/.rcc
QT += multimedia

HEADERS += \
    src/main/abstraction/buffer.h \
    src/main/abstraction/port.h \
    src/main/abstraction/inport.h \
    src/test/abstraction/testinport.h \
    src/main/abstraction/outport.h \
    src/test/abstraction/testoutport.h \
    src/main/abstraction/sequencer.h \
    src/main/abstraction/module.h \
    src/main/abstraction/synthpro.h \
    src/test/abstraction/mockmodule.h \
    src/test/abstraction/mockwell.h \
    src/test/abstraction/testsequencer.h \
    src/test/abstraction/mockinoutmodule.h \
    src/test/abstraction/testvco.h \
    src/main/abstraction/vco.h \
    src/main/abstraction/wavegeneratordummy.h \
    src/main/abstraction/wavegeneratorempty.h \
    src/test/abstraction/mockserializerwell.h \
    src/main/factory/synthprofactory.h \
    src/main/factory/simplefactory.h \
    src/test/abstraction/testwavegeneratorempty.h

SOURCES += src/test/test.cpp \
    src/main/abstraction/buffer.cpp \
    src/main/abstraction/port.cpp \
    src/main/abstraction/inport.cpp \
    src/test/abstraction/testinport.cpp \
    src/main/abstraction/outport.cpp \
    src/test/abstraction/testoutport.cpp \
    src/main/abstraction/sequencer.cpp \
    src/main/abstraction/module.cpp \
    src/main/abstraction/synthpro.cpp \
    src/test/abstraction/mockmodule.cpp \
    src/test/abstraction/mockwell.cpp \
    src/test/abstraction/testsequencer.cpp \
    src/test/abstraction/mockinoutmodule.cpp \
    src/test/abstraction/testvco.cpp \
    src/main/abstraction/vco.cpp \
    src/main/abstraction/wavegeneratordummy.cpp \
    src/main/abstraction/wavegeneratorempty.cpp \
    src/test/abstraction/mockserializerwell.cpp \
    src/main/factory/simplefactory.cpp \
    src/test/abstraction/testwavegeneratorempty.cpp

INCLUDEPATH += src/main/ src/test/
