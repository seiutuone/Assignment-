#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

const int TOTAL_ASG = 5;
const int CAPACITY = 10;

struct Student {
    string id;
    int mstMark;
    int assignmentMarks[TOTAL_ASG];
    int finalMark;
    int coursework;
    int totalMark;
    char grade;

    void printResults(){
        cout << setw(20) << id << setw(20) << coursework << setw(20) << totalMark << setw(20) << grade << endl;
    }
};

void calculateCoursework(Student students[CAPACITY], int size);
void calculateTotal(Student students[CAPACITY], int size);
void printResults(Student students[CAPACITY], int size);
char getGrade(int totalMark);
string printLine(int length);

int main()
{
    cout << left;

    Student students[CAPACITY];
    int size = 0;

    ifstream readFile;
    readFile.open("student-grades.txt");

    if (!readFile)
    {
        cout << "File not found" << endl;
        return 1;
    }

    else
    {
        string temp;
        getline(readFile, temp);

        while (!readFile.eof())
        {
            readFile >> students[size].id;

            for (int i = 0; i < TOTAL_ASG; i++)
            {
                // read all assignment marks
                readFile >> students[size].assignmentMarks[i];
            }

            // read mst and final mark
            readFile >> students[size].mstMark;
            readFile >> students[size].finalMark;

            size++;
        }
    }

    calculateCoursework(students, size);
    calculateTotal(students, size);
    printResults(students, size);

    readFile.close();

    return 0;
}

void calculateCoursework(Student students[CAPACITY], int size)
{
    for (int i = 0; i < size; i++)
    {
        // reset student coursework
        students[i].coursework = 0;

        for (int j = 0; j < TOTAL_ASG; j++)
        {
            // add all assignment marks
            students[i].coursework += students[i].assignmentMarks[j];
        }

        // add mst mark
        students[i].coursework += students[i].mstMark;
    }
}

void calculateTotal(Student students[CAPACITY], int size)
{
    for (int i = 0; i < size; i++)
    {
        students[i].totalMark = students[i].coursework + students[i].finalMark;
    }
}

void printResults(Student students[CAPACITY], int size)
{
    int failureCount = 0;

    cout << setw(20) << "Id" << setw(20) << "CW" << setw(20) << "Total" << setw(20) << "Grade" << endl;
    cout << printLine(70) << endl;

    for (int i = 0; i < size; i++)
    {
        char studentGrade = getGrade(students[i].totalMark);
        students[i].grade =  studentGrade;

        if (studentGrade == 'D')
        {
            failureCount++;
        }

        students[i].printResults();
        cout << printLine(70) << endl;
    }

    cout << "\nNumber of students that failed: " << failureCount << endl;
}

char getGrade(int totalMark)
{
    if (totalMark < 50)
    {
        return 'D';
    }
    else if (totalMark < 65)
    {
        return 'C';
    }
    else if (totalMark < 80)
    {
        return 'B';
    }
    else
    {
        return 'A';
    }
}

string printLine(int length)
{
    string line = "";

    for (int i = 0; i < length; i++)
    {
        line += "-";
    }

    return line;
}