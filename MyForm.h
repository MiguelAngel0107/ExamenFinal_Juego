#pragma once
#include "Bola.h"
#include "Enemy.h"
#include "Paracaidista.h"
#include "Controladora.h"
#include <ctime>


namespace ExamenFinal {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			srand(time(NULL));
			g = this->CreateGraphics();
			bfc = BufferedGraphicsManager::Current;
			bf = bfc->Allocate(g, this->ClientRectangle);
			P = new Paracaidista();
			control = new Controladora();
			Pimg = gcnew Bitmap("Paracaidista.png");
			Bimg = gcnew Bitmap("Bola.png");
			Eimg = gcnew Bitmap("Enemy.png");
			F1 = gcnew Bitmap("Fondo1.jpg");
			F2 = gcnew Bitmap("Fondo2.jpg");
			F3 = gcnew Bitmap("Fondo3.jpg");
			F4 = gcnew Bitmap("Fondo4.jpg");
			control->createEnemies();
			bmpFondo = F2;
		}

	protected:

		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		Graphics^ g;
		BufferedGraphicsContext^ bfc;
		BufferedGraphics^ bf;

		Bitmap^ Pimg;
		Bitmap^ Bimg;
		Bitmap^ Eimg;

		Bitmap^ bmpFondo;

		Bitmap^ F1;
		Bitmap^ F2;
		Bitmap^ F3;
		Bitmap^ F4;

		Controladora* control;

		Paracaidista* P;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Timer^ timer2;
	private: System::Windows::Forms::Timer^ timer3;
	private: System::ComponentModel::IContainer^ components;



#pragma region Windows Form Designer generated code

		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->timer2 = (gcnew System::Windows::Forms::Timer(this->components));
			this->timer3 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(0, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(35, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"label1";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(0, 13);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(35, 13);
			this->label2->TabIndex = 1;
			this->label2->Text = L"label2";
			// 
			// timer2
			// 
			this->timer2->Interval = 5000;
			this->timer2->Tick += gcnew System::EventHandler(this, &MyForm::timer2_Tick);
			// 
			// timer3
			// 
			this->timer3->Enabled = true;
			this->timer3->Interval = 5000;
			this->timer3->Tick += gcnew System::EventHandler(this, &MyForm::timer3_Tick);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1211, 619);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {


		if (e->KeyCode == Keys::Up) {
			P->Mover(Direccion::Arriba, g);
		}
		else if (e->KeyCode == Keys::Down) {
			P->Mover(Direccion::Abajo, g);
		}
		else if (e->KeyCode == Keys::Left) {
			P->Mover(Direccion::Izquierda, g);
		}
		else if (e->KeyCode == Keys::Right) {
			P->Mover(Direccion::Derecha, g);
		}
		else if (e->KeyCode == Keys::Space) {
			Bola* b = new Bola(P->GetX(), P->GetY(), P->getDireccion());
			control->addBullet(b);
		}
		else if (e->KeyCode==Keys::M) {
			bmpFondo = F3;
			control->setVidas(4);

			this->timer2->Enabled = true;
		}
		else if (e->KeyCode == Keys::Escape) {
			this->timer1->Enabled = false;
			this->Close();
		}

	}
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		
		bf->Graphics->Clear(Color::WhiteSmoke);
		label1->Text = "Puntos Acumulados: " + control->getPuntos();	
		label2->Text = "Vidas: " + control->Vidas();

		bf->Graphics->DrawImage(bmpFondo, 0, 0, bmpFondo->Width , bmpFondo->Height );
		
		control->Colision(bf->Graphics, Eimg, Bimg);
		control->ColisionVidas(Eimg, P->getRectangle() , P);

		control->drawEveryThing(bf->Graphics, Eimg, Bimg);
		control->moveEveryThing(bf->Graphics, P->GetX(), P->GetY() );

		P->Mostrar(bf->Graphics, Pimg);



		bf->Render(g);

		if (control->Vidas() < 0) {
			this->timer1->Enabled = false;
			MessageBox::Show("PERDISTE");
			this->Close();
		}
		if (control->getPuntos() > 160) {
			this->timer1->Enabled = false;
			MessageBox::Show("GANASTE");
			this->Close();
		}
	}
	private: System::Void timer2_Tick(System::Object^ sender, System::EventArgs^ e) {
		bmpFondo = F2;
		this->timer2->Enabled = false;
	}
	private: System::Void timer3_Tick(System::Object^ sender, System::EventArgs^ e) {
		Enemy* b = new Enemy(rand()%1200, rand()%600);
		control->addEnemy(b);
		Enemy* a = new Enemy(rand() % 1200, rand() % 600);
		control->addEnemy(a);
	}
};
}
