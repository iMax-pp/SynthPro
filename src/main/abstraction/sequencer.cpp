#include "sequencer.h"

#include "abstraction/module.h"
#include "abstraction/synthpro.h"

Sequencer::Sequencer(SynthPro* synthpro)
    : QObject(synthpro)
    , m_synthpro(synthpro)
{
}

void Sequencer::process()
{
    foreach(Module* module, m_sortedModules) {
        module->process();
    }
}

void Sequencer::findWells()
{
    m_wells.clear();
    foreach(Module* module, m_synthpro->modules()) {
        if (module->outports().count() == 0) {
            m_wells.append(module);
        }
    }
}

void Sequencer::scheduleModules()
{
    m_sortedModules.clear();
    m_visitedModules.clear();
    findWells();
    scheduleModules(m_wells);
}

void Sequencer::scheduleModules(QList<Module*> modules)
{
    /*
     * Find recursively the requirements of each module (starting from the wells)
     */
    foreach(Module* module, modules) {
        if (!m_visitedModules.contains(module)) {
            // Add the module to the visited list, in order to avoid cycles
            m_visitedModules.append(module);

            // Apply recursively this process to the required modules of the current module
            scheduleModules(module->getReguirements());

            m_sortedModules.append(module);
        }
    }
}
