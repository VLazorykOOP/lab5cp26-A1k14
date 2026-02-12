#pragma once
#include <cmath> 

namespace OP26Lab5Graphics {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class GForm : public System::Windows::Forms::Form
	{
	public:
		GForm(void)
		{
			InitializeComponent();
		}

	protected:
		~GForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::Button^ button1;
	private: System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		   void InitializeComponent(void)
		   {
			   this->label1 = (gcnew System::Windows::Forms::Label());
			   this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			   this->button1 = (gcnew System::Windows::Forms::Button());
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			   this->SuspendLayout();
			   this->label1->AutoSize = true;
			   this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->label1->ForeColor = System::Drawing::SystemColors::HotTrack;
			   this->label1->Location = System::Drawing::Point(185, 9);
			   this->label1->Name = L"label1";
			   this->label1->Size = System::Drawing::Size(175, 29);
			   this->label1->TabIndex = 0;
			   this->label1->Text = L"Lab5_Graphics";
			   this->pictureBox1->BackColor = System::Drawing::Color::White;
			   this->pictureBox1->Location = System::Drawing::Point(69, 80);
			   this->pictureBox1->Name = L"pictureBox1";
			   this->pictureBox1->Size = System::Drawing::Size(1377, 500);
			   this->pictureBox1->TabIndex = 1;
			   this->pictureBox1->TabStop = false;
			   this->button1->Location = System::Drawing::Point(435, 25);
			   this->button1->Name = L"button1";
			   this->button1->Size = System::Drawing::Size(117, 49);
			   this->button1->TabIndex = 2;
			   this->button1->Text = L"Draw Tasks";
			   this->button1->UseVisualStyleBackColor = true;
			   this->button1->Click += gcnew System::EventHandler(this, &GForm::button1_Click);
			   this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(1485, 602);
			   this->Controls->Add(this->button1);
			   this->Controls->Add(this->pictureBox1);
			   this->Controls->Add(this->label1);
			   this->Name = L"GForm";
			   this->Text = L"Lab 5";
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }
#pragma endregion

	private: void DrawKochSegment(Graphics^ g, Pen^ pen, PointF p1, PointF p2, int depth) {
		if (depth == 0) {
			g->DrawLine(pen, p1, p2);
		}
		else {
			// Розрахунок координат точок ділення відрізка
			float dx = p2.X - p1.X;
			float dy = p2.Y - p1.Y;

			// Точки, що ділять відрізок на 3 частини
			PointF pA = PointF(p1.X + dx / 3.0f, p1.Y + dy / 3.0f);
			PointF pB = PointF(p1.X + 2 * dx / 3.0f, p1.Y + 2 * dy / 3.0f);

			// Вершина рівностороннього трикутника (поворот на -60 градусів)
			// Формула повороту вектора (pB-pA)
			float angle = -60.0f * (3.14159f / 180.0f); 
			float vx = pB.X - pA.X;
			float vy = pB.Y - pA.Y;

			PointF pPeak = PointF(
				pA.X + vx * cos(angle) - vy * sin(angle),
				pA.Y + vx * sin(angle) + vy * cos(angle)
			);

			// Рекурсивні виклики для 4 нових відрізків
			DrawKochSegment(g, pen, p1, pA, depth - 1);
			DrawKochSegment(g, pen, pA, pPeak, depth - 1);
			DrawKochSegment(g, pen, pPeak, pB, depth - 1);
			DrawKochSegment(g, pen, pB, p2, depth - 1);
		}
	}

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		Graphics^ g = pictureBox1->CreateGraphics();
		g->Clear(Color::White);
		g->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;


		Pen^ penBezier = gcnew Pen(Color::Red, 2);
		Pen^ penFrame = gcnew Pen(Color::LightGray, 1);

		// 4 опорні точки (P1, P2, P3, P4) зліва на екрані
		PointF P0(20, 250);   
		PointF P1(50, 50);    
		PointF P2(200, 50);   
		PointF P3(230, 250);  

		g->DrawLine(penFrame, P0, P1);
		g->DrawLine(penFrame, P1, P2);
		g->DrawLine(penFrame, P2, P3);
		g->DrawLine(penFrame, P3, P0); 
		g->DrawString("Bezier", gcnew System::Drawing::Font("Arial", 10), Brushes::Red, 20, 260);

		// Малюємо саму криву Безьє за формулою 
		// B(t) = (1-t)^3*P0 + 3t(1-t)^2*P1 + 3t^2(1-t)*P2 + t^3*P3
		PointF prev = P0;
		for (float t = 0; t <= 1.0; t += 0.01f) {
			float u = 1 - t;
			float tt = t * t;
			float uu = u * u;
			float uuu = uu * u;
			float ttt = tt * t;

			float x = uuu * P0.X + 3 * uu * t * P1.X + 3 * u * tt * P2.X + ttt * P3.X;
			float y = uuu * P0.Y + 3 * uu * t * P1.Y + 3 * u * tt * P2.Y + ttt * P3.Y;

			PointF current = PointF(x, y);
			g->DrawLine(penBezier, prev, current);
			prev = current;
		}

		Pen^ penKoch = gcnew Pen(Color::Blue, 1);
		int K = 3; // Порядок фракталу (глибина рекурсії)

		// Координати трикутника (справа на екрані)
		PointF T1(300, 200);
		PointF T2(450, 50);
		PointF T3(600, 200); // Вершини

		// фрактал на кожній з 3-х сторін
		DrawKochSegment(g, penKoch, T1, T2, K);
		DrawKochSegment(g, penKoch, T2, T3, K);
		DrawKochSegment(g, penKoch, T3, T1, K);

		g->DrawString("Koch Fractal", gcnew System::Drawing::Font("Arial", 10), Brushes::Blue, 350, 260);
	}
	};
}