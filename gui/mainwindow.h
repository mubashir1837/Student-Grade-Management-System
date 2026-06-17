#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVector>
#include "student.h"
#include "chartsview.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddStudent();
    void onEditStudent();
    void onDeleteStudent();
    void onSearchChanged(const QString &text);
    void onSaveData();
    void onLoadData();
    void onClearDatabase();
    void onExportCSV();
    void onTableSelectionChanged();
    void onToggleTheme();

private:
    void setupUi();
    void updateTable();
    void updateStatistics();
    void loadSettingsAndData();
    void saveSettingsAndData();

    // Data Store
    QVector<Student> studentsList;
    const QString dbFilename = "students_db.txt";
    bool isDarkMode = true;

    // Main widgets
    QTableWidget *studentsTable;
    QLineEdit *searchEdit;
    
    // KPI Labels
    QLabel *kpiTotalStudents;
    QLabel *kpiClassAverage;
    QLabel *kpiTopper;
    QLabel *kpiLowest;

    // Control Buttons
    QPushButton *addBtn;
    QPushButton *editBtn;
    QPushButton *deleteBtn;
    QPushButton *saveBtn;
    QPushButton *themeToggleBtn;
    QPushButton *clearBtn;
    QPushButton *exportBtn;

    // Charts component
    ChartsView *chartsWidget;
};

#endif // MAINWINDOW_H
