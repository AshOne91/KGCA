#include "Pair.h"

template <typename T1, typename T2>
Pair<T1, T2>::Pair()
{
}

template <typename T1, typename T2>
Pair<T1, T2>::Pair(T1 first, T2 second):T1(first),T2(second)
{
}
