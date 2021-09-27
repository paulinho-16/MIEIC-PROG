#include <iostream>
#include <fstream>
#include <vector>
#include "Student.h"
using namespace std;

int Student::weightShortExam = 20;
int Student::weightProject = 30;
int Student::weightExam = 50;

Student::Student()
{
	this->code = "up000000000";
	this->name = "No Name";
	this->shortExam = 0;
	this->project = 0;
	this->exam = 0;
	this->finalGrade = 0;
}

Student::Student(const string &code, const string &name)
{
	this->code = code;
	this->name = name;
	this->shortExam = 0;
	this->project = 0;
	this->exam = 0;
	this->finalGrade = 0;
}

void Student::setGrades(double shortExam, double project, double exam)
{
	this->shortExam = shortExam;
	this->project = project;
	this->exam = exam;
	this->finalGrade = int(round(weightShortExam / 100.0 * shortExam + weightProject / 100.0 * project + weightExam / 100.0 * exam));
}

string Student::getCode() const
{
	return code;
}

string Student::getName() const
{
	return name;
}

double Student::getShortExam() const
{
	return shortExam;
}

double Student::getProject() const
{
	return project;
}

double Student::getExam() const
{
	return exam;
}

int Student::getFinalGrade() const
{
	return finalGrade;
}

bool Student::isApproved() const
{
	if (finalGrade >= 9.5)
		return true;
	return false;
}

void Student::readStudentData()
{
	cout << "\nStudent Code? ";
	cin >> code;
	cin.ignore(1000, '\n');
	cout << "Student Name? ";
	getline(cin, name);
	cout << "Short exam grade? ";
	cin >> shortExam;
	cout << "Project grade? ";
	cin >> project;
	cout << "Exam Grade? ";
	cin >> exam;
	setGrades(shortExam, project, exam);
}
