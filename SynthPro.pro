DESTDIR = bin
OBJECTS_DIR = bin/.obj
MOC_DIR = bin/.moc
RCC_DIR = bin/.rcc

QT += multimedia

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
    src/main/abstraction/filterlp229.h \
    src/main/abstraction/filterhp229.h \
    src/main/abstraction/inport.h \
    src/main/abstraction/vco.h \
    src/main/abstraction/wavegenerator.h \
    src/main/abstraction/wavegeneratordummy.h \
    src/main/abstraction/wavegeneratorsquare.h \
    src/main/abstraction/buffer.h \
    src/main/presentation/moduleview.h \
    src/main/control/cmodule.h \
    src/main/presentation/pmodule.h \
    src/main/presentation/pport.h \
    src/main/control/cport.h \
    src/main/control/cinport.h \
    src/main/control/coutport.h \
    src/main/abstraction/wavegeneratortriangle.h \
    src/main/abstraction/wavegeneratorsaw.h \
    src/main/abstraction/wavegeneratorsinus.h \
    src/main/abstraction/vcf.h \
    src/main/factory/filterfactory.h \
    src/main/presentation/pwire.h \
    src/main/control/cwire.h \
    src/main/abstraction/audiodeviceprovider.h \
    src/main/abstraction/modulebufferrecorder.h \
    src/main/abstraction/selector.h \
    src/main/abstraction/wavegeneratorempty.h \
    src/main/control/modulelistmodel.h \
    src/main/control/cvco.h \
    src/main/abstraction/dimmer.h \
    src/main/control/cdimmer.h \
    src/main/presentation/pdimmer.h \
    src/main/abstraction/moduleout.h \
    src/main/presentation/pvco.h \
    src/main/abstraction/clock.h \
    src/main/factory/wavegeneratorfactory.h \
    src/main/presentation/pselector.h \
    src/main/control/cselector.h \
    src/main/presentation/pmoduleout.h \
    src/main/control/cmoduleout.h \
    src/main/abstraction/vca.h \
    src/main/control/cvcf.h \
    src/main/presentation/pvcf.h \
    src/main/presentation/textwidget.h \
    src/main/control/cvca.h \
    src/main/presentation/pvca.h \
    src/main/abstraction/adsr.h \
    src/main/presentation/portwidget.h \
    src/main/abstraction/filtersoftsaturation.h \
    src/main/control/cportwidget.h \
    src/main/abstraction/lfo.h \
    src/main/presentation/plfo.h \
    src/main/control/clfo.h

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
    src/main/abstraction/filterlp229.cpp \
    src/main/abstraction/filterhp229.cpp \
    src/main/abstraction/inport.cpp \
    src/main/abstraction/vco.cpp \
    src/main/abstraction/wavegeneratordummy.cpp \
    src/main/abstraction/wavegeneratorsquare.cpp \
    src/main/abstraction/buffer.cpp \
    src/main/presentation/moduleview.cpp \
    src/main/control/cmodule.cpp \
    src/main/presentation/pmodule.cpp \
    src/main/presentation/pport.cpp \
    src/main/control/cport.cpp \
    src/main/control/cinport.cpp \
    src/main/control/coutport.cpp \
    src/main/abstraction/wavegeneratortriangle.cpp \
    src/main/abstraction/wavegeneratorsaw.cpp \
    src/main/abstraction/wavegeneratorsinus.cpp \
    src/main/abstraction/vcf.cpp \
    src/main/factory/filterfactory.cpp \
    src/main/presentation/pwire.cpp \
    src/main/control/cwire.cpp \
    src/main/abstraction/audiodeviceprovider.cpp \
    src/main/abstraction/modulebufferrecorder.cpp \
    src/main/abstraction/selector.cpp \
    src/main/abstraction/wavegeneratorempty.cpp \
    src/main/control/modulelistmodel.cpp \
    src/main/control/cvco.cpp \
    src/main/abstraction/dimmer.cpp \
    src/main/control/cdimmer.cpp \
    src/main/presentation/pdimmer.cpp \
    src/main/abstraction/moduleout.cpp \
    src/main/presentation/pvco.cpp \
    src/main/abstraction/clock.cpp \
    src/main/factory/wavegeneratorfactory.cpp \
    src/main/presentation/pselector.cpp \
    src/main/control/cselector.cpp \
    src/main/presentation/pmoduleout.cpp \
    src/main/control/cmoduleout.cpp \
    src/main/abstraction/vca.cpp \
    src/main/control/cvcf.cpp \
    src/main/presentation/pvcf.cpp \
    src/main/presentation/textwidget.cpp \
    src/main/control/cvca.cpp \
    src/main/presentation/pvca.cpp \
    src/main/abstraction/adsr.cpp \
    src/main/presentation/portwidget.cpp \
    src/main/abstraction/filtersoftsaturation.cpp \
    src/main/control/cportwidget.cpp \
    src/main/abstraction/lfo.cpp \
    src/main/presentation/plfo.cpp \
    src/main/control/clfo.cpp

INCLUDEPATH += src/main/

RESOURCES += \
    src/resources/SynthPro.qrc
