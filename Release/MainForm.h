#pragma once

#include "SessionInfoForm.h"
#include "ScreenShotManager.h"
#include "ProcessManager.h"
#include "ThreadManager.h"
#include <string>
#include <list>
#include <msclr\marshal_cppstd.h>

namespace ScreenProject 
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	using namespace msclr::interop;
	using namespace std;

	/// <summary>
	/// Сводка для MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();

			SetDefault();
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ListBox^ TrackedProcessListBox;
	protected:

	protected:
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::ComboBox^ AllProcessesCB;

	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Button^ AddProcessToTrackB;
	private: System::Windows::Forms::Button^ DeleteProcessFromTrack;
	private: System::Windows::Forms::Button^ StartTrackingB;
	private: System::Windows::Forms::Button^ CancelTrackingB;
	private: System::Windows::Forms::Label^ TrackingStatusLabel;
	private: System::Windows::Forms::ComboBox^ ScreenShotIntervalCB;

	private: System::Windows::Forms::Label^ label3;

	protected:

	protected:


	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->TrackedProcessListBox = (gcnew System::Windows::Forms::ListBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->AllProcessesCB = (gcnew System::Windows::Forms::ComboBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->AddProcessToTrackB = (gcnew System::Windows::Forms::Button());
			this->DeleteProcessFromTrack = (gcnew System::Windows::Forms::Button());
			this->StartTrackingB = (gcnew System::Windows::Forms::Button());
			this->CancelTrackingB = (gcnew System::Windows::Forms::Button());
			this->TrackingStatusLabel = (gcnew System::Windows::Forms::Label());
			this->ScreenShotIntervalCB = (gcnew System::Windows::Forms::ComboBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// TrackedProcessListBox
			// 
			this->TrackedProcessListBox->FormattingEnabled = true;
			this->TrackedProcessListBox->ItemHeight = 20;
			this->TrackedProcessListBox->Location = System::Drawing::Point(12, 37);
			this->TrackedProcessListBox->Name = L"TrackedProcessListBox";
			this->TrackedProcessListBox->Size = System::Drawing::Size(367, 364);
			this->TrackedProcessListBox->TabIndex = 0;
			this->TrackedProcessListBox->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::TrackedProcessListBox_SelectedIndexChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(8, 14);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(184, 17);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Отслеживаемые процессы";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// AllProcessesCB
			// 
			this->AllProcessesCB->FormattingEnabled = true;
			this->AllProcessesCB->Location = System::Drawing::Point(401, 37);
			this->AllProcessesCB->Name = L"AllProcessesCB";
			this->AllProcessesCB->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->AllProcessesCB->Size = System::Drawing::Size(367, 28);
			this->AllProcessesCB->TabIndex = 2;
			this->AllProcessesCB->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::AllProcessesCB_SelectedIndexChanged);
			// 
			// label2
			// 
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(434, 14);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(334, 20);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Доступные процессы";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// AddProcessToTrackB
			// 
			this->AddProcessToTrackB->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->AddProcessToTrackB->Enabled = false;
			this->AddProcessToTrackB->ForeColor = System::Drawing::SystemColors::ButtonFace;
			this->AddProcessToTrackB->Location = System::Drawing::Point(401, 76);
			this->AddProcessToTrackB->Name = L"AddProcessToTrackB";
			this->AddProcessToTrackB->Size = System::Drawing::Size(179, 42);
			this->AddProcessToTrackB->TabIndex = 4;
			this->AddProcessToTrackB->Text = L"Добавить";
			this->AddProcessToTrackB->UseVisualStyleBackColor = false;
			this->AddProcessToTrackB->Click += gcnew System::EventHandler(this, &MainForm::AddProcessToTrackB_Click);
			// 
			// DeleteProcessFromTrack
			// 
			this->DeleteProcessFromTrack->BackColor = System::Drawing::Color::Crimson;
			this->DeleteProcessFromTrack->Enabled = false;
			this->DeleteProcessFromTrack->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->DeleteProcessFromTrack->ForeColor = System::Drawing::SystemColors::ButtonFace;
			this->DeleteProcessFromTrack->Location = System::Drawing::Point(589, 76);
			this->DeleteProcessFromTrack->Name = L"DeleteProcessFromTrack";
			this->DeleteProcessFromTrack->Size = System::Drawing::Size(179, 42);
			this->DeleteProcessFromTrack->TabIndex = 5;
			this->DeleteProcessFromTrack->Text = L"Удалить";
			this->DeleteProcessFromTrack->UseVisualStyleBackColor = false;
			this->DeleteProcessFromTrack->Click += gcnew System::EventHandler(this, &MainForm::DeleteProcessFromTrack_Click);
			// 
			// StartTrackingB
			// 
			this->StartTrackingB->BackColor = System::Drawing::Color::DarkTurquoise;
			this->StartTrackingB->Enabled = false;
			this->StartTrackingB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->StartTrackingB->ForeColor = System::Drawing::SystemColors::HighlightText;
			this->StartTrackingB->Location = System::Drawing::Point(401, 295);
			this->StartTrackingB->Name = L"StartTrackingB";
			this->StartTrackingB->Size = System::Drawing::Size(367, 50);
			this->StartTrackingB->TabIndex = 6;
			this->StartTrackingB->Text = L"Начать отслеживание";
			this->StartTrackingB->UseVisualStyleBackColor = false;
			this->StartTrackingB->Click += gcnew System::EventHandler(this, &MainForm::StartTrackingB_Click);
			// 
			// CancelTrackingB
			// 
			this->CancelTrackingB->BackColor = System::Drawing::Color::Crimson;
			this->CancelTrackingB->Enabled = false;
			this->CancelTrackingB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->CancelTrackingB->ForeColor = System::Drawing::SystemColors::ButtonFace;
			this->CancelTrackingB->Location = System::Drawing::Point(401, 351);
			this->CancelTrackingB->Name = L"CancelTrackingB";
			this->CancelTrackingB->Size = System::Drawing::Size(367, 50);
			this->CancelTrackingB->TabIndex = 7;
			this->CancelTrackingB->Text = L"Прекратить отслеживание";
			this->CancelTrackingB->UseVisualStyleBackColor = false;
			this->CancelTrackingB->Click += gcnew System::EventHandler(this, &MainForm::CancelTrackingB_Click);
			// 
			// TrackingStatusLabel
			// 
			this->TrackingStatusLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->TrackingStatusLabel->ForeColor = System::Drawing::SystemColors::AppWorkspace;
			this->TrackingStatusLabel->Location = System::Drawing::Point(401, 269);
			this->TrackingStatusLabel->Name = L"TrackingStatusLabel";
			this->TrackingStatusLabel->Size = System::Drawing::Size(367, 23);
			this->TrackingStatusLabel->TabIndex = 8;
			this->TrackingStatusLabel->Text = L"Отслеживание начато...";
			this->TrackingStatusLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->TrackingStatusLabel->Visible = false;
			// 
			// ScreenShotIntervalCB
			// 
			this->ScreenShotIntervalCB->FormattingEnabled = true;
			this->ScreenShotIntervalCB->Items->AddRange(gcnew cli::array< System::Object^  >(7) {
				L"5 сек.", L"30 сек.", L"1 мин.", L"5 мин.",
					L"10 мин.", L"30 мин.", L"1 час."
			});
			this->ScreenShotIntervalCB->Location = System::Drawing::Point(589, 191);
			this->ScreenShotIntervalCB->Name = L"ScreenShotIntervalCB";
			this->ScreenShotIntervalCB->Size = System::Drawing::Size(143, 28);
			this->ScreenShotIntervalCB->TabIndex = 9;
			this->ScreenShotIntervalCB->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::ScreenShotIntervalCB_SelectedIndexChanged);
			// 
			// label3
			// 
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(437, 184);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(146, 40);
			this->label3->TabIndex = 10;
			this->label3->Text = L"Интервал создания скриншотов:";
			this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// MainForm
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->BackColor = System::Drawing::Color::AliceBlue;
			this->ClientSize = System::Drawing::Size(780, 421);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->ScreenShotIntervalCB);
			this->Controls->Add(this->TrackingStatusLabel);
			this->Controls->Add(this->CancelTrackingB);
			this->Controls->Add(this->StartTrackingB);
			this->Controls->Add(this->DeleteProcessFromTrack);
			this->Controls->Add(this->AddProcessToTrackB);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->AllProcessesCB);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->TrackedProcessListBox);
			this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"MainForm";
			this->ShowIcon = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"ScreenProject";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: 

		void SetDefault()
		{
			TrackedProcessListBox->Items->Clear();
			TrackedProcessListBox->SelectedIndex = -1;
			AllProcessesCB->Items->Clear();

			auto lis = ProcessManager::GetAllProcesses();

			for (string process : lis)
			{
				AllProcessesCB->Items->Add(gcnew System::String(process.c_str()));

			}
		}
		void Check()
		{
			if (TrackedProcessListBox->Items->Count > 0 && ScreenShotIntervalCB->SelectedIndex != -1)
			{
				StartTrackingB->Enabled = true;
			}
			else
			{
				StartTrackingB->Enabled = false;
			}
		}

		System::Void AllProcessesCB_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) 
		{
			if (AllProcessesCB->SelectedIndex != -1)
			{
				AddProcessToTrackB->Enabled = true;
			}
			else
			{
				AddProcessToTrackB->Enabled = false;
			}
		}

		System::Void AddProcessToTrackB_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			TrackedProcessListBox->Items->Add(AllProcessesCB->SelectedItem);

			AllProcessesCB->Items->RemoveAt(AllProcessesCB->SelectedIndex);
			//AllProcessesCB->SelectedIndex = -1;
			AddProcessToTrackB->Enabled = false;

			Check();
		}

		System::Void TrackedProcessListBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) 
		{
			if (TrackedProcessListBox->SelectedIndex != -1)
			{
				DeleteProcessFromTrack->Enabled = true;
			}
			else
			{
				DeleteProcessFromTrack->Enabled = false;
			}
		}

		System::Void DeleteProcessFromTrack_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			AllProcessesCB->Items->Add(TrackedProcessListBox->SelectedItem);
			
			TrackedProcessListBox->Items->RemoveAt(TrackedProcessListBox->SelectedIndex);

			DeleteProcessFromTrack->Enabled = false;

			Check();
		}

		void SwitchControlsEnable()
		{
			AllProcessesCB->Enabled = !AllProcessesCB->Enabled;
			TrackedProcessListBox->Enabled = !TrackedProcessListBox->Enabled;

			CancelTrackingB->Enabled = !CancelTrackingB->Enabled;
			StartTrackingB->Enabled = !StartTrackingB->Enabled;

			TrackingStatusLabel->Visible = !TrackingStatusLabel->Visible;

			ScreenShotIntervalCB->Enabled = !ScreenShotIntervalCB->Enabled;
		}

		System::Void StartTrackingB_Click(System::Object^ sender, System::EventArgs^ e)
		{
			SwitchControlsEnable();

			int interval = 0;

			if (ScreenShotIntervalCB->Text == "5 сек.")
			{
				interval = 5000;
			} 
			else if (ScreenShotIntervalCB->Text == "30 сек.")
			{
				interval = 30000;
			}
			else if (ScreenShotIntervalCB->Text == "1 мин.")
			{
				interval = 60000;
			}
			else if (ScreenShotIntervalCB->Text == "5 мин.")
			{
				interval = 300000;
			}
			else if (ScreenShotIntervalCB->Text == "10 мин.")
			{
				interval = 600000;
			}
			else if (ScreenShotIntervalCB->Text == "30 мин.")
			{
				interval = 1800000;
			}
			else if (ScreenShotIntervalCB->Text == "1 час.")
			{
				interval = 3600000;
			}

			list<string> trackingProcesses = TrackedProcesesToList();

			ThreadManager::ScreenShotThreadStart(trackingProcesses, interval);
		}

		System::Void ScreenShotIntervalCB_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) 
		{
			Check();
		}

		list<string> TrackedProcesesToList()
		{
			list<string> trackingProcesses;

			for (int i = 0; i < TrackedProcessListBox->Items->Count; i++)
			{
				string item = marshal_as<std::string>(TrackedProcessListBox->Items[i]->ToString());

				trackingProcesses.emplace_back(item);
			}

			return trackingProcesses;
		}

		System::Void CancelTrackingB_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			ThreadManager::ScreenShotThreadClose();

			list<string> nameOfProceses;

			for (string process : TrackedProcesesToList())
			{
				string processName = "";

				for (int i = 0; i < process.size() - 4; i++)
				{
					processName += process[i];
				}

				nameOfProceses.emplace_back(processName);
			}

			SessionInfoForm^ sessionInfoForm = gcnew SessionInfoForm(nameOfProceses);
			sessionInfoForm->ShowDialog();


			SetDefault();

			SwitchControlsEnable();

			Check();
		}
	};
}
