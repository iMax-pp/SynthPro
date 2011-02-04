#include "synthpro.h"

SynthPro::SynthPro(QObject* parent)
    : QObject(parent)
{

}

QList<Module*> SynthPro::modules()
{
    return m_modules;
}

void SynthPro::add(Module* module)
{
    m_modules.append(module);
}
