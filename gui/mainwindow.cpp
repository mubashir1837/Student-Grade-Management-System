#include "mainwindow.h"
#include "addstudentdialog.h"
#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QTabWidget>
#include <QGroupBox>
#include <QStatusBar>
#include <QStyle>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Student Grade Management System (Premium Edition)");
    resize(1024, 700);

    setupUi();
    loadSettingsAndData();
}

MainWindow::~MainWindow() {
    saveSettingsAndData();
}

void MainWindow::setupUi() {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(15, 15, 15, 15);
    mainLayout->setSpacing(15);

    // Title Block
    QHBoxLayout *titleLayout = new QHBoxLayout();
    
    QLabel *titleLabel = new QLabel("STUDENT GRADE ANALYTICS SYSTEM", this);
    titleLabel->setObjectName("titleLabel");
    titleLabel->setWordWrap(true);
    titleLabel->setStyleSheet("font-size: 22px; font-weight: bold; color: #38bdf8; padding: 0px; border: none;");
    
    titleLayout->addWidget(titleLabel);
    titleLayout->addStretch();
    
    // Theme Switch Button
    themeToggleBtn = new QPushButton("☀️ Light Mode", this);
    themeToggleBtn->setObjectName("secondaryButton");
    connect(themeToggleBtn, &QPushButton::clicked, this, &MainWindow::onToggleTheme);
    titleLayout->addWidget(themeToggleBtn);
    
    // Save DB status button
    saveBtn = new QPushButton("Save Database", this);
    saveBtn->setObjectName("secondaryButton");
    connect(saveBtn, &QPushButton::clicked, this, &MainWindow::onSaveData);
    titleLayout->addWidget(saveBtn);

    mainLayout->addLayout(titleLayout);

    // Main Tabbed Widget
    QTabWidget *tabWidget = new QTabWidget(this);
    
    // TAB 1: Student registry
    QWidget *registryTab = new QWidget(this);
    QVBoxLayout *registryLayout = new QVBoxLayout(registryTab);
    registryLayout->setContentsMargins(10, 10, 10, 10);
    registryLayout->setSpacing(12);

    // Action Toolbar
    QHBoxLayout *toolbarLayout = new QHBoxLayout();
    toolbarLayout->setSpacing(8);

    searchEdit = new QLineEdit(this);
    searchEdit->setPlaceholderText("🔍 Search student by name or roll number...");
    searchEdit->setMinimumWidth(300);
    connect(searchEdit, &QLineEdit::textChanged, this, &MainWindow::onSearchChanged);
    toolbarLayout->addWidget(searchEdit);
    toolbarLayout->addSpacing(15);

    addBtn = new QPushButton(" Add Student", this);
    addBtn->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #10b981, stop:1 #059669); color: #ffffff; font-weight: bold; border-radius: 8px;");
    connect(addBtn, &QPushButton::clicked, this, &MainWindow::onAddStudent);
    toolbarLayout->addWidget(addBtn);

    editBtn = new QPushButton(" Edit", this);
    editBtn->setObjectName("secondaryButton");
    editBtn->setEnabled(false);
    connect(editBtn, &QPushButton::clicked, this, &MainWindow::onEditStudent);
    toolbarLayout->addWidget(editBtn);

    deleteBtn = new QPushButton(" Delete", this);
    deleteBtn->setObjectName("dangerButton");
    deleteBtn->setEnabled(false);
    connect(deleteBtn, &QPushButton::clicked, this, &MainWindow::onDeleteStudent);
    toolbarLayout->addWidget(deleteBtn);

    toolbarLayout->addStretch();

    exportBtn = new QPushButton("Export CSV", this);
    exportBtn->setObjectName("secondaryButton");
    connect(exportBtn, &QPushButton::clicked, this, &MainWindow::onExportCSV);
    toolbarLayout->addWidget(exportBtn);

    clearBtn = new QPushButton("Clear All", this);
    clearBtn->setObjectName("dangerButton");
    connect(clearBtn, &QPushButton::clicked, this, &MainWindow::onClearDatabase);
    toolbarLayout->addWidget(clearBtn);

    registryLayout->addLayout(toolbarLayout);

    // Table
    studentsTable = new QTableWidget(this);
    studentsTable->setColumnCount(9);
    QStringList headers = {
        "Roll No", "Student Name", "Programming", "Calculus", 
        "Physics", "English", "ICT", "Average %", "Grade"
    };
    studentsTable->setHorizontalHeaderLabels(headers);
    studentsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    studentsTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    studentsTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    studentsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    studentsTable->setSelectionMode(QAbstractItemView::SingleSelection);
    studentsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    
    connect(studentsTable, &QTableWidget::itemSelectionChanged, this, &MainWindow::onTableSelectionChanged);
    connect(studentsTable, &QTableWidget::doubleClicked, this, &MainWindow::onEditStudent);
    
    registryLayout->addWidget(studentsTable);

    // KPI Metrics Section at Bottom of registry
    QGroupBox *kpiGroup = new QGroupBox("Class Performance Summary KPIs", this);
    kpiGroup->setMinimumHeight(90);
    QHBoxLayout *kpiLayout = new QHBoxLayout(kpiGroup);
    kpiLayout->setContentsMargins(15, 10, 15, 10);
    kpiLayout->setSpacing(20);

    // Helper lambda for KPI cards
    auto makeKpiCard = [this, &kpiLayout](const QString &title, QLabel* &labelVal, const QString &accentColor) {
        QVBoxLayout *vBox = new QVBoxLayout();
        vBox->setSpacing(2);
        
        QLabel *lblTitle = new QLabel(title, this);
        lblTitle->setWordWrap(true);
        lblTitle->setStyleSheet("color: #64748b; font-size: 10px; font-weight: bold; text-transform: uppercase;");
        
        labelVal = new QLabel("-", this);
        labelVal->setWordWrap(true);
        labelVal->setStyleSheet(QString("font-size: 16px; font-weight: bold; color: %1;").arg(accentColor));
        
        vBox->addWidget(lblTitle);
        vBox->addWidget(labelVal);
        kpiLayout->addLayout(vBox);
    };

    makeKpiCard("Evaluated Students", kpiTotalStudents, "#ffffff");
    kpiLayout->addSpacing(10);
    makeKpiCard("Class Average Mark", kpiClassAverage, "#38bdf8"); // Cyan
    kpiLayout->addSpacing(10);
    makeKpiCard("Class Topper (Highest)", kpiTopper, "#10b981");   // Green
    kpiLayout->addSpacing(10);
    makeKpiCard("Needs Assistance (Lowest)", kpiLowest, "#ef4444"); // Red

    registryLayout->addWidget(kpiGroup);
    tabWidget->addTab(registryTab, "Student Registry");

    // TAB 2: Charts / Analytics
    chartsWidget = new ChartsView(this);
    tabWidget->addTab(chartsWidget, "Analytics Dashboard");

    mainLayout->addWidget(tabWidget);

    // Status Bar
    QStatusBar *bar = new QStatusBar(this);
    setStatusBar(bar);
    bar->showMessage("Database ready. Add records to compile grades.");
}

