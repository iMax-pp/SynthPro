#include "filterfactory.h"

#include "abstraction/filter.h"
#include "abstraction/filterhp229.h"
#include "abstraction/filterlp229.h"
#include "abstraction/filtersoftsaturation.h"

FilterFactory::FilterFactory()
{
    m_selectorConversionMap.insert(0, "Low Pass");
    m_selectorConversionMap.insert(1, "High Pass");
    m_selectorConversionMap.insert(2, "Soft Saturation");
}

Filter* FilterFactory::createFilter(const QString& filterType)
{
    if (filterType == "Filter LP") {
        return new FilterLP229();
    }

    if (filterType == "Filter HP") {
        return new FilterHP229();
    }

    if (filterType == "Soft Saturation") {
        return new FilterSoftSaturation();
    }

    return new FilterLP229();
}

QHash<int, QString>& FilterFactory::selectorConversionMap()
{
    return m_selectorConversionMap;
}
