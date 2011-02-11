CONFIG += qtestlib

DESTDIR = bin/test
OBJECTS_DIR = bin/test/.obj
MOC_DIR = bin/test/.moc
RCC_DIR = bin/test/.rcc
QT += multimedia

HEADERS += \
    src/main/abstraction/buffer.h \
    src/main/abstraction/virtualport.h \
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
    src/main/abstraction/lfo.h \
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
    src/main/abstraction/wavrecorder.h \
    src/main/abstraction/speaker.h \
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
    src/main/abstraction/filterhp229.h \
    src/main/abstraction/filtersoftsaturation.h \
    src/main/factory/filterfactory.h \
    src/main/abstraction/vca.h \
    src/main/abstraction/adsr.h \
    src/test/abstraction/testvca.h \
    src/test/abstraction/testvcf.h \
    src/test/abstraction/testadsr.h \
    src/main/abstraction/moduleoscilloscope.h \
    src/main/abstraction/pushbutton.h \
    src/main/abstraction/modulekeyboard.h \
    src/main/abstraction/port.h \
    src/test/abstraction/testlfo.h


SOURCES += src/test/test.cpp \
    src/main/abstraction/buffer.cpp \
    src/main/abstraction/virtualport.cpp \
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
    src/main/abstraction/lfo.cpp \
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
    src/main/abstraction/wavrecorder.cpp \
    src/main/abstraction/speaker.cpp \
    src/test/abstraction/testmodulebufferrecorder.cpp \
    src/test/abstraction/testwavegeneratorempty.cpp \
    src/test/abstraction/testwavegeneratortriangle.cpp \
    src/test/abstraction/testwavegeneratorsquare.cpp \
    src/test/abstraction/testwavegeneratorsaw.cpp \
    src/test/abstraction/testwavegeneratorsinus.cpp \
    src/main/abstraction/clock.cpp \
    src/test/abstraction/testaudiodeviceprovider.cpp \
    src/main/abstraction/vcf.cpp \
    src/main/abstraction/filterdummy.cpp \
    src/main/abstraction/filterincrement.cpp \
    src/main/abstraction/filterlp229.cpp \
    src/main/abstraction/filterhp229.cpp \
    src/main/abstraction/filtersoftsaturation.cpp \
    src/main/abstraction/vca.cpp \
    src/main/abstraction/adsr.cpp \
    src/test/abstraction/testvca.cpp \
    src/main/factory/wavegeneratorfactorydummy.cpp \
    src/main/factory/filterfactorydummy.cpp \
    src/test/abstraction/testvcf.cpp \
    src/test/abstraction/testadsr.cpp \
    src/main/abstraction/moduleoscilloscope.cpp \
    src/main/abstraction/pushbutton.cpp \
    src/main/abstraction/modulekeyboard.cpp \
    src/main/abstraction/port.cpp \
    src/test/abstraction/testlfo.cpp


INCLUDEPATH += src/main/ src/test/
