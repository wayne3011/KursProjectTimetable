#pragma once

namespace KursProjectTimetable {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for DeleteFacultyForm
	/// </summary>
	public ref class DeleteFacultyForm : public System::Windows::Forms::Form
	{
	public:
		DeleteFacultyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
		int facultyNumber = -1;

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~DeleteFacultyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label1;
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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(DeleteFacultyForm::typeid));
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->addButton = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->addButton))->BeginInit();
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->BackColor = System::Drawing::SystemColors::Window;
			this->textBox1->ForeColor = System::Drawing::Color::Black;
			this->textBox1->Location = System::Drawing::Point(168, 10);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(39, 20);
			this->textBox1->TabIndex = 0;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &DeleteFacultyForm::textBox1_TextChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(13, 13);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(149, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"¬ведите номер факультета:";
			// 
			// addButton
			// 
			this->addButton->BackColor = System::Drawing::SystemColors::Control;
			this->addButton->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"addButton.BackgroundImage")));
			this->addButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->addButton->Location = System::Drawing::Point(213, 12);
			this->addButton->Name = L"addButton";
			this->addButton->Size = System::Drawing::Size(19, 17);
			this->addButton->TabIndex = 2;
			this->addButton->TabStop = false;
			this->addButton->Click += gcnew System::EventHandler(this, &DeleteFacultyForm::addButton_Click);
			this->addButton->MouseEnter += gcnew System::EventHandler(this, &DeleteFacultyForm::addButton_MouseEnter);
			this->addButton->MouseLeave += gcnew System::EventHandler(this, &DeleteFacultyForm::addButton_MouseLeave);
			// 
			// DeleteFacultyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(241, 41);
			this->Controls->Add(this->addButton);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Name = L"DeleteFacultyForm";
			this->Text = L"DeleteFacultyForm";
			this->Load += gcnew System::EventHandler(this, &DeleteFacultyForm::AddFacultyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->addButton))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void AddFacultyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void addButton_Click(System::Object^ sender, System::EventArgs^ e) {
		try
		{
			facultyNumber = Convert::ToInt32(textBox1->Text);
		}
		catch (System::Exception^ ex)
		{
			textBox1->ForeColor = System::Drawing::Color::Red;
			return;
		}
		this->Close();
	}
	private: System::Void addButton_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
		addButton->BackColor = Color::Gray;
	};
	private: System::Void addButton_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
		addButton->BackColor = SystemColors::Control;
	};
	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		textBox1->ForeColor = System::Drawing::Color::Black;
	}

	};
}
