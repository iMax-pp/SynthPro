#ifndef PDIAL_H
#define PDIAL_H

#include "presentation/component/pdimmer.h"

/**
 * Concrete presentation of a PDimmer.
 * Represents a dial.
 */
class PDial : public PDimmer {
public:
    PDial(CDimmer*, const QString& name, int min, int max, int defaultValue,
          QGraphicsItem* parent = 0);
};

#endif // PDIAL_H
