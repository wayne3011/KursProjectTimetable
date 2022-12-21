#pragma once
#include "list.h"
#include "circular_list.h"
#include "doubly_linked_list.h"

struct Lesson {
	std::string subjectName;//название предмета
	int audienceNumber;//номер аудитории
	std::string teacherName;//имя преподавателя
	int lessonNumber;//номер занятия
	Lesson() {};
	Lesson(std::string subjectName, int audienceNumber, std::string teacherName, int lessonNumber) {//иницилизация всей структуры
		this->audienceNumber = audienceNumber;
		this->lessonNumber = lessonNumber;
		this->subjectName = subjectName;
		this->teacherName = teacherName;
	};
	Lesson(int lessonNumber) {//иницилизация структуры для поиска по номеру занятия
		this->audienceNumber = -1;
		this->lessonNumber = lessonNumber;
		this->subjectName = "";
		this->teacherName = "";
	}
	bool operator!=(Lesson other) {
		return this->lessonNumber != other.lessonNumber;
	}
	bool operator>(Lesson other) {
		return this->lessonNumber > other.lessonNumber;
	}
	bool operator==(Lesson other) {
		return this->lessonNumber == other.lessonNumber;
	}
};
struct SchoolDay {
	std::string day;//название дня недели
	SLList<Lesson> lessons;//список занятий
	int numberWeekDay = -1;//номер дня недели
	SchoolDay() {
		day = "";
		lessons = SLList<Lesson>();
	};

	SchoolDay(int numberOfWeekDay) {//иницилизация по номеру дня недели
		std::string week[7] = { "Понедельник", "Вторник", "Среда", "Четверг", "Пятница", "Суббота", "Воскресенье" };
		if (numberOfWeekDay >= 0 && numberOfWeekDay < 7) {
			this->day = week[numberOfWeekDay];
			this->numberWeekDay = numberOfWeekDay;
		}
		else this->day = "UNKNOWN";
	}
	SchoolDay(std::string day) {//иницилизация по названию дня недели
		std::string week[7] = { "Понедельник", "Вторник", "Среда", "Четверг", "Пятница", "Суббота", "Воскресенье" };
		for (size_t i = 0; i < 7; i++)
		{
			if (day == week[i]) {
				this->numberWeekDay = i;
				this->day = day;
				return;
			}
		}
		this->day = "UNKNOWN";
	}
	bool operator!=(SchoolDay other) {
		return this->numberWeekDay != other.numberWeekDay;
	}
	bool operator>(SchoolDay other) {
		return this->numberWeekDay > other.numberWeekDay;
	};
	bool operator==(SchoolDay other) {
		return this->numberWeekDay == other.numberWeekDay;
	}
};
struct Timetable {
	CircularList<SchoolDay> schoolDays;//список учебных дней
	Timetable(CircularList<SchoolDay> schoolDays)
	{
		this->schoolDays = schoolDays;
	}
	Timetable()
	{

	}
};
struct Group {
	int number;//номер группы
	Timetable timetable;//расписание
	Group() {};
	Group(int number) {
		this->number = number;
	}
	bool operator>(Group other) {
		return this->number > other.number;
	}
	bool operator!=(Group other) {
		return this->number != other.number;
	}
	bool operator==(Group other) {
		return this->number == other.number;
	}
};
struct Course {
	int number;//номер курса
	DLList<Group> groups;//список групп
	Course() {};
	Course(int number) {
		this->number = number;
	};
	bool operator< (Course Value) {
		return this->number < Value.number;
	}
	bool operator>(Course other) {
		return this->number > other.number;
	}
	bool operator!=(Course other) {
		return this->number != other.number;
	}
	bool operator==(Course other) {
		return this->number == other.number;
	}
};
struct Faculty
{
	int number;//номер факультета
	SLList<Course> courses;//список курсов
	Faculty() {};
	Faculty(int number) {
		this->number = number;
	};
	bool operator>(Faculty other) {
		return this->number > other.number;
	}
	bool operator==(Faculty other) {
		return this->number == other.number;
	}
	bool operator!=(Faculty other) {
		return this->number != other.number;
	}
};

