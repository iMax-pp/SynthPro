#include "synthpro.h"

#include "abstraction/clock.h"
#include "abstraction/inport.h"
#include "abstraction/module.h"
#include "abstraction/outport.h"
#include "abstraction/port.h"
#include "abstraction/sequencer.h"

SynthPro::SynthPro(QObject* parent)
    : QObject(parent)
{
    Clock::instance().start();
    connect(this, SIGNAL(connectionsChanged(const SynthPro*)), &Sequencer::instance(), SLOT(scheduleModules(const SynthPro*)));
}

const QList<Module*> SynthPro::modules() const
{
    return m_modules;
}

void SynthPro::add(Module* module)
{
    m_modules.append(module);

    foreach (Port* port, module->inports()) {
        connect(port, SIGNAL(connectionsChanged()), this, SLOT(connectionsChanged()));
    }
    foreach (Port* port, module->outports()) {
        connect(port, SIGNAL(connectionsChanged()), this, SLOT(connectionsChanged()));
    }
}

void SynthPro::connectionsChanged()
{
    emit connectionsChanged(this);
}
