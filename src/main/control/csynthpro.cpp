#include "csynthpro.h"

#include "control/cmodule.h"
#include "control/cmoduleout.h"
#include "control/cvca.h"
#include "control/cvcf.h"
#include "control/cvco.h"
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

void CSynthPro::addModule(QtFactory::ModuleType moduleType, const QPointF& pos)
{
    Module* module = 0;

    switch (moduleType) {
    case QtFactory::KeyboardId:
        break;
    case QtFactory::VCOId:
        module = dynamic_cast<Module*>(m_factory->createVCO());
        break;
    case QtFactory::VCFId:
        module = dynamic_cast<Module*>(m_factory->createVCF());
        break;
    case QtFactory::VCAId:
        module = dynamic_cast<Module*>(m_factory->createVCA());
        break;
    case QtFactory::ADSRId:
        break;
    case QtFactory::AudioOuputId:
        module = dynamic_cast<Module*>(m_factory->createModuleOut(0));
        break;
    case QtFactory::FileOutputId:
        break;
    default:
        break;
    }

    if (module) {
        add(module);
        dynamic_cast<CModule*>(module)->presentation()->setPos(pos);
    }
}
