#include "cProyectil.h"
#include "cGame.h"



cProyectil::cProyectil()
{
	this->dmg = 100;
}

cProyectil::cProyectil(int id, int tipo)
{
	this->id = id;
	this->dmg = 100;
	this->tipo = tipo;
}


cProyectil::~cProyectil()
{
}


void cProyectil::Logic(int * map)
{
	//Whats next tile?
	if ((y % TILE_SIZE) <= 1)
	{
		y += speedY;
		x += speedX;
		//si choca con tile, se autodestruye muy fuerte
		if (CollidesMapWall(map, false)) delete this;
	}
	//Advance, no problem
	else
	{
		y += speedY;
		x += speedX;
		//TODO: si choca, hace magia
	}
}

void cProyectil::Draw(cData * dat)
{
	float xo, yo, xf, yf;
	switch (tipo) {
	case 0: 
		
		xo = 0.1796875f * GetFrame(); //cada uno son 46*50 y la imagen es de 256*64
		yo = 0.78125f;
		NextFrame(4);
		//coord textur: xo,yo
		xf = xo + 0.1796875f;//1/8 da el 0.125
		yf = 0.f; //xk la nave ocupa toda la altura d la textura

		DrawRect(dat->GetID(IMG_ESTATIC), xo, yo, xf, yf);
		break;

	case 1:
		xo = 0.203125f * GetFrame(); //cada uno son 13*12, la imagen util 52*12 y la imagen es de 64*16
		yo = 1.f;
		NextFrame(4);
		//coord textur: xo,yo
		xf = xo + 0.203125f;//1/8 da el 0.125
		yf = 0.f; //xk la nave ocupa toda la altura d la textura
		DrawRect(dat->GetID(IMG_BULLET_VOLADOR), xo, yo, xf, yf);
		break;
	}
	
}

void cProyectil::setSpeed(int x, int y)
{
	this->speedX = x;
	this->speedY = y;
}

void cProyectil::getSpeed(int * x, int * y)
{
	*x = this->speedX;
	*y = this->speedY;
}

void cProyectil::setId(int id)
{
	this->id = id;
}

int cProyectil::getId()
{
	return this->id;
}

int cProyectil::getDamage()
{
	return this->dmg;
}
