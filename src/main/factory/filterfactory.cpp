#include "filterfactory.h"

#include "abstraction/filter/filter.h"
#include "abstraction/filter/filterhp229.h"
#include "abstraction/filter/filterlp229.h"
#include "abstraction/filter/filtersoftsaturation.h"

FilterFactory::FilterFactory()
{
    m_selectorConversionMap.insert(0, "Low Pass");
    m_selectorConversionMap.insert(1, "High Pass");
    m_selectorConversionMap.insert(2, "Soft Saturation");
}

Filter* FilterFactory::createFilter(const QString& filterType)
{
    if (filterType == "Low Pass") {
        return new FilterLP229();
    }

    if (filterType == "High Pass") {
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