void MainWindow::onTableSelectionChanged() {
    bool hasSelection = !studentsTable->selectedItems().isEmpty();
    editBtn->setEnabled(hasSelection);
    deleteBtn->setEnabled(hasSelection);
}

void MainWindow::updateTable() {
    studentsTable->setRowCount(0);
    
    for (int row = 0; row < studentsList.size(); ++row) {
        const Student &s = studentsList[row];
        studentsTable->insertRow(row);

        QTableWidgetItem *itemRoll = new QTableWidgetItem(s.rollNumber);
        QTableWidgetItem *itemName = new QTableWidgetItem(s.name);
        
        itemRoll->setTextAlignment(Qt::AlignCenter);
        itemName->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        
        studentsTable->setItem(row, 0, itemRoll);
        studentsTable->setItem(row, 1, itemName);

        for (int i = 0; i < NUM_SUBJECTS; ++i) {
            QTableWidgetItem *itemMark = new QTableWidgetItem(QString::number(s.marks[i], 'f', 1));
            itemMark->setTextAlignment(Qt::AlignCenter);
            studentsTable->setItem(row, 2 + i, itemMark);
        }

        QTableWidgetItem *itemAvg = new QTableWidgetItem(QString::number(s.average, 'f', 2) + "%");
        QTableWidgetItem *itemGrade = new QTableWidgetItem(QString(s.grade));
        
        itemAvg->setTextAlignment(Qt::AlignCenter);
        itemGrade->setTextAlignment(Qt::AlignCenter);

        // Highlight/color average text
        itemAvg->setForeground(QBrush(QColor("#38bdf8")));
        itemAvg->setFont(QFont("", -1, QFont::Bold));

        // Color grades uniquely
        if (s.grade == 'A') {
            itemGrade->setForeground(QBrush(QColor("#10b981"))); // Green
        } else if (s.grade == 'B') {
            itemGrade->setForeground(QBrush(QColor("#3b82f6"))); // Blue
        } else if (s.grade == 'C') {
            itemGrade->setForeground(QBrush(QColor("#eab308"))); // Yellow
        } else if (s.grade == 'D') {
            itemGrade->setForeground(QBrush(QColor("#a855f7"))); // Purple
        } else {
            itemGrade->setForeground(QBrush(QColor("#ef4444"))); // Red
        }
        itemGrade->setFont(QFont("", -1, QFont::Bold));

        studentsTable->setItem(row, 7, itemAvg);
        studentsTable->setItem(row, 8, itemGrade);
    }
    
    // Apply search filter if any exists
    onSearchChanged(searchEdit->text());
}

