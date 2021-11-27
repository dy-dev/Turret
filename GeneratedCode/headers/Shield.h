//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : Shield.h
//  @ Date : 25/11/2021
//  @ Author : 
//
//


#if !defined(_SHIELD_H)
#define _SHIELD_H

#include "GraphicObjects.h"

class Shield : public GraphicObjects {
public:
	void ReceiveImpact();
	void LevelUp();
	void FullRestore();
	void Restore(int p_iRestorePoints);
private:
	int m_iLevel;
	int m_iMaxPoints;
	int m_iCurrentPoints;
	Shield();
};

#endif  //_SHIELD_H
