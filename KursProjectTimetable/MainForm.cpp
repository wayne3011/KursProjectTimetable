#include "MainForm.h"
#include "DataStruct.h"
#include "json.hpp"
#include <iostream>
#include <fstream>
#include "string_converter.h"
using namespace KursProjectTimetable;
using namespace System::Windows::Forms;
[STAThread]
int main(array < String^>^ args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(0);
    KursProjectTimetable::MainForm form;
    Application::Run(% form);
}
SLList<Faculty> faculties;
struct SelectedSchoolDay {
	int facultyNumber;
	int courseNumber;
	int groupNumber;
	SchoolDay selectedDay;
	SelectedSchoolDay()
	{

	}
	SelectedSchoolDay(int facultyNumber, int courseNumber, int groupNumber, SchoolDay selectedDay)
	{
		this->facultyNumber = facultyNumber;
		this->courseNumber = courseNumber;
		this->groupNumber = groupNumber;
		this->selectedDay = selectedDay;
	}
};
SelectedSchoolDay selectedsSchoolDay;
void jParse(nlohmann::json_abi_v3_11_2::json& j_complete, SLList<Faculty>& faculties);
System::Windows::Forms::TreeView^ schoolDayTreePaint(SchoolDay schoolDay);
void KursProjectTimetable::MainForm::loadFromFile(String^ fileName)
{
	faculties.clear();
	const char* fileName_str = (const char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(fileName)).ToPointer();
	std::ifstream fin(fileName_str);
	nlohmann::json j_complete = nlohmann::json::parse(fin);
	jParse(j_complete, faculties);
	facultiesListPaint();
}
void KursProjectTimetable::MainForm::facultiesListPaint()
{
	faculties.sort();
	this->tableLayoutPanel1->Controls->RemoveByKey("tabControl");
	TabControl^ tabControl = gcnew(TabControl);
	tabControl->Location = System::Drawing::Point(3, 48);
	tabControl->Name = L"tabControl";
	tabControl->SelectedIndex = 0;
	tabControl->Size = System::Drawing::Size(548, 496);
	tabControl->TabIndex = 1;

	for (size_t i = 0; i < faculties.getSize(); i++)
	{
		TabPage^ faculty = gcnew(TabPage);
		faculty->Text = "��������� �" + faculties[i].number;
		TreeView^ courses = gcnew(TreeView);
		courses->NodeMouseClick += gcnew System::Windows::Forms::TreeNodeMouseClickEventHandler(this, &MainForm::treeView_NodeClick);
		courses->Size = System::Drawing::Size(tabControl->Size.Width - 10, tabControl->Size.Height - 27);
		for (size_t j = 0; j < faculties[i].courses.getSize(); j++)
		{
			TreeNode^ course = gcnew(TreeNode);
			course->Text = "���� �" + faculties[i].courses[j].number;
			for (size_t k = 0; k < faculties[i].courses[j].groups.getSize(); k++)
			{
				TreeNode^ group = gcnew(TreeNode);
				group->Text = "������ �" + faculties[i].courses[j].groups[k].number;
				for (size_t f = 0; f < faculties[i].courses[j].groups[k].timetable.schoolDays.GetSize(); f++)
				{
					TreeNode^ day = gcnew(TreeNode);
					day->Text = stoS(faculties[i].courses[j].groups[k].timetable.schoolDays[f].day);
					group->Nodes->Add(day);
				}
				course->Nodes->Add(group);
			}
			courses->Nodes->Add(course);
		}
		faculty->Controls->Add(courses);
		tabControl->Controls->Add(faculty);
	}
	this->tableLayoutPanel1->Controls->Add(tabControl, 0, 1);
}
void KursProjectTimetable::MainForm::timetablePaint(int facultyNumber, int courseNumber, int groupNumber, int dayNumber) {
	TreeView^ schoolDay = schoolDayTreePaint(faculties[facultyNumber].courses[courseNumber].groups[groupNumber].timetable.schoolDays[dayNumber]);
	schoolDay->Name = L"schoolDayTree";
	schoolDay->Size = System::Drawing::Size(treeBox->Width-4, treeBox->Height-15);
	schoolDay->Location = System::Drawing::Point(2, 12);
	schoolDay->Margin = System::Windows::Forms::Padding(0, 25, 0, 0);
	schoolDay->BorderStyle = System::Windows::Forms::BorderStyle::None;
	schoolDay->BackColor = treeBox->BackColor;
	treeBox->Controls->Add(schoolDay);
	selectedsSchoolDay = SelectedSchoolDay(facultyNumber, courseNumber, groupNumber, faculties[facultyNumber].courses[courseNumber].groups[groupNumber].timetable.schoolDays[dayNumber]);
	treeBox->Text = "������ �" + (groupNumber+1) + " " + stoS(selectedsSchoolDay.selectedDay.day);
	treeBox->Update();
}
System::Windows::Forms::TreeView^ schoolDayTreePaint(SchoolDay schoolDay) {
	TreeView^ schoolDayTree = gcnew TreeView;
	schoolDay.lessons.sort();
	for (size_t i = 0; i < schoolDay.lessons.getSize(); i++)
	{
		TreeNode^ lesson = gcnew TreeNode;
		lesson->Text = schoolDay.lessons[i].lessonNumber + "." + stoS(schoolDay.lessons[i].subjectName);
		TreeNode^ audienceNumber = gcnew TreeNode;
		audienceNumber->Text = "��������� �" + schoolDay.lessons[i].audienceNumber;
		TreeNode^ teacherName = gcnew TreeNode;
		teacherName->Text = "��� �������������:" + stoS(schoolDay.lessons[i].teacherName);
		lesson->Nodes->Add(audienceNumber);
		lesson->Nodes->Add(teacherName);
		schoolDayTree->Nodes->Add(lesson);
	}
	return schoolDayTree;
};
void KursProjectTimetable::MainForm::nextDayPaint() {
	SchoolDay nextSchoolDay = faculties[selectedsSchoolDay.facultyNumber].courses[selectedsSchoolDay.courseNumber].groups[selectedsSchoolDay.groupNumber].timetable.schoolDays.getNext(selectedsSchoolDay.selectedDay);
	TreeView^ schoolDay = schoolDayTreePaint(nextSchoolDay);
	schoolDay->Name = L"schoolDayTree";
	schoolDay->Size = System::Drawing::Size(treeBox->Width - 4, treeBox->Height - 15);
	schoolDay->Location = System::Drawing::Point(2, 12);
	schoolDay->Margin = System::Windows::Forms::Padding(0, 25, 0, 0);
	schoolDay->BorderStyle = System::Windows::Forms::BorderStyle::None;
	schoolDay->BackColor = treeBox->BackColor;
	treeBox->Controls->Add(schoolDay);
	selectedsSchoolDay.selectedDay = nextSchoolDay;
	treeBox->Text = "������ �" + (selectedsSchoolDay.groupNumber+1) + " " + stoS(selectedsSchoolDay.selectedDay.day);
	treeBox->Update();
}
void KursProjectTimetable::MainForm::previousDayPaint() {
	SchoolDay nextSchoolDay = faculties[selectedsSchoolDay.facultyNumber].courses[selectedsSchoolDay.courseNumber].groups[selectedsSchoolDay.groupNumber].timetable.schoolDays.getPrevious(selectedsSchoolDay.selectedDay);
	TreeView^ schoolDay = schoolDayTreePaint(nextSchoolDay);
	schoolDay->Name = L"schoolDayTree";
	schoolDay->Size = System::Drawing::Size(treeBox->Width - 4, treeBox->Height - 12);
	schoolDay->Location = System::Drawing::Point(2, 12);
	schoolDay->Margin = System::Windows::Forms::Padding(0, 25, 0, 0);
	schoolDay->BorderStyle = System::Windows::Forms::BorderStyle::None;
	schoolDay->BackColor = treeBox->BackColor;
	treeBox->Controls->Add(schoolDay);
	selectedsSchoolDay.selectedDay = nextSchoolDay;
	treeBox->Text = "������ �" + selectedsSchoolDay.groupNumber + " " + stoS(selectedsSchoolDay.selectedDay.day);
	treeBox->Update();
}
void KursProjectTimetable::MainForm::addFaculty(int facultyNumber) {
	Faculty faculty;
	faculty.number = facultyNumber;
	faculties.push_end(faculty);
	KursProjectTimetable::MainForm::facultiesListPaint();
}
void KursProjectTimetable::MainForm::addCourse(int facultyNumber, int courseNumber) {
	if (faculties.is_empty()) {
		MessageBox::Show(this, "���������� ������ �����������!");
		return;
	};
	Course course = Course(courseNumber);
	try
	{
		faculties.getByValue(Faculty(facultyNumber)).courses.push_end(course);
	}
	catch (const std::exception&)
	{
		MessageBox::Show(this, "�������� ����� ����������!");
	}
	KursProjectTimetable::MainForm::facultiesListPaint();
}
void KursProjectTimetable::MainForm::addGroup(int facultyNumber, int courseNumber, int groupNumber) {
	if (faculties.is_empty()) {
		MessageBox::Show(this, "���������� ������ �����������!");
		return;
	};
	
	Faculty* faculty;
	try
	{
		faculty = &faculties.getByValue(Faculty(facultyNumber));
	}
	catch (const std::exception&)
	{
		MessageBox::Show(this, "�������� ����� ����������!");
		return;
	}
	if (faculty->courses.is_empty()) {
		MessageBox::Show(this, "���������� ������ ������ ���������� �" + facultyNumber + "!");
		return;
	}
	Course* course;
	try
	{
		course = &faculty->courses.getByValue(Course(courseNumber));
	}
	catch (const std::exception&)
	{
		MessageBox::Show(this, "�������� ����� �����!");
		return;
	}
	course->groups.push_end(Group(groupNumber));
	KursProjectTimetable::MainForm::facultiesListPaint();
}
void KursProjectTimetable::MainForm::addSchoolDayNumber(int facultyNumber, int courseNumber, int groupNumber, int schoolDayNumber) {
	if (faculties.is_empty()) {
		MessageBox::Show(this, "���������� ������ �����������!");
		return;
	};

	Faculty* faculty;
	try
	{
		faculty = &faculties.getByValue(Faculty(facultyNumber));
	}
	catch (const std::exception&)
	{
		MessageBox::Show(this, "�������� ����� ����������!");
		return;
	}
	if (faculty->courses.is_empty()) {
		MessageBox::Show(this, "���������� ������ ������ ���������� �" + facultyNumber + "!");
		return;
	}
	Course* course;
	try
	{
		course = &faculty->courses.getByValue(Course(courseNumber));
	}
	catch (const std::exception&)
	{
		MessageBox::Show(this, "�������� ����� �����!");
		return;
	}
	if (course->groups.is_empty()) {
		MessageBox::Show(this, "���������� ������ ����� ���������� �" + facultyNumber + " " + "����� �" + courseNumber);
		return;
	}
	Group* group;
	try
	{
		group = &course->groups.getByValue(Group(groupNumber));
	}
	catch (const std::exception&)
	{
		MessageBox::Show(this, "�������� ����� ������!");
		return;
	}
	group->timetable.schoolDays.push_end(SchoolDay(schoolDayNumber));
	KursProjectTimetable::MainForm::facultiesListPaint();
}
void KursProjectTimetable::MainForm::addLesson(int facultyNumber, int courseNumber, int groupNumber, int schoolDayNumber, System::String^ subjectName, System::String^ teacherName, int lessonNumber, int audienceNumber) {
	if (faculties.is_empty()) {
		MessageBox::Show(this, "���������� ������ �����������!");
		return;
	};

	Faculty* faculty;
	try
	{
		faculty = &faculties.getByValue(Faculty(facultyNumber));
	}
	catch (const std::exception&)
	{
		MessageBox::Show(this, "�������� ����� ����������!");
		return;
	}
	if (faculty->courses.is_empty()) {
		MessageBox::Show(this, "���������� ������ ������ ���������� �" + facultyNumber + "!");
		return;
	}
	Course* course;
	try
	{
		course = &faculty->courses.getByValue(Course(courseNumber));
	}
	catch (const std::exception&)
	{
		MessageBox::Show(this, "�������� ����� �����!");
		return;
	}
	if (course->groups.is_empty()) {
		MessageBox::Show(this, "���������� ������ ����� ���������� �" + facultyNumber + " " + "����� �" + courseNumber);
		return;
	}
	Group* group;
	try
	{
		group = &course->groups.getByValue(Group(groupNumber));
	}
	catch (const std::exception&)
	{
		MessageBox::Show(this, "�������� ����� ������!");
		return;
	}
	if (group->timetable.schoolDays.is_empty()) {
		MessageBox::Show(this, "���������� ���������� ������ �" + groupNumber + " ����� �" + courseNumber + " " + " ���������� �" + facultyNumber);
		return;
	}
	SchoolDay* schoolDay;
	try
	{
		schoolDay = &group->timetable.schoolDays.getByValue(SchoolDay(schoolDayNumber));
	}
	catch (const std::exception&)
	{
		MessageBox::Show(this, "�������� ����� ��� ������!");
		return;
	}
	schoolDay->lessons.push_end(Lesson(Stos(subjectName), audienceNumber, Stos(teacherName), lessonNumber));
	KursProjectTimetable::MainForm::facultiesListPaint();
}
void jParse(nlohmann::json_abi_v3_11_2::json& j_complete, SLList<Faculty>& faculties)
{
	for (auto& j_faculty : j_complete.items())
	{
		Faculty faculty;
		faculty.number = j_faculty.value()["facultynumber"].get<int>();
		SLList<Course> courses;
		for (auto& j_course : j_faculty.value()["courses"].items()) {
			Course course;
			course.number = j_course.value()["coursenumber"].get<int>();
			DLList<Group> groups;
			for (auto& j_group : j_course.value()["groups"].items())
			{
				Group group;
				group.number = j_group.value()["groupnumber"].get<int>();
				Timetable timetable;
				CircularList<SchoolDay> schoolDays;
				for (auto& j_timetable : j_group.value()["timetable"].items())
				{
					SchoolDay schoolDay;
					schoolDay.day = j_timetable.value()["day"].get<std::string>();
					SLList<Lesson> lessons;
					for (auto& j_lesson : j_timetable.value()["lessons"].items())
					{
						Lesson lesson;
						lesson.lessonNumber = j_lesson.value()["lessonnumber"].get<int>();
						lesson.audienceNumber = j_lesson.value()["audiencenumber"].get<int>();
						lesson.subjectName = j_lesson.value()["subjectname"].get<std::string>();
						lesson.teacherName = j_lesson.value()["teachername"].get<std::string>();
						lessons.push_end(lesson);
					}
					schoolDay.lessons = lessons;
					schoolDays.push_end(schoolDay);
				}
				//schoolDays.sort();
				timetable.schoolDays = schoolDays;
				group.timetable = timetable;
				groups.push_end(group);
			}
			groups.sort();
			course.groups = groups;
			courses.push_end(course);
		}
		courses.sort();
		faculty.courses = courses;
		faculties.push_end(faculty);
	}
	faculties.sort();
}