void MainWindow::updateStatistics() {
    int total = studentsList.size();
    kpiTotalStudents->setText(QString::number(total));

    if (total == 0) {
        kpiClassAverage->setText("-");
        kpiTopper->setText("-");
        kpiLowest->setText("-");
        statusBar()->showMessage("No student records available. Database is empty.");
        return;
    }

    float sumAverage = 0;
    float maxAverage = -1;
    float minAverage = 101;
    QString topperName = "";
    QString lowestName = "";

    for (const auto &s : studentsList) {
        sumAverage += s.average;
        if (s.average > maxAverage) {
            maxAverage = s.average;
            topperName = QString("%1 (%2%)").arg(s.name).arg(QString::number(s.average, 'f', 1));
        }
        if (s.average < minAverage) {
            minAverage = s.average;
            lowestName = QString("%1 (%2%)").arg(s.name).arg(QString::number(s.average, 'f', 1));
        }
    }

    float classAverage = sumAverage / total;
    kpiClassAverage->setText(QString::number(classAverage, 'f', 2) + "%");
    kpiTopper->setText(topperName);
    kpiLowest->setText(lowestName);

    statusBar()->showMessage(QString("Loaded %1 students. Class average is %2%").arg(total).arg(QString::number(classAverage, 'f', 1)));
}

void MainWindow::onAddStudent() {
    AddStudentDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        Student newStudent = dialog.getStudentData();

        // Check roll number uniqueness
        for (const auto &s : studentsList) {
            if (s.rollNumber.trimmed().toLower() == newStudent.rollNumber.trimmed().toLower()) {
                QMessageBox::critical(this, "Save Error", QString("Roll Number '%1' already exists!").arg(newStudent.rollNumber));
                return;
            }
        }

        studentsList.append(newStudent);
        updateTable();
        updateStatistics();
        chartsWidget->updateCharts(studentsList);
        onSaveData();
    }
}

void MainWindow::onEditStudent() {
    int currentRow = studentsTable->currentRow();
    if (currentRow < 0 || currentRow >= studentsList.size()) {
        return;
    }

    // Get selected student
    const Student &editStudent = studentsList[currentRow];

    AddStudentDialog dialog(this, &editStudent);
    if (dialog.exec() == QDialog::Accepted) {
        Student updatedStudent = dialog.getStudentData();
        studentsList[currentRow] = updatedStudent;
        updateTable();
        updateStatistics();
        chartsWidget->updateCharts(studentsList);
        onSaveData();
    }
}

void MainWindow::onDeleteStudent() {
    int currentRow = studentsTable->currentRow();
    if (currentRow < 0 || currentRow >= studentsList.size()) {
        return;
    }

    const Student &s = studentsList[currentRow];
    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Delete Student Record",
        QString("Are you sure you want to delete the record of %1 (%2)?").arg(s.name).arg(s.rollNumber),
        QMessageBox::Yes | QMessageBox::No
    );

    if (reply == QMessageBox::Yes) {
        studentsList.removeAt(currentRow);
        updateTable();
        updateStatistics();
        chartsWidget->updateCharts(studentsList);
        onSaveData();
    }
}

