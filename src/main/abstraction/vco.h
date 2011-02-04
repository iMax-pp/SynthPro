#ifndef VCO_H
#define VCO_H

#include "module.h"

class VCO : public Module
{
    Q_OBJECT
public:
   VCO(QObject * parent=0);
   virtual void process() ;
   virtual QList<Module*>::const_iterator getReguirements() const ;
};

#endif // VCO_H
