#include "pmixer.h"

#include "control/module/cmixer.h"
#include "presentation/component/pdimmer.h"
#include "presentation/component/pport.h"
#include "presentation/component/pvirtualport.h"

PMixer::PMixer(CMixer* control)
    : PModule(control)
{
}

void PMixer::initialize(QMap<PVirtualPort*, PDimmer*>*, PVirtualPort*)
{

}
