#pragma once
#include "Bola.h"
#include "Enemy.h"
#include <vector>
#include "Paracaidista.h"

using namespace std;

class Controladora {
private:
	vector<Bola*>Bolas;
	vector<Enemy*>enemies;
	int puntos = 0;
	int vidas = 4;
public:

	void createEnemies() {

		Enemy* a = new Enemy(95, 185);
		Enemy* b = new Enemy(95, 480);
		Enemy* c = new Enemy(280, 185);
		Enemy* d = new Enemy(480, 480);
		Enemy* e = new Enemy(280, 480);

		enemies.push_back(a);
		enemies.push_back(b);
		enemies.push_back(c);
		enemies.push_back(d);
		enemies.push_back(e);

	}
	void addEnemy(Enemy* b) {
		enemies.push_back(b);
	}
	void addBullet(Bola* b) {
		Bolas.push_back(b);
	}

	void drawEveryThing(Graphics^ g, Bitmap^ bmpEnemy, Bitmap^ bmpBullet) {
		for (int i = 0; i < enemies.size(); i++)
		{
			enemies[i]->Mostrar(g, bmpEnemy);
		}
		for (int i = 0; i < Bolas.size(); i++)
		{
			Bolas[i]->Mostrar(g, bmpBullet);
		}
	}

	void moveEveryThing(Graphics^ g, int x , int y) {
		for (int i = 0; i < enemies.size(); i++)
		{
			enemies[i]->Mover(g, x, y);
		}
		for (int i = 0; i < Bolas.size(); i++)
		{
			Bolas[i]->Mover(g);
		}
	}

	void Colision(Graphics^ g, Bitmap^ Vimg, Bitmap^ Pimg) {
		//verificar
		for (int i = 0; i < Bolas.size(); i++)
		{
			if (Bolas[i]->GetX() <= 0 || Bolas[i]->GetX() >= g->VisibleClipBounds.Width ||
				Bolas[i]->GetY() <= 0 || Bolas[i]->GetY() >= g->VisibleClipBounds.Height) {
				Bolas[i]->setVisibility(false);
			}
		}

		// colision bullet vs enemy
		for (int i = 0; i < enemies.size(); i++)
		{
			for (int j = 0; j < Bolas.size(); j++)
			{
				if (enemies[i]->getRectangle(Vimg).IntersectsWith(Bolas[j]->getRectangle(Pimg))) {
					
					if (enemies[i]->getRectangle(Vimg).IntersectsWith(Bolas[j]->getRectangle(Vimg))) {
						enemies[i]->setVisibility(false);
						Bolas[j]->setVisibility(false);
					}
				}
			}
		}
		//borrar
		for (int i = 0; i < Bolas.size(); i++)
		{
			if (!Bolas[i]->getVisibility()) { //if(Bullets[i]->getVisibility()==false)
				Bolas.erase(Bolas.begin() + i);
			}
		}

		for (int i = 0; i < enemies.size(); i++)
		{
			if (!enemies[i]->getVisibility()) {
				enemies.erase(enemies.begin() + i);
				puntos = puntos + 8;
			}
		}

	}

	void ColisionVidas(Bitmap^ Vimg, Rectangle R, Paracaidista*P) {
		// colision bullet vs enemy
		for (int i = 0; i < enemies.size(); i++)
		{
			if (enemies[i]->getRectangle(Vimg).IntersectsWith(R)) {
				vidas--;
				P->SetX(0);
				P->SetY(0);
			}
		}
	}
	
	int getPuntos() {
		return puntos;
	}

	void setVidas(int x) {
		vidas = x;
	}

	int Vidas() {
		return vidas;
	}

};