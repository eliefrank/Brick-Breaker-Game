#include"MyListener.h"

MyListener::MyListener(Board& board)
    :m_board(board)
{
}

void MyListener::BeginContact(b2Contact* contact)
{
    const b2Fixture* fixtureA = contact->GetFixtureA();
    const b2Fixture* fixtureB = contact->GetFixtureB();

    const b2Body* body1 = fixtureA->GetBody();
    const b2Body* body2 = fixtureB->GetBody();

    auto obj1 = m_board.getObjWithId((int)(size_t)body1->GetUserData());
    auto obj2 = m_board.getObjWithId((int)(size_t)body2->GetUserData());

    if (obj1 && obj2)
        m_board.processCollision(*obj1, *obj2);
}

//void MyListener::EndContact(b2Contact* contact)
//{
//}

//void MyListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
//{
//}
