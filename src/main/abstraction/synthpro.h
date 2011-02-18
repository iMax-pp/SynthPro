#ifndef SYNTHPRO_H
#define SYNTHPRO_H

#include <QObject>

class Module;

/**
 * Main class of the application.
 * Holds the list of instanciated Module.
 */
class SynthPro : public QObject {
    Q_OBJECT

public:
    explicit SynthPro(QObject* parent = 0);
    virtual ~SynthPro();

    /// @returns The QList of modules contained by this SynthPro.
    const QList<Module*> modules() const;

    /// @param module to add to this SynthPro.
    virtual void add(Module*);

public slots:
    /// @param module to remove from this SynthPro.
    void remove(QObject*);

protected slots:
    // Slot called when a connection to a VirtualPort is changed in a Module.
    void connectionsChanged();

signals:
    // Signal triggered when the slot connectionsChanged is called.
    void connectionsChanged(const SynthPro*);

private:
    QList<Module*> m_modules;
};

#endif // SYNTHPRO_H
