#pragma once
#include "Entidad.h"
class Bola :public Entidad {
private:

	char direccion;
	bool visibility;
public:

	Bola(int x, int y, char d) {

		direccion = d;
		dx = dy = 30;
		this->x = x + 32;
		this->y = y + 50;
		visibility = true;
	}
	~Bola() {}

	void Mostrar(Graphics^ g, Bitmap^ img)
	{
		g->DrawImage(img, x, y, img->Width , img->Height );
	}

	void Mover(Graphics^ g)
	{
		switch (direccion)
		{
		case 'W':
			if (y > 0)
				y -= dy;
			break;
		case 'S':
			if (y + alto + dy < g->VisibleClipBounds.Height)
				y += dy;
			break;
		case 'A':
			if (x > 0)
				x -= dx;
			break;
		case 'D':
			if (x + ancho + dx < g->VisibleClipBounds.Width)
				x += dx;
			break;
		}
	}
	Rectangle getRectangle(Bitmap^ img) {
		return Rectangle(x, y, img->Width , img->Height );
	}


	void setVisibility(bool v) { visibility = v; }
	bool getVisibility() { return visibility; }
};