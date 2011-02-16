#ifndef FILTERFACTORY_H
#define FILTERFACTORY_H

#include <QHash>

class Filter;

/**
 *  This factory instantiate Filters according to a QString value given as parameter of the createFilter method.
 */
class FilterFactory {
public:
    FilterFactory();

    Filter* createFilter(const QString&);
    QHash<int, QString>& selectorConversionMap();

    static QString LowPass;
    static QString HighPass;
    static QString SoftSaturation;

protected:
    QHash<int, QString> m_selectorConversionMap;
};

#endif // FILTERFACTORY_H
