CONFIG += qtestlib

DESTDIR = bin/test
OBJECTS_DIR = bin/test/.obj
MOC_DIR = bin/test/.moc
RCC_DIR = bin/test/.rcc

QT += multimedia

HEADERS += \
    src/main/abstraction/audiodeviceprovider.h \
    src/main/abstraction/buffer.h \
    src/main/abstraction/clock.h \
    src/main/abstraction/component/dimmer.h \
    src/main/abstraction/component/inport.h \
    src/main/abstraction/component/outport.h \
    src/main/abstraction/component/port.h \
    src/main/abstraction/component/pushbutton.h \
    src/main/abstraction/component/selector.h \
    src/main/abstraction/component/virtualport.h \
    src/main/abstraction/filter/filter.h \
    src/main/abstraction/filter/filterdummy.h \
    src/main/abstraction/filter/filterhp229.h \
    src/main/abstraction/filter/filterincrement.h \
    src/main/abstraction/filter/filterlp229.h \
    src/main/abstraction/filter/filtersoftsaturation.h \
    src/main/abstraction/module.h \
    src/main/abstraction/module/adsr.h \
    src/main/abstraction/module/delay.h \
    src/main/abstraction/module/keyboard.h \
    src/main/abstraction/module/lfo.h \
    src/main/abstraction/module/oscilloscope.h \
    src/main/abstraction/module/speaker.h \
    src/main/abstraction/module/vca.h \
    src/main/abstraction/module/vcf.h \
    src/main/abstraction/module/vco.h \
    src/main/abstraction/module/wavrecorder.h \
    src/main/abstraction/sequencer.h \
    src/main/abstraction/synthpro.h \
    src/main/abstraction/wavegen/wavegeneratordummy.h \
    src/main/abstraction/wavegen/wavegeneratorempty.h \
    src/main/abstraction/wavegen/wavegeneratorsaw.h \
    src/main/abstraction/wavegen/wavegeneratorsinus.h \
    src/main/abstraction/wavegen/wavegeneratorsquare.h \
    src/main/abstraction/wavegen/wavegeneratortriangle.h \
    src/main/factory/filterfactory.h \
    src/main/factory/simplefactory.h \
    src/main/factory/synthprofactory.h \
    src/main/factory/wavegeneratorfactory.h \
    src/test/abstraction/mock/mockinoutmodule.h \
    src/test/abstraction/mock/mockmodule.h \
    src/test/abstraction/mock/mockserializerwell.h \
    src/test/abstraction/mock/mockwell.h \
    src/test/abstraction/module/testadsr.h \
    src/test/abstraction/module/testdelay.h \
    src/test/abstraction/module/testlfo.h \
    src/test/abstraction/module/testvca.h \
    src/test/abstraction/module/testvcf.h \
    src/test/abstraction/module/testvco.h \
    src/test/abstraction/module/testwavrecorder.h \
    src/test/abstraction/testaudiodeviceprovider.h \
    src/test/abstraction/testinport.h \
    src/test/abstraction/testoutport.h \
    src/test/abstraction/testsequencer.h \
    src/test/abstraction/wavegen/testwavegeneratorempty.h \
    src/test/abstraction/wavegen/testwavegeneratorsaw.h \
    src/test/abstraction/wavegen/testwavegeneratorsinus.h \
    src/test/abstraction/wavegen/testwavegeneratorsquare.h \
    src/test/abstraction/wavegen/testwavegeneratortriangle.h

SOURCES += \
    src/main/abstraction/audiodeviceprovider.cpp \
    src/main/abstraction/buffer.cpp \
    src/main/abstraction/clock.cpp \
    src/main/abstraction/component/dimmer.cpp \
    src/main/abstraction/component/inport.cpp \
    src/main/abstraction/component/outport.cpp \
    src/main/abstraction/component/port.cpp \
    src/main/abstraction/component/pushbutton.cpp \
    src/main/abstraction/component/selector.cpp \
    src/main/abstraction/component/virtualport.cpp \
    src/main/abstraction/filter/filterdummy.cpp \
    src/main/abstraction/filter/filterhp229.cpp \
    src/main/abstraction/filter/filterincrement.cpp \
    src/main/abstraction/filter/filterlp229.cpp \
    src/main/abstraction/filter/filtersoftsaturation.cpp \
    src/main/abstraction/module.cpp \
    src/main/abstraction/module/adsr.cpp \
    src/main/abstraction/module/delay.cpp \
    src/main/abstraction/module/keyboard.cpp \
    src/main/abstraction/module/lfo.cpp \
    src/main/abstraction/module/oscilloscope.cpp \
    src/main/abstraction/module/speaker.cpp \
    src/main/abstraction/module/vca.cpp \
    src/main/abstraction/module/vcf.cpp \
    src/main/abstraction/module/vco.cpp \
    src/main/abstraction/module/wavrecorder.cpp \
    src/main/abstraction/sequencer.cpp \
    src/main/abstraction/synthpro.cpp \
    src/main/abstraction/wavegen/wavegeneratordummy.cpp \
    src/main/abstraction/wavegen/wavegeneratorempty.cpp \
    src/main/abstraction/wavegen/wavegeneratorsaw.cpp \
    src/main/abstraction/wavegen/wavegeneratorsinus.cpp \
    src/main/abstraction/wavegen/wavegeneratorsquare.cpp \
    src/main/abstraction/wavegen/wavegeneratortriangle.cpp \
    src/main/factory/filterfactorydummy.cpp \
    src/main/factory/simplefactory.cpp \
    src/main/factory/wavegeneratorfactorydummy.cpp \
    src/test/abstraction/mock/mockinoutmodule.cpp \
    src/test/abstraction/mock/mockmodule.cpp \
    src/test/abstraction/mock/mockserializerwell.cpp \
    src/test/abstraction/mock/mockwell.cpp \
    src/test/abstraction/module/testadsr.cpp \
    src/test/abstraction/module/testdelay.cpp \
    src/test/abstraction/module/testlfo.cpp \
    src/test/abstraction/module/testvca.cpp \
    src/test/abstraction/module/testvcf.cpp \
    src/test/abstraction/module/testvco.cpp \
    src/test/abstraction/module/testwavrecorder.cpp \
    src/test/abstraction/testaudiodeviceprovider.cpp \
    src/test/abstraction/testinport.cpp \
    src/test/abstraction/testoutport.cpp \
    src/test/abstraction/testsequencer.cpp \
    src/test/abstraction/wavegen/testwavegeneratorempty.cpp \
    src/test/abstraction/wavegen/testwavegeneratorsaw.cpp \
    src/test/abstraction/wavegen/testwavegeneratorsinus.cpp \
    src/test/abstraction/wavegen/testwavegeneratorsquare.cpp \
    src/test/abstraction/wavegen/testwavegeneratortriangle.cpp \
    src/test/test.cpp


INCLUDEPATH += src/main/ src/test/
