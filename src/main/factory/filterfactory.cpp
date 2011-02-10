#include "filterfactory.h"

#include "abstraction/filter.h"
#include "abstraction/filterdummy.h"
#include "abstraction/filterincrement.h"
#include "abstraction/filterlp229.h"
#include "abstraction/filterhp229.h"

FilterFactory::FilterFactory()
{
    m_selectorConversionMap.insert(0, "FilterDummy");
    m_selectorConversionMap.insert(1, "FilterIncrement");
    m_selectorConversionMap.insert(2, "FilterLP229");
    m_selectorConversionMap.insert(3, "FilterHP229");
}

Filter* FilterFactory::createFilter(const QString& filterType)
{
    if (filterType == "FilterDummy") {
        return new FilterDummy();
    }

    if (filterType == "FilterIncrement") {
        return new FilterIncrement();
    }

    if (filterType == "FilterLP229") {
        return new FilterLP229();
    }

    if (filterType == "FilterHP229") {
        return new FilterHP229();
    }

    return new FilterDummy();
}

QHash<int, QString>& FilterFactory::selectorConversionMap()
{
    return m_selectorConversionMap;
}
