#include "cBicho.h"
#include "cScene.h"
#include "Globals.h"

cBicho::cBicho(void)
{
	seq=0;
	delay=0;
	health = 100;
	
}
cBicho::~cBicho(void){}

cBicho::cBicho(int posx,int posy,int width,int height)
{
	x = posx;
	y = posy;
	w = width;
	h = height;
}

void cBicho::Draw(cData *dat) {}

bool cBicho::CollidesBicho(cBicho * bicho)
{
	cRect r;
	bicho->GetArea(&r);
	return this->Collides(&r);
}
void cBicho::dealDamage(int dmg)
{
	this->health -= dmg;
}

int cBicho::getHealth()
{
	return this->health;
}

void cBicho::SetPosition(int posx,int posy)
{
	x = posx;
	y = posy;
}
void cBicho::GetPosition(int *posx,int *posy)
{
	*posx = x;
	*posy = y;
}
void cBicho::SetTile(int tx,int ty)
{
	x = tx * TILE_SIZE;
	y = ty * TILE_SIZE;
}
void cBicho::GetTile(int *tx,int *ty)
{
	*tx = x / TILE_SIZE;
	*ty = y / TILE_SIZE;
}
void cBicho::SetWidthHeight(int width,int height)
{
	w = width;
	h = height;
}
void cBicho::GetWidthHeight(int *width,int *height)
{
	*width = w;
	*height = h;
}
bool cBicho::Collides(cRect *rc)
{
	//return ((x>rc->left) && (x+w<rc->right) && (y>rc->bottom) && (y+h<rc->top));
	return (x < rc->right &&
		x + w > rc->left &&
		y < rc->top &&
		y + h > rc->bottom);
}
bool cBicho::CollidesMapWall(int *map,bool right)
{
	int tile_x,tile_y;
	int j;
	int width_tiles,height_tiles;

	tile_x = x / TILE_SIZE;
	tile_y = y / TILE_SIZE;
	width_tiles  = w / TILE_SIZE;
	height_tiles = h / TILE_SIZE;

	if(right)	tile_x += width_tiles;
	
	for(j=0;j<height_tiles;j++)
	{
		if(map[ tile_x + ((tile_y+j)*SCENE_WIDTH) ] != 0)	return true;
	}
	
	return false;
}

bool cBicho::CollidesMapFloor(int *map)
{
	int tile_x,tile_y;
	int width_tiles;
	bool on_base;
	int i;

	tile_x = x / TILE_SIZE;
	tile_y = y / TILE_SIZE;

	width_tiles = w / TILE_SIZE +1;
	if( (x % TILE_SIZE) != 0) width_tiles++;

	on_base = false;
	i=0;
	while((i<width_tiles) && !on_base)
	{
		if( (y % TILE_SIZE) == 0 )
		{
			if(map[ (tile_x + i) + ((tile_y - 1) * SCENE_WIDTH) ] != 0)
				on_base = true;
		}
		else
		{
			if(map[ (tile_x + i) + (tile_y * SCENE_WIDTH) ] != 0)
			{
				y = (tile_y + 1) * TILE_SIZE;
				on_base = true;
			}
		}
		i++;
	}
	return on_base;
}



void cBicho::GetArea(cRect *rc)
{
	rc->left   = x;
	rc->right  = x+w;
	rc->bottom = y;
	rc->top    = y+h;
}
void cBicho::DrawRect(int tex_id,float xo,float yo,float xf,float yf)
{
	int screen_x,screen_y;

	screen_x = x + SCENE_Xo;
	screen_y = y + SCENE_Yo + (BLOCK_SIZE - TILE_SIZE);

	glEnable(GL_TEXTURE_2D);
	
	glBindTexture(GL_TEXTURE_2D,tex_id);
	glBegin(GL_QUADS);	
		glTexCoord2f(xo,yo);	glVertex2i(screen_x  ,screen_y);
		glTexCoord2f(xf,yo);	glVertex2i(screen_x+w,screen_y);
		glTexCoord2f(xf,yf);	glVertex2i(screen_x+w,screen_y+h);
		glTexCoord2f(xo,yf);	glVertex2i(screen_x  ,screen_y+h);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void cBicho::MoveLeft(int *map)
{
	int xaux;
	
	//Whats next tile?
	if( (x % TILE_SIZE) <= 1)
	{
		xaux = x;
		x -= STEP_LENGTH;

		if(CollidesMapWall(map,false))
		{
			x = xaux;
			state = STATE_CENTER;
		}
	}
	//Advance, no problem
	else
	{
		x -= STEP_LENGTH - STEP_LENGTH;
		if(state != STATE_CENTER)
		{
			state = STATE_CENTER;
			seq = 0;
			delay = 0;
		}
	}
}
void cBicho::MoveDown(int * map)
{
	//copy paste from move jump(copypasted from moveLeft) swapping from x to y
	int xaux;

	//Whats next tile?
	if ((y % TILE_SIZE) <= 1)
	{
		xaux = y;
		y -= STEP_LENGTH;

		if (CollidesMapWall(map, false))
		{
			y = xaux;
			state = STATE_CENTER;
		}
	}
	//Advance, no problem
	else
	{
		y -= STEP_LENGTH;
		if (state != STATE_CENTER)
		{
			state = STATE_CENTER;
			seq = 0;
			delay = 0;
		}
	}
}
void cBicho::MoveRight(int *map)
{
	int xaux;

	//Whats next tile?
	if( (x % TILE_SIZE) <= 1)
	{
		xaux = x;
		x += STEP_LENGTH;

		if(CollidesMapWall(map,true))
		{
			x = xaux;
			state = STATE_CENTER;
		}
	}
	//Advance, no problem
	else
	{
		x += STEP_LENGTH;

		if(state != STATE_CENTER)
		{
			state = STATE_CENTER;
			seq = 0;
			delay = 0;
		}
	}
}
void cBicho::MoveHalfRight(int * map)
{
	int xaux;

	//Whats next tile?
	if ((x % TILE_SIZE) == 0)
	{
		xaux = x;
		x += STEP_LENGTH/2;

		if (CollidesMapWall(map, true))
		{
			x = xaux;
		}
	}
	//Advance, no problem
	else
	{
		x += STEP_LENGTH/2;

		if (state != STATE_CENTER)
		{
			seq = 0;
			delay = 0;
		}
	}
}
void cBicho::Stop()
{
	switch(state)
	{
		case STATE_CENTER:	state = STATE_CENTER;		break; //xk si queremos que tire fuego, aqui djara de tirarlo
		default:	state = STATE_CENTER;	break; //aqui en realidad no tendria k ir al centro directamente, tendria k haber
			//una transicion
	}
}
void cBicho::Jump(int *map)
{
	//copy paste from move LEFT swapping from x to y
	int xaux;

	//Whats next tile?
	if ((y % TILE_SIZE) == 0)
	{
		xaux = y;
		y += STEP_LENGTH;

		if (CollidesMapWall(map, false))
		{
			y = xaux;
			state = STATE_CENTER;
		}
	}
	//Advance, no problem
	else
	{
		y += STEP_LENGTH;
		if (state != STATE_CENTER)
		{
			state = STATE_CENTER;
			seq = 0;
			delay = 0;
		}
	}

}
void cBicho::Logic(int *map)
{
}
void cBicho::NextFrame(int max)
{
	delay++;
	if(delay == FRAME_DELAY)
	{
		seq++;
		seq%=max;
		delay = 0;
	}
}
int cBicho::GetFrame()
{
	return seq;
}
int cBicho::GetState()
{
	return state;
}
void cBicho::SetState(int s)
{
	state = s;
}