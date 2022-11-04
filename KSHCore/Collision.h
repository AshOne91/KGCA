#pragma once
#include "TMath.h"
#include "Vector.h"
#include "Matrix.h"
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
        if (fabs(x1 - dest.x1) < Epsilon_)
        {
            if (fabs(y1 - dest.y1) < Epsilon_)
            {
                if (fabs(w - dest.w) < Epsilon_)
                {
                    if (fabs(h - dest.h) < Epsilon_)
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
    TVector3 vCenter;
    float fRadius;
    Sphere() {};
    Sphere(const TVector3& vC, float r) {
        vCenter = vC;
        fRadius = r;
    };
};
struct stBox
{
    TVector3 vMin;
    TVector3 vSize;
};

struct AABB
{
    TVector3 vMin;
    TVector3 vMax;
};

struct OBB
{
    TVector3 vCenter;
    TVector3 vAxis[3];
    float fDistance[3];
};

struct K_BOX
{
    TVector3 vPos[8];
    // aabb
    TVector3 vMin;
    TVector3 vMax;
    // obb
    TVector3 vCenter;
    TVector3 vAxis[3];
    float fExtent[3];
};

struct Box : stBox
{
    TVector3 vMax;
    TVector3 vCenter;
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
    Box(const TVector3& vPos, const TVector3& vSize)
    {
        Set(vPos, vSize);
    }
    void  Set(const TVector3& vPos, const TVector3& vSize)
    {
        vMin = vPos;
        this->vSize = vSize;
        vMax = vMin + vSize;
        vCenter = (vMin + vMax);
        vCenter /= 2.0f;
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
