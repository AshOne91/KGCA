#include "TCollision.h"

TCollisionType TCollision::RectToRect(TRect& a, TRect& b)
{
    // 0 완전제외(0)
// 1 완전포함(1) -> 걸쳐져 있는 상태(2)
// x1(10)----30----x2(40)
    /*float x1 = a._x;
    float y1 = a._y;
    float x2 = a._x + a._w;
    float y2 = a._y + a._h;

    float z1 = b._x;
    float w1 = b._y;
    float z2 = b._x + b._w;
    float w2 = b._y + b._h;*/

    // 합집합
    float fMinX; float fMinY;
    float fMaxX; float fMaxY;
    fMinX = a._x < b._x ? a._x : b._x;
    fMinY = a._y < b._y ? a._y : b._y;
    fMaxX = a._x2 > b._x2 ? a._x2 : b._x2;
    fMaxY = a._y2 > b._y2 ? a._y2 : b._y2;

    // 가로 판정
    if ((a._w + b._w) > (fMaxX - fMinX))
    {
        //세로 판정
        if ((a._h + b._h) > (fMaxY - fMinY))
        {
            // 교차한다. 교집합
            float x, y, x2, y2;
            TRect Intersett;
            x = a._x > b._x ? a._x : b._x;
            y = a._y > b._y ? a._y : b._y;
            x2 = a._x2 < b._x2 ? a._x2 : b._x2;
            y2 = a._y2 < b._y2 ? a._y2 : b._y2;
            Intersett.Set(x, y, x2 - x, y2 - y);
            if (Intersett == a || Intersett == b)
            {
                return TCollisionType::RECT_IN;
            }
            return TCollisionType::RECT_OVERLAP;
        }
    }
    return TCollisionType::RECT_OUT;
}

bool TCollision::RectToInRect(TRect& a, TRect& b)
{
    if (a._x <= b._x)
    {
        if ((a._x + a._w) >= b._x + b._w)
        {
            if (a._y <= b._y)
            {
                if ((a._y + a._h) >= b._y + b._h)
                {
                    return true;
                }
            }
        }
    }
    return false;
}