#pragma once
#include "Renderer.h"

CRenderer gRenderer;

struct SProjector
{
	char* Name;
	ID3DXEffect* Fx;
};

const int MAX_PROJECTORS = 4;

SProjector gProjectors[MAX_PROJECTORS] = 
{
	{"null", NULL},
	{"mirror", NULL},
	{"cube", NULL},
	{"stereographic", NULL}
};

float gPhi = .0f;
float gPsi = .0f;
float gOldPhi = .0f;
float gOldPsi = .0f;
int gOldX = 0;
int gOldY = 0;

bool gDrag = false;

IDirect3DTexture9* gTex = NULL;

namespace FishEyeGPU
{

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;
	std::string CLIStringToStdString(System::String^ pString)
	{
		IntPtr pA = Marshal::StringToHGlobalAnsi(pString);
		std::string lR(static_cast<char *>(pA.ToPointer()));
		Marshal::FreeHGlobal(pA);
		return lR;
	}			


	/// <summary>
	/// Summary for frmMain
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class frmMain : public System::Windows::Forms::Form
	{
	public:
		frmMain(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~frmMain()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^  pnlRender;
	private: System::Windows::Forms::ComboBox^  cmbProjectors;
	private: System::Windows::Forms::Timer^  tmrRender;
	private: System::Windows::Forms::OpenFileDialog^  dlgOpen;
	private: System::Windows::Forms::Button^  btnOpen;
	private: System::ComponentModel::IContainer^  components;
	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->pnlRender = (gcnew System::Windows::Forms::Panel());
			this->cmbProjectors = (gcnew System::Windows::Forms::ComboBox());
			this->tmrRender = (gcnew System::Windows::Forms::Timer(this->components));
			this->dlgOpen = (gcnew System::Windows::Forms::OpenFileDialog());
			this->btnOpen = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// pnlRender
			// 
			this->pnlRender->Location = System::Drawing::Point(12, 12);
			this->pnlRender->Name = L"pnlRender";
			this->pnlRender->Size = System::Drawing::Size(512, 512);
			this->pnlRender->TabIndex = 0;
			this->pnlRender->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &frmMain::pnlRender_Paint);
			this->pnlRender->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &frmMain::pnlRender_MouseMove);
			this->pnlRender->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &frmMain::pnlRender_MouseDown);
			this->pnlRender->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &frmMain::pnlRender_MouseUp);
			// 
			// cmbProjectors
			// 
			this->cmbProjectors->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cmbProjectors->FormattingEnabled = true;
			this->cmbProjectors->Location = System::Drawing::Point(559, 12);
			this->cmbProjectors->Name = L"cmbProjectors";
			this->cmbProjectors->Size = System::Drawing::Size(121, 21);
			this->cmbProjectors->TabIndex = 1;
			this->cmbProjectors->SelectedIndexChanged += gcnew System::EventHandler(this, &frmMain::cmbProjectors_SelectedIndexChanged);
			// 
			// tmrRender
			// 
			this->tmrRender->Interval = 30;
			this->tmrRender->Tick += gcnew System::EventHandler(this, &frmMain::tmrRender_Tick);
			// 
			// dlgOpen
			// 
			this->dlgOpen->FileName = L"openFileDialog1";
			this->dlgOpen->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &frmMain::dlgOpen_FileOk);
			// 
			// btnOpen
			// 
			this->btnOpen->Location = System::Drawing::Point(559, 39);
			this->btnOpen->Name = L"btnOpen";
			this->btnOpen->Size = System::Drawing::Size(121, 23);
			this->btnOpen->TabIndex = 2;
			this->btnOpen->Text = L"Открыть...";
			this->btnOpen->UseVisualStyleBackColor = true;
			this->btnOpen->Click += gcnew System::EventHandler(this, &frmMain::btnOpen_Click);
			// 
			// frmMain
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(692, 560);
			this->Controls->Add(this->btnOpen);
			this->Controls->Add(this->cmbProjectors);
			this->Controls->Add(this->pnlRender);
			this->Name = L"frmMain";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"FishEye GPU Projector";
			this->Load += gcnew System::EventHandler(this, &frmMain::frmMain_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
		void Render()
		{
			int i = cmbProjectors->SelectedIndex;
			ID3DXEffect*& lFx = gProjectors[i].Fx;
			float reso[2] =
			{
				pnlRender->Width,
				pnlRender->Height
			};
			lFx->SetValue("reso", reso, D3DX_DEFAULT);
			lFx->SetFloat("gPhi", gPhi);
			lFx->SetFloat("gPsi", gPsi);
			lFx->SetTexture("TexDiffuse", gTex);
			gRenderer.Begin();
			lFx->Begin(NULL, 0);
			lFx->BeginPass(0);
			gRenderer.RenderFSQ();
			lFx->EndPass();
			lFx->End();
			gRenderer.End();
		}
	private:
		System::Void frmMain_Load(System::Object^  sender, System::EventArgs^  e)
		{
			gRenderer.Init((HWND)(pnlRender->Handle.ToPointer()));

			for (int i = 0; i < MAX_PROJECTORS; ++i)
			{
				cmbProjectors->Items->Add(gcnew System::String(gProjectors[i].Name));
				gRenderer.CreateEffectFromFile(std::string("data/") + gProjectors[i].Name + ".fx", gProjectors[i].Fx);
			}
			cmbProjectors->SelectedIndex = 0;
		}
	private:
		System::Void pnlRender_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e)
		{
			Render();
		}
	private: System::Void cmbProjectors_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
				 Render();
			 }
	private: System::Void pnlRender_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e){
				 gDrag = true;
				 gOldX = e->X;
				 gOldY = e->Y;
				 gOldPhi = gPhi;
				 gOldPsi = gPsi;
			 }
	private: System::Void pnlRender_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				 if (gDrag)
				 {
					 gPhi = gOldPhi + (gOldX - e->X) / 512.0f;
					 gPsi = gOldPsi + (gOldY - e->Y) / 512.0f;
					 Render();
				 }
			 }
	private: System::Void pnlRender_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				 gDrag = false;
			 }
	private: System::Void tmrRender_Tick(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void btnOpen_Click(System::Object^  sender, System::EventArgs^  e) {
				 dlgOpen->ShowDialog();

			 }
	private: System::Void dlgOpen_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
				 D3DXCreateTextureFromFileA(gRenderer.mDevice, CLIStringToStdString(dlgOpen->FileName).c_str(), &gTex);
				 Render();
			 }
	};
}

