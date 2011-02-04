CONFIG += qtestlib

DESTDIR = bin/test
OBJECTS_DIR = bin/test/.obj
MOC_DIR = bin/test/.moc
RCC_DIR = bin/test/.rcc

HEADERS += \
    src/main/abstraction/buffer.h \
    src/main/abstraction/port.h \
    src/main/abstraction/inport.h \
    src/test/abstraction/testinport.h \
    src/main/abstraction/outport.h \
    src/test/abstraction/testvco.h \
    src/main/abstraction/module.h \
    src/main/abstraction/vco.h

SOURCES += src/test/test.cpp \
    src/main/abstraction/buffer.cpp \
    src/main/abstraction/port.cpp \
    src/main/abstraction/inport.cpp \
    src/test/abstraction/testinport.cpp \
    src/main/abstraction/outport.cpp \
    src/test/abstraction/testoutport.cpp \
    src/test/abstraction/testvco.cpp \
    src/main/abstraction/module.cpp \
    src/main/abstraction/vco.cpp

INCLUDEPATH += src/main/ src/test/
