#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qcontainerfwd.h>
#include <qobject.h>
#include "ComcenterDebug.h"
#include "DynamicChartWidget.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ComcenterDebug *comcenter_debug;
    QStringList joints;
    QStringList coms;
    QStringList remotes;
    //joint绘制
    DynamicChartWidget *joint_chart;

};
#endif // MAINWINDOW_H
