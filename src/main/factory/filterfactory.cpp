#include "filterfactory.h"

#include "abstraction/filter/filter.h"
#include "abstraction/filter/filterhp229.h"
#include "abstraction/filter/filterlp229.h"
#include "abstraction/filter/filtersoftsaturation.h"

QString FilterFactory::LowPass = "Low Pass";
QString FilterFactory::HighPass = "High Pass";
QString FilterFactory::SoftSaturation = "Soft Saturation";

FilterFactory::FilterFactory()
{
    m_selectorConversionMap.insert(0, LowPass);
    m_selectorConversionMap.insert(1, HighPass);
    m_selectorConversionMap.insert(2, SoftSaturation);
}

Filter* FilterFactory::createFilter(const QString& filterType)
{
    if (filterType == LowPass) {
        return new FilterLP229();
    }

    if (filterType == HighPass) {
        return new FilterHP229();
    }

    if (filterType == SoftSaturation) {
        return new FilterSoftSaturation();
    }

    return new FilterLP229();
}

QHash<int, QString>& FilterFactory::selectorConversionMap()
{
    return m_selectorConversionMap;
}
