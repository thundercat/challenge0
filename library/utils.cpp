#include "utils.h"

#include "event.h"
#include <QDebugStateSaver>

QDebug& operator <<(QDebug &debug, const Event &event)
{
    QDebugStateSaver saver(debug);
    debug.nospace() << event.toString();
    return debug;
}
