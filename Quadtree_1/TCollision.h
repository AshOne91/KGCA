#pragma once
#include <iostream>
#include <vector>
#include <queue>

enum TCollisionType
{
	RECT_OUT = 0,
	RECT_IN,
	RECT_OVERLAP
};
struct Rect
{
    float _x;
    float _y;
    float _w;
    float _h;
};
struct TCircle
{
    float cx;
    float cy;
    float fRadius;
    TCircle() {};
    TCircle(float x, float y, float r)
    {
        cx = x;
        cy = y;
        fRadius = r;
    };
};
struct TRect : Rect
{
    float _x2; // x + w;
    float _y2; // y + h;
    float _cx;
    float _cy;
    bool operator == (TRect& dest)
    {
        if (fabs(_x-dest._x) < 0.001f)
        {
            if (fabs(_y-dest._y) < 0.001f)
            {
                if (fabs(_w-dest._w) < 0.001f)
                {
                    if (fabs(_h-dest._h) < 0.001f)
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    TRect() {}
    TRect(float x, float y, float w, float h)
    {
        Set(x, y, w, h);
    }
    void Set(float x, float y, float w, float h)
    {
        this->_x = x;
        this->_y = y;
        this->_w = w;
        this->_h = h;
        _x2 = x + w;
        _y2 = y + h;
        _cx = (x + _x2) / 2.0f;
        _cy = (y + _y2) / 2.0f;
    }
};

class TCollision
{
public:
    static TCollisionType RectToRect(TRect& a, TRect& b);
    static bool           RectToInRect(TRect& a, TRect& b);
    static bool           CircleToCircle(TCircle& a, TCircle& b);
};