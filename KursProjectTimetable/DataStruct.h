#pragma once
#include "list.h"
#include "circular_list.h"
#include "doubly_linked_list.h"

struct Lesson {
	std::string subjectName;
	int audienceNumber;
	std::string teacherName;
	int lessonNumber;
	Lesson() {};
	Lesson(std::string subjectName, int audienceNumber, std::string teacherName, int lessonNumber) {
		this->audienceNumber = audienceNumber;
		this->lessonNumber = lessonNumber;
		this->subjectName = subjectName;
		this->teacherName = teacherName;
	};
	bool operator!=(Lesson other) {
		return this->lessonNumber != other.lessonNumber;
	}
	bool operator>(Lesson other) {
		return this->lessonNumber > other.lessonNumber;
	}
};
struct SchoolDay {
	std::string day;
	SLList<Lesson> lessons;
	SchoolDay() {};
	SchoolDay(std::string day)
	{
		this->day = day;
	}
	SchoolDay(int numberOfWeekDay) {
		std::string week[7] = { "Понедельник", "Вторник", "Среда", "Четверг", "Пятница", "Суббота", "Воскресенье" };
		this->day = week[numberOfWeekDay-1];
	}
	bool operator!=(SchoolDay other) {
		return this->day != other.day;
	}
	bool operator>(SchoolDay other) {
		return this->day > other.day;
	};
};
struct Timetable {
	CircularList<SchoolDay> schoolDays;
	Timetable(CircularList<SchoolDay> schoolDays)
	{
		this->schoolDays = schoolDays;
	}
	Timetable()
	{

	}
};
struct Group {
	int number;
	Timetable timetable;
	Group()
	{

	}
	Group(int number) {
		this->number = number;
	}
	bool operator>(Group other) {
		return this->number > other.number;
	}
	bool operator!=(Group other) {
		return this->number != other.number;
	}
};
struct Course {
	int number;
	DLList<Group> groups;
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
};
struct Faculty
{
	int number;
	SLList<Course> courses;
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

