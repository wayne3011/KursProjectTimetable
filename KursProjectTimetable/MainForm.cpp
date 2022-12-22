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
    KursProjectTimetable::MainForm form;//создаём объект главной формы приложения
    Application::Run(% form);//запускаем приложение с главной формой
}
SLList<Faculty> faculties;//глобальная переменная для хранения корня базы данных -  списка факультетов
struct SelectedSchoolDay {//текущий выбранный день недели с расписанием
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
//парсинг json-файла с расписанием и заполнение соотвествующих полей базы данных
void jParse(nlohmann::json_abi_v3_11_2::json& j_complete, SLList<Faculty>& faculties);
//функция иницилизации расписания в конкретный учебный день
System::Windows::Forms::TreeView^ schoolDayTreePaint(SchoolDay& schoolDay);
void KursProjectTimetable::MainForm::loadFromFile(String^ fileName)//загрузка расписания из файла
{
	faculties.clear();//очищаем старую базу данных
	const char* fileName_str = (const char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(fileName)).ToPointer();
	std::ifstream fin(fileName_str);
	nlohmann::json j_complete = nlohmann::json::parse(fin);//считываем данные с jsona
	jParse(j_complete, faculties);//парсим json и записываем данные в базу данных
	facultiesListPaint();//отрисовываем новый список факультетов
}
void KursProjectTimetable::MainForm::outInFile(String^ path) {//выгрузка расписаний в файл
	std::ofstream fout(Stos(path));
	nlohmann::ordered_json json_faculties = nlohmann::ordered_json();//создаем json-запись со списком факультетов

	for (size_t i = 0; i < faculties.getSize(); i++)//заполняем json со списком факультетов
	{
		nlohmann::ordered_json json_faculty = nlohmann::ordered_json();//создаём отдельный json каждого факультет

		json_faculty["facultynumber"] = faculties[i].number;
		nlohmann::ordered_json json_courses;//создаем json-запись со списком курсов

		for (size_t j = 0; j < faculties[i].courses.getSize(); j++)//заполняем json со списком курсов
		{
			nlohmann::json json_course;//создаём отдельный json каждого курса
			json_course["coursenumber"] = faculties[i].courses[j].number;
			nlohmann::ordered_json json_groups;//создаем json-запись со списком групп
			for (size_t k = faculties[i].courses[j].groups.getSize() - 1; k != -1; k--)//заполняем json со списком групп
			{
				nlohmann::json json_group;////создаём отдельный json каждой группы
				json_group["groupnumber"] = faculties[i].courses[j].groups[k].number;
				nlohmann::json json_timetable;//создаем json-запись расписание со списком учебных дней 
				for (size_t l = 0; l < faculties[i].courses[j].groups[k].timetable.schoolDays.GetSize(); l++)
				{
					nlohmann::json json_schoolDay;//создаём отдельный json для каждого дня
					json_schoolDay["day"] = cp2utf(faculties[i].courses[j].groups[k].timetable.schoolDays[l].day.c_str());
					for (size_t f = 0; f < faculties[i].courses[j].groups[k].timetable.schoolDays[l].lessons.getSize(); f++)
					{
						nlohmann::ordered_json json_lesson;//создаём отдельный json для занятия
						//заполняем поля записи занятия
						json_lesson["audiencenumber"] = faculties[i].courses[j].groups[k].timetable.schoolDays[l].lessons[f].audienceNumber;
						json_lesson["subjectname"] = cp2utf(faculties[i].courses[j].groups[k].timetable.schoolDays[l].lessons[f].subjectName.c_str());
						json_lesson["teachername"] = cp2utf(faculties[i].courses[j].groups[k].timetable.schoolDays[l].lessons[f].teacherName.c_str());
						json_lesson["lessonnumber"] = faculties[i].courses[j].groups[k].timetable.schoolDays[l].lessons[f].lessonNumber;
						json_schoolDay["lessons"].push_back(json_lesson);//добавляем занятие в список занятий в учебный день
					}
					json_group["timetable"].push_back(json_schoolDay);//добавляем учебный день в список с расписанием группы
				}
				json_course["groups"].push_back(json_group);//добавляем группу в список групп курса
			}
			json_faculty["courses"].push_back(json_course);//добавляем курс группу в список курсов факультета
		}
		json_faculties.push_back(json_faculty);//добавляем факультет в список факультетов
	}
	fout << json_faculties;//выводим финальную json-запись в файл
	fout.close();
}
//отрисовка списка факультетов
void KursProjectTimetable::MainForm::facultiesListPaint()
{
	faculties.sort();//перед отрисовкой списка факультетов сортируем его для вывода по порядку
	this->tableLayoutPanel1->Controls->RemoveByKey("tabControl");//удаялем прошлый список факультета из представления
	TabControl^ tabControl = gcnew(TabControl);//создаём новый визуальный элемент со списком факультетов
	tabControl->Location = System::Drawing::Point(3, 48);
	tabControl->Name = L"tabControl";
	tabControl->SelectedIndex = 0;
	tabControl->Size = System::Drawing::Size(548, 496);
	tabControl->TabIndex = 1;

	for (size_t i = 0; i < faculties.getSize(); i++)//для каждого факультета
	{
		TabPage^ faculty = gcnew(TabPage);//создаём вкладку для списка факультетов
		faculty->Text = "Факультет №" + faculties[i].number;
		TreeView^ courses = gcnew(TreeView);//создаём вложенное во вкладку дерево, где узлы верхнего уровня - курсы
		courses->NodeMouseClick += gcnew System::Windows::Forms::TreeNodeMouseClickEventHandler(this, &MainForm::treeView_NodeClick);//привязываем событие нажатия на узел дерева
		courses->Size = System::Drawing::Size(tabControl->Size.Width - 10, tabControl->Size.Height - 27);
		for (size_t j = 0; j < faculties[i].courses.getSize(); j++)//для каждого курса
		{
			TreeNode^ course = gcnew(TreeNode);//создаём узел с курсом
			course->Text = "Курс №" + faculties[i].courses[j].number;//текст, отображаемый в узле курса
			for (size_t k = 0; k < faculties[i].courses[j].groups.getSize(); k++)//для каждой группы
			{
				TreeNode^ group = gcnew(TreeNode);//создаём узел с группой
				group->Text = "Группа №" + faculties[i].courses[j].groups[k].number;//текст, отображаемый в узле группы
				for (size_t f = 0; f < faculties[i].courses[j].groups[k].timetable.schoolDays.GetSize(); f++)//для каждого учебного дня
				{
					TreeNode^ day = gcnew(TreeNode);//создаём узел с учебным днем
					day->Text = stoS(faculties[i].courses[j].groups[k].timetable.schoolDays[f].day);//текст, отображаемый в узле учебного дня
					day->Name = "WeekDay";//название визуального элемента - узла с учебным днём
					group->Nodes->Add(day);//к узлу группы в потомки записываем узел учебного дня
				}
				course->Nodes->Add(group);//к узлу курса в потомки записываем узел группы
			}
			courses->Nodes->Add(course);//добавляем узел курса в дерево с курсами отдельного факультета
		}
		faculty->Controls->Add(courses);//добавляем дерево с курсами на вкладку отдельного факультета
		tabControl->Controls->Add(faculty);//добавляем вкладку факультета к списку всех факультетов
	}
	this->tableLayoutPanel1->Controls->Add(tabControl, 0, 1);//размещаем спиок факультетов на главной форме
}
void KursProjectTimetable::MainForm::timetablePaint(int facultyNumber, int courseNumber, int groupNumber, int dayNumber) {//отрисовка расписания
	TreeView^ schoolDay = schoolDayTreePaint(faculties[facultyNumber].courses[courseNumber].groups[groupNumber].timetable.schoolDays[dayNumber]);//создаём дерево со списком занятий
	treeBox->Controls->RemoveByKey("schoolDayTree");//удаляем старое дерево с расписанием														//иницилизируем его функцией для отрисовки учебного дня
	schoolDay->Name = L"schoolDayTree";
	schoolDay->Size = System::Drawing::Size(treeBox->Width - 4, treeBox->Height - 15);
	schoolDay->Location = System::Drawing::Point(2, 12);
	schoolDay->Margin = System::Windows::Forms::Padding(0, 25, 0, 0);
	schoolDay->BorderStyle = System::Windows::Forms::BorderStyle::None;
	schoolDay->BackColor = treeBox->BackColor;
	treeBox->Controls->Add(schoolDay);//добавляем новое дерево в блок с расписанием
	//обновляем выбранный в расписании день
	selectedsSchoolDay = SelectedSchoolDay(facultyNumber, courseNumber, groupNumber, faculties[facultyNumber].courses[courseNumber].groups[groupNumber].timetable.schoolDays[dayNumber]);
	treeBox->Text = "Группа №" + (groupNumber+1) + " " + stoS(selectedsSchoolDay.selectedDay.day);
}

System::Windows::Forms::TreeView^ schoolDayTreePaint(SchoolDay& schoolDay) {//функция иницилизации расписания в конкретный учебный день
	
	TreeView^ schoolDayTree = gcnew TreeView;//создаём дерево с распианием для учебного дня, где верхние узлы - занятия
	schoolDay.lessons.sort();
	for (size_t i = 0; i < schoolDay.lessons.getSize(); i++)
	{
		TreeNode^ lesson = gcnew TreeNode;//создаём узел с занятием 
		lesson->Text = schoolDay.lessons[i].lessonNumber + "." + stoS(schoolDay.lessons[i].subjectName);//подписываем узел с занятием названием предмета
		//вложенные узлы занятия определяем полями структуры занятия
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
void KursProjectTimetable::MainForm::nextDayPaint() {//переход на следуюший день недели
	//получаем следующий от выбранного элемента день
	SchoolDay nextSchoolDay = faculties[selectedsSchoolDay.facultyNumber].courses[selectedsSchoolDay.courseNumber].groups[selectedsSchoolDay.groupNumber].timetable.schoolDays.getNext(selectedsSchoolDay.selectedDay);
	TreeView^ schoolDay = schoolDayTreePaint(nextSchoolDay);//иницилизируем дерево со списком занятий
	schoolDay->Name = L"schoolDayTree";
	schoolDay->Size = System::Drawing::Size(treeBox->Width - 4, treeBox->Height - 15);
	schoolDay->Location = System::Drawing::Point(2, 12);
	schoolDay->Margin = System::Windows::Forms::Padding(0, 25, 0, 0);
	schoolDay->BorderStyle = System::Windows::Forms::BorderStyle::None;
	schoolDay->BackColor = treeBox->BackColor;
	treeBox->Controls->Add(schoolDay);//добавляем дерево с занятиями на группу элементов с расписанием
	selectedsSchoolDay.selectedDay = nextSchoolDay;
	treeBox->Text = "Группа №" + (selectedsSchoolDay.groupNumber+1) + " " + stoS(selectedsSchoolDay.selectedDay.day);
}
void KursProjectTimetable::MainForm::previousDayPaint() {//переход на предыдущий день недели
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
}
//добавление нового факультета
void KursProjectTimetable::MainForm::addFaculty(int facultyNumber) {
	//создаём новую запись с факультетом
	Faculty faculty;
	faculty.number = facultyNumber;
	faculties.push_end(faculty);//добавляем новую запись в базу данных
	faculties.sort();
	KursProjectTimetable::MainForm::facultiesListPaint();//отрисовываем список факультетов заново
}
void KursProjectTimetable::MainForm::deleteFaculty(int facultyNumber) {//удаление факультета
	if (faculties.is_empty()) {//проверем не пустой ли список факультетов
		MessageBox::Show(this, "Отсутсвует список факультетов!");
		return;
	};
	try
	{
		faculties.removeByValue(Faculty(facultyNumber));//удаляем факультет
	}
	catch (const std::exception&)//если не получилось найти номер факультета с полученным для удаления значением
	{
		MessageBox::Show(this, "Неверный номер факультета!");
		return;
	}
	
	KursProjectTimetable::MainForm::facultiesListPaint();//отрисовываем список факультетов заново
}
void KursProjectTimetable::MainForm::deleteCourse(int facultyNumber, int courseNumber) {//удаление курса
	if (faculties.is_empty()) {//проверем не пустой ли список факультетов
		MessageBox::Show(this, "Отсутсвует список факультетов!");
		return;
	};
	Faculty* faculty;
	try//пытаемся получить ссылку на нужный факультет, где находится удаляемый курс
	{
		faculty = &faculties.getByValue(Faculty(facultyNumber));
	}
	catch (const std::exception&)
	{
		MessageBox::Show(this, "Неверный номер факультета!");
		return;
	}
	try//пытаемся удалить курс с заданным пользователем для удаления значения
	{
		faculty->courses.removeByValue(Course(courseNumber));
	}
	catch (const std::exception&)
	{
		MessageBox::Show(this, "Неверный номер курса!");
		return;
	}
	KursProjectTimetable::MainForm::facultiesListPaint();//отрисовываем список факультетов заново
}
void KursProjectTimetable::MainForm::addCourse(int facultyNumber, int courseNumber) {//добавление нового курса
	if (faculties.is_empty()) {//проверем не пустой ли список факультетов
		MessageBox::Show(this, "Отсутсвует список факультетов!");
		return;
	};
	Faculty* faculty;
	try
	{
		faculty = &faculties.getByValue(Faculty(facultyNumber));//получаем ссылку на факультет, в который нужно добавить курс
	}
	catch (const std::exception&)
	{
		MessageBox::Show(this, "Неверный номер факультета!");
	}
	faculty->courses.push_end(Course(courseNumber));//добавляем новый курс в список курсов факультета
	faculty->courses.sort();
	KursProjectTimetable::MainForm::facultiesListPaint();//отрисовываем список факультетов заново
}

///
///далее функции удаления и добавления элемента имеют схожую реализацию
/// 
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
	}
	catch (const std::exception&)
	{
		MessageBox::Show("Неверный номер пары!");
	}
	
	KursProjectTimetable::MainForm::timetablePaint(faculties.getIndexByValue(*faculty),faculty->courses.getIndexByValue(*course),course->groups.getIndexByValue(*group),group->timetable.schoolDays.getIndexByValue(*schoolDay));
};
//парсинг json-файла с расписанием и заполнение соотвествующих полей базы данных
void jParse(nlohmann::json_abi_v3_11_2::json& j_complete, SLList<Faculty>& faculties)
{
	for (auto& j_faculty : j_complete.items())//проходим весь список факультетов
	{
		Faculty faculty;//создаём запись факультета
		faculty.number = j_faculty.value()["facultynumber"].get<int>();//получаем номер факультета
		SLList<Course> courses;//создаём список курсов для факультета
		for (auto& j_course : j_faculty.value()["courses"].items()) {//проходим весь список курсов факультета
			Course course;//создаём запись курса
			course.number = j_course.value()["coursenumber"].get<int>();//получаем номер курса
			DLList<Group> groups;//создаём список групп для курса
			for (auto& j_group : j_course.value()["groups"].items())//проходим весь список групп курса
			{
				Group group;//создаём запись группы
				
				group.number = j_group.value()["groupnumber"].get<int>();//получаем номер группы
				Timetable timetable;//создаём расписание для группы
				CircularList<SchoolDay> schoolDays;//создаём список учебных дней для группы
				for (auto& j_timetable : j_group.value()["timetable"].items())//проходим весь список учебных дней группы
				{
					SchoolDay schoolDay = SchoolDay(utf2cp(j_timetable.value()["day"].get<std::string>()));//получаем название учебного дня для группы
					 
					SLList<Lesson> lessons;//создаём список занятий для учебного дня
					for (auto& j_lesson : j_timetable.value()["lessons"].items())
					{
						//создаём объект занятия и заполняем его поля
						Lesson lesson;
						lesson.lessonNumber = j_lesson.value()["lessonnumber"].get<int>();
						lesson.audienceNumber = j_lesson.value()["audiencenumber"].get<int>();
						lesson.subjectName = utf2cp(j_lesson.value()["subjectname"].get<std::string>());
						lesson.teacherName = utf2cp(j_lesson.value()["teachername"].get<std::string>());
						lessons.push_end(lesson);//добавляем занятие в список занятий
					}
					
					schoolDay.lessons = lessons;//заполняем поле списка занятий иницилизированным списком
					schoolDays.push_end(schoolDay);//добавляем учбеный день в список учебных дней
				}
				schoolDays.sort();//сортируем список учебных дней
				timetable.schoolDays = schoolDays;////заполняем поле расписания списком учебных дней
				group.timetable = timetable;//заполняем поле расписание группы расписанием
				groups.push_end(group);//добавляем группу в список групп
			}
			groups.sort();//сортируем список групп
			course.groups = groups;//заполняем поле курса списком групп
			courses.push_end(course);//добавляем курс в список курсов
		}
		courses.sort();//сортируем список курсов
		faculty.courses = courses;//заполняем поле списка курсов новым списком курсов
		faculties.push_end(faculty);//добавляем полученный факультет в список факультетов
	}
	faculties.sort();//сортируем список факультетов
}
