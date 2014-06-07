#pragma once

#include "../dll/state.cpp"
#include "../dll/SetStates.cpp"
#include "../dll/CellAutomata.cpp"
#include "../dll/CellAuto2D.cpp"
#include "../dll/parserFunction.cpp"
#include "../dll/doubleStack.cpp"
#include "../dll/intStack.cpp"
 
using namespace nameParser;
using namespace CellAuto;

CellAuto2D cellAuto;

namespace GUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices; //for Marshal

	/// <summary>
	/// —водка дл€ Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
		float lenghtX;
		float lenghtY;
		int width;
		int height;

		int change;
	private: System::Windows::Forms::TextBox^  textBoxUser;
	private: System::Windows::Forms::RadioButton^  radioButtonNeighbourhoodUser;
	private: System::Windows::Forms::Label^  labelError;
	private: System::Windows::Forms::NumericUpDown^  sizeY;

			 Nbrhd nbrhd;
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			nbrhd = Nbrhd::NEUMANN;
			width = 5;
			height = 5;
			change = 0;
			cellAuto.SetDim(width, height);
			cellAuto.SetNbrhd(nbrhd);
			cellAuto.SetTestConf();
			//
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::GroupBox^  groupBoxSize;
	private: System::Windows::Forms::NumericUpDown^  size;
	protected: 

	protected: 




	private: System::Windows::Forms::GroupBox^  groupBoxStart;

	private: System::Windows::Forms::RadioButton^  radioButtonUser;

	private: System::Windows::Forms::RadioButton^  radioButtonRand;

	private: System::Windows::Forms::RadioButton^  radioButtonTest;
	private: System::Windows::Forms::PictureBox^  pictureBox;


	private: System::Windows::Forms::GroupBox^  groupBoxNeigh;

	private: System::Windows::Forms::RadioButton^  radioButtonMvon;

	private: System::Windows::Forms::RadioButton^  radioButtonMoore;

	private: System::Windows::Forms::RadioButton^  radioButtonNeu;
	private: System::Windows::Forms::Button^  buttonNext;
	private: System::Windows::Forms::Button^  buttonSlide;
	private: System::Windows::Forms::Button^  buttonStop;
	private: System::Windows::Forms::Timer^  timer;
	private: System::ComponentModel::IContainer^  components;





	private:
		/// <summary>
		/// “ребуетс€ переменна€ конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// ќб€зательный метод дл€ поддержки конструктора - не измен€йте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->groupBoxSize = (gcnew System::Windows::Forms::GroupBox());
			this->sizeY = (gcnew System::Windows::Forms::NumericUpDown());
			this->size = (gcnew System::Windows::Forms::NumericUpDown());
			this->groupBoxStart = (gcnew System::Windows::Forms::GroupBox());
			this->radioButtonUser = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonRand = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonTest = (gcnew System::Windows::Forms::RadioButton());
			this->pictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->groupBoxNeigh = (gcnew System::Windows::Forms::GroupBox());
			this->labelError = (gcnew System::Windows::Forms::Label());
			this->textBoxUser = (gcnew System::Windows::Forms::TextBox());
			this->radioButtonNeighbourhoodUser = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonMvon = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonMoore = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonNeu = (gcnew System::Windows::Forms::RadioButton());
			this->buttonNext = (gcnew System::Windows::Forms::Button());
			this->buttonSlide = (gcnew System::Windows::Forms::Button());
			this->buttonStop = (gcnew System::Windows::Forms::Button());
			this->timer = (gcnew System::Windows::Forms::Timer(this->components));
			this->groupBoxSize->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->sizeY))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->size))->BeginInit();
			this->groupBoxStart->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox))->BeginInit();
			this->groupBoxNeigh->SuspendLayout();
			this->SuspendLayout();
			// 
			// groupBoxSize
			// 
			this->groupBoxSize->Controls->Add(this->sizeY);
			this->groupBoxSize->Controls->Add(this->size);
			this->groupBoxSize->Location = System::Drawing::Point(517, 12);
			this->groupBoxSize->Name = L"groupBoxSize";
			this->groupBoxSize->Size = System::Drawing::Size(146, 83);
			this->groupBoxSize->TabIndex = 0;
			this->groupBoxSize->TabStop = false;
			this->groupBoxSize->Text = L"size";
			// 
			// sizeY
			// 
			this->sizeY->Location = System::Drawing::Point(6, 49);
			this->sizeY->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {3, 0, 0, 0});
			this->sizeY->Name = L"sizeY";
			this->sizeY->Size = System::Drawing::Size(134, 22);
			this->sizeY->TabIndex = 1;
			this->sizeY->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {5, 0, 0, 0});
			this->sizeY->ValueChanged += gcnew System::EventHandler(this, &Form1::sizeY_ValueChanged);
			// 
			// size
			// 
			this->size->Location = System::Drawing::Point(6, 21);
			this->size->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {3, 0, 0, 0});
			this->size->Name = L"size";
			this->size->Size = System::Drawing::Size(134, 22);
			this->size->TabIndex = 0;
			this->size->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {5, 0, 0, 0});
			this->size->ValueChanged += gcnew System::EventHandler(this, &Form1::sizeX_ValueChanged);
			// 
			// groupBoxStart
			// 
			this->groupBoxStart->Controls->Add(this->radioButtonUser);
			this->groupBoxStart->Controls->Add(this->radioButtonRand);
			this->groupBoxStart->Controls->Add(this->radioButtonTest);
			this->groupBoxStart->Location = System::Drawing::Point(517, 115);
			this->groupBoxStart->Name = L"groupBoxStart";
			this->groupBoxStart->Size = System::Drawing::Size(146, 109);
			this->groupBoxStart->TabIndex = 1;
			this->groupBoxStart->TabStop = false;
			this->groupBoxStart->Text = L"start conf";
			this->groupBoxStart->Enter += gcnew System::EventHandler(this, &Form1::groupBoxStart_Enter);
			// 
			// radioButtonUser
			// 
			this->radioButtonUser->AutoSize = true;
			this->radioButtonUser->Location = System::Drawing::Point(7, 78);
			this->radioButtonUser->Name = L"radioButtonUser";
			this->radioButtonUser->Size = System::Drawing::Size(57, 21);
			this->radioButtonUser->TabIndex = 2;
			this->radioButtonUser->Text = L"user";
			this->radioButtonUser->UseVisualStyleBackColor = true;
			this->radioButtonUser->CheckedChanged += gcnew System::EventHandler(this, &Form1::radioButtonUser_CheckedChanged);
			// 
			// radioButtonRand
			// 
			this->radioButtonRand->AutoSize = true;
			this->radioButtonRand->Location = System::Drawing::Point(7, 50);
			this->radioButtonRand->Name = L"radioButtonRand";
			this->radioButtonRand->Size = System::Drawing::Size(77, 21);
			this->radioButtonRand->TabIndex = 1;
			this->radioButtonRand->Text = L"random";
			this->radioButtonRand->UseVisualStyleBackColor = true;
			this->radioButtonRand->CheckedChanged += gcnew System::EventHandler(this, &Form1::radioButtonRand_CheckedChanged);
			// 
			// radioButtonTest
			// 
			this->radioButtonTest->AutoSize = true;
			this->radioButtonTest->Checked = true;
			this->radioButtonTest->Location = System::Drawing::Point(7, 22);
			this->radioButtonTest->Name = L"radioButtonTest";
			this->radioButtonTest->Size = System::Drawing::Size(52, 21);
			this->radioButtonTest->TabIndex = 0;
			this->radioButtonTest->TabStop = true;
			this->radioButtonTest->Text = L"test";
			this->radioButtonTest->UseVisualStyleBackColor = true;
			this->radioButtonTest->CheckedChanged += gcnew System::EventHandler(this, &Form1::radioButtonTest_CheckedChanged);
			// 
			// pictureBox
			// 
			this->pictureBox->Location = System::Drawing::Point(12, 12);
			this->pictureBox->Name = L"pictureBox";
			this->pictureBox->Size = System::Drawing::Size(461, 461);
			this->pictureBox->TabIndex = 2;
			this->pictureBox->TabStop = false;
			this->pictureBox->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::pictureBox_MouseDown);
			// 
			// groupBoxNeigh
			// 
			this->groupBoxNeigh->Controls->Add(this->labelError);
			this->groupBoxNeigh->Controls->Add(this->textBoxUser);
			this->groupBoxNeigh->Controls->Add(this->radioButtonNeighbourhoodUser);
			this->groupBoxNeigh->Controls->Add(this->radioButtonMvon);
			this->groupBoxNeigh->Controls->Add(this->radioButtonMoore);
			this->groupBoxNeigh->Controls->Add(this->radioButtonNeu);
			this->groupBoxNeigh->Location = System::Drawing::Point(510, 230);
			this->groupBoxNeigh->Name = L"groupBoxNeigh";
			this->groupBoxNeigh->Size = System::Drawing::Size(153, 164);
			this->groupBoxNeigh->TabIndex = 3;
			this->groupBoxNeigh->TabStop = false;
			this->groupBoxNeigh->Text = L"neighbourhood";
			// 
			// labelError
			// 
			this->labelError->AutoSize = true;
			this->labelError->ForeColor = System::Drawing::Color::Red;
			this->labelError->Location = System::Drawing::Point(105, 108);
			this->labelError->Name = L"labelError";
			this->labelError->Size = System::Drawing::Size(42, 17);
			this->labelError->TabIndex = 5;
			this->labelError->Text = L"error!";
			this->labelError->Visible = false;
			this->labelError->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::labelError_Paint);
			// 
			// textBoxUser
			// 
			this->textBoxUser->Location = System::Drawing::Point(7, 133);
			this->textBoxUser->Name = L"textBoxUser";
			this->textBoxUser->Size = System::Drawing::Size(140, 22);
			this->textBoxUser->TabIndex = 4;
			this->textBoxUser->Text = L"A+C+E+G";
			this->textBoxUser->TextChanged += gcnew System::EventHandler(this, &Form1::textBoxUser_TextChanged);
			// 
			// radioButtonNeighbourhoodUser
			// 
			this->radioButtonNeighbourhoodUser->AutoSize = true;
			this->radioButtonNeighbourhoodUser->Location = System::Drawing::Point(7, 106);
			this->radioButtonNeighbourhoodUser->Name = L"radioButtonNeighbourhoodUser";
			this->radioButtonNeighbourhoodUser->Size = System::Drawing::Size(59, 21);
			this->radioButtonNeighbourhoodUser->TabIndex = 3;
			this->radioButtonNeighbourhoodUser->TabStop = true;
			this->radioButtonNeighbourhoodUser->Text = L"User";
			this->radioButtonNeighbourhoodUser->UseVisualStyleBackColor = true;
			this->radioButtonNeighbourhoodUser->CheckedChanged += gcnew System::EventHandler(this, &Form1::radioButtonNeighbourhoodUser_CheckedChanged);
			// 
			// radioButtonMvon
			// 
			this->radioButtonMvon->AutoSize = true;
			this->radioButtonMvon->Location = System::Drawing::Point(7, 78);
			this->radioButtonMvon->Name = L"radioButtonMvon";
			this->radioButtonMvon->Size = System::Drawing::Size(63, 21);
			this->radioButtonMvon->TabIndex = 2;
			this->radioButtonMvon->Text = L"Mvon";
			this->radioButtonMvon->UseVisualStyleBackColor = true;
			this->radioButtonMvon->CheckedChanged += gcnew System::EventHandler(this, &Form1::radioButtonMvon_CheckedChanged);
			// 
			// radioButtonMoore
			// 
			this->radioButtonMoore->AutoSize = true;
			this->radioButtonMoore->Location = System::Drawing::Point(7, 50);
			this->radioButtonMoore->Name = L"radioButtonMoore";
			this->radioButtonMoore->Size = System::Drawing::Size(69, 21);
			this->radioButtonMoore->TabIndex = 1;
			this->radioButtonMoore->Text = L"Moore";
			this->radioButtonMoore->UseVisualStyleBackColor = true;
			this->radioButtonMoore->CheckedChanged += gcnew System::EventHandler(this, &Form1::radioButtonMoore_CheckedChanged);
			// 
			// radioButtonNeu
			// 
			this->radioButtonNeu->AutoSize = true;
			this->radioButtonNeu->Checked = true;
			this->radioButtonNeu->Location = System::Drawing::Point(7, 22);
			this->radioButtonNeu->Name = L"radioButtonNeu";
			this->radioButtonNeu->Size = System::Drawing::Size(90, 21);
			this->radioButtonNeu->TabIndex = 0;
			this->radioButtonNeu->TabStop = true;
			this->radioButtonNeu->Text = L"Neumann";
			this->radioButtonNeu->UseVisualStyleBackColor = true;
			this->radioButtonNeu->CheckedChanged += gcnew System::EventHandler(this, &Form1::radioButtonNeu_CheckedChanged);
			// 
			// buttonNext
			// 
			this->buttonNext->Location = System::Drawing::Point(510, 400);
			this->buttonNext->Name = L"buttonNext";
			this->buttonNext->Size = System::Drawing::Size(153, 25);
			this->buttonNext->TabIndex = 4;
			this->buttonNext->Text = L"Next";
			this->buttonNext->UseVisualStyleBackColor = true;
			this->buttonNext->Click += gcnew System::EventHandler(this, &Form1::buttonNext_Click);
			// 
			// buttonSlide
			// 
			this->buttonSlide->Location = System::Drawing::Point(510, 431);
			this->buttonSlide->Name = L"buttonSlide";
			this->buttonSlide->Size = System::Drawing::Size(153, 25);
			this->buttonSlide->TabIndex = 5;
			this->buttonSlide->Text = L"Slide show";
			this->buttonSlide->UseVisualStyleBackColor = true;
			this->buttonSlide->Click += gcnew System::EventHandler(this, &Form1::buttonSlide_Click);
			// 
			// buttonStop
			// 
			this->buttonStop->Location = System::Drawing::Point(510, 462);
			this->buttonStop->Name = L"buttonStop";
			this->buttonStop->Size = System::Drawing::Size(153, 25);
			this->buttonStop->TabIndex = 6;
			this->buttonStop->Text = L"Stop";
			this->buttonStop->UseVisualStyleBackColor = true;
			this->buttonStop->Click += gcnew System::EventHandler(this, &Form1::buttonStop_Click);
			// 
			// timer
			// 
			this->timer->Tick += gcnew System::EventHandler(this, &Form1::timer_Tick);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(675, 499);
			this->Controls->Add(this->buttonStop);
			this->Controls->Add(this->buttonSlide);
			this->Controls->Add(this->buttonNext);
			this->Controls->Add(this->groupBoxNeigh);
			this->Controls->Add(this->pictureBox);
			this->Controls->Add(this->groupBoxStart);
			this->Controls->Add(this->groupBoxSize);
			this->Name = L"Form1";
			this->Text = L"CellAuto";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::Form1_Paint);
			this->groupBoxSize->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->sizeY))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->size))->EndInit();
			this->groupBoxStart->ResumeLayout(false);
			this->groupBoxStart->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox))->EndInit();
			this->groupBoxNeigh->ResumeLayout(false);
			this->groupBoxNeigh->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: 
		void Draw()
		{
			SolidBrush ^grayBrush = gcnew SolidBrush(Color::Gray);
			int x = pictureBox->Size.Width;
			int y =	pictureBox->Size.Height;

			lenghtX = (float)(x - 1) / width;
			lenghtY = (float)(y - 1) / height;
			Pen ^bluePan = gcnew Pen(Color::Blue, 1);

			SolidBrush ^blackBrush = gcnew SolidBrush(Color::Black);
			SolidBrush ^whiteBrush = gcnew SolidBrush(Color::White);
			SolidBrush ^greenBrush = gcnew SolidBrush(Color::Green);

			for (int i = 0; i < width; i++)
			{
				for (int j = 0; j < height; j++)
				{
					if (cellAuto.GetCell(i, j) == 1) 
					{
						pictureBox->CreateGraphics()->FillRectangle(blackBrush, i * lenghtX, j * lenghtY, lenghtX, lenghtY);
					}
					else if (cellAuto.GetCell(i, j) == 2)
					{
						pictureBox->CreateGraphics()->FillRectangle(greenBrush, i * lenghtX, j * lenghtY, lenghtX, lenghtY);
					}
					else
					{
						pictureBox->CreateGraphics()->FillRectangle(whiteBrush, i * lenghtX, j * lenghtY, lenghtX, lenghtY);
					}
				}
				pictureBox->CreateGraphics()->DrawLine(bluePan, i * lenghtX, 0.0f, i * lenghtX, (float)y);
			}

			pictureBox->CreateGraphics()->DrawLine(bluePan, width * lenghtX, 0.0f, width * lenghtX, (float)y);

			for (int j = 0; j <= height; j++)
				pictureBox->CreateGraphics()->DrawLine(bluePan, 0.0f, j * lenghtY, (float)x, j * lenghtY);
		}

	private: System::Void Form1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) 
			 {
			 }

	private: System::Void buttonSlide_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				 timer->Enabled = true;
			 }

	private: System::Void buttonStop_Click(System::Object^  sender, System::EventArgs^  e) {
				 timer->Enabled = false;
			 }
	private: System::Void buttonNext_Click(System::Object^  sender, System::EventArgs^  e) {
				 cellAuto.GetNextConf();
				 Draw();

				 if (cellAuto.getError()) labelError->Visible = true;
				 else labelError->Visible = false;
			 }
	private: System::Void timer_Tick(System::Object^  sender, System::EventArgs^  e) {
				 cellAuto.GetNextConf();
				 Draw();
			 }
	private: System::Void sizeX_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
				 width = Convert::ToInt32(size->Value);
				 cellAuto.SetDim(width, height);
				 Draw();
			 }
	private: System::Void radioButtonTest_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
				 if (radioButtonTest->Checked) 
				 {
					 cellAuto.SetTestConf();
					 Draw();
				 }
			 }
	private: System::Void radioButtonRand_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
				 if (radioButtonRand->Checked) 
				 {
					 cellAuto.SetRndConf();
					 Draw();
				 }
			 }
	private: System::Void radioButtonUser_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void radioButtonNeu_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
				 nbrhd = Nbrhd::NEUMANN;
				 cellAuto.SetNbrhd(nbrhd);
			 }
	private: System::Void radioButtonMoore_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
				 nbrhd = Nbrhd::MOORE;
				 cellAuto.SetNbrhd(nbrhd);
			 }
	private: System::Void radioButtonMvon_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
				 nbrhd = Nbrhd::MVON;
				 cellAuto.SetNbrhd(nbrhd);
			 }
	private: System::Void pictureBox_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void pictureBox_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				 cellAuto.ChangeCell(e->X / lenghtX, e->Y / lenghtY);
				 Draw();
				 radioButtonUser->Checked = true;
			 }
	private: System::Void groupBoxStart_Enter(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void radioButtonNeighbourhoodUser_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
				 nbrhd = Nbrhd::USER;
				 cellAuto.SetNbrhd(nbrhd);
			 }
	private: System::Void textBoxUser_TextChanged(System::Object^  sender, System::EventArgs^  e) {
				 char *str = (char*)(void*)Marshal::StringToHGlobalAnsi(textBoxUser->Text);
				 cellAuto.ChangeFormula(str);
			 }
	private: System::Void labelError_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
			 }
	private: System::Void sizeY_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
				 height = Convert::ToInt32(sizeY->Value);
				 cellAuto.SetDim(width, height);
				 Draw();
			 }
};
}

