#ifndef MODULE_H
#define MODULE_H

#include <QObject>

class InPort;
class OutPort;

/**
 * A module is a component performing a single function (generating a signal, filtering, etc.)
 */
class Module : public QObject {
    Q_OBJECT

public:
    Module(QObject* parent = 0);

    /// Get the list of output ports of this module
    virtual QList<OutPort*>::const_iterator outports() const;

    /// Get the list of input ports of this module FIXME is it needed?
    virtual QList<InPort*>::const_iterator inports() const;

    /**
     * Operation called by the sequencer. Subclasses have to implement their own.
     */
    virtual void process() = 0;

    /// Get the list of required modules for this module to perform its function
    virtual QList<Module*>::const_iterator getReguirements() const = 0;

protected:
    QList<OutPort*> m_outports;
    QList<InPort*> m_inports;
};

#endif // MODULE_H
