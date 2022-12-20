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
	Lesson(int lessonNumber) {
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
	std::string day;
	SLList<Lesson> lessons;
	int numberWeekDay = -1;
	SchoolDay() {
		day = "";
		lessons = SLList<Lesson>();
	};

	SchoolDay(int numberOfWeekDay) {
		std::string week[7] = { "Понедельник", "Вторник", "Среда", "Четверг", "Пятница", "Суббота", "Воскресенье" };
		if (numberOfWeekDay >= 0 && numberOfWeekDay < 7) {
			this->day = week[numberOfWeekDay];
			this->numberWeekDay = numberOfWeekDay;
		}
			
		else this->day = "UNKNOWN";
	}
	bool operator!=(SchoolDay other) {
		return this->day != other.day;
	}
	bool operator>(SchoolDay other) {
		return this->numberWeekDay > other.numberWeekDay;
	};
	bool operator==(SchoolDay other) {
		return this->day == other.day;
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
	bool operator==(Course other) {
		return this->number == other.number;
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

