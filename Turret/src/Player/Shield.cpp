#include "Player/Shield.h"

Shield::Shield(Vector2 p_Position, const int p_iScreenWidth, const int p_iScreenHeight, const char* p_pcTexturePath)
    : GraphicObjects(p_Position, p_iScreenWidth, p_iScreenHeight, p_pcTexturePath)
    , m_iCurrentPoints{}
    , m_iLevel{}
    , m_iMaxPoints{}
{
}

void Shield::ReceiveImpact()
{
}

void Shield::LevelUp()
{
}

void Shield::FullRestore()
{
}

void Shield::Restore(int p_iRestorePoints)
{
}
