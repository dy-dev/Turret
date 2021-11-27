#pragma once

#include "Game/MovableObjects.h"

class Drones : public MovableObjects {
public:
    int m_iScanRange;
    void ScanForEnemy();
    void OnEnemyInRange();
};