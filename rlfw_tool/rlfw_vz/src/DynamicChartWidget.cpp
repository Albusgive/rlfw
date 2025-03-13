#include "DynamicChartWidget.h"
#include <QDebug>
#include <QRandomGenerator>
#include <QVBoxLayout>

DynamicChartWidget::DynamicChartWidget(QWidget *parent) : QWidget(parent) {
  // 初始化图表
  chart = new QChart();
  chart->setMargins(QMargins(0, 0, 0, 0)); // 紧凑布局
  chart->setBackgroundRoundness(0);

  // 初始化视图
  chartView = new QChartView(chart);
  chartView->setRenderHint(QPainter::Antialiasing);

  // 初始化坐标轴
  axisX = new QValueAxis;
  axisY = new QValueAxis;
  axisX->setTitleText("Time");
  axisY->setTitleText("Value");
  axisX->setRange(0, 10); // 初始X轴范围
  axisY->setRange(0, 10); // 初始Y轴范围
  chart->addAxis(axisX, Qt::AlignBottom);
  chart->addAxis(axisY, Qt::AlignLeft);

  QVBoxLayout *parentLayout = new QVBoxLayout(parent);
  parentLayout->setContentsMargins(0, 0, 0, 0); // 消除边距
  parentLayout->setSpacing(0);                  // 消除部件间距
  chart->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  parentLayout->addWidget(chartView); // 添加子窗口到父布局
}

DynamicChartWidget::~DynamicChartWidget() {
  qDeleteAll(seriesMap);
  delete chart;
}

// ================== 曲线管理 ==================
void DynamicChartWidget::addSeries(const QString &name) {
  if (name == "None")
    return;
  if (seriesMap.contains(name)) {
    qWarning() << "Series" << name << "already exists!";
    return;
  }
  QLineSeries *series = new QLineSeries;
  series->setName(name);
  series->setColor(generateColor(name));
  chart->addSeries(series);
  series->attachAxis(axisX);
  series->attachAxis(axisY);
  seriesMap[name] = series;
}

void DynamicChartWidget::removeSeries(const QString &name) {
  if (name == "None")
    return;
  if (!seriesMap.contains(name)) {
    qWarning() << "Series" << name << "does not exist!";
    return;
  }
  QLineSeries *series = seriesMap.take(name);
  chart->removeSeries(series);
  delete series;

  // 如果无曲线时重置Y轴
  if (seriesMap.isEmpty()) {
    globalMinY = globalMaxY = 0;
    isFirstDataPoint = true;
    axisY->setRange(0, 10);
  }
}

void DynamicChartWidget::clearAllSeries() {
  for (auto &name : seriesMap.keys()) {
    removeSeries(name);
  }
}

// ================== 数据更新 ==================
void DynamicChartWidget::updateData(const QString &name, qreal x, qreal y) {
  if (!seriesMap.contains(name))
    return;

  // 更新全局Y范围
  if (isFirstDataPoint) {
    globalMinY = globalMaxY = y;
    isFirstDataPoint = false;
  } else {
    globalMinY = qMin(globalMinY, y);
    globalMaxY = qMax(globalMaxY, y);
  }

  // 添加数据点
  seriesMap[name]->append(x, y);

  // 动态调整X轴
  if (x > axisX->max()) {
    axisX->setRange(x - 10, x);
  }

  // 更新Y轴范围
  updateYAxisRange();
}

// ================== Y轴动态范围 ==================
void DynamicChartWidget::updateYAxisRange() {
  if (seriesMap.isEmpty())
    return;

  // 计算缓冲范围（10%的差值）
  const qreal buffer = (globalMaxY - globalMinY) * 0.1;
  const qreal min = globalMinY - buffer;
  const qreal max = globalMaxY + buffer;

  // 避免无效范围
  if (qFuzzyCompare(min + 1, max + 1)) {
    axisY->setRange(min - 1, min + 1);
  } else {
    axisY->setRange(min, max);
  }

  axisY->applyNiceNumbers(); // 优化刻度显示
}

// ================== 颜色生成 ==================
QColor DynamicChartWidget::generateColor(const QString &name) const {
  const uint hash = qHash(name); // 基于名称生成哈希值
  // HSL参数设置
  return QColor::fromHsl(
      hash % 360,              // 色调 (0-359) 覆盖全色环
      150 + (hash >> 8) % 106, // 饱和度 (150-255) 保证颜色鲜艳
      70 + (hash >> 16) % 80   // 亮度 (70-150) 避免过浅
  );
}