#pragma once
#include "AddFacultyForm.h"
#include "AddCourseForm.h"
#include "AddGroupForm.h"
#include "AddSchoolDayForm.h"
#include "AddLessonForm.h"
#include "DeleteFacultyForm.h"
#include "DeleteCourseForm.h"
#include "DeleteGroupForm.h"
#include "DeleteSchoolDayForm.h"
#include "DeleteLessonForm.h"
namespace KursProjectTimetable {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// ������� ���� ����������
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
		}
	protected:
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
	private: System::Windows::Forms::GroupBox^ controlElementBox;

	private: System::Windows::Forms::GroupBox^ treeBox;
	private: System::Windows::Forms::Button^ buttonNext;
	private: System::Windows::Forms::Button^ buttonPrevious;
	private: System::Windows::Forms::Button^ addCourseButton;

	private: System::Windows::Forms::Button^ addFacultyButton;

	private: System::Windows::Forms::Button^ addLessonButton;

	private: System::Windows::Forms::Button^ addGroupButton;
	private: System::Windows::Forms::Button^ addSchoolDay_button;
	private: System::Windows::Forms::Button^ deleteLessonButton;
	private: System::Windows::Forms::Button^ deleteSchoolDayButton;
	private: System::Windows::Forms::Button^ deleteCourseButton;
	private: System::Windows::Forms::Button^ deleteGroupButton;
	private: System::Windows::Forms::Button^ deleteFacultyButton;
	private: System::Windows::Forms::GroupBox^ fileManagerBox;
	private: System::Windows::Forms::Button^ outInFileButton;

	private:
		System::ComponentModel::Container^ components;
		//������ Windows Form Designer ��� ��������� ������������ �����, ����������� ������
#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->loadDataButton = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->controlElementBox = (gcnew System::Windows::Forms::GroupBox());
			this->deleteLessonButton = (gcnew System::Windows::Forms::Button());
			this->deleteSchoolDayButton = (gcnew System::Windows::Forms::Button());
			this->deleteCourseButton = (gcnew System::Windows::Forms::Button());
			this->deleteGroupButton = (gcnew System::Windows::Forms::Button());
			this->deleteFacultyButton = (gcnew System::Windows::Forms::Button());
			this->addSchoolDay_button = (gcnew System::Windows::Forms::Button());
			this->addLessonButton = (gcnew System::Windows::Forms::Button());
			this->addGroupButton = (gcnew System::Windows::Forms::Button());
			this->addCourseButton = (gcnew System::Windows::Forms::Button());
			this->addFacultyButton = (gcnew System::Windows::Forms::Button());
			this->treeBox = (gcnew System::Windows::Forms::GroupBox());
			this->buttonNext = (gcnew System::Windows::Forms::Button());
			this->buttonPrevious = (gcnew System::Windows::Forms::Button());
			this->fileManagerBox = (gcnew System::Windows::Forms::GroupBox());
			this->outInFileButton = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel1->SuspendLayout();
			this->controlElementBox->SuspendLayout();
			this->treeBox->SuspendLayout();
			this->fileManagerBox->SuspendLayout();
			this->SuspendLayout();
			// 
			// loadDataButton
			// 
			this->loadDataButton->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->loadDataButton->AutoSize = true;
			this->loadDataButton->Location = System::Drawing::Point(0, 0);
			this->loadDataButton->Name = L"loadDataButton";
			this->loadDataButton->Size = System::Drawing::Size(132, 40);
			this->loadDataButton->TabIndex = 0;
			this->loadDataButton->Text = L"��������� ����������";
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
			this->tableLayoutPanel1->Controls->Add(this->controlElementBox, 1, 1);
			this->tableLayoutPanel1->Controls->Add(this->fileManagerBox, 0, 0);
			this->tableLayoutPanel1->Location = System::Drawing::Point(12, 2);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 2;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 8.379889F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 91.62011F)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(860, 547);
			this->tableLayoutPanel1->TabIndex = 0;
			// 
			// controlElementBox
			// 
			this->controlElementBox->Controls->Add(this->deleteLessonButton);
			this->controlElementBox->Controls->Add(this->deleteSchoolDayButton);
			this->controlElementBox->Controls->Add(this->deleteCourseButton);
			this->controlElementBox->Controls->Add(this->deleteGroupButton);
			this->controlElementBox->Controls->Add(this->deleteFacultyButton);
			this->controlElementBox->Controls->Add(this->addSchoolDay_button);
			this->controlElementBox->Controls->Add(this->addLessonButton);
			this->controlElementBox->Controls->Add(this->addGroupButton);
			this->controlElementBox->Controls->Add(this->addCourseButton);
			this->controlElementBox->Controls->Add(this->addFacultyButton);
			this->controlElementBox->Controls->Add(this->treeBox);
			this->controlElementBox->Location = System::Drawing::Point(557, 48);
			this->controlElementBox->Name = L"controlElementBox";
			this->controlElementBox->Size = System::Drawing::Size(300, 496);
			this->controlElementBox->TabIndex = 1;
			this->controlElementBox->TabStop = false;
			this->controlElementBox->Text = L"groupBox1";
			// 
			// deleteLessonButton
			// 
			this->deleteLessonButton->Location = System::Drawing::Point(155, 376);
			this->deleteLessonButton->Name = L"deleteLessonButton";
			this->deleteLessonButton->Size = System::Drawing::Size(142, 23);
			this->deleteLessonButton->TabIndex = 12;
			this->deleteLessonButton->Text = L"������� �������";
			this->deleteLessonButton->UseVisualStyleBackColor = true;
			this->deleteLessonButton->Click += gcnew System::EventHandler(this, &MainForm::deleteLessonButton_Click);
			// 
			// deleteSchoolDayButton
			// 
			this->deleteSchoolDayButton->Location = System::Drawing::Point(155, 347);
			this->deleteSchoolDayButton->Name = L"deleteSchoolDayButton";
			this->deleteSchoolDayButton->Size = System::Drawing::Size(142, 23);
			this->deleteSchoolDayButton->TabIndex = 11;
			this->deleteSchoolDayButton->Text = L"������� ������� ����";
			this->deleteSchoolDayButton->UseVisualStyleBackColor = true;
			this->deleteSchoolDayButton->Click += gcnew System::EventHandler(this, &MainForm::deleteSchoolDayButton_Click);
			// 
			// deleteCourseButton
			// 
			this->deleteCourseButton->Location = System::Drawing::Point(155, 287);
			this->deleteCourseButton->Name = L"deleteCourseButton";
			this->deleteCourseButton->Size = System::Drawing::Size(142, 23);
			this->deleteCourseButton->TabIndex = 10;
			this->deleteCourseButton->Text = L"������� ����";
			this->deleteCourseButton->UseVisualStyleBackColor = true;
			this->deleteCourseButton->Click += gcnew System::EventHandler(this, &MainForm::deleteCourseButton_Click);
			// 
			// deleteGroupButton
			// 
			this->deleteGroupButton->Location = System::Drawing::Point(155, 318);
			this->deleteGroupButton->Name = L"deleteGroupButton";
			this->deleteGroupButton->Size = System::Drawing::Size(142, 23);
			this->deleteGroupButton->TabIndex = 9;
			this->deleteGroupButton->Text = L"������� ������";
			this->deleteGroupButton->UseVisualStyleBackColor = true;
			this->deleteGroupButton->Click += gcnew System::EventHandler(this, &MainForm::deleteGroupButton_Click);
			// 
			// deleteFacultyButton
			// 
			this->deleteFacultyButton->Location = System::Drawing::Point(155, 257);
			this->deleteFacultyButton->Name = L"deleteFacultyButton";
			this->deleteFacultyButton->Size = System::Drawing::Size(142, 23);
			this->deleteFacultyButton->TabIndex = 8;
			this->deleteFacultyButton->Text = L"������� ���������";
			this->deleteFacultyButton->UseVisualStyleBackColor = true;
			this->deleteFacultyButton->Click += gcnew System::EventHandler(this, &MainForm::deleteFacultyButton_Click);
			// 
			// addSchoolDay_button
			// 
			this->addSchoolDay_button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->addSchoolDay_button->Location = System::Drawing::Point(7, 347);
			this->addSchoolDay_button->Name = L"addSchoolDay_button";
			this->addSchoolDay_button->Size = System::Drawing::Size(142, 23);
			this->addSchoolDay_button->TabIndex = 7;
			this->addSchoolDay_button->Text = L"�������� ������� ����";
			this->addSchoolDay_button->UseVisualStyleBackColor = true;
			this->addSchoolDay_button->Click += gcnew System::EventHandler(this, &MainForm::addSchoolDay_button_Click);
			// 
			// addLessonButton
			// 
			this->addLessonButton->Location = System::Drawing::Point(7, 376);
			this->addLessonButton->Name = L"addLessonButton";
			this->addLessonButton->Size = System::Drawing::Size(142, 23);
			this->addLessonButton->TabIndex = 6;
			this->addLessonButton->Text = L"�������� �������";
			this->addLessonButton->UseVisualStyleBackColor = true;
			this->addLessonButton->Click += gcnew System::EventHandler(this, &MainForm::addLessonButton_Click);
			// 
			// addGroupButton
			// 
			this->addGroupButton->Location = System::Drawing::Point(7, 318);
			this->addGroupButton->Name = L"addGroupButton";
			this->addGroupButton->Size = System::Drawing::Size(142, 23);
			this->addGroupButton->TabIndex = 5;
			this->addGroupButton->Text = L"�������� ������";
			this->addGroupButton->UseVisualStyleBackColor = true;
			this->addGroupButton->Click += gcnew System::EventHandler(this, &MainForm::addGroupButton_Click);
			// 
			// addCourseButton
			// 
			this->addCourseButton->Location = System::Drawing::Point(7, 287);
			this->addCourseButton->Name = L"addCourseButton";
			this->addCourseButton->Size = System::Drawing::Size(142, 23);
			this->addCourseButton->TabIndex = 4;
			this->addCourseButton->Text = L"�������� ����";
			this->addCourseButton->UseVisualStyleBackColor = true;
			this->addCourseButton->Click += gcnew System::EventHandler(this, &MainForm::addCourseButton_Click);
			// 
			// addFacultyButton
			// 
			this->addFacultyButton->Location = System::Drawing::Point(7, 257);
			this->addFacultyButton->Name = L"addFacultyButton";
			this->addFacultyButton->Size = System::Drawing::Size(142, 23);
			this->addFacultyButton->TabIndex = 3;
			this->addFacultyButton->Text = L"�������� ���������";
			this->addFacultyButton->UseVisualStyleBackColor = true;
			this->addFacultyButton->Click += gcnew System::EventHandler(this, &MainForm::addFacultyButton_Click);
			// 
			// treeBox
			// 
			this->treeBox->Controls->Add(this->buttonNext);
			this->treeBox->Controls->Add(this->buttonPrevious);
			this->treeBox->ForeColor = System::Drawing::SystemColors::ControlText;
			this->treeBox->Location = System::Drawing::Point(0, 0);
			this->treeBox->Margin = System::Windows::Forms::Padding(3, 25, 3, 3);
			this->treeBox->Name = L"treeBox";
			this->treeBox->Padding = System::Windows::Forms::Padding(3, 25, 3, 3);
			this->treeBox->Size = System::Drawing::Size(300, 250);
			this->treeBox->TabIndex = 2;
			this->treeBox->TabStop = false;
			// 
			// buttonNext
			// 
			this->buttonNext->Location = System::Drawing::Point(156, 221);
			this->buttonNext->Name = L"buttonNext";
			this->buttonNext->Size = System::Drawing::Size(90, 25);
			this->buttonNext->TabIndex = 1;
			this->buttonNext->Text = L"���������";
			this->buttonNext->UseVisualStyleBackColor = true;
			this->buttonNext->Click += gcnew System::EventHandler(this, &MainForm::buttonNext_Click);
			// 
			// buttonPrevious
			// 
			this->buttonPrevious->Location = System::Drawing::Point(40, 221);
			this->buttonPrevious->Name = L"buttonPrevious";
			this->buttonPrevious->Size = System::Drawing::Size(90, 25);
			this->buttonPrevious->TabIndex = 0;
			this->buttonPrevious->Text = L"����������";
			this->buttonPrevious->UseVisualStyleBackColor = true;
			this->buttonPrevious->Click += gcnew System::EventHandler(this, &MainForm::buttonPrevious_Click);
			// 
			// fileManagerBox
			// 
			this->fileManagerBox->Controls->Add(this->outInFileButton);
			this->fileManagerBox->Controls->Add(this->loadDataButton);
			this->fileManagerBox->Location = System::Drawing::Point(3, 3);
			this->fileManagerBox->Name = L"fileManagerBox";
			this->fileManagerBox->Size = System::Drawing::Size(270, 39);
			this->fileManagerBox->TabIndex = 2;
			this->fileManagerBox->TabStop = false;
			// 
			// outInFileButton
			// 
			this->outInFileButton->Location = System::Drawing::Point(138, 0);
			this->outInFileButton->Name = L"outInFileButton";
			this->outInFileButton->Size = System::Drawing::Size(132, 40);
			this->outInFileButton->TabIndex = 1;
			this->outInFileButton->Text = L"��������� ����������";
			this->outInFileButton->UseVisualStyleBackColor = true;
			this->outInFileButton->Click += gcnew System::EventHandler(this, &MainForm::outInFileButton_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(884, 561);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"MainForm";
			this->Text = L"����������";
			this->tableLayoutPanel1->ResumeLayout(false);
			this->controlElementBox->ResumeLayout(false);
			this->treeBox->ResumeLayout(false);
			this->fileManagerBox->ResumeLayout(false);
			this->fileManagerBox->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
		//�������� ���������� �� �����
		void loadFromFile(String^ fileName);
		//�������� ���������� � ����
		void outInFile(String^ path);
		//��������� ������ �����������
		void facultiesListPaint();
		//��������� ����������
		void timetablePaint(int facultyNumber, int courseNumber, int groupNumber, int dayNumber);
		//������� �� ��������� ���� ������
		void nextDayPaint();
		//������� �� ���������� ���� ������
		void previousDayPaint();
		//���������� ������ ����������
		void addFaculty(int facultyNumber);
		//�������� ����������
		void deleteFaculty(int facultyNumber);
		//�������� �����
		void deleteCourse(int facultyNumber, int courseNumber);
		//���������� ������ �����
		void addCourse(int facultyNumber, int courseNumber);
		//�������� ������
		void deleteGroup(int facultyNumber, int courseNumber, int groupNumber);
		//���������� ����� ������
		void addGroup(int facultyNumber, int courseNumber, int groupNumber);
		//���������� ������ �������� ���
		void addSchoolDay(int facultyNumber, int courseNumber, int groupNumber, int schoolDayNumber);
		//�������� �������� ���
		void deleteSchoolDay(int facultyNumber, int courseNumber, int groupNumber, int schoolDayNumber);
		//���������� ������ �������
		void addLesson(int facultyNumber, int courseNumber, int groupNumber, int schoolDayNumber, System::String^ subjectName, System::String^ teacherName, int lessonNumber, int audienceNumber);
		//�������� �������
		void deleteLesson(int facultyNumber, int courseNumber, int groupNumber, int schoolDayNumber, int lessonNumber);

		


	//���������� ������� ������� �� ������ loadDataButton(��������� ����������)
	private: System::Void loadDataButton_Click(System::Object^ sender, System::EventArgs^ e) {
		OpenFileDialog openFileDialog;
		openFileDialog.Filter = "JSON (.json)|*.json";
		if (openFileDialog.ShowDialog() == Windows::Forms::DialogResult::OK) {//�������� ������ ��� ��������� ���� ������ �����

			this->tableLayoutPanel1->Controls->RemoveByKey("tabControl");//������� ������� ���������� ������ ����������� �� ������ �����������
			loadFromFile(openFileDialog.FileName);//�������� ������� ����� � �����
		}

		else return;
	}
	//���������� ������� ������� �� ������ outInFileButton(��������� ����������)
	private: System::Void outInFileButton_Click(System::Object^ sender, System::EventArgs^ e) {
		SaveFileDialog selectedFile;
		selectedFile.Filter = "JSON (.json)|*.json";
		selectedFile.DefaultExt = ".json";
		if (selectedFile.ShowDialog() == Windows::Forms::DialogResult::OK) {//��������� ������ ��� ��������� ���� ������ �����
			outInFile(selectedFile.FileName);//�������� ������� ������ � ����
		}
	}
		   //���������� ������� ������� �� ������ treeView � �����������(����� �������� ���)
	private: System::Void treeView_NodeClick(System::Object^ sender, System::Windows::Forms::TreeNodeMouseClickEventArgs^ e) {
		if (e->Node->Name == "WeekDay") {//���� ������ �� ����, ���������� ���� ������
			this->treeBox->Controls->RemoveByKey("schoolDayTree");//�� �������� � ����������� ������� ������ ����������
			timetablePaint(e->Node->TreeView->Parent->TabIndex, e->Node->Parent->Parent->Index, e->Node->Parent->Index, e->Node->Index);//������� ������� ��������� ������ ����������
		};
	}
		   //���������� ������� ������� �� ������ buttonPrevious(����������)
	private: System::Void buttonPrevious_Click(System::Object^ sender, System::EventArgs^ e) {
		if (!this->treeBox->Controls->ContainsKey("schoolDayTree")) return;//���� ��������� ������������ ��� ��� ��� �� �������� ������ �� ������
		//�����
		this->treeBox->Controls->RemoveByKey("schoolDayTree");//������� ������� ����������
		previousDayPaint();//������������ ���������� ��� ���������� �� ������� ���
	}
		   //���������� ������� ������� �� ������ buttonNext(���������)
	private: System::Void buttonNext_Click(System::Object^ sender, System::EventArgs^ e) {
		if (!this->treeBox->Controls->ContainsKey("schoolDayTree")) return;
		this->treeBox->Controls->RemoveByKey("schoolDayTree");
		nextDayPaint();
	}
		   //���������� ������� ������� �� ������ addFacultyButton(�������� ���������)
	private: System::Void addFacultyButton_Click(System::Object^ sender, System::EventArgs^ e) {
		AddFacultyForm^ addFacultyForm = gcnew(KursProjectTimetable::AddFacultyForm);//������ ������ ����� ��� ����� ���������������� �������� ������ ����������
		addFacultyForm->ShowDialog();//���������� ����� ��� ����� ���������������� �������� ������ ����������
		if (addFacultyForm->facultyNumber == -1) {//���� �������� �� ���� ������� ��������� ���� ����� ����� ������� -1
			return;
		}
		//��������� ����� ���������
		addFaculty(addFacultyForm->facultyNumber);

	}
		   ///
		   /// ��������� ����������� ������� ������ ���������� ����� ������ ������, �� ����������� �������� ���������� �������� ������������� �����
		   ///

		   //���������� ������� ������� �� ������ addCourse(�������� ����)
	private: System::Void addCourseButton_Click(System::Object^ sender, System::EventArgs^ e) {
		KursProjectTimetable::AddCourseForm^ addCourseForm = gcnew(KursProjectTimetable::AddCourseForm);
		addCourseForm->ShowDialog();
		if (addCourseForm->facultyNumber == -1 || addCourseForm->facultyNumber == -1) {
			return;
		}
		addCourse(addCourseForm->facultyNumber, addCourseForm->courseNumber);

	}
		   //���������� ������� ������� �� ������ addGroupButton(�������� ������)
	private: System::Void addGroupButton_Click(System::Object^ sender, System::EventArgs^ e) {
		KursProjectTimetable::AddGroupForm^ addGroupForm = gcnew(KursProjectTimetable::AddGroupForm);
		addGroupForm->ShowDialog();
		if (addGroupForm->facultyNumber == -1 || addGroupForm->groupNumber == -1 || addGroupForm->courseNumber == -1) {
			return;
		}
		addGroup(addGroupForm->facultyNumber, addGroupForm->courseNumber, addGroupForm->groupNumber);
	}
		   //���������� ������� ������� �� ������ addSchoolDay(�������� ������� ����)
	private: System::Void addSchoolDay_button_Click(System::Object^ sender, System::EventArgs^ e) {
		KursProjectTimetable::AddSchoolDayForm^ addSchoolDayForm = gcnew(KursProjectTimetable::AddSchoolDayForm);
		addSchoolDayForm->ShowDialog();
		if (addSchoolDayForm->facultyNumber == -1 || addSchoolDayForm->courseNumber == -1 || addSchoolDayForm->groupNumber == -1 || addSchoolDayForm->schoolDayNumber == -1) {
			return;
		}
		addSchoolDay(addSchoolDayForm->facultyNumber, addSchoolDayForm->courseNumber, addSchoolDayForm->groupNumber, addSchoolDayForm->schoolDayNumber-1);
	}
		   //���������� ������� ������� �� ������ addLessonButton(�������� �������)
	private: System::Void addLessonButton_Click(System::Object^ sender, System::EventArgs^ e) {
		KursProjectTimetable::AddLessonForm^ addLessonForm = gcnew(KursProjectTimetable::AddLessonForm);
		addLessonForm->ShowDialog();
		if (addLessonForm->facultyNumber == -1 || addLessonForm->courseNumber == -1 || addLessonForm->groupNumber == -1 || addLessonForm->schoolDayNumber == -1 || addLessonForm->audienceNumber == -1 || addLessonForm->lessonNumber == -1 || addLessonForm->subjectName->Length == 0 || addLessonForm->teacherName->Length == 0) {
			return;
		};
		addLesson(addLessonForm->facultyNumber, addLessonForm->courseNumber, addLessonForm->groupNumber, addLessonForm->schoolDayNumber-1, addLessonForm->subjectName, addLessonForm->teacherName, addLessonForm->lessonNumber, addLessonForm->audienceNumber);
	}
		   //���������� ������� ������� �� ������ deleteFacultyButton(������� ���������)
	private: System::Void deleteFacultyButton_Click(System::Object^ sender, System::EventArgs^ e) {
		KursProjectTimetable::DeleteFacultyForm^ deleteFacultyForm = gcnew(KursProjectTimetable::DeleteFacultyForm);//������ ������ ����� ��� ��������� ���������������� ������ ��� �������� ����������
		deleteFacultyForm->ShowDialog();//���������� ����� ��� ��������� ���������������� ������ ��� �������� ����������

		if (deleteFacultyForm->facultyNumber == -1) {//���� �������� �� ���� ������� ��������� ���� ����� ����� ������� -1
			return;
		}
		deleteFaculty(deleteFacultyForm->facultyNumber);//������� ���������
	}

		  ///
		  /// ��������� ����������� ������� ������ �������� ����� ������ ������, �� ����������� �������� ���������� �������� ������������� �����
		  ///

		   //���������� ������� ������� �� ������ deleteCourseButton(������� ����)
	private: System::Void deleteCourseButton_Click(System::Object^ sender, System::EventArgs^ e) {
		KursProjectTimetable::DeleteCourseForm^ deleteCourseForm = gcnew(KursProjectTimetable::DeleteCourseForm);
		deleteCourseForm->ShowDialog();
		if (deleteCourseForm->facultyNumber == -1 || deleteCourseForm->facultyNumber == -1) {
			return;
		}
		deleteCourse(deleteCourseForm->facultyNumber, deleteCourseForm->courseNumber);
	}
		   //���������� ������� ������� �� ������ deleteGroupButton(������� ������)
	private: System::Void deleteGroupButton_Click(System::Object^ sender, System::EventArgs^ e) {
		KursProjectTimetable::DeleteGroupForm^ deleteGroupForm = gcnew(KursProjectTimetable::DeleteGroupForm);
		deleteGroupForm->ShowDialog();
		if (deleteGroupForm->facultyNumber == -1 || deleteGroupForm->groupNumber == -1 || deleteGroupForm->courseNumber == -1) {
			return;
		};
		deleteGroup(deleteGroupForm->facultyNumber, deleteGroupForm->courseNumber, deleteGroupForm->groupNumber);
	};
		   //���������� ������� ������� �� ������ deleteSchoolDayButton(������� ������� ����)
	private: System::Void deleteSchoolDayButton_Click(System::Object^ sender, System::EventArgs^ e) {
		KursProjectTimetable::DeleteSchoolDayForm^ deleteSchoolDayForm = gcnew(KursProjectTimetable::DeleteSchoolDayForm);
		deleteSchoolDayForm->ShowDialog();
		if (deleteSchoolDayForm->facultyNumber == -1 || deleteSchoolDayForm->courseNumber == -1 || deleteSchoolDayForm->groupNumber == -1 || deleteSchoolDayForm->schoolDayNumber == -1) {
			return;
		}
		deleteSchoolDay(deleteSchoolDayForm->facultyNumber, deleteSchoolDayForm->courseNumber, deleteSchoolDayForm->groupNumber, deleteSchoolDayForm->schoolDayNumber-1);
	}
		   //���������� ������� ������� �� ������ deleteLessonButton(������� �������)
private: System::Void deleteLessonButton_Click(System::Object^ sender, System::EventArgs^ e) {
	KursProjectTimetable::DeleteLessonForm^ deleteLessonForm = gcnew(KursProjectTimetable::DeleteLessonForm);
	deleteLessonForm->ShowDialog();
	if (deleteLessonForm->facultyNumber == -1 || deleteLessonForm->courseNumber == -1 || deleteLessonForm->groupNumber == -1 || deleteLessonForm->schoolDayNumber == -1 || deleteLessonForm->lessonNumber == -1) {
		return;
	}
	deleteLesson(deleteLessonForm->facultyNumber, deleteLessonForm->courseNumber, deleteLessonForm->groupNumber, deleteLessonForm->schoolDayNumber-1, deleteLessonForm->lessonNumber);
}

};
}; 
