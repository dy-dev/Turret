//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : Grapnel.h
//  @ Date : 25/11/2021
//  @ Author : 
//
//


#if !defined(_GRAPNEL_H)
#define _GRAPNEL_H

#include "MovableObjects.h"

class Grapnel : public MovableObjects {
public:
	void TryGrabBonus(float p_fOrientation);
	void CalculateDirection();
	void Extends();
	void CatchBonus();
private:
	Vector2 m_Position;
	Vector2 m_Direction;
	Texture2D m_TextureHook;
	Texture2D m_TextureCable;
	Rectangle m_SourceRectangle;
	Rectangle m_DestRectangle;
	bool m_bLaunched;
	Grapnel();
};

#endif  //_GRAPNEL_H
