#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
#include <algorithm>

using namespace std;

// Constants for UI styling
const string RESET = "\033[0m";
const string BOLD = "\033[1m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string MAGENTA = "\033[35m";
const string CYAN = "\033[36m";
const string WHITE = "\033[37m";

const int NUM_SUBJECTS = 5;
const string SUBJECTS[NUM_SUBJECTS] = {
    "Programming Fundamentals",
    "Calculus & Analytical Geometry",
    "Applied Physics",
    "English Composition",
    "Introduction to ICT"
};

struct Student {
    string rollNumber;
    string name;
    float marks[NUM_SUBJECTS];
    float totalMarks;
    float average;
    char grade;
};

// Function declarations
void printHeader();
void printDivider();
char calculateGrade(float average);
void addStudent(vector<Student>& students);
void displayAllStudents(const vector<Student>& students);
void searchStudent(const vector<Student>& students);
void updateStudent(vector<Student>& students);
void deleteStudent(vector<Student>& students);
void displayStatistics(const vector<Student>& students);
void saveToFile(const vector<Student>& students, const string& filename);
void loadFromFile(vector<Student>& students, const string& filename);
void clearScreen();
void pressEnterToContinue();
int getValidInteger(const string& prompt, int minVal, int maxVal);
float getValidFloat(const string& prompt, float minVal, float maxVal);
string getValidString(const string& prompt);

int main() {
    vector<Student> students;
    const string filename = "students_db.txt";
    
    // Load existing records on startup
    loadFromFile(students, filename);
    
    int choice;
    do {
        clearScreen();
        printHeader();
        cout << BOLD << CYAN << "      STUDENT GRADE MANAGEMENT SYSTEM (Terminal Edition)" << RESET << endl;
        printDivider();
        cout << BOLD << "  [1]" << RESET << " Add New Student Record" << endl;
        cout << BOLD << "  [2]" << RESET << " View All Student Records" << endl;
        cout << BOLD << "  [3]" << RESET << " Search Student by Roll Number" << endl;
        cout << BOLD << "  [4]" << RESET << " Update Student Record" << endl;
        cout << BOLD << "  [5]" << RESET << " Delete Student Record" << endl;
        cout << BOLD << "  [6]" << RESET << " View Class Performance Statistics" << endl;
        cout << BOLD << "  [7]" << RESET << " Save Data to File" << endl;
        cout << BOLD << "  [8]" << RESET << " Exit Program" << endl;
        printDivider();
        
        choice = getValidInteger("Enter your choice (1-8): ", 1, 8);
        
        switch (choice) {
            case 1:
                clearScreen();
                addStudent(students);
                pressEnterToContinue();
                break;
            case 2:
                clearScreen();
                displayAllStudents(students);
                pressEnterToContinue();
                break;
            case 3:
                clearScreen();
                searchStudent(students);
                pressEnterToContinue();
                break;
            case 4:
                clearScreen();
                updateStudent(students);
                pressEnterToContinue();
                break;
            case 5:
                clearScreen();
                deleteStudent(students);
                pressEnterToContinue();
                break;
            case 6:
                clearScreen();
                displayStatistics(students);
                pressEnterToContinue();
                break;
            case 7:
                clearScreen();
                saveToFile(students, filename);
                pressEnterToContinue();
                break;
            case 8:
                // Auto-save before exit
                saveToFile(students, filename);
                cout << GREEN << BOLD << "\nThank you for using the Student Grade Management System! Exiting..." << RESET << endl;
                break;
        }
    } while (choice != 8);
    
    return 0;
}

void printHeader() {
    cout << CYAN << "=====================================================================" << RESET << endl;
    cout << CYAN << " **********           LAB PROJECT: SEMESTER - I            **********" << RESET << endl;
    cout << CYAN << "=====================================================================" << RESET << endl;
}

void printDivider() {
    cout << CYAN << "---------------------------------------------------------------------" << RESET << endl;
}

void clearScreen() {
    // Cross-platform clear screen (Linux/Unix preferred here)
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pressEnterToContinue() {
    cout << "\nPress Enter to return to main menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

char calculateGrade(float average) {
    if (average >= 85) return 'A'; // A+ or A, representing outstanding
    if (average >= 75) return 'B'; // Above average
    if (average >= 60) return 'C'; // Average
    if (average >= 50) return 'D'; // Below average/Pass
    return 'F';                    // Fail
}

string getValidString(const string& prompt) {
    string value;
    while (true) {
        cout << prompt;
        getline(cin >> ws, value);
        if (!value.empty()) {
            return value;
        }
        cout << RED << "Input cannot be empty. Please try again." << RESET << endl;
    }
}

int getValidInteger(const string& prompt, int minVal, int maxVal) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            if (value >= minVal && value <= maxVal) {
                return value;
            }
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << RED << "Invalid input. Please enter an integer between " << minVal << " and " << maxVal << "." << RESET << endl;
    }
}

float getValidFloat(const string& prompt, float minVal, float maxVal) {
    float value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            if (value >= minVal && value <= maxVal) {
                return value;
            }
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << RED << "Invalid input. Please enter a value between " << minVal << " and " << maxVal << "." << RESET << endl;
    }
}

