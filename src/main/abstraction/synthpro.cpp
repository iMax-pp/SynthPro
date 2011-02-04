#include "synthpro.h"

SynthPro::SynthPro(QObject *parent)
    : QObject(parent)
{

}

QList<Module*> SynthPro::modules()
{
    return m_modules;
}
