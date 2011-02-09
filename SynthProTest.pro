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
    src/main/abstraction/dimmer.h \
    src/main/abstraction/selector.h \
    src/main/abstraction/wavegeneratordummy.h \
    src/main/abstraction/wavegeneratorempty.h \
    src/main/abstraction/wavegeneratortriangle.h \
    src/main/abstraction/wavegeneratorsquare.h \
    src/main/abstraction/wavegeneratorsaw.h \
    src/main/abstraction/wavegeneratorsinus.h \
    src/main/abstraction/audiodeviceprovider.h \
    src/test/abstraction/mockserializerwell.h \
    src/main/factory/synthprofactory.h \
    src/main/factory/simplefactory.h \
    src/main/abstraction/modulebufferrecorder.h \
    src/main/abstraction/moduleout.h \
    src/test/abstraction/testmodulebufferrecorder.h \
    src/test/abstraction/testwavegeneratorempty.h \
    src/test/abstraction/testwavegeneratortriangle.h \
    src/test/abstraction/testwavegeneratorsquare.h \
    src/test/abstraction/testwavegeneratorsaw.h \
    src/test/abstraction/testwavegeneratorsinus.h \
    src/main/abstraction/clock.h \
    src/main/factory/wavegeneratorfactory.h \
    src/test/abstraction/testaudiodeviceprovider.h \
    src/main/abstraction/vcf.h \
    src/main/abstraction/filter.h \
    src/main/abstraction/filterdummy.h \
    src/main/abstraction/filterincrement.h \
    src/main/abstraction/filterlp229.h \
    src/main/factory/filterfactory.h \
    src/main/abstraction/vca.h

SOURCES += src/test/test.cpp \
    src/main/abstraction/buffer.cpp \
    src/main/abstraction/port.cpp \
    src/main/abstraction/inport.cpp \
    src/test/abstraction/testinport.cpp \
    src/main/abstraction/outport.cpp \
    src/main/abstraction/dimmer.cpp \
    src/main/abstraction/selector.cpp \
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
    src/main/abstraction/wavegeneratortriangle.cpp \
    src/main/abstraction/wavegeneratorsquare.cpp \
    src/main/abstraction/wavegeneratorsaw.cpp \
    src/main/abstraction/wavegeneratorsinus.cpp \
    src/main/abstraction/audiodeviceprovider.cpp \
    src/test/abstraction/mockserializerwell.cpp \
    src/main/factory/simplefactory.cpp \
    src/main/abstraction/modulebufferrecorder.cpp \
    src/main/abstraction/moduleout.cpp \
    src/test/abstraction/testmodulebufferrecorder.cpp \
    src/test/abstraction/testwavegeneratorempty.cpp \
    src/test/abstraction/testwavegeneratortriangle.cpp \
    src/test/abstraction/testwavegeneratorsquare.cpp \
    src/test/abstraction/testwavegeneratorsaw.cpp \
    src/test/abstraction/testwavegeneratorsinus.cpp \
    src/main/abstraction/clock.cpp \
    src/main/factory/wavegeneratorfactory.cpp \
    src/test/abstraction/testaudiodeviceprovider.cpp \
    src/main/abstraction/vcf.cpp \
    src/main/abstraction/filterdummy.cpp \
    src/main/abstraction/filterincrement.cpp \
    src/main/abstraction/filterlp229.cpp \
    src/main/factory/filterfactory.cpp \
    src/main/abstraction/vca.cpp

INCLUDEPATH += src/main/ src/test/
