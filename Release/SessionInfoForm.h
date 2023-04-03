#pragma once

#include "ScreenShotManager.h"
#include "ProcessManager.h"
#include "ThreadManager.h"
#include <string>
#include <list>
#include <msclr\marshal_cppstd.h>
#include "ShellAPI.h"
#include "FolderManager.h"

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
	/// Сводка для SessionInfoForm
	/// </summary>
	public ref class SessionInfoForm : public System::Windows::Forms::Form
	{
	public:
		SessionInfoForm(list<string> nameOfProcesses)
		{
			InitializeComponent();
			
			SetListBoxInfo(nameOfProcesses);
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~SessionInfoForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ListView^ InfoListView;
	protected:
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::ColumnHeader^ columnHeader1;
	private: System::Windows::Forms::ColumnHeader^ columnHeader2;
	private: System::Windows::Forms::ColumnHeader^ columnHeader3;
	private: System::Windows::Forms::ColumnHeader^ columnHeader4;

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
			this->InfoListView = (gcnew System::Windows::Forms::ListView());
			this->columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader2 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader3 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader4 = (gcnew System::Windows::Forms::ColumnHeader());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// InfoListView
			// 
			this->InfoListView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(4) {
				this->columnHeader1,
					this->columnHeader2, this->columnHeader3, this->columnHeader4
			});
			this->InfoListView->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->InfoListView->FullRowSelect = true;
			this->InfoListView->GridLines = true;
			this->InfoListView->HideSelection = false;
			this->InfoListView->Location = System::Drawing::Point(12, 68);
			this->InfoListView->Name = L"InfoListView";
			this->InfoListView->Size = System::Drawing::Size(778, 406);
			this->InfoListView->TabIndex = 0;
			this->InfoListView->UseCompatibleStateImageBehavior = false;
			this->InfoListView->View = System::Windows::Forms::View::Details;
			this->InfoListView->SelectedIndexChanged += gcnew System::EventHandler(this, &SessionInfoForm::InfoListView_SelectedIndexChanged);
			// 
			// columnHeader1
			// 
			this->columnHeader1->Text = L"";
			this->columnHeader1->Width = 1;
			// 
			// columnHeader2
			// 
			this->columnHeader2->Text = L"Имя процесса";
			this->columnHeader2->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->columnHeader2->Width = 311;
			// 
			// columnHeader3
			// 
			this->columnHeader3->Text = L"Время использования";
			this->columnHeader3->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->columnHeader3->Width = 223;
			// 
			// columnHeader4
			// 
			this->columnHeader4->Text = L"Подробнее";
			this->columnHeader4->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->columnHeader4->Width = 230;
			// 
			// label1
			// 
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(778, 56);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Сводка за день";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// SessionInfoForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::AliceBlue;
			this->ClientSize = System::Drawing::Size(802, 486);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->InfoListView);
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"SessionInfoForm";
			this->ShowIcon = false;
			this->ResumeLayout(false);

		}
#pragma endregion

		void SetListBoxInfo(list<string> nameOfProcesses)
		{
			for (string process : nameOfProcesses)
			{				

				ListViewItem^ item = gcnew ListViewItem("");
				item->SubItems->Add(gcnew System::String(process.c_str()));
				item->SubItems->Add(gcnew System::String(ProcessManager::GetUsedProcessTime(process).c_str()));
				item->SubItems->Add("перейти к каталогу->");

				InfoListView->Items->Add(item);
			}
		}
		System::Void InfoListView_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) 
		{
			if (InfoListView->SelectedIndices->Count == 0)
			{
				return;
			}

			string processName = marshal_as<std::string>(InfoListView->SelectedItems[0]->SubItems[1]->Text->ToString());

			time_t timeNow = time(0);

			tm* currentTime = localtime(&timeNow);

			const time_t tmDate = time(nullptr);

			char bufDate[64];
			strftime(bufDate, std::size(bufDate), "%d.%m.%Y", localtime(&tmDate));

			string path = FolderManager::GetMainFolderPath() + processName + "\\" + bufDate;

			LPCSTR folderPath = path.c_str();

			ShellExecuteA(GetForegroundWindow(), "open", folderPath, NULL, NULL, SW_RESTORE); //Открывает локальный диск C

			InfoListView->SelectedIndices->Clear();
		}
	};
}
