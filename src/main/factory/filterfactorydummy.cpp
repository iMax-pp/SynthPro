#include "filterfactory.h"

#include "abstraction/filter.h"
#include "abstraction/filterdummy.h"
#include "abstraction/filterhp229.h"
#include "abstraction/filterincrement.h"
#include "abstraction/filterlp229.h"
#include "abstraction/filtersoftsaturation.h"

FilterFactory::FilterFactory()
{
    m_selectorConversionMap.insert(0, "Dummy");
    m_selectorConversionMap.insert(1, "Increment");
    m_selectorConversionMap.insert(2, "Low Pass");
    m_selectorConversionMap.insert(3, "High Pass");
    m_selectorConversionMap.insert(4, "Soft Saturation");
}

Filter* FilterFactory::createFilter(const QString& filterType)
{
    if (filterType == "Dummy") {
        return new FilterDummy();
    }

    if (filterType == "Increment") {
        return new FilterIncrement();
    }

    if (filterType == "Low Pass") {
        return new FilterLP229();
    }

    if (filterType == "High Pass") {
        return new FilterHP229();
    }

    if (filterType == "Soft Saturation") {
        return new FilterSoftSaturation();
    }

    return new FilterDummy();
}

QHash<int, QString>& FilterFactory::selectorConversionMap()
{
    return m_selectorConversionMap;
}

