#ifndef MODULE_H
#define MODULE_H

#include <QObject>

class In;
class Out;

/**
 * A module is a component performing a single function (generating a signal, filtering, etc.)
 */
class Module : public QObject {
    Q_OBJECT

public:
    Module(QObject* parent = 0);

    /// Get the list of output ports of this module
    virtual QList<Out*>::const_iterator outports() const;

    /// Get the list of input ports of this module FIXME is it needed?
    virtual QList<In*>::const_iterator inports() const;

    /**
     * Operation called by the sequencer. Subclasses have to implement their own.
     */
    virtual void process() = 0;

    /// Get the list of required modules for this module to perform its function
    virtual QList<Module*>::const_iterator getReguirements() const = 0;

private:
    QList<Out*> m_outports;
    QList<In*> m_inports;
};

#endif // MODULE_H
