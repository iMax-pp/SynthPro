#include "csynthpro.h"

#include "cinport.h"
#include "control/clfo.h"
#include "control/cmodule.h"
#include "control/cmoduleout.h"
#include "control/coutport.h"
#include "control/cvca.h"
#include "control/cvcf.h"
#include "control/cvco.h"
#include "control/cvirtualport.h"
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
        break;
    case SynthProFactory::LFOId:
        module = dynamic_cast<Module*>(m_factory->createLFO(this));
        break;
    case SynthProFactory::AudioOuputId:
        module = dynamic_cast<Module*>(m_factory->createModuleOut(this));
        break;
    case SynthProFactory::FileOutputId:
        break;
    default:
        break;
    }

    if (module) {
        add(module);
        dynamic_cast<CModule*>(module)->presentation()->setPos(pos);
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
