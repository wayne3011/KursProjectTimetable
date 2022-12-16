#pragma once
namespace KursProjectTimetable {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for addGroupForm
	/// </summary>
	public ref class AddLessonForm : public System::Windows::Forms::Form
	{
	public:
		AddLessonForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
		int facultyNumber = -1;
		int courseNumber = -1;
		int groupNumber = -1;
		int schoolDayNumber = -1;
		int lessonNumber = -1;
		int audienceNumber = -1;
		System::String^ subjectName = gcnew String("");
		System::String^ teacherName = gcnew String("");
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::TextBox^ lessonNumberBox;
	private: System::Windows::Forms::TextBox^ subjectNameBox;
	private: System::Windows::Forms::TextBox^ audienceNumberBox;
	private: System::Windows::Forms::TextBox^ teacherNameBox;
	private: System::Windows::Forms::Label^ label8;

	public:
	private: System::Windows::Forms::TextBox^ textBox4;



	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~AddLessonForm()
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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(AddLessonForm::typeid));
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->addButton = (gcnew System::Windows::Forms::PictureBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->lessonNumberBox = (gcnew System::Windows::Forms::TextBox());
			this->subjectNameBox = (gcnew System::Windows::Forms::TextBox());
			this->audienceNumberBox = (gcnew System::Windows::Forms::TextBox());
			this->teacherNameBox = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->addButton))->BeginInit();
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(168, 10);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(31, 20);
			this->textBox1->TabIndex = 0;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &AddLessonForm::textBox1_TextChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(13, 13);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(149, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Введите номер факультета:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(36, 66);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(126, 13);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Введите номер группы:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(43, 39);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(119, 13);
			this->label3->TabIndex = 3;
			this->label3->Text = L"Введите номер курса:";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(169, 36);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(30, 20);
			this->textBox2->TabIndex = 4;
			this->textBox2->TextChanged += gcnew System::EventHandler(this, &AddLessonForm::textBox2_TextChanged);
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(169, 63);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(30, 20);
			this->textBox3->TabIndex = 5;
			this->textBox3->TextChanged += gcnew System::EventHandler(this, &AddLessonForm::textBox3_TextChanged);
			// 
			// addButton
			// 
			this->addButton->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"addButton.BackgroundImage")));
			this->addButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->addButton->Location = System::Drawing::Point(369, 92);
			this->addButton->Name = L"addButton";
			this->addButton->Size = System::Drawing::Size(19, 17);
			this->addButton->TabIndex = 8;
			this->addButton->TabStop = false;
			this->addButton->Click += gcnew System::EventHandler(this, &AddLessonForm::addButton_Click);
			this->addButton->MouseEnter += gcnew System::EventHandler(this, &AddLessonForm::addButton_MouseEnter);
			this->addButton->MouseLeave += gcnew System::EventHandler(this, &AddLessonForm::addButton_MouseLeave);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(15, 92);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(147, 13);
			this->label4->TabIndex = 9;
			this->label4->Text = L"Введите номер дня недели:";
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(169, 89);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(30, 20);
			this->textBox4->TabIndex = 10;
			this->textBox4->TextChanged += gcnew System::EventHandler(this, &AddLessonForm::textBox4_TextChanged);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(216, 13);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(112, 13);
			this->label5->TabIndex = 11;
			this->label5->Text = L"Название предмета:";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(229, 39);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(99, 13);
			this->label6->TabIndex = 12;
			this->label6->Text = L"Номер аудитории:";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(216, 65);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(112, 13);
			this->label7->TabIndex = 13;
			this->label7->Text = L"Имя преподавателя:";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(255, 92);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(73, 13);
			this->label8->TabIndex = 14;
			this->label8->Text = L"Номер пары:";
			// 
			// lessonNumberBox
			// 
			this->lessonNumberBox->Location = System::Drawing::Point(334, 89);
			this->lessonNumberBox->Name = L"lessonNumberBox";
			this->lessonNumberBox->Size = System::Drawing::Size(29, 20);
			this->lessonNumberBox->TabIndex = 15;
			this->lessonNumberBox->TextChanged += gcnew System::EventHandler(this, &AddLessonForm::lessonNumberBox_TextChanged);
			// 
			// subjectNameBox
			// 
			this->subjectNameBox->Location = System::Drawing::Point(334, 10);
			this->subjectNameBox->Name = L"subjectNameBox";
			this->subjectNameBox->Size = System::Drawing::Size(129, 20);
			this->subjectNameBox->TabIndex = 16;
			// 
			// audienceNumberBox
			// 
			this->audienceNumberBox->Location = System::Drawing::Point(334, 36);
			this->audienceNumberBox->Name = L"audienceNumberBox";
			this->audienceNumberBox->Size = System::Drawing::Size(54, 20);
			this->audienceNumberBox->TabIndex = 17;
			this->audienceNumberBox->TextChanged += gcnew System::EventHandler(this, &AddLessonForm::audienceNumber_TextChanged);
			// 
			// teacherNameBox
			// 
			this->teacherNameBox->Location = System::Drawing::Point(334, 63);
			this->teacherNameBox->Name = L"teacherNameBox";
			this->teacherNameBox->Size = System::Drawing::Size(129, 20);
			this->teacherNameBox->TabIndex = 18;
			// 
			// AddLessonForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(475, 116);
			this->Controls->Add(this->teacherNameBox);
			this->Controls->Add(this->audienceNumberBox);
			this->Controls->Add(this->subjectNameBox);
			this->Controls->Add(this->lessonNumberBox);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->addButton);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Location = System::Drawing::Point(334, 62);
			this->Name = L"AddLessonForm";
			this->Text = L"AddLessonForm";
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

		try
		{
			schoolDayNumber = Convert::ToInt32(textBox4->Text);
		}
		catch (System::Exception^ ex)
		{
			textBox4->ForeColor = System::Drawing::Color::Red;
			errorFlag = true;
		}

		try
		{
			lessonNumber = Convert::ToInt32(lessonNumberBox->Text);
		}
		catch (System::Exception^ ex)
		{
			lessonNumberBox->ForeColor = System::Drawing::Color::Red;
			errorFlag = true;
		}

		try
		{
			audienceNumber = Convert::ToInt32(audienceNumberBox->Text);
		}
		catch (System::Exception^ ex)
		{
			audienceNumberBox->ForeColor = System::Drawing::Color::Red;
			errorFlag = true;
		}
		teacherName = teacherNameBox->Text;
		subjectName = subjectNameBox->Text;
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
	private: System::Void textBox4_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		textBox4->ForeColor = System::Drawing::Color::Black;
	}
	private: System::Void lessonNumberBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		lessonNumberBox->ForeColor = System::Drawing::Color::Black;
	}
	private: System::Void audienceNumber_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		audienceNumberBox->ForeColor = System::Drawing::Color::Black;
	}
	
	private: System::Void addButton_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
		addButton->BackColor = Color::Gray;
	};
	private: System::Void addButton_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
		addButton->BackColor = SystemColors::Control;
	};
	};
}
