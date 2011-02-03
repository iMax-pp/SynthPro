#ifndef MODULE_H
#define MODULE_H

#include <QObject>

class In;
class Out;

class Module : public QObject {
public:
    Q_OBJECT
    Module(QObject* parent = 0);
    virtual QList<Out*> outports() const;
    virtual QList<In*> inports() const;
    virtual void process() = 0;

private:
    QList<Out*> m_outports;
    QList<In*> m_inports;
};

#endif // MODULE_H
