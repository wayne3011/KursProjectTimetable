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
void jParse(nlohmann::json_abi_v3_11_2::json& j_complete, SLList<Faculty>& faculties);
System::Windows::Forms::TreeView^ schoolDayTreePaint(SchoolDay schoolDay);
void KursProjectTimetable::MainForm::loadFromFile(String^ fileName)
{
	
	const char* fileName_str = (const char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(fileName)).ToPointer();
	std::ifstream fin(fileName_str);
	nlohmann::json j_complete = nlohmann::json::parse(fin);
	jParse(j_complete, faculties);

	TabControl^ tabControl = gcnew(TabControl);
	tabControl->Location = System::Drawing::Point(3, 48);
	tabControl->Name = L"tabControl";
	tabControl->SelectedIndex = 0;
	tabControl->Size = System::Drawing::Size(548, 496);
	tabControl->TabIndex = 1;

	for (size_t i = 0; i < faculties.getSize(); i++)
	{
		TabPage^ faculty = gcnew(TabPage);
		faculty->Text = "Факультет №" + faculties[i].number;
		TreeView^ courses = gcnew(TreeView);
		courses->NodeMouseClick += gcnew System::Windows::Forms::TreeNodeMouseClickEventHandler(this, &MainForm::treeView_NodeClick);
		courses->Size = System::Drawing::Size(tabControl->Size.Width-10, tabControl->Size.Height-27);
		for (size_t j = 0; j < faculties[i].courses.getSize(); j++)
		{
			TreeNode^ course = gcnew(TreeNode);
			course->Text = "Курс №" + faculties[i].courses[j].number;
			for (size_t k = 0; k < faculties[i].courses[j].groups.getSize(); k++)
			{
				TreeNode^ group = gcnew(TreeNode);
				group->Text = "Группа №" + faculties[i].courses[j].groups[k].number;
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
	this->tableLayoutPanel1->Controls->Add(tabControl,0,1);
}
void KursProjectTimetable::MainForm::timetablePaint(int facultyNumber, int courseNumber, int groupNumber, int dayNumber) {
	TreeView^ schoolDay = schoolDayTreePaint(faculties[facultyNumber].courses[courseNumber].groups[groupNumber].timetable.schoolDays[dayNumber]);
	schoolDay->Name = L"schoolDayTree";
	schoolDay->Size = System::Drawing::Size(treeBox->Width, treeBox->Height);
	schoolDay->Margin = System::Windows::Forms::Padding(0, 25, 0, 0);
	treeBox->Controls->Add(schoolDay);
	treeBox->Update();
}
System::Windows::Forms::TreeView^ schoolDayTreePaint(SchoolDay schoolDay) {
	TreeView^ schoolDayTree = gcnew TreeView;
	for (size_t i = 0; i < schoolDay.lessons.getSize(); i++)
	{
		TreeNode^ lesson = gcnew TreeNode;
		lesson->Text = stoS(schoolDay.lessons[i].SubjectName);
		TreeNode^ audienceNumber = gcnew TreeNode;
		audienceNumber->Text = "Аудитория №" + schoolDay.lessons[i].audienceNumber;
		TreeNode^ teacherName = gcnew TreeNode;
		teacherName->Text = "Имя преподавателя:" + stoS(schoolDay.lessons[i].TeacherName);
		lesson->Nodes->Add(audienceNumber);
		lesson->Nodes->Add(teacherName);
		schoolDayTree->Nodes->Add(lesson);
	}
	return schoolDayTree;
};
void KursProjectTimetable::MainForm::nextDayPaint() {
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
						lesson.audienceNumber = j_lesson.value()["audiencenumber"].get<int>();
						lesson.SubjectName = j_lesson.value()["subjectname"].get<std::string>();
						lesson.TeacherName = j_lesson.value()["teachername"].get<std::string>();
						lessons.push_end(lesson);
					}
					schoolDay.lessons = lessons;
					schoolDays.push_end(schoolDay);
				}
				timetable.schoolDays = schoolDays;
				group.timetable = timetable;
				groups.push_end(group);
			}
			course.groups = groups;
			courses.push_end(course);
		}
		faculty.courses = courses;
		faculties.push_end(faculty);
	}
}