void addStudent(vector<Student>& students) {
    cout << BOLD << CYAN << "=== ADD NEW STUDENT RECORD ===" << RESET << endl << endl;
    
    Student newStudent;
    
    // Get unique Roll Number
    while (true) {
        newStudent.rollNumber = getValidString("Enter Roll Number (e.g., F24-101): ");
        
        // Check if roll number already exists
        bool exists = false;
        for (const auto& s : students) {
            if (s.rollNumber == newStudent.rollNumber) {
                exists = true;
                break;
            }
        }
        
        if (!exists) {
            break;
        }
        cout << RED << "Error: Roll Number '" << newStudent.rollNumber << "' already exists! Try another one." << RESET << endl;
    }
    
    newStudent.name = getValidString("Enter Student Full Name: ");
    
    cout << endl << YELLOW << "Enter Marks obtained (out of 100) for each subject:" << RESET << endl;
    newStudent.totalMarks = 0;
    
    for (int i = 0; i < NUM_SUBJECTS; i++) {
        string prompt = "  " + SUBJECTS[i] + ": ";
        newStudent.marks[i] = getValidFloat(prompt, 0.0f, 100.0f);
        newStudent.totalMarks += newStudent.marks[i];
    }
    
    newStudent.average = newStudent.totalMarks / NUM_SUBJECTS;
    newStudent.grade = calculateGrade(newStudent.average);
    
    students.push_back(newStudent);
    cout << endl << GREEN << BOLD << "Student record for '" << newStudent.name << "' has been added successfully!" << RESET << endl;
}

void displayAllStudents(const vector<Student>& students) {
    cout << BOLD << CYAN << "=== ALL STUDENT RECORDS ===" << RESET << endl << endl;
    
    if (students.empty()) {
        cout << YELLOW << "No student records found in the database. Please add a student first!" << RESET << endl;
        return;
    }
    
    // Draw table header
    printDivider();
    cout << left << setw(12) << BOLD + "Roll No" 
         << setw(20) << "Name" 
         << setw(8) << "PF" 
         << setw(8) << "Calc" 
         << setw(8) << "Phys" 
         << setw(8) << "Eng" 
         << setw(8) << "ICT" 
         << setw(8) << "Avg" 
         << setw(6) << "Grade" + RESET << endl;
    printDivider();
    
    for (const auto& s : students) {
        string gradeColor = RESET;
        if (s.grade == 'A') gradeColor = GREEN;
        else if (s.grade == 'B') gradeColor = BLUE;
        else if (s.grade == 'C') gradeColor = YELLOW;
        else if (s.grade == 'D') gradeColor = MAGENTA;
        else gradeColor = RED + BOLD;
        
        cout << left << setw(12) << s.rollNumber 
             << setw(20) << (s.name.length() > 18 ? s.name.substr(0, 15) + "..." : s.name)
             << setw(8) << fixed << setprecision(1) << s.marks[0]
             << setw(8) << s.marks[1]
             << setw(8) << s.marks[2]
             << setw(8) << s.marks[3]
             << setw(8) << s.marks[4]
             << setw(8) << s.average
             << gradeColor << setw(6) << s.grade << RESET << endl;
    }
    printDivider();
    cout << "Total Students: " << BOLD << students.size() << RESET << endl;
}

