#include "filterfactory.h"

#include "abstraction/filter/filter.h"
#include "abstraction/filter/filterhp229.h"
#include "abstraction/filter/filterlp229.h"
#include "abstraction/filter/filtersoftsaturation.h"

const QString FilterFactory::LowPass = QObject::tr("Low Pass");
const QString FilterFactory::HighPass = QObject::tr("High Pass");
const QString FilterFactory::SoftSaturation = QObject::tr("Soft Saturation");

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
