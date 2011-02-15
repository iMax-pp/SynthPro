#include "synthpro.h"

#include "abstraction/clock.h"
#include "abstraction/component/inport.h"
#include "abstraction/component/outport.h"
#include "abstraction/component/virtualport.h"
#include "abstraction/module.h"
#include "abstraction/sequencer.h"
#include <QSignalMapper>

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

    foreach (VirtualPort* port, module->inports()) {
        connect(port, SIGNAL(connectionsChanged()), this, SLOT(connectionsChanged()));
    }
    foreach (VirtualPort* port, module->outports()) {
        connect(port, SIGNAL(connectionsChanged()), this, SLOT(connectionsChanged()));
    }

    QSignalMapper* mapper = new QSignalMapper(this);
    connect(module, SIGNAL(destroyed()), mapper, SLOT(map()));
    mapper->setMapping(module, module);
    connect(mapper, SIGNAL(mapped(QObject*)), SLOT(remove(QObject*)));
}

void SynthPro::remove(QObject* module)
{
    m_modules.removeOne(static_cast<Module*>(module));
}

void SynthPro::connectionsChanged()
{
    emit connectionsChanged(this);
}
