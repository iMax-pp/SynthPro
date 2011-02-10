#include "filterfactory.h"

#include "abstraction/filter.h"
#include "abstraction/filterhp229.h"
#include "abstraction/filterlp229.h"

FilterFactory::FilterFactory()
{
    m_selectorConversionMap.insert(0, "FilterLP229");
    m_selectorConversionMap.insert(1, "FilterHP229");
}

Filter* FilterFactory::createFilter(const QString& filterType)
{
    if (filterType == "FilterLP229") {
        return new FilterLP229();
    }

    if (filterType == "FilterHP229") {
        return new FilterHP229();
    }

    return new FilterLP229();
}

QHash<int, QString>& FilterFactory::selectorConversionMap()
{
    return m_selectorConversionMap;
}
