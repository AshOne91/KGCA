#include "Pair.h"

#pragma warning(disable:26495)
template <typename T1, typename T2>
Pair<T1, T2>::Pair()
{
}
#pragma warning(default:26495)

template <typename T1, typename T2>
Pair<T1, T2>::Pair(T1 first, T2 second):T1(first),T2(second)
{
}
