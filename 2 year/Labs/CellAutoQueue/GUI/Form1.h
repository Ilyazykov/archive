#pragma once

#include "../dll/state.cpp"
#include "../dll/SetStates.cpp"
#include "../dll/CellAutomata.cpp"
#include "../dll/CellAuto2D.cpp"
#include "../dll/CellAuto1D.cpp"
#include "../dll/queue.cpp"

using namespace CellAuto;

CellAuto1D cellAuto;
myQueue *queue;

namespace GUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
		float lenght;
		float dept;
		int sizes;
		int height;
		int change;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown1;



			 Nbrhd nbrhd;
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			int x = pictureBox->Size.Width;
			int y =	pictureBox->Size.Height;
			lenght = (float)(y - 1) / sizes;
			dept = (float)(x - 1) / height;

			nbrhd = Nbrhd::NEUMANN;
			sizes = 5;
			height = 5;
			change = 0;
			queue = new myQueue(height, sizes);
			cellAuto.SetDim(sizes);
			cellAuto.SetNbrhd(nbrhd);
			//
			cellAuto.SetTestConf();
			queue->push(cellAuto);
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~Form1()
		{
			delete queue;
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
			this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->size = (gcnew System::Windows::Forms::NumericUpDown());
			this->groupBoxStart = (gcnew System::Windows::Forms::GroupBox());
			this->radioButtonUser = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonRand = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonTest = (gcnew System::Windows::Forms::RadioButton());
			this->pictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->groupBoxNeigh = (gcnew System::Windows::Forms::GroupBox());
			this->radioButtonMvon = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonMoore = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonNeu = (gcnew System::Windows::Forms::RadioButton());
			this->buttonNext = (gcnew System::Windows::Forms::Button());
			this->buttonSlide = (gcnew System::Windows::Forms::Button());
			this->buttonStop = (gcnew System::Windows::Forms::Button());
			this->timer = (gcnew System::Windows::Forms::Timer(this->components));
			this->groupBoxSize->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->size))->BeginInit();
			this->groupBoxStart->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox))->BeginInit();
			this->groupBoxNeigh->SuspendLayout();
			this->SuspendLayout();
			// 
			// groupBoxSize
			// 
			this->groupBoxSize->Controls->Add(this->numericUpDown1);
			this->groupBoxSize->Controls->Add(this->size);
			this->groupBoxSize->Location = System::Drawing::Point(448, 12);
			this->groupBoxSize->Name = L"groupBoxSize";
			this->groupBoxSize->Size = System::Drawing::Size(130, 85);
			this->groupBoxSize->TabIndex = 0;
			this->groupBoxSize->TabStop = false;
			this->groupBoxSize->Text = L"size";
			// 
			// numericUpDown1
			// 
			this->numericUpDown1->Location = System::Drawing::Point(7, 49);
			this->numericUpDown1->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {3, 0, 0, 0});
			this->numericUpDown1->Name = L"numericUpDown1";
			this->numericUpDown1->Size = System::Drawing::Size(117, 22);
			this->numericUpDown1->TabIndex = 1;
			this->numericUpDown1->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {5, 0, 0, 0});
			this->numericUpDown1->ValueChanged += gcnew System::EventHandler(this, &Form1::numericUpDown1_ValueChanged);
			// 
			// size
			// 
			this->size->Location = System::Drawing::Point(6, 21);
			this->size->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {3, 0, 0, 0});
			this->size->Name = L"size";
			this->size->Size = System::Drawing::Size(117, 22);
			this->size->TabIndex = 0;
			this->size->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {5, 0, 0, 0});
			this->size->ValueChanged += gcnew System::EventHandler(this, &Form1::sizeX_ValueChanged);
			// 
			// groupBoxStart
			// 
			this->groupBoxStart->Controls->Add(this->radioButtonUser);
			this->groupBoxStart->Controls->Add(this->radioButtonRand);
			this->groupBoxStart->Controls->Add(this->radioButtonTest);
			this->groupBoxStart->Location = System::Drawing::Point(448, 103);
			this->groupBoxStart->Name = L"groupBoxStart";
			this->groupBoxStart->Size = System::Drawing::Size(130, 109);
			this->groupBoxStart->TabIndex = 1;
			this->groupBoxStart->TabStop = false;
			this->groupBoxStart->Text = L"start conf";
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
			this->pictureBox->Size = System::Drawing::Size(410, 410);
			this->pictureBox->TabIndex = 2;
			this->pictureBox->TabStop = false;
			this->pictureBox->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::pictureBox_MouseDown);
			// 
			// groupBoxNeigh
			// 
			this->groupBoxNeigh->Controls->Add(this->radioButtonMvon);
			this->groupBoxNeigh->Controls->Add(this->radioButtonMoore);
			this->groupBoxNeigh->Controls->Add(this->radioButtonNeu);
			this->groupBoxNeigh->Location = System::Drawing::Point(448, 235);
			this->groupBoxNeigh->Name = L"groupBoxNeigh";
			this->groupBoxNeigh->Size = System::Drawing::Size(130, 112);
			this->groupBoxNeigh->TabIndex = 3;
			this->groupBoxNeigh->TabStop = false;
			this->groupBoxNeigh->Text = L"neighbourhood";
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
			this->buttonNext->Location = System::Drawing::Point(448, 353);
			this->buttonNext->Name = L"buttonNext";
			this->buttonNext->Size = System::Drawing::Size(130, 25);
			this->buttonNext->TabIndex = 4;
			this->buttonNext->Text = L"Next";
			this->buttonNext->UseVisualStyleBackColor = true;
			this->buttonNext->Click += gcnew System::EventHandler(this, &Form1::buttonNext_Click);
			// 
			// buttonSlide
			// 
			this->buttonSlide->Location = System::Drawing::Point(448, 384);
			this->buttonSlide->Name = L"buttonSlide";
			this->buttonSlide->Size = System::Drawing::Size(130, 25);
			this->buttonSlide->TabIndex = 5;
			this->buttonSlide->Text = L"Slide show";
			this->buttonSlide->UseVisualStyleBackColor = true;
			this->buttonSlide->Click += gcnew System::EventHandler(this, &Form1::buttonSlide_Click);
			// 
			// buttonStop
			// 
			this->buttonStop->Location = System::Drawing::Point(448, 415);
			this->buttonStop->Name = L"buttonStop";
			this->buttonStop->Size = System::Drawing::Size(130, 25);
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
			this->ClientSize = System::Drawing::Size(590, 452);
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
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown1))->EndInit();
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

			Pen ^bluePan = gcnew Pen(Color::Blue, 1);
			SolidBrush ^blackBrush = gcnew SolidBrush(Color::Black);
			SolidBrush ^whiteBrush = gcnew SolidBrush(Color::White);

			lenght = (float)(y - 1) / sizes;
			dept = (float)(x - 1) / height;

			for (int i = 0; i < height; i++)
			{
				for (int j = 0; j < sizes; j++)
				{
					if (queue->viewElem(i, j)) 
					{
						pictureBox->CreateGraphics()->FillRectangle(blackBrush, i * dept, j * lenght, dept, lenght);
					}
					else
					{
						pictureBox->CreateGraphics()->FillRectangle(whiteBrush, i * dept, j * lenght, dept, lenght);
					}
				}
				pictureBox->CreateGraphics()->DrawLine(bluePan, i * dept, 0.0f, i * dept, (float)y);
			}
			for (int i = 0; i < sizes; i++)
				pictureBox->CreateGraphics()->DrawLine(bluePan, 0.0f, i * lenght, (float)x, i * lenght);
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
				 queue->push(cellAuto);
				 Draw();
			 }
	private: System::Void timer_Tick(System::Object^  sender, System::EventArgs^  e) {
				 cellAuto.GetNextConf();
				 queue->push(cellAuto);
				 Draw();
			 }
	private: System::Void radioButtonTest_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
				 if (radioButtonTest->Checked) 
				 {
					cellAuto.SetTestConf();
					delete queue;
					queue = new myQueue(height, sizes);
					queue->push(cellAuto);
					Draw();
				 }
			 }
	private: System::Void radioButtonRand_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
				 if (radioButtonRand->Checked) 
				 {
					cellAuto.SetRndConf();
					delete queue;
					queue = new myQueue(height, sizes);
					queue->push(cellAuto);
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
				 if (int(e->X / dept) == queue->GetHi())
				 {
					 cellAuto.ChangeCell(e->Y / lenght);
					 queue->changeCell(e->Y / lenght);
					 Draw();
					 radioButtonUser->Checked = true;
				 }
			 }

	private: System::Void sizeX_ValueChanged(System::Object^  sender, System::EventArgs^  e) 
			 {
				sizes = Convert::ToInt32(size->Value);
				cellAuto.SetDim(sizes);
				delete queue;
				queue = new myQueue(height, sizes);
				queue->push(cellAuto);
				Draw();
			 }
	private: System::Void numericUpDown1_ValueChanged(System::Object^  sender, System::EventArgs^  e) 
			 {
				height = Convert::ToInt32(numericUpDown1->Value);
				delete queue;
				queue = new myQueue(height, sizes);
				queue->push(cellAuto);
				Draw();
			 }
	};
}

