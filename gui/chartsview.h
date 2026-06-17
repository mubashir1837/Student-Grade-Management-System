#ifndef CHARTSVIEW_H
#define CHARTSVIEW_H

#include <QWidget>
#include <QChartView>
#include <QChart>
#include <QBarSeries>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QPieSeries>
#include <QPieSlice>
#include "student.h"

class ChartsView : public QWidget {
    Q_OBJECT

public:
    explicit ChartsView(QWidget *parent = nullptr);
    void updateCharts(const QVector<Student>& students);
    void setTheme(bool darkMode);

private:
    void setupTheme(QChart *chart);

    QChartView *barChartView;
    QChartView *pieChartView;

    QChart *barChart;
    QChart *pieChart;
    bool isDarkMode = true;
};

#endif // CHARTSVIEW_H
