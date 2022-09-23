#pragma once
#include "Vector.h"
#include <vector>
#include <queue>

enum CollisionType
{
    RECT_OUT = 0,
    RECT_IN,
    RECT_OVERLAP,
};

struct Circle
{
    float cx;
    float cy;
    float fRadius;
    Circle() {};
    Circle(float x, float y, float r) {
        cx = x;
        cy = y;
        fRadius = r;
    };
};

struct stRect
{
    float  x1;
    float  y1;
    float  w;
    float  h;
};

struct Rect : stRect
{
    float  x2;//x+w
    float  y2;//y+h
    float  cx;
    float  cy;
    bool   operator == (const Rect& dest)
    {
        if (fabs(x1 - dest.x1) < Epsilon)
        {
            if (fabs(y1 - dest.y1) < Epsilon)
            {
                if (fabs(w - dest.w) < Epsilon)
                {
                    if (fabs(h - dest.h) < Epsilon)
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    Rect() {}
    Rect(float x, float y, float z, float w) {
        Set(x, y, z, w);
    }
    void  Set(float x, float y, float z, float w)
    {
        this->x1 = x;
        this->y1 = y;
        this->w = z;
        this->h = w;
        x2 = this->x1 + this->w;
        y2 = this->y1 + this->h;
        cx = (this->x1 + x2) / 2.0f;
        cy = (this->y1 + y2) / 2.0f;
    }
};

struct Sphere
{
    Vector3D vCenter;
    float fRadius;
    Sphere() {};
    Sphere(const Vector3D& vC, float r) {
        vCenter = vC;
        fRadius = r;
    };
};
struct stBox
{
    Vector3D vMin;
    Vector3D vSize;
};
struct Box : stBox
{
    Vector3D vMax;
    Vector3D vCenter;
    bool   operator == (const Box& dest)
    {
        if (vMin == dest.vMin)
        {
            if (vSize == dest.vSize)
            {
                return true;
            }
        }
        return false;
    }
    Box() {}
    Box(const Vector3D& vPos, const Vector3D& vSize)
    {
        Set(vPos, vSize);
    }
    void  Set(const Vector3D& vPos, const Vector3D& vSize)
    {
        vMin = vPos;
        this->vSize = vSize;
        vMax = vMin + vSize;
        vCenter = (vMin + vMax) / 2.0f;
    }
};

class Collision
{
public:
    static CollisionType   RectToRect(const Rect& a, const Rect& b, Rect& Intersect);
    static bool             RectToInRect(const Rect& a, const Rect& b);
    static bool             RectToPoint(const Rect& a, const POINT& p);
    static bool             CircleToCircle(const Circle& a, const Circle& b);
public:
    static CollisionType   BoxToBox(const Box& a, const Box& b);
    static bool             BoxToInBox(const Box& a, const Box& b);
    static bool             SphereToSphere(const Sphere& a, const Sphere& b);
};
