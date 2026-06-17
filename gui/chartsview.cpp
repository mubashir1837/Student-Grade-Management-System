#include "chartsview.h"
#include <QHBoxLayout>
#include <QColor>
#include <QBrush>
#include <QFont>
#include <QPen>

ChartsView::ChartsView(QWidget *parent) : QWidget(parent) {
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    barChart = new QChart();
    pieChart = new QChart();

    barChartView = new QChartView(barChart, this);
    pieChartView = new QChartView(pieChart, this);

    barChartView->setRenderHint(QPainter::Antialiasing);
    pieChartView->setRenderHint(QPainter::Antialiasing);

    mainLayout->addWidget(barChartView, 3);
    mainLayout->addWidget(pieChartView, 2);

    setupTheme(barChart);
    setupTheme(pieChart);
}

void ChartsView::setTheme(bool darkMode) {
    isDarkMode = darkMode;
    setupTheme(barChart);
    setupTheme(pieChart);
}

void ChartsView::setupTheme(QChart *chart) {
    if (isDarkMode) {
        chart->setBackgroundBrush(QBrush(QColor("#1e293b"))); // matching groupbox dark background
        chart->setTitleBrush(QBrush(QColor("#38bdf8")));     // Light cyan title
        chart->legend()->setLabelColor(QColor("#94a3b8"));
    } else {
        chart->setBackgroundBrush(QBrush(QColor("#ffffff"))); // White card background
        chart->setTitleBrush(QBrush(QColor("#0284c7")));     // Sky blue title
        chart->legend()->setLabelColor(QColor("#475569"));
    }
    
    QFont titleFont = chart->titleFont();
    titleFont.setBold(true);
    titleFont.setPointSize(14);
    chart->setTitleFont(titleFont);
    
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
}

void ChartsView::updateCharts(const QVector<Student>& students) {
    // Clear old data
    barChart->removeAllSeries();
    pieChart->removeAllSeries();
    
    // Remove axes from previous plots
    for (auto axis : barChart->axes()) {
        barChart->removeAxis(axis);
        delete axis;
    }

    if (students.isEmpty()) {
        barChart->setTitle("Subject Averages (No Data)");
        pieChart->setTitle("Grade Distribution (No Data)");
        return;
    }

    QColor labelColor = isDarkMode ? QColor("#94a3b8") : QColor("#475569");
    QColor linePenColor = isDarkMode ? QColor("#475569") : QColor("#cbd5e1");
    QColor gridPenColor = isDarkMode ? QColor("#334155") : QColor("#f1f5f9");
    QColor barColor = isDarkMode ? QColor("#38bdf8") : QColor("#0284c7");
    QColor barBorderColor = isDarkMode ? QColor("#0284c7") : QColor("#0369a1");

    // 1. BAR CHART: SUBJECT AVERAGES
    barChart->setTitle("Subject-Wise Performance Averages");
    QBarSeries *barSeries = new QBarSeries();
    QBarSet *averageSet = new QBarSet("Class Average (%)");
    averageSet->setColor(barColor);
    averageSet->setBorderColor(barBorderColor);

    float subjectSum[NUM_SUBJECTS] = {0.0f};
    for (const auto& s : students) {
        for (int i = 0; i < NUM_SUBJECTS; ++i) {
            subjectSum[i] += s.marks[i];
        }
    }

    QStringList categories;
    for (int i = 0; i < NUM_SUBJECTS; ++i) {
        float avg = subjectSum[i] / students.size();
        *averageSet << avg;
        categories << SUBJECTS[i];
    }

    barSeries->append(averageSet);
    barChart->addSeries(barSeries);

    // Axes
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setLabelsColor(labelColor);
    axisX->setLinePen(QPen(linePenColor));
    barChart->addAxis(axisX, Qt::AlignBottom);
    barSeries->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 100);
    axisY->setTitleText("Percentage");
    axisY->setTitleBrush(QBrush(labelColor));
    axisY->setLabelsColor(labelColor);
    axisY->setLinePen(QPen(linePenColor));
    axisY->setGridLinePen(QPen(gridPenColor));
    barChart->addAxis(axisY, Qt::AlignLeft);
    barSeries->attachAxis(axisY);


    // 2. PIE CHART: GRADE DISTRIBUTION
    pieChart->setTitle("Class Grade Distribution");
    QPieSeries *pieSeries = new QPieSeries();

    int gradeCounts[5] = {0}; // A, B, C, D, F
    for (const auto& s : students) {
        if (s.grade == 'A') gradeCounts[0]++;
        else if (s.grade == 'B') gradeCounts[1]++;
        else if (s.grade == 'C') gradeCounts[2]++;
        else if (s.grade == 'D') gradeCounts[3]++;
        else gradeCounts[4]++;
    }

    QString grades[5] = {"Grade A", "Grade B", "Grade C", "Grade D", "Grade F"};
    QString colors[5] = {"#10b981", "#3b82f6", "#eab308", "#a855f7", "#ef4444"};

    for (int i = 0; i < 5; ++i) {
        if (gradeCounts[i] > 0) {
            float pct = (static_cast<float>(gradeCounts[i]) / students.size()) * 100.0f;
            QString label = QString("%1: %2 (%3%)").arg(grades[i]).arg(gradeCounts[i]).arg(QString::number(pct, 'f', 1));
            QPieSlice *slice = pieSeries->append(label, gradeCounts[i]);
            slice->setBrush(QColor(colors[i]));
            slice->setPen(QPen(isDarkMode ? QColor("#1e293b") : QColor("#ffffff"), 1.5));
            slice->setLabelVisible(true);
            slice->setLabelColor(isDarkMode ? QColor("#f8fafc") : QColor("#0f172a"));
        }
    }

    pieChart->addSeries(pieSeries);
}
