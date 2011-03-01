#ifndef QTRIO_H
#define QTRIO_H

#include <QPair>

template<class T1, class T2, class T3>
class QTrio
{
public:
    explicit QTrio() { }
    explicit QTrio(T1 first,T2 second,T3 third) : first(first), second(second), third(third) { }
    T1 first;
    T2 second;
    T3 third;
};

#endif // QTRIO_H
