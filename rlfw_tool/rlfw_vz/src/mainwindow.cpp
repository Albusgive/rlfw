#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "ComcenterDebug.h"
#include "QPushButton"
#include <QtCharts>
#include <qcombobox.h>
#include <qcontainerfwd.h>
#include <qlogging.h>
#include <qobject.h>
#include <qpushbutton.h>
#include <qsize.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  comcenter_debug = new ComcenterDebug("rlfw_vz");
  // 请求服务器参数
  connect(ui->get_cfg_btn, &QPushButton::clicked, comcenter_debug,
          &ComcenterDebug::requestComParameter);
  connect(
      comcenter_debug, &ComcenterDebug::emitComParameter, this,
      [=](QString type, QStringList names, QStringList types) {
        QString msg;
        for (int i = 0; i < names.size() && i < types.size(); ++i) {
          msg += QString("<span style='color: blue;'>%1</span>").arg(names[i]) +
                 ": " +
                 QString("<span style='color: green;'>%1</span><br>")
                     .arg(types[i]);
        }
        if (type == "MountCom") {
          ui->coms_text_edit->setText(msg);
          coms = names;
        } else if (type == "MountMotor") {
          ui->joints_text_edit->setText(msg);
          joints = names;
        } else if (type == "MountRmote") {
          ui->remotes_text_edit->setText(msg);
          remotes = names;
        }
      });
  /*-----------------joint界面-----------------*/
  joint_chart = new DynamicChartWidget(ui->joint_plot);
  connect(ui->able_cfg_btn, &QPushButton::clicked, this, [=]() {
    ui->add_joint_combox->addItems(joints);
    ui->del_joint_box->addItems(joints);
  });
  connect(ui->add_joint_combox, &QComboBox::currentTextChanged, joint_chart,
          &DynamicChartWidget::addSeries);
  connect(ui->del_joint_box, &QComboBox::currentTextChanged, joint_chart,
          &DynamicChartWidget::removeSeries);
  connect(ui->joint_select_para, &QComboBox::currentTextChanged,
          comcenter_debug, &ComcenterDebug::setJointDataType);
}
MainWindow::~MainWindow() { delete ui; }
