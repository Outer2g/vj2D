#pragma once
#include "cBicho.h"
#include "Globals.h"

//tipos proyectil
#define BULLET_SIMPLE 1
#define BULLET_DOBLE 2
class cProyectil :	public cBicho
{
public:
	cProyectil();
	~cProyectil();

	bool CollidesBicho(cBicho* bicho);
	virtual void Logic(int *map);

	virtual void Draw(cData *dat);

	void setSpeed(int x, int y);
	void getSpeed(int* x, int* y);
	int getDamage();
private:
	int dmg;
	int speedX, speedY;
};

