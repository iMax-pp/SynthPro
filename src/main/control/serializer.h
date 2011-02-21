#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <QTextStream>

class CModule;
class CSynthPro;

void operator<<(QTextStream&, const CSynthPro&);
void operator<<(QTextStream&, const CModule&);

#endif // SERIALIZER_H
