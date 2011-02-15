#ifndef SYNTHPRO_H
#define SYNTHPRO_H

#include <QObject>

class Module;

class SynthPro : public QObject {
    Q_OBJECT

public:
    SynthPro(QObject* parent = 0);

    /// @return The list of modules contained by this SynthPro
    const QList<Module*> modules() const;

    /// Add a module to this SynthPro
    virtual void add(Module*);

signals:
    void connectionsChanged(const SynthPro*);

public slots:
    void remove(QObject*);

private slots:
    void connectionsChanged();

private:
    QList<Module*> m_modules;
};

#endif // SYNTHPRO_H
