#include "synthpro.h"

#include "abstraction/clock.h"
#include "abstraction/component/inport.h"
#include "abstraction/component/outport.h"
#include "abstraction/component/virtualport.h"
#include "abstraction/module.h"
#include "abstraction/sequencer.h"

SynthPro::SynthPro(QObject* parent)
    : QObject(parent)
{
    Clock::instance().start();
    connect(this, SIGNAL(connectionsChanged(const SynthPro*)), &Sequencer::instance(), SLOT(scheduleModules(const SynthPro*)));
}

SynthPro::~SynthPro()
{
}

const QList<Module*> SynthPro::modules() const
{
    return m_modules;
}

void SynthPro::add(Module* module)
{
    m_modules.append(module);

    foreach (VirtualPort* port, module->inports()) {
        connect(port, SIGNAL(connectionsChanged()), this, SLOT(connectionsChanged()));
    }
    foreach (VirtualPort* port, module->outports()) {
        connect(port, SIGNAL(connectionsChanged()), this, SLOT(connectionsChanged()));
    }
}

void SynthPro::remove(QObject* object)
{
    Module* module = static_cast<Module*>(object);
    m_modules.removeOne(module);
    module->prepareDestruction();
    module->deleteLater();
}

void SynthPro::connectionsChanged()
{
    emit connectionsChanged(this);
}
