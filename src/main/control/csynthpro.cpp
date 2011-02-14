#include "csynthpro.h"

#include "abstraction/clock.h"
#include "control/cmodule.h"
#include "control/component/cinport.h"
#include "control/component/coutport.h"
#include "control/component/cvirtualport.h"
#include "control/module/cadsr.h"
#include "control/module/cdelay.h"
#include "control/module/ckeyboard.h"
#include "control/module/clfo.h"
#include "control/module/cmixer.h"
#include "control/module/coscilloscope.h"
#include "control/module/cspeaker.h"
#include "control/module/cvca.h"
#include "control/module/cvcf.h"
#include "control/module/cvco.h"
#include "control/module/cwavrecorder.h"

#include <QGraphicsScene>

CSynthPro::CSynthPro(SynthProFactory* factory)
    : SynthPro()
    , m_presentation(0)
    , m_graphicsScene(new QGraphicsScene)
    , m_factory(factory)
{
}

CSynthPro::~CSynthPro()
{
    if (m_presentation) {
        delete m_presentation;
    }

    // Delete each module.
    foreach (Module* module, modules()) {
        delete module;
    }

    // m_graphicsScene has no parent so we must destroy it ourselves.
    delete m_graphicsScene;
}

void CSynthPro::setPresentation(PSynthPro* presentation)
{
    if (m_presentation) {
        delete m_presentation;
    }

    m_presentation = presentation;
    m_presentation->setGraphicsScene(m_graphicsScene);

    if (Clock::instance().isStarted()) {
        // By default the Play/Pause button is on Pause, so let's change this.
        m_presentation->togglePlayPause();
    }
}

PSynthPro* CSynthPro::presentation() const
{
    return m_presentation;
}

void CSynthPro::add(Module* module)
{
    CModule* cModule = dynamic_cast<CModule*>(module);

    if (cModule) {
        SynthPro::add(cModule);

        if (modules().contains(cModule)) {
            m_graphicsScene->addItem(cModule->presentation());
        }
    }
}

void CSynthPro::addModule(SynthProFactory::ModuleType moduleType, const QPointF& pos)
{
    Module* module = 0;

    switch (moduleType) {
    case SynthProFactory::KeyboardId:
        module = dynamic_cast<Module*>(m_factory->createKeyboard(this));
        break;
    case SynthProFactory::VCOId:
        module = dynamic_cast<Module*>(m_factory->createVCO(this));
        break;
    case SynthProFactory::VCFId:
        module = dynamic_cast<Module*>(m_factory->createVCF(this));
        break;
    case SynthProFactory::VCAId:
        module = dynamic_cast<Module*>(m_factory->createVCA(this));
        break;
    case SynthProFactory::ADSRId:
        module = dynamic_cast<Module*>(m_factory->createADSR(this));
        break;
    case SynthProFactory::DelayId:
        module = dynamic_cast<Module*>(m_factory->createDelay(this));
        break;
    case SynthProFactory::MixerId:
        module = dynamic_cast<Module*>(m_factory->createMixer(this));
        break;
        case SynthProFactory::LFOId:
        module = dynamic_cast<Module*>(m_factory->createLFO(this));
        break;
    case SynthProFactory::AudioOuputId:
        module = dynamic_cast<Module*>(m_factory->createSpeaker(this));
        break;
    case SynthProFactory::FileOutputId:
        module = dynamic_cast<Module*>(m_factory->createWavRecorder(this));
        break;
    case SynthProFactory::OscilloscopeId:
        module = dynamic_cast<Module*>(m_factory->createOscilloscope(this));
        break;
    default:
        break;
    }

    if (module) {
        add(module);
        dynamic_cast<CModule*>(module)->presentation()->setPos(pos);
    }

    // Post initialisation. May be useful to some modules.
    if (moduleType == SynthProFactory::KeyboardId) {
        CKeyboard* keyb = dynamic_cast<CKeyboard*>(module);
        keyb->postInitialize();
    }
}

void CSynthPro::showFeedback(CVirtualPort* from)
{
    foreach (Module* module, modules()) {
        foreach (VirtualPort* port, module->inports()) {
            dynamic_cast<CInPort*>(port)->showCompatibleFeedback(from);
        }
        foreach (VirtualPort* port, module->outports()) {
            dynamic_cast<COutPort*>(port)->showCompatibleFeedback(from);
        }
    }
}

void CSynthPro::hideFeedback()
{
    foreach (Module* module, modules()) {
        foreach (VirtualPort* port, module->inports()) {
            dynamic_cast<CInPort*>(port)->hideFeedback();
        }
        foreach (VirtualPort* port, module->outports()) {
            dynamic_cast<COutPort*>(port)->hideFeedback();
        }
    }
}

void CSynthPro::play(bool resume)
{
    if (resume) {
        Clock::instance().start();
    } else {
        Clock::instance().pause();
    }
}
