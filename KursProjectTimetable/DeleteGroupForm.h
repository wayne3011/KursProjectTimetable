#pragma once

namespace KursProjectTimetable {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for DeleteGroupForm
	/// </summary>
	public ref class DeleteGroupForm : public System::Windows::Forms::Form
	{
	public:
		DeleteGroupForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
		int facultyNumber = -1;
		int courseNumber = -1;
		int groupNumber = -1;


	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~DeleteGroupForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::PictureBox^ addButton;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(DeleteGroupForm::typeid));
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->addButton = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->addButton))->BeginInit();
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(168, 10);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(31, 20);
			this->textBox1->TabIndex = 0;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &DeleteGroupForm::textBox1_TextChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(13, 13);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(149, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"������� ����� ����������:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(36, 66);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(126, 13);
			this->label2->TabIndex = 2;
			this->label2->Text = L"������� ����� ������:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(43, 39);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(119, 13);
			this->label3->TabIndex = 3;
			this->label3->Text = L"������� ����� �����:";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(169, 36);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(30, 20);
			this->textBox2->TabIndex = 4;
			this->textBox2->TextChanged += gcnew System::EventHandler(this, &DeleteGroupForm::textBox2_TextChanged);
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(169, 63);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(30, 20);
			this->textBox3->TabIndex = 5;
			this->textBox3->TextChanged += gcnew System::EventHandler(this, &DeleteGroupForm::textBox3_TextChanged);
			// 
			// addButton
			// 
			this->addButton->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"addButton.BackgroundImage")));
			this->addButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->addButton->Location = System::Drawing::Point(205, 66);
			this->addButton->Name = L"addButton";
			this->addButton->Size = System::Drawing::Size(19, 17);
			this->addButton->TabIndex = 8;
			this->addButton->TabStop = false;
			this->addButton->Click += gcnew System::EventHandler(this, &DeleteGroupForm::addButton_Click);
			this->addButton->MouseEnter += gcnew System::EventHandler(this, &DeleteGroupForm::addButton_MouseEnter);
			this->addButton->MouseLeave += gcnew System::EventHandler(this, &DeleteGroupForm::addButton_MouseLeave);
			// 
			// DeleteGroupForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 89);
			this->Controls->Add(this->addButton);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Name = L"DeleteGroupForm";
			this->Text = L"DeleteGroupForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->addButton))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void addButton_Click(System::Object^ sender, System::EventArgs^ e) {
		bool errorFlag = false;
		try
		{
			facultyNumber = Convert::ToInt32(textBox1->Text);
		}
		catch (System::Exception^ ex)
		{
			textBox1->ForeColor = System::Drawing::Color::Red;
			errorFlag = true;
		}

		try
		{
			courseNumber = Convert::ToInt32(textBox2->Text);
		}
		catch (System::Exception^ ex)
		{
			textBox2->ForeColor = System::Drawing::Color::Red;
			errorFlag = true;
		}

		try
		{
			groupNumber = Convert::ToInt32(textBox3->Text);
		}
		catch (System::Exception^ ex)
		{
			textBox3->ForeColor = System::Drawing::Color::Red;
			errorFlag = true;
		}
		if (errorFlag) return;
		this->Close();
	}
	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		textBox1->ForeColor = System::Drawing::Color::Black;
	}
	private: System::Void textBox2_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		textBox2->ForeColor = System::Drawing::Color::Black;
	}
	private: System::Void textBox3_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		textBox3->ForeColor = System::Drawing::Color::Black;
	}
	private: System::Void addButton_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
		addButton->BackColor = Color::Gray;
	};
	private: System::Void addButton_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
		addButton->BackColor = SystemColors::Control;
	};
	};
}
