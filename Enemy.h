#pragma once
#include "Entidad.h"
using namespace System;
using namespace System::Drawing;
using namespace std;

class Enemy : public Entidad{

private:
	bool visibility;
public:
	Enemy(int X, int Y)
	{
		x = X;
		y = Y;
		dx = dy = 3;
		fila = 2;
		columna = 0;
		visibility = true;

	}
	~Enemy() {}

	void Mostrar(Graphics^ g, Bitmap^ img)
	{
		alto = (img->Height)/6 ;
		ancho = (img->Width)/5 ;

		Rectangle molde = Rectangle(columna * ancho, fila * alto, ancho, alto);

		g->DrawImage(img, x, y, molde, GraphicsUnit::Pixel);

		columna++;
		if (columna == 5) {
			columna = 0;
		}

	}

	void Mover(Graphics^ g , int X, int Y) {

		Rectangle ColisionVirus = Rectangle(x + 40, y + 20 + dy, ancho * 0.5, alto * 0.7);
		Rectangle ColisionVirus1 = Rectangle(x + 40 + dx, y + 20, ancho * 0.5, alto * 0.7);

		//Contorno del Personaje
		g->DrawRectangle(Pens::Red, ColisionVirus);
		g->DrawRectangle(Pens::Yellow, ColisionVirus);

		if (x > g->VisibleClipBounds.Width || x < 1) dx *= -1;
		if (y > g->VisibleClipBounds.Height || y < 1) dy *= -1;

		x = dx + x;
		y = dy + y;

		if (x>X) {
			fila = 5;
		}

	}
	Rectangle getRectangle(Bitmap^ img) {
		Rectangle ColisionVirus = Rectangle(x + 40, y + 20, ancho * 0.5, alto * 0.7);
		return ColisionVirus;
	}
	void setVisibility(bool v) { visibility = v; }
	bool getVisibility() { return visibility; }
};