void searchStudent(const vector<Student>& students) {
    cout << BOLD << CYAN << "=== SEARCH STUDENT RECORD ===" << RESET << endl << endl;
    
    if (students.empty()) {
        cout << YELLOW << "Database is empty." << RESET << endl;
        return;
    }
    
    string roll = getValidString("Enter Roll Number to search: ");
    bool found = false;
    
    for (const auto& s : students) {
        if (s.rollNumber == roll) {
            found = true;
            printDivider();
            cout << BOLD << GREEN << "Student Record Found!" << RESET << endl;
            printDivider();
            cout << left << setw(20) << "Roll Number:" << s.rollNumber << endl;
            cout << left << setw(20) << "Student Name:" << s.name << endl;
            printDivider();
            cout << BOLD << YELLOW << "Subject-wise Marks:" << RESET << endl;
            for (int i = 0; i < NUM_SUBJECTS; ++i) {
                cout << "  - " << left << setw(32) << SUBJECTS[i] << ": " << s.marks[i] << " / 100" << endl;
            }
            printDivider();
            cout << left << setw(20) << "Total Marks:" << s.totalMarks << " / 500" << endl;
            cout << left << setw(20) << "Average Percentage:" << fixed << setprecision(2) << s.average << "%" << endl;
            
            string gradeColor = RESET;
            if (s.grade == 'A') gradeColor = GREEN;
            else if (s.grade == 'B') gradeColor = BLUE;
            else if (s.grade == 'C') gradeColor = YELLOW;
            else if (s.grade == 'D') gradeColor = MAGENTA;
            else gradeColor = RED + BOLD;
            
            cout << left << setw(20) << "Final Grade:" << gradeColor << BOLD << s.grade << RESET << endl;
            printDivider();
            break;
        }
    }
    
    if (!found) {
        cout << RED << "Error: Student with Roll Number '" << roll << "' not found." << RESET << endl;
    }
}

void updateStudent(vector<Student>& students) {
    cout << BOLD << CYAN << "=== UPDATE STUDENT RECORD ===" << RESET << endl << endl;
    
    if (students.empty()) {
        cout << YELLOW << "Database is empty." << RESET << endl;
        return;
    }
    
    string roll = getValidString("Enter Roll Number to update: ");
    bool found = false;
    
    for (auto& s : students) {
        if (s.rollNumber == roll) {
            found = true;
            cout << endl << "Student Found: " << BOLD << s.name << RESET << " (" << s.rollNumber << ")" << endl;
            cout << "Press Enter to keep current name, or type new name to update." << endl;
            
            string newName;
            cout << "Enter New Name [" << s.name << "]: ";
            getline(cin >> ws, newName);
            
            // If user enters nothing (just whitespace/enter), keep old name
            if (!newName.empty()) {
                s.name = newName;
            }
            
            cout << endl << YELLOW << "Enter new marks for subjects (or input invalid number to keep current marks):" << RESET << endl;
            s.totalMarks = 0;
            
            for (int i = 0; i < NUM_SUBJECTS; ++i) {
                cout << "  " << SUBJECTS[i] << " [Current: " << s.marks[i] << "]: ";
                string markInput;
                getline(cin, markInput);
                
                if (!markInput.empty()) {
                    try {
                        float mark = stof(markInput);
                        if (mark >= 0.0f && mark <= 100.0f) {
                            s.marks[i] = mark;
                        } else {
                            cout << RED << "    Invalid range! Keeping current marks: " << s.marks[i] << RESET << endl;
                        }
                    } catch (...) {
                        cout << YELLOW << "    Keeping current marks: " << s.marks[i] << RESET << endl;
                    }
                }
                s.totalMarks += s.marks[i];
            }
            
            s.average = s.totalMarks / NUM_SUBJECTS;
            s.grade = calculateGrade(s.average);
            
            cout << endl << GREEN << BOLD << "Student record updated successfully!" << RESET << endl;
            break;
        }
    }
    
    if (!found) {
        cout << RED << "Error: Student with Roll Number '" << roll << "' not found." << RESET << endl;
    }
}

