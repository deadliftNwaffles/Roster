#include "pch.h"
#include "roster.h"
#include <string>
#include <sstream>
#include <vector>

using namespace std;
//random comment
int main() {
	cout << "C867, C++, ID-000943664, Luis Ocampo" << endl;

	Roster *classRoster = new Roster();

	const string students[5] = {
		"A1,John,Smith,John1989@mail.com,20,30,35,40,SECURITY",
		"A2,Suzan,Erickson,Erickson_1990@mailcom,19,50,30,40,NETWORK",
		"A3,Jack,Napoli,The_lawyer99yahoo.com,19,20,40,33,SOFTWARE",
		"A4,Erin,Black,Erin.black@comcast.net,22,50,58,40,SECURITY",
		"A5,Luis,Ocampo,Locamp3@wgu.edu,25,30,40,22,SOFTWARE",
	};

	for (int i = 0; i < 5; i++) {
		stringstream ss(students[i]);
		vector<string> input;

		while (ss.good()) {
			string substr;
			getline(ss, substr, ',');
			input.push_back(substr);
		}

		Degree degree;
		string studentDegree = input.at(8);
		if (studentDegree == "SECURITY") {
			degree = SECURITY;
		}
		else if (studentDegree == "NETWORK") {
			degree = NETWORKING;
		}
		else {
			degree = SOFTWARE;
		}

		classRoster->Add(input.at(0), input.at(1), input.at(2), input.at(3), stoi(input.at(4)), stoi(input.at(5)), stoi(input.at(6)), stoi(input.at(7)), degree);
	}

	classRoster->PrintAll();

	classRoster->PrintInvalidEmails();

	cout << endl;

	for (int i = 0; i < 5; i++) {
		classRoster->PrintDaysInCourse(classRoster->ClassRosterArray[i]->GetID());
	}

	cout << endl;

	classRoster->PrintByDegreeProgram(SOFTWARE);

	cout << endl;

	classRoster->Remove("A3");
	classRoster->Remove("A3");

	delete classRoster;

	return 0;
}

Roster::~Roster() {

}

void Roster::Add(string studentID, string firstName, string lastName, string emailAddress, int age, int daysInCourse1, int daysInCourse2, int daysInCourse3, Degree program) {
	int days[3] = { daysInCourse1, daysInCourse2, daysInCourse3 };

	for (int i = 0; i < 5; i++) {
		if (ClassRosterArray[i] == nullptr) {
			if (program == SECURITY) {
				ClassRosterArray[i] = new SecurityStudent(studentID, firstName, lastName, emailAddress, age, days, program);
			}
			else if (program == NETWORKING) {
				ClassRosterArray[i] = new NetworkStudent(studentID, firstName, lastName, emailAddress, age, days, program);
			}
			else {
				ClassRosterArray[i] = new SoftwareStudent(studentID, firstName, lastName, emailAddress, age, days, program);
			}

			break;
		}
	}
}

void Roster::Remove(string studentID) {
	int i = 0;
	bool found = false;

	while (i < 5) {

		if (ClassRosterArray[i] != nullptr && ClassRosterArray[i]->GetID() == studentID) {

			ClassRosterArray[i] = nullptr;

			found = true;

			break;
		}

		i++;
	}

	if (found == false) {
		cout << "Error: Student not found." << endl;
	}
}

void Roster::PrintAll() {
	int i = 0;

	while (i < 5) {

		if (ClassRosterArray[i] != nullptr) {
			ClassRosterArray[i]->Print();
		}

		i++;
	}
}

void Roster::PrintDaysInCourse(string studentID) {
	int i = 0;

	while (i < 5) {
		if (ClassRosterArray[i] != nullptr && ClassRosterArray[i]->GetID() == studentID) {
			int* daysToAvg = ClassRosterArray[i]->GetDaysToCompleteCourse();
			float sumOfDays = 0.0;

			for (int i = 0; i < 3; i++) {
				sumOfDays += daysToAvg[i];
			}

			cout << (sumOfDays / 3) << endl;
		}

		i++;
	}
}

void Roster::PrintInvalidEmails() {
	int i = 0;

	while (i < 5) {
		Student* student = ClassRosterArray[i];
		string email = student->GetEmail();
		bool foundError = false;

		if (email.find('@') == string::npos) {
			foundError = true;
		}

		if (email.find('.') == string::npos) {
			foundError = true;
		}

		if (email.find(' ') != string::npos) {
			foundError = true;
		}

		if (foundError == true) {
			cout << email << endl;
		}

		i++;
	}
}

void Roster::PrintByDegreeProgram(Degree degree) {
	int i = 0;

	while (i < 5) {
		Student* student = ClassRosterArray[i];

		if (student->GetDegreeProgram() == degree) {
			student->Print();
		}

		i++;
	}
}