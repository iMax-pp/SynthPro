DESTDIR = bin
OBJECTS_DIR = bin/.obj
MOC_DIR = bin/.moc
RCC_DIR = bin/.rcc

QT += multimedia

HEADERS += \
    src/main/abstraction/audiodeviceprovider.h \
    src/main/abstraction/buffer.h \
    src/main/abstraction/clock.h \
    src/main/abstraction/component/connection.h \
    src/main/abstraction/component/dimmer.h \
    src/main/abstraction/component/inport.h \
    src/main/abstraction/component/outport.h \
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
    src/main/abstraction/module/mixer.h \
    src/main/abstraction/module/oscilloscope.h \
    src/main/abstraction/module/sampler.h \
    src/main/abstraction/module/speaker.h \
    src/main/abstraction/module/vca.h \
    src/main/abstraction/module/vcf.h \
    src/main/abstraction/module/vco.h \
    src/main/abstraction/module/wavlooper.h \
    src/main/abstraction/module/wavrecorder.h \
    src/main/abstraction/sequencer.h \
    src/main/abstraction/synthpro.h \
    src/main/abstraction/wavegen/wavegenerator.h \
    src/main/abstraction/wavegen/wavegeneratordummy.h \
    src/main/abstraction/wavegen/wavegeneratorempty.h \
    src/main/abstraction/wavegen/wavegeneratorsaw.h \
    src/main/abstraction/wavegen/wavegeneratorsinus.h \
    src/main/abstraction/wavegen/wavegeneratorsquare.h \
    src/main/abstraction/wavegen/wavegeneratortriangle.h \
    src/main/control/cmodule.h \
    src/main/control/component/cdimmer.h \
    src/main/control/component/cinport.h \
    src/main/control/component/coutport.h \
    src/main/control/component/cport.h \
    src/main/control/component/cpushbutton.h \
    src/main/control/component/cselector.h \
    src/main/control/component/cvirtualport.h \
    src/main/control/component/cwire.h \
    src/main/control/csynthpro.h \
    src/main/control/module/cadsr.h \
    src/main/control/module/cdelay.h \
    src/main/control/module/ckeyboard.h \
    src/main/control/module/clfo.h \
    src/main/control/module/cmixer.h \
    src/main/control/module/coscilloscope.h \
    src/main/control/module/csampler.h \
    src/main/control/module/cspeaker.h \
    src/main/control/module/cvca.h \
    src/main/control/module/cvcf.h \
    src/main/control/module/cvco.h \
    src/main/control/module/cwavlooper.h \
    src/main/control/module/cwavrecorder.h \
    src/main/control/modulelistmodel.h \
    src/main/factory/filterfactory.h \
    src/main/factory/qtfactory.h \
    src/main/factory/synthprofactory.h \
    src/main/factory/wavegeneratorfactory.h \
    src/main/presentation/component/pdial.h \
    src/main/presentation/component/pdimmer.h \
    src/main/presentation/component/pport.h \
    src/main/presentation/component/ppushbutton.h \
    src/main/presentation/component/pselector.h \
    src/main/presentation/component/pslider.h \
    src/main/presentation/component/pvirtualport.h \
    src/main/presentation/component/pwire.h \
    src/main/presentation/module/padsr.h \
    src/main/presentation/module/pdelay.h \
    src/main/presentation/module/pkeyboard.h \
    src/main/presentation/module/plfo.h \
    src/main/presentation/module/pmixer.h \
    src/main/presentation/module/poscilloscope.h \
    src/main/presentation/module/psampler.h \
    src/main/presentation/module/pspeaker.h \
    src/main/presentation/module/pvca.h \
    src/main/presentation/module/pvcf.h \
    src/main/presentation/module/pvco.h \
    src/main/presentation/module/pwavlooper.h \
    src/main/presentation/module/pwavrecorder.h \
    src/main/presentation/pmodule.h \
    src/main/presentation/psynthpro.h \
    src/main/presentation/widget/moduleview.h \
    src/main/presentation/widget/pixmapbuttonwidget.h \
    src/main/presentation/widget/pixmapwidget.h \
    src/main/presentation/widget/pkeyboardkey.h \
    src/main/presentation/widget/pkeyboardview.h \
    src/main/presentation/widget/poscilloscopeview.h \
    src/main/presentation/widget/progressbarwidget.h \
    src/main/presentation/widget/textwidget.h \
    src/main/abstraction/module/timecriticalmodule.h

