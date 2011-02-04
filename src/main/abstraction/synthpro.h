#ifndef SYNTHPRO_H
#define SYNTHPRO_H

#include <QObject>

class Module;

class SynthPro : public QObject {
    Q_OBJECT

public:
    SynthPro(QObject *parent = 0);
    QList<Module*> modules();

private:
    QList<Module*> m_modules;
};

#endif // SYNTHPRO_H
