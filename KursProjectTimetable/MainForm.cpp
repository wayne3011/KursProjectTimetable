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
System::Windows::Forms::TreeView^ schoolDayTreePaint(SchoolDay& schoolDay);
void KursProjectTimetable::MainForm::loadFromFile(String^ fileName)
{
	faculties.clear();
	const char* fileName_str = (const char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(fileName)).ToPointer();
	std::ifstream fin(fileName_str);
	nlohmann::json j_complete = nlohmann::json::parse(fin);
	jParse(j_complete, faculties);
	facultiesListPaint();
}
void KursProjectTimetable::MainForm::outInFile(String^ path) {
	std::ofstream fout(Stos(path));
	nlohmann::ordered_json json_faculties = nlohmann::ordered_json();

	for (size_t i = 0; i < faculties.getSize(); i++)
	{
		nlohmann::ordered_json json_faculty = nlohmann::ordered_json();

		json_faculty["facultynumber"] = faculties[i].number;
		nlohmann::ordered_json json_courses;

		for (size_t j = 0; j < faculties[i].courses.getSize(); j++)
		{
			nlohmann::json json_course;
			json_course["coursenumber"] = faculties[i].courses[j].number;
			nlohmann::ordered_json json_groups;
			for (size_t k = faculties[i].courses[j].groups.getSize() - 1; k != -1; k--)
			{
				nlohmann::json json_group;
				json_group["groupnumber"] = faculties[i].courses[j].groups[k].number;
				nlohmann::json json_timetable;
				for (size_t l = 0; l < faculties[i].courses[j].groups[k].timetable.schoolDays.GetSize(); l++)
				{
					nlohmann::json json_schoolDay;
					json_schoolDay["day"] = cp2utf(faculties[i].courses[j].groups[k].timetable.schoolDays[l].day.c_str());
					for (size_t f = 0; f < faculties[i].courses[j].groups[k].timetable.schoolDays[l].lessons.getSize(); f++)
					{
						nlohmann::ordered_json json_lesson;
						json_lesson["audiencenumber"] = faculties[i].courses[j].groups[k].timetable.schoolDays[l].lessons[f].audienceNumber;
						json_lesson["subjectname"] = cp2utf(faculties[i].courses[j].groups[k].timetable.schoolDays[l].lessons[f].subjectName.c_str());
						json_lesson["teachername"] = cp2utf(faculties[i].courses[j].groups[k].timetable.schoolDays[l].lessons[f].teacherName.c_str());
						json_lesson["lessonnumber"] = faculties[i].courses[j].groups[k].timetable.schoolDays[l].lessons[f].lessonNumber;
						json_schoolDay["lessons"].push_back(json_lesson);
					}
					json_group["timetable"].push_back(json_schoolDay);
				}
				json_course["groups"].push_back(json_group);
			}
			json_faculty["courses"].push_back(json_course);
		}
		json_faculties.push_back(json_faculty);
	}
	fout << json_faculties;
	fout.close();
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
		faculty->Text = "Факультет №" + faculties[i].number;
		TreeView^ courses = gcnew(TreeView);
		courses->NodeMouseClick += gcnew System::Windows::Forms::TreeNodeMouseClickEventHandler(this, &MainForm::treeView_NodeClick);
		courses->Size = System::Drawing::Size(tabControl->Size.Width - 10, tabControl->Size.Height - 27);
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
					day->Name = "WeekDay";
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
	treeBox->Controls->RemoveByKey("schoolDayTree");
	schoolDay->Name = L"schoolDayTree";
	schoolDay->Size = System::Drawing::Size(treeBox->Width - 4, treeBox->Height - 15);
	schoolDay->Location = System::Drawing::Point(2, 12);
	schoolDay->Margin = System::Windows::Forms::Padding(0, 25, 0, 0);
	schoolDay->BorderStyle = System::Windows::Forms::BorderStyle::None;
	schoolDay->BackColor = treeBox->BackColor;
	treeBox->Controls->Add(schoolDay);
	selectedsSchoolDay = SelectedSchoolDay(facultyNumber, courseNumber, groupNumber, faculties[facultyNumber].courses[courseNumber].groups[groupNumber].timetable.schoolDays[dayNumber]);
	treeBox->Text = "Группа №" + (groupNumber+1) + " " + stoS(selectedsSchoolDay.selectedDay.day);
	treeBox->Update();
}

