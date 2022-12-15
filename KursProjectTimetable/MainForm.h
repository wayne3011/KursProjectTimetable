#pragma once
namespace KursProjectTimetable {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
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
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}


	protected:
	private: System::Windows::Forms::TabPage^ tabPage2;
	private: System::Windows::Forms::Button^ loadDataButton;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
	private: System::Windows::Forms::GroupBox^ treeBox;
	private: System::Windows::Forms::Button^ buttonNext;

	private: System::Windows::Forms::Button^ buttonPrevious;







	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->loadDataButton = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->treeBox = (gcnew System::Windows::Forms::GroupBox());
			this->buttonNext = (gcnew System::Windows::Forms::Button());
			this->buttonPrevious = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel1->SuspendLayout();
			this->treeBox->SuspendLayout();
			this->SuspendLayout();
			// 
			// loadDataButton
			// 
			this->loadDataButton->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->loadDataButton->AutoSize = true;
			this->loadDataButton->Location = System::Drawing::Point(3, 6);
			this->loadDataButton->Name = L"loadDataButton";
			this->loadDataButton->Size = System::Drawing::Size(132, 32);
			this->loadDataButton->TabIndex = 0;
			this->loadDataButton->Text = L"Загрузить расписание";
			this->loadDataButton->UseVisualStyleBackColor = true;
			this->loadDataButton->Click += gcnew System::EventHandler(this, &MainForm::loadDataButton_Click);
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->tableLayoutPanel1->ColumnCount = 2;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				64.4186F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				35.58139F)));
			this->tableLayoutPanel1->Controls->Add(this->loadDataButton, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->treeBox, 1, 1);
			this->tableLayoutPanel1->Location = System::Drawing::Point(12, 2);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 2;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 8.379889F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 91.62011F)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(860, 547);
			this->tableLayoutPanel1->TabIndex = 0;
			this->tableLayoutPanel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MainForm::tableLayoutPanel1_Paint);
			// 
			// treeBox
			// 
			this->treeBox->Controls->Add(this->buttonNext);
			this->treeBox->Controls->Add(this->buttonPrevious);
			this->treeBox->ForeColor = System::Drawing::SystemColors::ControlText;
			this->treeBox->Location = System::Drawing::Point(557, 70);
			this->treeBox->Margin = System::Windows::Forms::Padding(3, 25, 3, 3);
			this->treeBox->Name = L"treeBox";
			this->treeBox->Padding = System::Windows::Forms::Padding(3, 25, 3, 3);
			this->treeBox->Size = System::Drawing::Size(300, 250);
			this->treeBox->TabIndex = 1;
			this->treeBox->TabStop = false;
			// 
			// buttonNext
			// 
			this->buttonNext->Location = System::Drawing::Point(156, 221);
			this->buttonNext->Name = L"buttonNext";
			this->buttonNext->Size = System::Drawing::Size(90, 25);
			this->buttonNext->TabIndex = 1;
			this->buttonNext->Text = L"Следующий";
			this->buttonNext->UseVisualStyleBackColor = true;
			this->buttonNext->Click += gcnew System::EventHandler(this, &MainForm::buttonNext_Click);
			// 
			// buttonPrevious
			// 
			this->buttonPrevious->Location = System::Drawing::Point(40, 221);
			this->buttonPrevious->Name = L"buttonPrevious";
			this->buttonPrevious->Size = System::Drawing::Size(90, 25);
			this->buttonPrevious->TabIndex = 0;
			this->buttonPrevious->Text = L"Предыдущий";
			this->buttonPrevious->UseVisualStyleBackColor = true;
			this->buttonPrevious->Click += gcnew System::EventHandler(this, &MainForm::buttonPrevious_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(884, 561);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel1->PerformLayout();
			this->treeBox->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
		void loadFromFile(String^ fileName);
		void timetablePaint(int facultyNumber, int courseNumber, int groupNumber, int dayNumber);
		void nextDayPaint();
		void previousDayPaint();
		private: System::Void loadDataButton_Click(System::Object^ sender, System::EventArgs^ e) {
		OpenFileDialog openFileDialog;
		openFileDialog.Filter = "JSON (.json)|*.json";
		if (openFileDialog.ShowDialog() == Windows::Forms::DialogResult::OK) {
			
			this->treeBox->Controls->RemoveByKey("tabControl");
			loadFromFile(openFileDialog.FileName);
		}
		else return;
		}
		private: System::Void tableLayoutPanel1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		}
		private: System::Void treeView_NodeClick(System::Object^ sender, System::Windows::Forms::TreeNodeMouseClickEventArgs ^ e) {
			if (e->Node->Nodes->Count == 0) {
				this->treeBox->Controls->RemoveByKey("schoolDayTree");
				timetablePaint(e->Node->TreeView->Parent->TabIndex, e->Node->Parent->Parent->Index, e->Node->Parent->Index, e->Node->Index);
				treeBox->Update();
			};
		}
private: System::Void buttonPrevious_Click(System::Object^ sender, System::EventArgs^ e) {
	if (!this->treeBox->Controls->ContainsKey("schoolDayTree")) return;
	this->treeBox->Controls->RemoveByKey("schoolDayTree");
	previousDayPaint();
}
private: System::Void buttonNext_Click(System::Object^ sender, System::EventArgs^ e) {
	if (!this->treeBox->Controls->ContainsKey("schoolDayTree")) return;
	this->treeBox->Controls->RemoveByKey("schoolDayTree");
	nextDayPaint();
}
};
}
