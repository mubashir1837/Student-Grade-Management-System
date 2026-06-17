#ifndef STUDENT_H
#define STUDENT_H

#include <QString>
#include <QVector>

const int NUM_SUBJECTS = 5;
const QString SUBJECTS[NUM_SUBJECTS] = {
    "Programming Fundamentals",
    "Calculus & Analytical Geometry",
    "Applied Physics",
    "English Composition",
    "Introduction to ICT"
};

struct Student {
    QString rollNumber;
    QString name;
    float marks[NUM_SUBJECTS];
    float totalMarks;
    float average;
    QChar grade;

    static QChar calculateGrade(float average) {
        if (average >= 85) return 'A';
        if (average >= 75) return 'B';
        if (average >= 60) return 'C';
        if (average >= 50) return 'D';
        return 'F';
    }
};

#endif // STUDENT_H
