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
#include "control/module/csampler.h"
#include "control/module/cspeaker.h"
#include "control/module/cvca.h"
#include "control/module/cvcf.h"
#include "control/module/cvco.h"
#include "control/module/cwavlooper.h"
#include "control/module/cwavrecorder.h"
#include "control/serializer.h"

#include <QFile>
#include <QGraphicsScene>

CSynthPro::CSynthPro(SynthProFactory* factory)
    : SynthPro()
    , m_presentation(0)
    , m_graphicsScene(new QGraphicsScene(this))
    , m_factory(factory)
{
    dropAttemptsCount = 0;
}

CSynthPro::~CSynthPro()
{
    if (!m_presentation.isNull()) {
        delete m_presentation;
    }
}

void CSynthPro::setPresentation(PSynthPro* presentation)
{
    if (!m_presentation.isNull()) {
        delete m_presentation;
    }

    m_presentation = presentation;
    m_presentation->setGraphicsScene(m_graphicsScene);

    if (Clock::instance().isStarted()) {
        // By default the Play/Pause button is on Pause, so let's change this.
        m_presentation->togglePlayPause();
    }
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

Module* CSynthPro::addModule(SynthProFactory::ModuleType moduleType, const QPointF& pos)
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
    case SynthProFactory::SamplerId:
        module = dynamic_cast<Module*>(m_factory->createSampler(this));
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
    case SynthProFactory::WavLooperId:
        module = dynamic_cast<Module*>(m_factory->createWavLooper(this));
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

    return module;
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

void CSynthPro::newScheme()
{
    foreach (Module* module, modules()) {
        remove(dynamic_cast<Module*>(module));
    }
}

void CSynthPro::saveTo(const QString& filename)
{
    QFile file(filename);

    if (file.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream out(&file);
        // Add a simple header.
        out << "synthpro 1.0" << endl;
        // And the whole content of the scheme.
        out << *this;
    }
}

void CSynthPro::loadFrom(const QString& filename)
{
    QFile file(filename);

    if (file.open(QFile::ReadOnly)) {
        QTextStream stream(&file);
        QString line = stream.readLine();

        // Check if the header is present.
        if (line != "synthpro 1.0") {
            m_presentation->errorLoading(tr("Error loading scheme file of non-compatible format."));
            return;
        }

        // Then start a new scheme.
        newScheme();
        line = stream.readLine();

        // Retrieve the count of modules.
        int nbModules = line.toInt();

        // And recreate each one.
        for (int i = 0; i < nbModules && !line.isNull(); i++) {
            line = stream.readLine();
            QStringList elements = line.split(QRegExp("\\s+"), QString::SkipEmptyParts);

            // Retrieve module name (Remove the number at name start).
            QString name = elements[0].remove(QRegExp("[0-9]{1,2}"));
            QString id = elements[1];

            QHash<QString, Module*> modules;

            // Retrieve module position.
            QPointF pos(elements[2].toInt(), elements[3].toInt());

            // Create module from given name and position.
            if (name == "CKeyboard") {
                modules[id] = addModule(SynthProFactory::KeyboardId, pos);
            } else if (name == "CVCO") {
                modules[id] = addModule(SynthProFactory::VCOId, pos);
            } else if (name == "CVCF") {
                modules[id] = addModule(SynthProFactory::VCFId, pos);
            } else if (name == "CVCA") {
                modules[id] = addModule(SynthProFactory::VCAId, pos);
            } else if (name == "CADSR") {
                modules[id] = addModule(SynthProFactory::ADSRId, pos);
            } else if (name == "CDelay") {
                modules[id] = addModule(SynthProFactory::DelayId, pos);
            } else if (name == "CMixer") {
                modules[id] = addModule(SynthProFactory::MixerId, pos);
            } else if (name == "CSampler") {
                modules[id] = addModule(SynthProFactory::SamplerId, pos);
            } else if (name == "CLFO") {
                modules[id] = addModule(SynthProFactory::LFOId, pos);
            } else if (name == "CSpeaker") {
                modules[id] = addModule(SynthProFactory::AudioOuputId, pos);
            } else if (name == "CWavRecorder") {
                modules[id] = addModule(SynthProFactory::FileOutputId, pos);
            } else if (name == "COscilloscope") {
                modules[id] = addModule(SynthProFactory::OscilloscopeId, pos);
            } else if (name == "CWavLooper") {
                modules[id] = addModule(SynthProFactory::WavLooperId, pos);
            } else {
                m_presentation->errorLoading(tr("Error loading an unexpected module."));
            }

            // Read settings.
            line = stream.readLine();
            dynamic_cast<CModule*>(modules[id])->setUpSettings(line);
            // TODO
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

int CSynthPro::dropAttemptsCount = 0;
