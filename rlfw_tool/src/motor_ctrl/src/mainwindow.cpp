#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QPushButton"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  motorCTRLnode = new MotorCTRL("motor_ctrl");
  connect(ui->pushButton, &QPushButton::clicked, this,
          [this]() { motorCTRLnode->pub(); });
  connect(ui->pushButton_2, &QPushButton::clicked, this,
          [this]() { motorCTRLnode->stop(); });
  connect(ui->pushButton_3, &QPushButton::clicked, this,
          [this]() { motorCTRLnode->request(); });
  connect(ui->pushButton_4, &QPushButton::clicked, this,
          [this]() { 
            if(ui->pushButton_4->isCheckable())
            {
                ui->pushButton_4->setCheckable(false);
                motorCTRLnode->enable(1);
                ui->pushButton_4->setText("电机失能");
            }
            else {
                ui->pushButton_4->setCheckable(true);
                motorCTRLnode->enable(0);
                ui->pushButton_4->setText("电机使能");
            }
          });
  connect(motorCTRLnode, SIGNAL(emitTopicData(QString)), this,
          SLOT(updateTopicInfo(QString)));
  connect(motorCTRLnode, SIGNAL(emitSrvData(QString)), this,
          SLOT(updateSrvInfo(QString)));
}
void MainWindow::updateTopicInfo(QString data) {
  ui->label_2->clear();
  ui->label_2->setText(data);
}
void MainWindow::updateSrvInfo(QString data) {
  ui->label->clear();
  ui->label->setText(data);
}
MainWindow::~MainWindow() { delete ui; }