void MainWindow::onSearchChanged(const QString &text) {
    QString query = text.trimmed().toLower();
    
    for (int row = 0; row < studentsTable->rowCount(); ++row) {
        QString roll = studentsTable->item(row, 0)->text().toLower();
        QString name = studentsTable->item(row, 1)->text().toLower();
        
        bool match = roll.contains(query) || name.contains(query);
        studentsTable->setRowHidden(row, !match);
    }
}

void MainWindow::onSaveData() {
    QFile file(dbFilename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        statusBar()->showMessage("Error: Could not save database file!");
        return;
    }

    QTextStream out(&file);
    for (const auto &s : studentsList) {
        out << s.rollNumber << "|"
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
    file.close();
    statusBar()->showMessage("Database saved successfully.", 3000);
}

void MainWindow::onLoadData() {
    QFile file(dbFilename);
    if (!file.exists()) {
        return;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    studentsList.clear();
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.trimmed().isEmpty()) continue;

        QStringList parts = line.split('|');
        if (parts.size() < 10) continue;

        Student s;
        s.rollNumber = parts[0];
        s.name = parts[1];
        for (int i = 0; i < NUM_SUBJECTS; ++i) {
            s.marks[i] = parts[2 + i].toFloat();
        }
        s.totalMarks = parts[7].toFloat();
        s.average = parts[8].toFloat();
        s.grade = parts[9].at(0);

        studentsList.append(s);
    }
    file.close();
}

void MainWindow::onClearDatabase() {
    if (studentsList.isEmpty()) return;

    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Clear Database",
        "Are you sure you want to permanently delete all student records?",
        QMessageBox::Yes | QMessageBox::No
    );

    if (reply == QMessageBox::Yes) {
        studentsList.clear();
        updateTable();
        updateStatistics();
        chartsWidget->updateCharts(studentsList);
        onSaveData();
    }
}

void MainWindow::onExportCSV() {
    if (studentsList.isEmpty()) {
        QMessageBox::warning(this, "Export Fail", "No data to export!");
        return;
    }

    QString savePath = QFileDialog::getSaveFileName(
        this, "Export Student Records", 
        "student_grades_export.csv", 
        "CSV Files (*.csv)"
    );

    if (savePath.isEmpty()) return;

    QFile file(savePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Export Error", "Could not open file to write!");
        return;
    }

    QTextStream out(&file);
    // Header
    out << "Roll Number,Student Name,";
    for (int i = 0; i < NUM_SUBJECTS; ++i) {
        out << SUBJECTS[i] << ",";
    }
    out << "Total Marks,Average Percentage,Grade\n";

    // Records
    for (const auto &s : studentsList) {
        QString rollEscaped = s.rollNumber;
        QString nameEscaped = s.name;
        rollEscaped.replace("\"", "\"\"");
        nameEscaped.replace("\"", "\"\"");

        out << "\"" << rollEscaped << "\","
            << "\"" << nameEscaped << "\",";
        for (int i = 0; i < NUM_SUBJECTS; ++i) {
            out << s.marks[i] << ",";
        }
        out << s.totalMarks << "," << s.average << "," << s.grade << "\n";
    }

    file.close();
    QMessageBox::information(this, "Export Complete", "Data exported successfully to CSV!");
}

void MainWindow::loadSettingsAndData() {
    onLoadData();
    updateTable();
    updateStatistics();
    chartsWidget->updateCharts(studentsList);
}

void MainWindow::saveSettingsAndData() {
    onSaveData();
}

void MainWindow::onToggleTheme() {
    isDarkMode = !isDarkMode;
    
    QString styleFilePath = isDarkMode ? ":/style.qss" : ":/light_style.qss";
    QFile styleFile(styleFilePath);
    if (styleFile.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream styleStream(&styleFile);
        qApp->setStyleSheet(styleStream.readAll());
        styleFile.close();
    }
    
    themeToggleBtn->setText(isDarkMode ? "☀️ Light Mode" : "🌙 Dark Mode");
    
    // Update addBtn style dynamically based on theme (since it's inline)
    if (isDarkMode) {
        addBtn->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #10b981, stop:1 #059669); color: #ffffff; font-weight: bold; border-radius: 8px;");
    } else {
        addBtn->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #10b981, stop:1 #047857); color: #ffffff; font-weight: bold; border-radius: 8px;");
    }
    
    // Update charts theme
    chartsWidget->setTheme(isDarkMode);
    chartsWidget->updateCharts(studentsList);
}
