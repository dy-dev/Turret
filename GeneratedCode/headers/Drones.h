//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : Drones.h
//  @ Date : 25/11/2021
//  @ Author : 
//
//


#if !defined(_DRONES_H)
#define _DRONES_H

#include "MovableObjects.h"

class Drones : public MovableObjects {
public:
	int m_iScanRange;
	void ScanForEnemy();
	void OnEnemyInRange();
};

#endif  //_DRONES_H
