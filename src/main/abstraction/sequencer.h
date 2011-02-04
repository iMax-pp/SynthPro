#ifndef SEQUENCER_H
#define SEQUENCER_H

#include <QObject>

class SynthPro;
class Module;

/**
 * The Sequencer make all the module working together, taking care of cycles and
 * dependencies
 */
class Sequencer : public QObject {
    Q_OBJECT

public:
    Sequencer(SynthPro* parent);

    /**
     * Process each module in the order computed before.
     */
    void process();

public slots:
    /**
     * Sort the modules in the right order to be processed.
     */
    void scheduleModules();

protected:
    void scheduleModules(QList<Module*> modules);
    void findWells();

private:
    SynthPro* m_synthpro;
    QList<Module*> m_visitedModules;

    QList<Module*> m_wells;
    QList<Module*> m_sortedModules;
};

#endif // SEQUENCER_H
