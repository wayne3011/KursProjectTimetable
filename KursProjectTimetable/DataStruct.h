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
};
struct Course {
	int number;
	DLList<Group> groups;
	Course() {};
	Course(int number) {
		this->number = number;
	};
	bool operator  < (Course Value) {
		return this->number < Value.number;
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
};

