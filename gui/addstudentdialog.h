#ifndef ADDSTUDENTDIALOG_H
#define ADDSTUDENTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QPushButton>
#include "student.h"

class AddStudentDialog : public QDialog {
    Q_OBJECT

public:
    explicit AddStudentDialog(QWidget *parent = nullptr, const Student *editStudent = nullptr);
    Student getStudentData() const;

private slots:
    void updateLiveStats();
    void validateAndAccept();

private:
    QLineEdit *rollNumberEdit;
    QLineEdit *nameEdit;
    QDoubleSpinBox *subjectEdits[NUM_SUBJECTS];
    
    QLabel *totalLabel;
    QLabel *avgLabel;
    QLabel *gradeLabel;

    QPushButton *saveButton;
    QPushButton *cancelButton;

    bool isEditMode;
};

#endif // ADDSTUDENTDIALOG_H
