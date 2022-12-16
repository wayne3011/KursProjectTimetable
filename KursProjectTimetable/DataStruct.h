#pragma once
#include "list.h"
#include "circular_list.h"
#include "doubly_linked_list.h"

struct Lesson {
	std::string SubjectName;
	int audienceNumber;
	std::string TeacherName;
};
struct SchoolDay {
	std::string day;
	SLList<Lesson> lessons;
	SchoolDay() {};
	SchoolDay(std::string day)
	{
		this->day = day;
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

