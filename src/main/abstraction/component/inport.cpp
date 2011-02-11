#include "inport.h"

#include "abstraction/buffer.h"
#include "abstraction/component/port.h"


InPort::InPort(Module* parent, const QString& name, SynthProFactory* factory, bool replicable, bool gate)
    : VirtualPort(parent, name, factory, replicable, gate)
{
}

void InPort::fetch()
{
    // Old code.
    /*
    m_buffer.clear();

    for (int i = 0; i < m_buffer.length(); i++) {
        foreach (Port* port, connections()) {
            if (port->connection()) {
                m_buffer.data()[i] += port->connection()->vPort()->buffer()->data()[i];
            }
        }
    }
    */

    // Optimised code.
    // We count only the connections that are actually connected to something !
    int nbConnectionTotal = connections().size();
    int nbConnectionUsed = 0;

    for (int i = 0; i < nbConnectionTotal; i++) {
        if (connections().at(i)->connection()) {
            nbConnectionUsed++;
        }
    }

    // If nothing is connected, clear the buffer.
    if (nbConnectionUsed == 0) {
        m_buffer.clear();
    } else {
        int size = m_buffer.length();

        // Scan all the connections to find those connected. The first one is simply duplicated.
        for (int noPass = 0; noPass < nbConnectionUsed; noPass++) {
            int noConnexion = 0;

            if (connections().at(noConnexion)) {
                // Found a connexion that is used.
                qreal* dataOut = m_buffer.data();
                qreal* dataIn = connections().at(noConnexion)->connection()->vPort()->buffer()->data();

                if (noPass == 0) {
                    // First connexion found : we duplicate it.
                    memcpy(dataOut, dataIn, sizeof(qreal) * m_buffer.length());
                } else {
                    // The other connexions are added.
                    for (int i = 0; i < size; i++) {
                        dataOut[i] += dataIn[i];
                    }
                }

                noConnexion++;
            }
        }
    }

}
