#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ComcenterDebug.h"
#include "DynamicChartWidget.h"
#include <QMainWindow>
#include <QPolygon>
#include <qbrush.h>
#include <qcontainerfwd.h>
#include <qimage.h>
#include <qobject.h>
#include <qpoint.h>
#include <qtimer.h>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  Ui::MainWindow *ui;
  ComcenterDebug *comcenter_debug;
  QStringList joints;
  QStringList coms;
  QStringList com_types;
  QStringList remotes;
  QStringList remote_types;
  // joint界面
  DynamicChartWidget *joint_chart;
  void connectJoint();
  void ctrlJoint();
  void allJointDisable();
  void allJointEnable();
  QTimer *joint_send_timer;

  // com界面
  void connectCom();
  QTimer *com_send_timer;
  void sendCom();

  // remote界面
  // gamepad子界面
  void connectRemote();
  QPoint lxy, rxy;
  QBrush l_brush,r_brush;
  QImage overlayImages(QImage baseImage, QImage topImage,
                       const QVector<QPolygon> &regions, QPoint l, QPoint r);
  QImage gamepad_base, gamepad_top;
  QHash<QString, QPolygon> gamepad_map = {
      {"a", QPolygon(QRect(QPoint(405, 138), QSize(48, 41)))},
      {"b", QPolygon(QRect(QPoint(440, 104), QSize(48, 41)))},
      {"x", QPolygon(QRect(QPoint(367, 103), QSize(48, 41)))},
      {"y", QPolygon(QRect(QPoint(405, 69), QSize(48, 41)))},
      {"lb", QPolygon(QRect(QPoint(107, 24), QPoint(233, 70)))},
      {"rb", QPolygon(QRect(QPoint(353, 22), QPoint(477, 73)))},
      {"screenhot", QPolygon(QRect(QPoint(245, 110), QSize(35, 28)))},
      {"menu", QPolygon(QRect(QPoint(317, 110), QSize(35, 28)))},
      {"home", QPolygon(QRect(QPoint(272, 53), QPoint(323, 97)))},
      // {"start",QPolygon()},
      {"xx1", QPolygon(QRect(QPoint(238, 195), QSize(25, 20)))},
      {"yy1", QPolygon(QRect(QPoint(220, 213), QSize(20, 25)))},
      {"xx2", QPolygon(QRect(QPoint(195, 197), QSize(25, 20)))},
      {"yy2", QPolygon(QRect(QPoint(220, 170), QSize(20, 25)))},
  };
  void updateGamepad(QStringList key, QVector<float> value);
};
#endif // MAINWINDOW_H
