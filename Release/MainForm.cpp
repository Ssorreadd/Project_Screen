#include "MainForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]

int main(cli::array<String^>^ args)
{
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();

	ScreenProject::MainForm mainForm;

	Application::Run(%mainForm);
}