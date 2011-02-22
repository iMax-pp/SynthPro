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

Module* CSynthPro::addModule(SynthProFactory::ModuleType moduleType, const QPointF& pos, bool loadFile)
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
        module = dynamic_cast<Module*>(m_factory->createWavRecorder(this, loadFile));
        break;
    case SynthProFactory::OscilloscopeId:
        module = dynamic_cast<Module*>(m_factory->createOscilloscope(this));
        break;
    case SynthProFactory::WavLooperId:
        module = dynamic_cast<Module*>(m_factory->createWavLooper(this, loadFile));
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

        QHash<QString, Module*> modulesList;
        QMultiHash<InPort*, QString> connections;

        // Recreate each one.
        for (int i = 0; i < nbModules && !line.isNull(); i++) {
            line = stream.readLine();
            QStringList elements = line.split(QRegExp("\\s+"), QString::SkipEmptyParts);

            // Retrieve module name (Remove the number at name start).
            QString name = elements[0].remove(QRegExp("[0-9]{1,2}"));
            QString id = elements[1];

            // Retrieve module position.
            QPointF pos(elements[2].toInt(), elements[3].toInt());

            // Create module from given name and position.
            if (name == "CKeyboard") {
                modulesList[id] = addModule(SynthProFactory::KeyboardId, pos);
            } else if (name == "CVCO") {
                modulesList[id] = addModule(SynthProFactory::VCOId, pos);
            } else if (name == "CVCF") {
                modulesList[id] = addModule(SynthProFactory::VCFId, pos);
            } else if (name == "CVCA") {
                modulesList[id] = addModule(SynthProFactory::VCAId, pos);
            } else if (name == "CADSR") {
                modulesList[id] = addModule(SynthProFactory::ADSRId, pos);
            } else if (name == "CDelay") {
                modulesList[id] = addModule(SynthProFactory::DelayId, pos);
            } else if (name == "CMixer") {
                modulesList[id] = addModule(SynthProFactory::MixerId, pos);
            } else if (name == "CSampler") {
                modulesList[id] = addModule(SynthProFactory::SamplerId, pos);
            } else if (name == "CLFO") {
                modulesList[id] = addModule(SynthProFactory::LFOId, pos);
            } else if (name == "CSpeaker") {
                modulesList[id] = addModule(SynthProFactory::AudioOuputId, pos);
            } else if (name == "CWavRecorder") {
                modulesList[id] = addModule(SynthProFactory::FileOutputId, pos);
            } else if (name == "COscilloscope") {
                modulesList[id] = addModule(SynthProFactory::OscilloscopeId, pos);
            } else if (name == "CWavLooper") {
                modulesList[id] = addModule(SynthProFactory::WavLooperId, pos);
            } else {
                m_presentation->errorLoading(tr("Error loading an unexpected module."));
            }

            // Read and Set up settings.
            line = stream.readLine();
            dynamic_cast<CModule*>(modulesList[id])->setUpSettings(line);

            // Retrieve connections.
            line = stream.readLine();
            // First the number of inports of this module,
            int nbInports = line.toInt();

            for (int i = 0; i < nbInports && !line.isNull(); i++) {
                // Then for each inport,
                line = stream.readLine();
                QStringList list = line.split(QRegExp("\\s+"), QString::SkipEmptyParts);
                InPort* inport = modulesList[id]->inports()[list[0].toInt()];

                // Its count of connections,
                int nbConnections = list[1].toInt();

                // And the connections.
                for (int j = 0; j < nbConnections * 2; j += 2) {
                    connections.insert(inport, QString(list[j + 2] + " " + list[j + 3]));
                }
            }
        }

        // Rebind the connections.
        foreach (InPort* inport, connections.uniqueKeys()) {
            QList<QString> moduleList = connections.values(inport);

            foreach (const QString& module, moduleList) {
                // Take each associated module of the inport and connect it to the given outport.
                QStringList list = module.split(QRegExp("\\s+"), QString::SkipEmptyParts);
                modulesList[list[0]]->outports()[list[1].toInt()]->connect(inport);
            }
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
