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

    static Sequencer& instance();

    /**
     * Process each module in the order computed before.
     */
    void process();

public slots:
    /**
     * Sort the modules in the right order to be processed.
     * Must be called each time the module configuration change.
     * @param synthpro The SynthPro to schedule modules
     */
    void scheduleModules(const SynthPro*);

protected:
    void scheduleModules(QList<Module*> modules);

    /// Find the wells modules owned by the synthpro
    void findWells(const SynthPro*);

private:
    Sequencer();
    Sequencer(Sequencer&); // Prevent copies

    QList<Module*> m_visitedModules;

    QList<Module*> m_wells;
    QList<Module*> m_sortedModules;
};

#endif // SEQUENCER_H
