#include "particle.h"
#include <assert.h>

void KPhysics::particle::integrate(real duration)
{
    if (inverseMass <= 0.0f) return;

    assert(duration > 0.0);

    position.addScaledVector(velocity, duration);

    Vector3 resultingAcc = acceleration;
    resultingAcc.addScaledVector(forceAccum, inverseMass);

    velocity.addScaledVector(resultingAcc, duration);

    velocity *= real_pow(damping, duration);

    clearAccumulator();
}

void KPhysics::particle::setMass(const real mass)
{
    assert(mass != 0);
    inverseMass = ((real)1.0) / mass;
}

KPhysics::real KPhysics::particle::getMass() const
{
    if (inverseMass == 0)
    {
        return REAL_MAX;
    }
    else
    {
        return ((real)1.0) / inverseMass;
    }
    return real();
}

void KPhysics::particle::setInverseMass(const real inverseMass)
{
    this->inverseMass = inverseMass;
}

KPhysics::real KPhysics::particle::getInverseMass() const
{
    return inverseMass;
}

bool KPhysics::particle::hasFiniteMass() const
{
    return inverseMass >= 0.0f;
}

void KPhysics::particle::setDamping(const real damping)
{
    this->damping = damping;
}

KPhysics::real KPhysics::particle::getDamping() const
{
    return damping;
}

void KPhysics::particle::setPosition(const Vector3& position)
{
    this->position = position;
}

void KPhysics::particle::setPosition(const real x, const real y, const real z)
{
    position.x = x;
    position.y = y;
    position.z = z;
}

void KPhysics::particle::getPosition(Vector3* position) const
{
    *position = this->position;
}

KPhysics::Vector3 KPhysics::particle::getPosition() const
{
    return position;
}

void KPhysics::particle::setVelocity(const Vector3& velocity)
{
    this->velocity = velocity;
}

void KPhysics::particle::setVelocity(const real x, const real y, const real z)
{
    velocity.x = x;
    velocity.y = y;
    velocity.z = z;
}

void KPhysics::particle::getVelocity(Vector3* velocity) const
{
    *velocity = this->velocity;
}

KPhysics::Vector3 KPhysics::particle::getVelocity() const
{
    return velocity;
}

void KPhysics::particle::setAcceleration(const Vector3& acceleration)
{
    this->acceleration = acceleration;
}

void KPhysics::particle::setAcceleration(const real x, const real y, const real z)
{
    acceleration.x = x;
    acceleration.y = y;
    acceleration.z = z;
}

void KPhysics::particle::getAcceleration(Vector3* acceleration) const
{
    *acceleration = this->acceleration;
}

KPhysics::Vector3 KPhysics::particle::getAcceleration() const
{
    return acceleration;
}

void KPhysics::particle::clearAccumulator()
{
    forceAccum.clear();
}

void KPhysics::particle::addForce(const Vector3& force)
{
    forceAccum += force;
}
