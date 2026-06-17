#include "addstudentdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QMessageBox>

AddStudentDialog::AddStudentDialog(QWidget *parent, const Student *editStudent)
    : QDialog(parent), isEditMode(editStudent != nullptr) {
    
    setWindowTitle(isEditMode ? "Edit Student Record" : "Add New Student");
    resize(480, 480);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    // Form Group
    QGroupBox *formGroup = new QGroupBox(isEditMode ? "Student Details (Edit)" : "Student Details", this);
    QFormLayout *formLayout = new QFormLayout(formGroup);
    formLayout->setSpacing(12);
    formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);

    rollNumberEdit = new QLineEdit(this);
    rollNumberEdit->setPlaceholderText("e.g. F24-101");
    if (isEditMode) {
        rollNumberEdit->setText(editStudent->rollNumber);
        rollNumberEdit->setEnabled(false); // Can't change roll number in edit mode
    }
    formLayout->addRow("Roll Number:", rollNumberEdit);

    nameEdit = new QLineEdit(this);
    nameEdit->setPlaceholderText("Enter student's full name");
    if (isEditMode) {
        nameEdit->setText(editStudent->name);
    }
    formLayout->addRow("Student Name:", nameEdit);

    formGroup->setLayout(formLayout);
    mainLayout->addWidget(formGroup);

    // Marks Group
    QGroupBox *marksGroup = new QGroupBox("Subject Marks (out of 100)", this);
    QFormLayout *marksLayout = new QFormLayout(marksGroup);
    marksLayout->setSpacing(8);

    for (int i = 0; i < NUM_SUBJECTS; i++) {
        subjectEdits[i] = new QDoubleSpinBox(this);
        subjectEdits[i]->setRange(0.0, 100.0);
        subjectEdits[i]->setDecimals(1);
        subjectEdits[i]->setSingleStep(1.0);
        if (isEditMode) {
            subjectEdits[i]->setValue(editStudent->marks[i]);
        }
        marksLayout->addRow(SUBJECTS[i] + ":", subjectEdits[i]);
        
        connect(subjectEdits[i], &QDoubleSpinBox::valueChanged, this, &AddStudentDialog::updateLiveStats);
    }
    
    marksGroup->setLayout(marksLayout);
    mainLayout->addWidget(marksGroup);

    // Live Metrics Preview Card
    QGroupBox *statsGroup = new QGroupBox("Live Evaluation Preview", this);
    QHBoxLayout *statsLayout = new QHBoxLayout(statsGroup);
    
    QVBoxLayout *totalCol = new QVBoxLayout();
    QLabel *totalTitle = new QLabel("TOTAL MARKS", this);
    totalTitle->setStyleSheet("color: #64748b; font-size: 10px; font-weight: bold;");
    totalLabel = new QLabel("0.0 / 500", this);
    totalLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #e2e8f0;");
    totalCol->addWidget(totalTitle);
    totalCol->addWidget(totalLabel);
    
    QVBoxLayout *avgCol = new QVBoxLayout();
    QLabel *avgTitle = new QLabel("AVERAGE %", this);
    avgTitle->setStyleSheet("color: #64748b; font-size: 10px; font-weight: bold;");
    avgLabel = new QLabel("0.00%", this);
    avgLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #38bdf8;");
    avgCol->addWidget(avgTitle);
    avgCol->addWidget(avgLabel);

    QVBoxLayout *gradeCol = new QVBoxLayout();
    QLabel *gradeTitle = new QLabel("GRADE", this);
    gradeTitle->setStyleSheet("color: #64748b; font-size: 10px; font-weight: bold;");
    gradeLabel = new QLabel("F", this);
    gradeLabel->setStyleSheet("font-size: 20px; font-weight: bold; color: #ef4444;");
    gradeCol->addWidget(gradeTitle);
    gradeCol->addWidget(gradeLabel);

    statsLayout->addLayout(totalCol);
    statsLayout->addLayout(avgCol);
    statsLayout->addLayout(gradeCol);
    
    statsGroup->setLayout(statsLayout);
    mainLayout->addWidget(statsGroup);

    // Buttons
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->setSpacing(10);
    
    cancelButton = new QPushButton("Cancel", this);
    cancelButton->setObjectName("secondaryButton");
    
    saveButton = new QPushButton(isEditMode ? "Update Record" : "Add Student", this);
    
    btnLayout->addStretch();
    btnLayout->addWidget(cancelButton);
    btnLayout->addWidget(saveButton);
    
    mainLayout->addLayout(btnLayout);

    // Connections
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    connect(saveButton, &QPushButton::clicked, this, &AddStudentDialog::validateAndAccept);

    // Initial stats trigger
    updateLiveStats();
}

void AddStudentDialog::updateLiveStats() {
    float total = 0;
    for (int i = 0; i < NUM_SUBJECTS; i++) {
        total += subjectEdits[i]->value();
    }
    
    float avg = total / NUM_SUBJECTS;
    QChar grade = Student::calculateGrade(avg);
    
    totalLabel->setText(QString::number(total, 'f', 1) + " / 500");
    avgLabel->setText(QString::number(avg, 'f', 2) + "%");
    gradeLabel->setText(QString(grade));

    // Style grade label color dynamically
    if (grade == 'A') {
        gradeLabel->setStyleSheet("font-size: 20px; font-weight: bold; color: #10b981;"); // Emerald Green
    } else if (grade == 'B') {
        gradeLabel->setStyleSheet("font-size: 20px; font-weight: bold; color: #3b82f6;"); // Blue
    } else if (grade == 'C') {
        gradeLabel->setStyleSheet("font-size: 20px; font-weight: bold; color: #eab308;"); // Yellow
    } else if (grade == 'D') {
        gradeLabel->setStyleSheet("font-size: 20px; font-weight: bold; color: #a855f7;"); // Purple/Magenta
    } else {
        gradeLabel->setStyleSheet("font-size: 20px; font-weight: bold; color: #ef4444;"); // Red
    }
}

void AddStudentDialog::validateAndAccept() {
    if (rollNumberEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Roll Number is required!");
        rollNumberEdit->setFocus();
        return;
    }
    if (nameEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Student Name is required!");
        nameEdit->setFocus();
        return;
    }
    accept();
}

Student AddStudentDialog::getStudentData() const {
    Student s;
    s.rollNumber = rollNumberEdit->text().trimmed();
    s.name = nameEdit->text().trimmed();
    
    s.totalMarks = 0;
    for (int i = 0; i < NUM_SUBJECTS; i++) {
        s.marks[i] = subjectEdits[i]->value();
        s.totalMarks += s.marks[i];
    }
    s.average = s.totalMarks / NUM_SUBJECTS;
    s.grade = Student::calculateGrade(s.average);
    
    return s;
}
