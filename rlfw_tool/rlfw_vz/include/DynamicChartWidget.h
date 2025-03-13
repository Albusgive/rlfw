#ifndef DYNAMICCHARTWIDGET_H
#define DYNAMICCHARTWIDGET_H

#include <QWidget>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QHash>
#include <QTimer>
#include <QChartView>


class DynamicChartWidget : public QWidget {
    Q_OBJECT
public:
    explicit DynamicChartWidget(QWidget *parent = nullptr);
    ~DynamicChartWidget();

    // 曲线管理
    void addSeries(const QString &name);       // 添加曲线
    void removeSeries(const QString &name);    // 删除曲线
    void clearAllSeries();                    // 清空所有曲线

    // 数据更新
    void updateData(const QString &name, qreal x, qreal y);

private:
    void updateYAxisRange();                   // Y轴动态范围更新

    QChart *chart;
    QChartView *chartView;
    QHash<QString, QLineSeries*> seriesMap;     // 曲线容器
    QValueAxis *axisX, *axisY;                 // 坐标轴
    QTimer *simulationTimer;                   // 数据生成定时器
    
    qreal currentX = 0;                        // 当前X轴位置
    qreal globalMinY = 0;                      // 全局最小Y值
    qreal globalMaxY = 0;                      // 全局最大Y值
    bool isFirstDataPoint = true;              // 首次数据标记

    QColor generateColor(const QString &name) const;  // 颜色生成
};

#endif // DYNAMICCHARTWIDGET_H