SOURCES += \
    src/main/abstraction/audiodeviceprovider.cpp \
    src/main/abstraction/buffer.cpp \
    src/main/abstraction/clock.cpp \
    src/main/abstraction/component/connection.cpp \
    src/main/abstraction/component/dimmer.cpp \
    src/main/abstraction/component/inport.cpp \
    src/main/abstraction/component/outport.cpp \
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
    src/main/abstraction/module/mixer.cpp \
    src/main/abstraction/module/oscilloscope.cpp \
    src/main/abstraction/module/sampler.cpp \
    src/main/abstraction/module/speaker.cpp \
    src/main/abstraction/module/vca.cpp \
    src/main/abstraction/module/vcf.cpp \
    src/main/abstraction/module/vco.cpp \
    src/main/abstraction/module/wavlooper.cpp \
    src/main/abstraction/module/wavrecorder.cpp \
    src/main/abstraction/sequencer.cpp \
    src/main/abstraction/synthpro.cpp \
    src/main/abstraction/wavegen/wavegeneratordummy.cpp \
    src/main/abstraction/wavegen/wavegeneratorempty.cpp \
    src/main/abstraction/wavegen/wavegeneratorsaw.cpp \
    src/main/abstraction/wavegen/wavegeneratorsinus.cpp \
    src/main/abstraction/wavegen/wavegeneratorsquare.cpp \
    src/main/abstraction/wavegen/wavegeneratortriangle.cpp \
    src/main/control/cmodule.cpp \
    src/main/control/component/cdimmer.cpp \
    src/main/control/component/cinport.cpp \
    src/main/control/component/coutport.cpp \
    src/main/control/component/cport.cpp \
    src/main/control/component/cpushbutton.cpp \
    src/main/control/component/cselector.cpp \
    src/main/control/component/cvirtualport.cpp \
    src/main/control/component/cwire.cpp \
    src/main/control/csynthpro.cpp \
    src/main/control/module/cadsr.cpp \
    src/main/control/module/cdelay.cpp \
    src/main/control/module/ckeyboard.cpp \
    src/main/control/module/clfo.cpp \
    src/main/control/module/cmixer.cpp \
    src/main/control/module/coscilloscope.cpp \
    src/main/control/module/csampler.cpp \
    src/main/control/module/cspeaker.cpp \
    src/main/control/module/cvca.cpp \
    src/main/control/module/cvcf.cpp \
    src/main/control/module/cvco.cpp \
    src/main/control/module/cwavlooper.cpp \
    src/main/control/module/cwavrecorder.cpp \
    src/main/control/modulelistmodel.cpp \
    src/main/factory/filterfactory.cpp \
    src/main/factory/qtfactory.cpp \
    src/main/factory/wavegeneratorfactory.cpp \
    src/main/main.cpp \
    src/main/presentation/component/pdial.cpp \
    src/main/presentation/component/pdimmer.cpp \
    src/main/presentation/component/pport.cpp \
    src/main/presentation/component/ppushbutton.cpp \
    src/main/presentation/component/pselector.cpp \
    src/main/presentation/component/pslider.cpp \
    src/main/presentation/component/pvirtualport.cpp \
    src/main/presentation/component/pwire.cpp \
    src/main/presentation/module/padsr.cpp \
    src/main/presentation/module/pdelay.cpp \
    src/main/presentation/module/pkeyboard.cpp \
    src/main/presentation/module/plfo.cpp \
    src/main/presentation/module/pmixer.cpp \
    src/main/presentation/module/poscilloscope.cpp \
    src/main/presentation/module/psampler.cpp \
    src/main/presentation/module/pspeaker.cpp \
    src/main/presentation/module/pvca.cpp \
    src/main/presentation/module/pvcf.cpp \
    src/main/presentation/module/pvco.cpp \
    src/main/presentation/module/pwavlooper.cpp \
    src/main/presentation/module/pwavrecorder.cpp \
    src/main/presentation/pmodule.cpp \
    src/main/presentation/psynthpro.cpp \
    src/main/presentation/widget/moduleview.cpp \
    src/main/presentation/widget/pixmapbuttonwidget.cpp \
    src/main/presentation/widget/pixmapwidget.cpp \
    src/main/presentation/widget/pkeyboardkey.cpp \
    src/main/presentation/widget/pkeyboardview.cpp \
    src/main/presentation/widget/poscilloscopeview.cpp \
    src/main/presentation/widget/progressbarwidget.cpp \
    src/main/presentation/widget/textwidget.cpp \
    src/main/abstraction/module/timecriticalmodule.cpp

INCLUDEPATH += src/main/

RESOURCES += \
    src/resources/SynthPro.qrc
