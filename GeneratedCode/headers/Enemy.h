//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : Enemy.h
//  @ Date : 25/11/2021
//  @ Author : 
//
//


#if !defined(_ENEMY_H)
#define _ENEMY_H

#include "GraphicObjects.h"
#include "Destroyable.h"
#include "Shooter.h"

class Enemy : public GraphicObjects, public Destroyable, public Shooter {
public:
	Texture getBackTexture();
	Color getTint();
	void setTint(int p_iColor);
	void setDestroyed(bool p_bDestroyed);
	bool getDestroyed();
	void Attack();
	bool getDestroyed();
	void setDestroyed(bool p_bDestroyed);
private:
	Texture m_BackTexture;
	Color m_Tint;
	bool m_bDestroyed;
	Munition *m_Munition;
	Enemy();
	~Enemy();
};

#endif  //_ENEMY_H
