#ifndef PDIAL_H
#define PDIAL_H

#include "presentation/component/pdimmer.h"

class QDial;

/**
 * Concrete presentation of a PDimmer.
 * Represents a dial.
 */
class PDial : public PDimmer {
public:
    PDial(CDimmer*, const QString& name, int min, int max, int defaultValue,
          QGraphicsItem* parent = 0);

    void setValue(int);

private:
    QDial* m_selector;
};

#endif // PDIAL_H
