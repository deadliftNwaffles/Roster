#pragma once
#include "student.h"

class SecurityStudent : public Student {
public:
	using Student::Student;
	Degree GetDegreeProgram();

private:
	Degree degree = SECURITY;
};

