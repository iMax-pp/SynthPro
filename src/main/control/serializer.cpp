#include "serializer.h"

#include "abstraction/module.h"
#include "control/cmodule.h"
#include "control/csynthpro.h"
#include <typeinfo>

void operator<<(QTextStream& stream, const CSynthPro& synthPro)
{
    stream << synthPro.modules().size() << endl;

    foreach (Module* module, synthPro.modules()) {
        CModule* cmodule = dynamic_cast<CModule*>(module);
        stream << *cmodule;
    }
}

void operator<<(QTextStream& stream, const CModule& module)
{
    // Serialize Module real type.
    stream << typeid(module).name() << " ";
    // Serialize Module id.
    stream << &module << " ";
    // Serialize Module position.
    stream << module.presentation()->pos().rx() << " " << module.presentation()->pos().ry();

    // Newline before settings.
    stream << endl;
    // Serialize Module settings.
    stream << module.settings();

    // Newline before input connections.
    stream << endl;
    // Serialize Module input connections.
    stream << module.inputConnections();
}
