#include "PhysicsObj.h"

PhysicsObj::PhysicsObj(b2World& world, const sf::Vector2f& loc, const sf::Vector2f& size, Type t)
    :m_t(t)
{
    auto objPhysicsInfo = ResourceManager::instance().getPhysicsInfo(t);
    b2BodyDef bodyDef;
    b2PolygonShape polygonShape;
    b2CircleShape circleShape;

    if (objPhysicsInfo._dynamic)
        bodyDef.type = b2_dynamicBody;
    else
        bodyDef.type = b2_staticBody;

    bodyDef.position.Set(loc.x * MPP, loc.y * MPP);

    m_body = world.CreateBody(&bodyDef);

    if (objPhysicsInfo._shape == RECT)
    {
        polygonShape.SetAsBox(size.x / 2 * MPP, size.y / 2 * MPP);
        m_fixtureDef.shape = &polygonShape;
    }
    else if (objPhysicsInfo._shape == CIRCLE)
    {
        circleShape.m_radius = size.x / 2 * MPP;
        m_fixtureDef.shape = &circleShape;
    }

    m_fixtureDef.friction = objPhysicsInfo._friction;
    m_fixtureDef.restitution = objPhysicsInfo._restitution;
    m_fixtureDef.density = objPhysicsInfo._density;
    m_fixture = m_body->CreateFixture(&m_fixtureDef);
}

PhysicsObj::~PhysicsObj()
{
    m_body->GetWorld()->DestroyBody(m_body);
}

void PhysicsObj::setPosition(const sf::Vector2f pos)
{
    auto angle = m_body->GetAngle();
    if (m_body->GetType() == b2BodyType::b2_dynamicBody)
        angle = 0;

    m_body->SetTransform(b2Vec2(pos.x * MPP, pos.y * MPP), angle);
    m_body->SetLinearVelocity(b2Vec2(0, 0));
    m_body->SetAngularVelocity(0);
    m_body->SetAwake(true);
}

b2Vec2 PhysicsObj::getPosition() const
{
    return m_body->GetPosition();
}

void PhysicsObj::applyForce(const b2Vec2& force)
{
    m_body->SetLinearVelocity({ force.x * 5, force.y * 5 });
}

void PhysicsObj::setID(int id)
{
    m_body->SetUserData((void*)((__int64)id));
}

void PhysicsObj::setSensor()
{
    m_fixture->SetSensor(true);
}

void PhysicsObj::updateVelocity()
{
    auto vel = m_body->GetLinearVelocity();

    b2Vec2 newVel(1, 1);
    if(vel.x > 0)
        newVel.x = 1;
    else if(vel.x == 0)
        newVel.x = 0;
    else
        newVel.x = -1;
        
    if(vel.y > 0)
        newVel.y = 1;
    else if(vel.y == 0)
        newVel.y = 0;
    else
        newVel.y = -1;
        
    if (!newVel.x && !newVel.y)
        newVel.y = 1;

    applyForce(newVel);
}

void PhysicsObj::setSize(const sf::Vector2f size)
{
    auto objPhysicsInfo = ResourceManager::instance().getPhysicsInfo(m_t);
    m_body->DestroyFixture(m_fixture);
    b2PolygonShape polygonShape;
    b2CircleShape circleShape;

    if (objPhysicsInfo._shape == RECT)
    {
        polygonShape.SetAsBox(size.x / 2 * MPP, size.y / 2 * MPP);
        m_fixtureDef.shape = &polygonShape;
    }
    else if (objPhysicsInfo._shape == CIRCLE)
    {
        circleShape.m_radius = size.x / 2 * MPP;
        m_fixtureDef.shape = &circleShape;
    }

    m_fixtureDef.friction = objPhysicsInfo._friction;
    m_fixtureDef.restitution = objPhysicsInfo._restitution;
    m_fixtureDef.density = objPhysicsInfo._density;
    m_fixture = m_body->CreateFixture(&m_fixtureDef);
}

void PhysicsObj::checkVelocity()
{
    if (!(m_body->GetLinearVelocity().x) && !(m_body->GetLinearVelocity().y))
        updateVelocity();
}
