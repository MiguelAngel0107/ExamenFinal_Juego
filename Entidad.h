#pragma once
using namespace System::Drawing;
enum Direccion { Arriba, Abajo, Izquierda, Derecha, Ninguna };

class Entidad
{
protected:
	int x, y;
	int dx, dy;
	int ancho, alto;
	int fila, columna;
public:
	Entidad() {

	};
	~Entidad() {};

	int GetX() {
		return x;
	};
	int GetY() {
		return y;
	};
	int GetDX() {
		return dx;
	};
	int GetDY() {
		return dy;
	};
	int GetAncho() {
		return ancho;
	};
	int GetAlto() {
		return alto;
	};
	int GetFila() {
		return fila;
	};
	int GetColumna() {
		return columna;
	};

	void SetX(int n) {
		x = n;
	};
	void SetY(int n) {
		y = n;
	};
	void SetDX(int n) {
		dx = n;
	};
	void SetDY(int n) {
		dy = n;
	};
	void SetAncho(int n) {
		ancho = n;
	};
	void SetAlto(int n) {
		alto = n;
	};
	void SetFila(int n) {
		fila = n;
	};
	void SetColumna(int n) {
		columna = n;
	};

	virtual void Mostrar(Graphics^ g, Bitmap^ img) {

	};
	virtual void Mover(Direccion direccion, Graphics^ g) {

	};
};