void deleteStudent(vector<Student>& students) {
    cout << BOLD << CYAN << "=== DELETE STUDENT RECORD ===" << RESET << endl << endl;
    
    if (students.empty()) {
        cout << YELLOW << "Database is empty." << RESET << endl;
        return;
    }
    
    string roll = getValidString("Enter Roll Number to delete: ");
    auto it = find_if(students.begin(), students.end(), [&roll](const Student& s) {
        return s.rollNumber == roll;
    });
    
    if (it != students.end()) {
        cout << RED << BOLD << "Warning: You are about to delete record of student: " 
             << it->name << " (" << it->rollNumber << ")" << RESET << endl;
        string confirm = getValidString("Are you sure you want to delete? (yes/no): ");
        
        // Lowercase comparison
        transform(confirm.begin(), confirm.end(), confirm.begin(), ::tolower);
        if (confirm == "yes" || confirm == "y") {
            students.erase(it);
            cout << GREEN << BOLD << "Student record deleted successfully!" << RESET << endl;
        } else {
            cout << YELLOW << "Deletion cancelled." << RESET << endl;
        }
    } else {
        cout << RED << "Error: Student with Roll Number '" << roll << "' not found." << RESET << endl;
    }
}

void displayStatistics(const vector<Student>& students) {
    cout << BOLD << CYAN << "=== CLASS PERFORMANCE STATISTICS ===" << RESET << endl << endl;
    
    if (students.empty()) {
        cout << YELLOW << "No student records available to calculate statistics." << RESET << endl;
        return;
    }
    
    float classTotalAverage = 0;
    float highestAverage = -1;
    float lowestAverage = 101;
    string topperName = "";
    string lowestName = "";
    
    float subjectTotals[NUM_SUBJECTS] = {0};
    float subjectHighest[NUM_SUBJECTS] = {-1, -1, -1, -1, -1};
    float subjectLowest[NUM_SUBJECTS] = {101, 101, 101, 101, 101};
    
    int gradeCounts[5] = {0}; // A, B, C, D, F
    
    for (const auto& s : students) {
        classTotalAverage += s.average;
        
        if (s.average > highestAverage) {
            highestAverage = s.average;
            topperName = s.name + " (" + s.rollNumber + ")";
        }
        if (s.average < lowestAverage) {
            lowestAverage = s.average;
            lowestName = s.name + " (" + s.rollNumber + ")";
        }
        
        for (int i = 0; i < NUM_SUBJECTS; ++i) {
            subjectTotals[i] += s.marks[i];
            if (s.marks[i] > subjectHighest[i]) subjectHighest[i] = s.marks[i];
            if (s.marks[i] < subjectLowest[i]) subjectLowest[i] = s.marks[i];
        }
        
        switch (s.grade) {
            case 'A': gradeCounts[0]++; break;
            case 'B': gradeCounts[1]++; break;
            case 'C': gradeCounts[2]++; break;
            case 'D': gradeCounts[3]++; break;
            case 'F': gradeCounts[4]++; break;
        }
    }
    
    float classAvg = classTotalAverage / students.size();
    
    printDivider();
    cout << BOLD << YELLOW << "Overall Class Metrics:" << RESET << endl;
    cout << "  - Total Students Evaluated: " << BOLD << students.size() << RESET << endl;
    cout << "  - Class Average Percentage: " << fixed << setprecision(2) << classAvg << "%" << endl;
    cout << "  - Highest Class Average   : " << highestAverage << "% [" << topperName << "]" << endl;
    cout << "  - Lowest Class Average    : " << lowestAverage << "% [" << lowestName << "]" << endl;
    
    printDivider();
    cout << BOLD << YELLOW << "Subject-wise Performance Breakdown:" << RESET << endl;
    cout << left << setw(32) << BOLD + "Subject Name" 
         << setw(12) << "Average" 
         << setw(12) << "Highest" 
         << setw(12) << "Lowest" + RESET << endl;
    printDivider();
    for (int i = 0; i < NUM_SUBJECTS; ++i) {
        float subAvg = subjectTotals[i] / students.size();
        cout << left << setw(32) << SUBJECTS[i]
             << setw(12) << fixed << setprecision(1) << subAvg
             << setw(12) << subjectHighest[i]
             << setw(12) << subjectLowest[i] << endl;
    }
    
    printDivider();
    cout << BOLD << YELLOW << "Grade Distribution Summary:" << RESET << endl;
    cout << "  - Grade A (Outstanding): " << GREEN << BOLD << gradeCounts[0] << RESET << endl;
    cout << "  - Grade B (Good)       : " << BLUE << gradeCounts[1] << RESET << endl;
    cout << "  - Grade C (Average)    : " << YELLOW << gradeCounts[2] << RESET << endl;
    cout << "  - Grade D (Passing)    : " << MAGENTA << gradeCounts[3] << RESET << endl;
    cout << "  - Grade F (Failing)    : " << RED << BOLD << gradeCounts[4] << RESET << endl;
    printDivider();
}