System::Windows::Forms::TreeView^ schoolDayTreePaint(SchoolDay& schoolDay) {
	
	TreeView^ schoolDayTree = gcnew TreeView;
	schoolDay.lessons.sort();
	for (size_t i = 0; i < schoolDay.lessons.getSize(); i++)
	{
		TreeNode^ lesson = gcnew TreeNode;
		lesson->Text = schoolDay.lessons[i].lessonNumber + "." + stoS(schoolDay.lessons[i].subjectName);
		TreeNode^ audienceNumber = gcnew TreeNode;
		audienceNumber->Text = "Аудитория №" + schoolDay.lessons[i].audienceNumber;
		TreeNode^ teacherName = gcnew TreeNode;
		teacherName->Text = "Имя преподавателя:" + stoS(schoolDay.lessons[i].teacherName);
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
	treeBox->Text = "Группа №" + (selectedsSchoolDay.groupNumber+1) + " " + stoS(selectedsSchoolDay.selectedDay.day);
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
	treeBox->Text = "Группа №" + (selectedsSchoolDay.groupNumber+1) + " " + stoS(selectedsSchoolDay.selectedDay.day);
	treeBox->Update();
}
void KursProjectTimetable::MainForm::addFaculty(int facultyNumber) {
	Faculty faculty;
	faculty.number = facultyNumber;
	faculties.push_end(faculty);
	faculties.sort();
	KursProjectTimetable::MainForm::facultiesListPaint();
}
void KursProjectTimetable::MainForm::deleteFaculty(int facultyNumber) {
	if (faculties.is_empty()) {
		MessageBox::Show(this, "Отсутсвует список факультетов!");
		return;
	};
	try
	{
		faculties.removeByValue(Faculty(facultyNumber));
		faculties.sort();
	}
	catch (const std::exception&)
	{
		MessageBox::Show(this, "Неверный номер факультета!");
		return;
	}
	
	KursProjectTimetable::MainForm::facultiesListPaint();
}
void KursProjectTimetable::MainForm::deleteCourse(int facultyNumber, int courseNumber) {
	if (faculties.is_empty()) {
		MessageBox::Show(this, "Отсутсвует список факультетов!");
		return;
	};
	Faculty faculty;
	try
	{
		faculty = faculties.getByValue(Faculty(facultyNumber));
	}
	catch (const std::exception&)
	{
		MessageBox::Show(this, "Неверный номер факультета!");
		return;
	}
	try
	{
		faculty.courses.removeByValue(Course(courseNumber));
		faculty.courses.sort();
	}
	catch (const std::exception&)
	{
		MessageBox::Show(this, "Неверный номер курса!");
		return;
	}
	KursProjectTimetable::MainForm::facultiesListPaint();
}
void KursProjectTimetable::MainForm::addCourse(int facultyNumber, int courseNumber) {
	if (faculties.is_empty()) {
		MessageBox::Show(this, "Отсутсвует список факультетов!");
		return;
	};
	Course course = Course(courseNumber);
	Faculty faculty;
	try
	{
		faculty = faculties.getByValue(Faculty(facultyNumber));
	}
	catch (const std::exception&)
	{
		MessageBox::Show(this, "Неверный номер факультета!");
	}
	faculty.courses.push_end(course);
	faculty.courses.sort();
	KursProjectTimetable::MainForm::facultiesListPaint();
}
void KursProjectTimetable::MainForm::deleteGroup(int facultyNumber, int courseNumber, int groupNumber) {
	if (faculties.is_empty()) {
		MessageBox::Show(this, "Отсутсвует список факультетов!");
		return;
	};

	Faculty* faculty;
	try
	{
		faculty = &faculties.getByValue(Faculty(facultyNumber));
	}
	catch (const std::exception&)
	{
		MessageBox::Show(this, "Неверный номер факультета!");
		return;
	}
	if (faculty->courses.is_empty()) {
		MessageBox::Show(this, "Отсутсвует список курсов факультета №" + facultyNumber + "!");
		return;
	}
	Course* course;
	try
	{
		course = &faculty->courses.getByValue(Course(courseNumber));
	}
	catch (const std::exception&)
	{
		MessageBox::Show(this, "Неверный номер курса!");
		return;
	}
	try
	{
		course->groups.removeByValue(Group(groupNumber));
		course->groups.sort();
	}
	catch (const std::exception&)
	{
		MessageBox::Show(this, "Неверный номер группы!");
	}
	
	KursProjectTimetable::MainForm::facultiesListPaint();
}
void KursProjectTimetable::MainForm::addGroup(int facultyNumber, int courseNumber, int groupNumber) {
	if (faculties.is_empty()) {
		MessageBox::Show(this, "Отсутсвует список факультетов!");
		return;
	};
	
	Faculty* faculty;
	try
	{
		faculty = &faculties.getByValue(Faculty(facultyNumber));
	}
	catch (const std::exception&)
	{
		MessageBox::Show(this, "Неверный номер факультета!");
		return;
	}
	if (faculty->courses.is_empty()) {
		MessageBox::Show(this, "Отсутсвует список курсов факультета №" + facultyNumber + "!");
		return;
	}
	Course* course;
	try
	{
		course = &faculty->courses.getByValue(Course(courseNumber));
	}
	catch (const std::exception&)
	{
		MessageBox::Show(this, "Неверный номер курса!");
		return;
	}
	course->groups.push_end(Group(groupNumber));
	course->groups.sort();
	KursProjectTimetable::MainForm::facultiesListPaint();
}
void KursProjectTimetable::MainForm::addSchoolDay(int facultyNumber, int courseNumber, int groupNumber, int schoolDayNumber) {
	if (faculties.is_empty()) {
		MessageBox::Show(this, "Отсутсвует список факультетов!");
		return;
	};

	Faculty* faculty;
	try
	{
		faculty = &faculties.getByValue(Faculty(facultyNumber));
	}
	catch (const std::exception&)
	{
		MessageBox::Show(this, "Неверный номер факультета!");
		return;
	}
	if (faculty->courses.is_empty()) {
		MessageBox::Show(this, "Отсутсвует список курсов факультета №" + facultyNumber + "!");
		return;
	}
	Course* course;
	try
	{
		course = &faculty->courses.getByValue(Course(courseNumber));
	}
	catch (const std::exception&)
	{
		MessageBox::Show(this, "Неверный номер курса!");
		return;
	}
	if (course->groups.is_empty()) {
		MessageBox::Show(this, "Отсутсвует список групп факультета №" + facultyNumber + " " + "курса №" + courseNumber);
		return;
	}
	Group* group;
	try
	{
		group = &course->groups.getByValue(Group(groupNumber));
	}
	catch (const std::exception&)
	{
		MessageBox::Show(this, "Неверный номер группы!");
		return;
	}
	group->timetable.schoolDays.push_end(SchoolDay(schoolDayNumber));
	group->timetable.schoolDays.sort();
	KursProjectTimetable::MainForm::facultiesListPaint();
}
void KursProjectTimetable::MainForm::deleteSchoolDay(int facultyNumber, int courseNumber, int groupNumber, int schoolDayNumber) {
	if (faculties.is_empty()) {
		MessageBox::Show(this, "Отсутсвует список факультетов!");
		return;
	};

	Faculty* faculty;
	try
	{
		faculty = &faculties.getByValue(Faculty(facultyNumber));
	}
	catch (const std::exception&)
	{
		MessageBox::Show(this, "Неверный номер факультета!");
		return;
	}
	if (faculty->courses.is_empty()) {
		MessageBox::Show(this, "Отсутсвует список курсов факультета №" + facultyNumber + "!");
		return;
	}
	Course* course;
	try
	{
		course = &faculty->courses.getByValue(Course(courseNumber));
	}
	catch (const std::exception&)
	{
		MessageBox::Show(this, "Неверный номер курса!");
		return;
	}
	if (course->groups.is_empty()) {
		MessageBox::Show(this, "Отсутсвует список групп факультета №" + facultyNumber + " " + "курса №" + courseNumber);
		return;
	}
	Group* group;
	try
	{
		group = &course->groups.getByValue(Group(groupNumber));
	}
	catch (const std::exception&)
	{
		MessageBox::Show(this, "Неверный номер группы!");
		return;
	}
	if (group->timetable.schoolDays.is_empty()) {
		MessageBox::Show(this,"Отсутсвует расписание группы №" + groupNumber +  " факультета №" + facultyNumber + " " + "курса №" + courseNumber);
		return;
	};
	try
	{
		group->timetable.schoolDays.removeByValue(SchoolDay(schoolDayNumber));
		group->timetable.schoolDays.sort();
	}
	catch (const std::exception&)
	{
		MessageBox::Show(this, "Неверный номер дня недели!");
		return;
	}
	KursProjectTimetable::MainForm::facultiesListPaint();
}
void KursProjectTimetable::MainForm::addLesson(int facultyNumber, int courseNumber, int groupNumber, int schoolDayNumber, System::String^ subjectName, System::String^ teacherName, int lessonNumber, int audienceNumber) {
	if (faculties.is_empty()) {
		MessageBox::Show(this, "Отсутсвует список факультетов!");
		return;
	};

	Faculty* faculty;
	try
	{
		faculty = &faculties.getByValue(Faculty(facultyNumber));
	}
	catch (const std::exception&)
	{
		MessageBox::Show(this, "Неверный номер факультета!");
		return;
	}
	if (faculty->courses.is_empty()) {
		MessageBox::Show(this, "Отсутсвует список курсов факультета №" + facultyNumber + "!");
		return;
	}
	Course* course;
	try
	{
		course = &faculty->courses.getByValue(Course(courseNumber));
	}
	catch (const std::exception&)
	{
		MessageBox::Show(this, "Неверный номер курса!");
		return;
	}
	if (course->groups.is_empty()) {
		MessageBox::Show(this, "Отсутсвует список групп факультета №" + facultyNumber + " " + "курса №" + courseNumber);
		return;
	}
	Group* group;
	try
	{
		group = &course->groups.getByValue(Group(groupNumber));
	}
	catch (const std::exception&)
	{
		MessageBox::Show(this, "Неверный номер группы!");
		return;
	}
	if (group->timetable.schoolDays.is_empty()) {
		MessageBox::Show(this, "Отсутсвует расписание группы №" + groupNumber + " Курса №" + courseNumber + " " + " Факультета №" + facultyNumber);
		return;
	}
	SchoolDay* schoolDay;
	try
	{
		schoolDay = &group->timetable.schoolDays.getByValue(SchoolDay(schoolDayNumber));
	}
	catch (const std::exception&)
	{
		MessageBox::Show(this, "Неверный номер дня недели!");
		return;
	}
	schoolDay->lessons.push_end(Lesson(Stos(subjectName), audienceNumber, Stos(teacherName), lessonNumber));
	schoolDay->lessons.sort();
	KursProjectTimetable::MainForm::timetablePaint(faculties.getIndexByValue(*faculty), faculty->courses.getIndexByValue(*course), course->groups.getIndexByValue(*group), group->timetable.schoolDays.getIndexByValue(*schoolDay));
}
void KursProjectTimetable::MainForm::deleteLesson(int facultyNumber, int courseNumber, int groupNumber, int schoolDayNumber, int lessonNumber) {
	if (faculties.is_empty()) {
		MessageBox::Show(this, "Отсутсвует список факультетов!");
		return;
	};

	Faculty* faculty;
	try
	{
		faculty = &faculties.getByValue(Faculty(facultyNumber));
	}
	catch (const std::exception&)
	{
		MessageBox::Show(this, "Неверный номер факультета!");
		return;
	}
	if (faculty->courses.is_empty()) {
		MessageBox::Show(this, "Отсутсвует список курсов факультета №" + facultyNumber + "!");
		return;
	}
	Course* course;
	try
	{
		course = &faculty->courses.getByValue(Course(courseNumber));
	}
	catch (const std::exception&)
	{
		MessageBox::Show(this, "Неверный номер курса!");
		return;
	}
	if (course->groups.is_empty()) {
		MessageBox::Show(this, "Отсутсвует список групп факультета №" + facultyNumber + " " + "курса №" + courseNumber);
		return;
	}
	Group* group;
	try
	{
		group = &course->groups.getByValue(Group(groupNumber));
	}
	catch (const std::exception&)
	{
		MessageBox::Show(this, "Неверный номер группы!");
		return;
	}
	if (group->timetable.schoolDays.is_empty()) {
		MessageBox::Show(this, "Отсутсвует расписание группы №" + groupNumber + " Курса №" + courseNumber + " " + " Факультета №" + facultyNumber);
		return;
	}
	SchoolDay* schoolDay;
	try
	{
		schoolDay = &group->timetable.schoolDays.getByValue(SchoolDay(schoolDayNumber));
	}
	catch (const std::exception&)
	{
		MessageBox::Show(this, "Неверный номер дня недели!");
		return;
	}
	if (schoolDay->lessons.is_empty()) {
		MessageBox::Show(this, "У группы №" + groupNumber + " Курса №" + courseNumber + " Факультета №" + facultyNumber + " и так нет занятий в " + stoS(schoolDay->day));
	}

	try
	{
		schoolDay->lessons.removeByValue(Lesson(lessonNumber));
		schoolDay->lessons.sort();
	}
	catch (const std::exception&)
	{
		MessageBox::Show("Неверный номер пары!");
	}
	
	KursProjectTimetable::MainForm::timetablePaint(faculties.getIndexByValue(*faculty),faculty->courses.getIndexByValue(*course),course->groups.getIndexByValue(*group),group->timetable.schoolDays.getIndexByValue(*schoolDay));
};
void jParse(nlohmann::json_abi_v3_11_2::json& j_complete, SLList<Faculty>& faculties)
{
	
//	Console::Write(stoS(j_complete.dump()));
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
					SchoolDay schoolDay = SchoolDay(utf2cp(j_timetable.value()["day"].get<std::string>()));;
					 
					SLList<Lesson> lessons;
					for (auto& j_lesson : j_timetable.value()["lessons"].items())
					{
						Lesson lesson;
						lesson.lessonNumber = j_lesson.value()["lessonnumber"].get<int>();
						lesson.audienceNumber = j_lesson.value()["audiencenumber"].get<int>();
						lesson.subjectName = utf2cp(j_lesson.value()["subjectname"].get<std::string>());
						lesson.teacherName = utf2cp(j_lesson.value()["teachername"].get<std::string>());
						lessons.push_end(lesson);
					}
					
					schoolDay.lessons = lessons;
					schoolDays.push_end(schoolDay);
					lessons.~SLList();
				}
				schoolDays.sort();
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
