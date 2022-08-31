#include <math.h>
#include "Collison.h"

bool Circle::operator==(const Circle& dest)
{
    if (this->center == dest.center)
    {
        if (fabsf(this->radius - this->radius) < Epsilon)
        {
            return true;
        }
    }
    return false;
}

bool Sphere::operator==(const Sphere& dest)
{
    if (this->center == dest.center)
    {
        if (fabsf(this->radius - this->radius) < Epsilon)
        {
            return true;
        }
    }
    return false;
}

bool Box2D::operator==(const Box2D& dest)
{
    if (fabsf(x1 - dest.x1) < Epsilon)
    {
        if (fabsf(y1 - dest.y1) < Epsilon)
        {
            if (fabsf(w - dest.w) < Epsilon)
            {
                if (fabsf(h - dest.h) < Epsilon)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Box3D::operator==(const Box3D& dest)
{
    if (this->min == dest.min)
    {
        if (this->size == dest.size)
        {
            return true;
        }
    }
    return false;
}

CollisionType Collision::CheckCollision(const Circle& a, const Circle& b)
{
    float lsq = Vector2D::DistanceSq(a.center, b.center);
    if (lsq > ((a.radius + b.radius) * (a.radius + b.radius)))
    {
        return CollisionType::COLLISON_OUT;
    }

    float sumRadius = a.radius + b.radius;
    float distance = Vector2D::Distance(a.center, b.center);
    if (distance <= sumRadius)
    {
        return CollisionType::COLLISON_IN;
    }

    return CollisionType::COLLISON_OVERLAP;
}

CollisionType Collision::CheckCollision(const Sphere& a, const Sphere& b)
{
    float lsq = Vector3D::DistanceSq(a.center, b.center);
    if (lsq > ((a.radius + b.radius) * (a.radius + b.radius)))
    {
        return CollisionType::COLLISON_OUT;
    }

    float sumRadius = a.radius + b.radius;
    float distance = Vector3D::Distance(a.center, b.center);
    if (distance <= sumRadius)
    {
        return CollisionType::COLLISON_IN;
    }

    return CollisionType::COLLISON_OVERLAP;
}

CollisionType Collision::CheckCollision(const Box2D& a, const Box2D& b)
{
    float fMinX;   float fMinY;
    float fMaxX;   float fMaxY;
    fMinX = a.x1 < b.x1 ? a.x1 : b.x1;
    fMinY = a.y1 < b.y1 ? a.y1 : b.y1;
    fMaxX = a.x2 > b.x2 ? a.x2 : b.x2;
    fMaxY = a.y2 > b.y2 ? a.y2 : b.y2;
    //  가로 판정
    if ((a.w + b.w) >= (fMaxX - fMinX))
    {
        //  세로 판정
        if ((a.h + b.h) >= (fMaxY - fMinY))
        {
            // 교차한다. 교집합
            float x, y, x2, y2;
            Box2D Intersect;
            x = a.x1 > b.x1 ? a.x1 : b.y1;
            y = a.y1 > b.y1 ? a.y1 : b.y1;
            x2 = a.x2 < b.x2 ? a.x2 : b.x2;
            y2 = a.y2 < b.y2 ? a.y2 : b.y2;
            Intersect.Set(x, y, x2 - x, y2 - y);
            if (Intersect == a || Intersect == b)
            {
                return CollisionType::COLLISON_IN;
            }
            return CollisionType::COLLISON_OVERLAP;
        }
    }
    return CollisionType::COLLISON_OUT;
}

CollisionType Collision::CheckCollision(const Box3D& a, const Box3D& b)
{
    // 0 : 완전제외(0)
    // 1 : 완전포함(1) -> 걸쳐져 있는 상태(2)
    // a.x(10)----30------a.x2(40)
    // 합집합
    float fMinX;    float fMaxX;
    float fMinY;    float fMaxY;
    float fMinZ;    float fMaxZ;
    fMinX = a.min.x < b.min.x ? a.min.x : b.min.x;
    fMinY = a.min.y < b.min.y ? a.min.y : b.min.y;
    fMaxX = a.max.x > b.max.x ? a.max.x : b.max.x;
    fMaxY = a.max.y > b.max.y ? a.max.y : b.max.y;

    fMinZ = a.min.z < b.min.z ? a.min.z : b.min.z;
    fMaxZ = a.max.z > b.max.z ? a.max.z : b.max.z;

    //  가로 판정
    if ((a.size.x + b.size.x) >= (fMaxX - fMinX))
    {
        //  세로 판정
        if ((a.size.y + b.size.y) >= (fMaxY - fMinY))
        {
            if ((a.size.z + b.size.z) >= (fMaxZ - fMinZ))
            {
                // 교차한다. 교집합
                Vector3D vMin, vMax;
                Box3D Intersect;
                vMin.x = a.min.x > b.min.x ? a.min.x : b.min.x;
                vMin.y = a.min.y > b.min.y ? a.min.y : b.min.y;
                vMin.z = a.min.z > b.min.z ? a.min.z : b.min.z;

                vMax.x = a.max.x < b.max.x ? a.max.x : b.max.x;
                vMax.y = a.max.y < b.max.y ? a.max.y : b.max.y;
                vMax.z = a.max.z < b.max.z ? a.max.z : b.max.z;

                Intersect.Set(vMin, vMax - vMin);
                if (Intersect == a || Intersect == b)
                {
                    return CollisionType::COLLISON_IN;
                }
                return CollisionType::COLLISON_OVERLAP;
            }
        }
    }
    return CollisionType::COLLISON_OUT;
}
