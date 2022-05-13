#include "MyForm.h"

#include <Windows.h>

#include "HashTable.h"
#include "DoublyLinkedList.h"
#include "HashFunc.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Runtime::InteropServices;

[STAThreadAttribute]
void main(cli::array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Archive1::MyForm form;
	Application::Run(% form);

	
}

System::Void Archive1::MyForm::MyForm_Load(System::Object^ sender, System::EventArgs^ e)
{
	table = new hash_table(hfunc);
	return System::Void();
}

System::Void Archive1::MyForm::çàãðóçèòüÁÄToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	table->LoadFromFile();
	return System::Void();
}

System::Void Archive1::MyForm::ñîõðàíèòüÁÄToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	table->SaveToFile();
	return System::Void();
}

System::Void Archive1::MyForm::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
	System::String^ str = System::Convert::ToString(maskedTextBox1->Text);
	str += System::Convert::ToString(maskedTextBox2->Text);
	char* str2 = (char*)(void*)Marshal::StringToHGlobalAnsi(str);
	richTextBox2->Text = gcnew System::String(table->FindInfo(str2));
	return System::Void();
}

System::Void Archive1::MyForm::button2_Click(System::Object^ sender, System::EventArgs^ e)
{
	System::String^ str = System::Convert::ToString(maskedTextBox4->Text);
	str += System::Convert::ToString(maskedTextBox3->Text);
	str += System::Convert::ToString(maskedTextBox5->Text);
	str += System::Convert::ToString(textBox1->Text);
	str += System::Convert::ToString(textBox2->Text);
	str += System::Convert::ToString(textBox3->Text);
	str += System::Convert::ToString(richTextBox1->Text);
	char* str2 = (char*)(void*)Marshal::StringToHGlobalAnsi(str);
	table->Register(str2);
	MessageBox::Show("Äàííûå áûëè óñïåøíî äîáàâëåíû", "Äîáàâëåíî");
	return System::Void();
}

System::Void Archive1::MyForm::button3_Click(System::Object^ sender, System::EventArgs^ e)
{
	System::String^ str = System::Convert::ToString(maskedTextBox4->Text);
	str += System::Convert::ToString(maskedTextBox3->Text);
	str += System::Convert::ToString(maskedTextBox5->Text);
	str += System::Convert::ToString(textBox1->Text);
	str += System::Convert::ToString(textBox2->Text);
	str += System::Convert::ToString(textBox3->Text);
	str += System::Convert::ToString(richTextBox1->Text);
	char* str2 = (char*)(void*)Marshal::StringToHGlobalAnsi(str);
	table->Remove(str2);
	return System::Void();
}

