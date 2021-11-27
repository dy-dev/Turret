#pragma once
#include "Game/GraphicObjects.h"

class Shield : public GraphicObjects {
public:   
    Shield(Vector2 p_Position, const int p_iScreenWidth, const int p_iScreenHeight, const char* p_pcTexturePath);

    void ReceiveImpact();
    void LevelUp();
    void FullRestore();
    void Restore(int p_iRestorePoints);
private:
    int m_iLevel;
    int m_iMaxPoints;
    int m_iCurrentPoints;
};