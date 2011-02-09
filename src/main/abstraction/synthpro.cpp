#include "synthpro.h"

#include "abstraction/clock.h"

SynthPro::SynthPro(QObject* parent)
    : QObject(parent)
{
    Clock::instance().start();
}

const QList<Module*> SynthPro::modules() const
{
    return m_modules;
}

void SynthPro::add(Module* module)
{
    m_modules.append(module);
}
