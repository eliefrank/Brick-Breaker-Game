#pragma once
#include "Board.h"

class MyListener : public b2ContactListener
{
public:
    MyListener(Board& board);
    virtual void BeginContact(b2Contact* contact) override;

    //virtual void EndContact(b2Contact* contact) override;
    //virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;

private:
    Board& m_board;
};