void saveToFile(const vector<Student>& students, const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cout << RED << "Error: Could not open file '" << filename << "' for saving data!" << RESET << endl;
        return;
    }
    
    for (const auto& s : students) {
        // Simple plain-text CSV format: roll|name|marks0|marks1|marks2|marks3|marks4|total|avg|grade
        outFile << s.rollNumber << "|"
                << s.name << "|"
                << s.marks[0] << "|"
                << s.marks[1] << "|"
                << s.marks[2] << "|"
                << s.marks[3] << "|"
                << s.marks[4] << "|"
                << s.totalMarks << "|"
                << s.average << "|"
                << s.grade << "\n";
    }
    
    outFile.close();
    cout << GREEN << BOLD << "Database saved successfully to '" << filename << "' (" << students.size() << " records)." << RESET << endl;
}

void loadFromFile(vector<Student>& students, const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        // If file doesn't exist, it's fine (first run)
        return;
    }
    
    students.clear();
    string line;
    while (getline(inFile, line)) {
        if (line.empty()) continue;
        
        stringstream ss(line);
        Student s;
        string temp;
        
        getline(ss, s.rollNumber, '|');
        getline(ss, s.name, '|');
        
        for (int i = 0; i < NUM_SUBJECTS; ++i) {
            getline(ss, temp, '|');
            s.marks[i] = stof(temp);
        }
        
        getline(ss, temp, '|');
        s.totalMarks = stof(temp);
        
        getline(ss, temp, '|');
        s.average = stof(temp);
        
        getline(ss, temp, '|');
        if (!temp.empty()) {
            s.grade = temp[0];
        } else {
            s.grade = calculateGrade(s.average);
        }
        
        students.push_back(s);
    }
    
    inFile.close();
    // Silent load on startup, but we'll print a message in menu or log it
}
