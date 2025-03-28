#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "ComcenterDebug.h"
#include "QPushButton"
#include <QtCharts>
#include <cstdint>
#include <qcheckbox.h>
#include <qcolor.h>
#include <qcombobox.h>
#include <qcontainerfwd.h>
#include <qfont.h>
#include <qlogging.h>
#include <qmainwindow.h>
#include <qnamespace.h>
#include <qobject.h>
#include <qpixmap.h>
#include <qpoint.h>
#include <qpushbutton.h>
#include <qsize.h>
#include <qtimer.h>
#include <qwindowdefs.h>
#include <ratio>
#include <thread>
#include <vector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  comcenter_debug = new ComcenterDebug("rlfw_vz");
  // 请求服务器参数
  connect(ui->get_cfg_btn, &QPushButton::clicked, this, [this]() {
    ui->coms_text_edit->clear();
    ui->joints_text_edit->clear();
    ui->remotes_text_edit->clear();
    joints.clear();
    coms.clear();
    com_types.clear();
    remotes.clear();
    remote_types.clear();
    comcenter_debug->requestComParameter();
    comcenter_debug->requestMappingParameter();
  });
  connect(ui->able_cfg_btn, &QPushButton::clicked, this, [this]() {
    ui->add_joint_combox->clear();
    ui->add_joint_combox->addItem("None");
    ui->del_joint_box->clear();
    ui->del_joint_box->addItem("None");
    ui->ctrl_joint->clear();
    ui->ctrl_joint->addItem("None");
    ui->com_select->clear();
    ui->com_select->addItem("None");
    ui->remote_select->clear();
    ui->remote_select->addItem("None");
    ui->add_joint_combox->addItems(joints);
    ui->del_joint_box->addItems(joints);
    ui->ctrl_joint->addItems(joints);
    ui->com_select->addItems(coms);
    ui->remote_select->addItems(remotes);
    comcenter_debug->resetQos(joints.size());
  });
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
          ui->coms_text_edit->append(msg);
          coms += names;
          com_types += types;
        } else if (type == "MountMotor") {
          ui->joints_text_edit->append(msg);
          joints += names;
        } else if (type == "MountRmote") {
          ui->remotes_text_edit->append(msg);
          remotes += names;
          remote_types += types;
        }
      });
  /*-----------------joint界面-----------------*/
  connectJoint();
  connectCom();
  connectRemote();
  comcenter_debug->start();
}
MainWindow::~MainWindow() { delete ui; }

void MainWindow::connectJoint() {
  joint_chart = new DynamicChartWidget(ui->joint_plot);
  joint_send_timer = new QTimer;
  connect(comcenter_debug, &ComcenterDebug::emitJointData, joint_chart,
          &DynamicChartWidget::updateData);
  connect(ui->add_joint_combox, &QComboBox::currentTextChanged, joint_chart,
          &DynamicChartWidget::addSeries);
  connect(ui->del_joint_box, &QComboBox::currentTextChanged, joint_chart,
          &DynamicChartWidget::removeSeries);
  connect(ui->joint_select_para, &QComboBox::currentTextChanged,
          comcenter_debug, &ComcenterDebug::setJointDataType);
  connect(ui->send_joint, &QPushButton::clicked, this, &MainWindow::ctrlJoint);
  connect(joint_send_timer, &QTimer::timeout, this, &MainWindow::ctrlJoint);
  connect(ui->is_timer, &QCheckBox::checkStateChanged, this,
          [=](Qt::CheckState state) {
            if (state == Qt::CheckState::Checked) {
              float timer_time = ui->timer->text().toFloat();
              ui->timer->setEnabled(false);
              joint_send_timer->setInterval(timer_time);
              joint_send_timer->start();
            } else if (state == Qt::CheckState::Unchecked) {
              ui->timer->setEnabled(true);
              joint_send_timer->stop();
            }
          });
  connect(ui->all_joint_enable, &QPushButton::clicked, this,
          &MainWindow::allJointEnable);
  connect(ui->all_joint_disable, &QPushButton::clicked, this,
          &MainWindow::allJointDisable);
  connect(ui->joint_enable, &QPushButton::clicked, this, [this]() {
    std::string joint_name = ui->ctrl_joint->currentText().toStdString();
    comcenter_debug->enableJoint(joint_name, true);
  });
  connect(ui->joint_disable, &QPushButton::clicked, this, [this]() {
    std::string joint_name = ui->ctrl_joint->currentText().toStdString();
    comcenter_debug->enableJoint(joint_name, false);
  });
  connect(ui->setZerobtn, &QPushButton::clicked, this, [this]() {
    std::string joint_name = ui->ctrl_joint->currentText().toStdString();
    comcenter_debug->setJointZero(joint_name);
  });
}

void MainWindow::ctrlJoint() {
  std::string joint_name = ui->ctrl_joint->currentText().toStdString();
  std::string ctrl_type = ui->ctrl_joint_type->currentText().toStdString();
  float torque = ui->torque->text().toFloat();
  float pos = ui->pos->text().toFloat();
  float vel = ui->vel->text().toFloat();
  float kp = ui->kp->text().toFloat();
  float kd = ui->kd->text().toFloat();
  comcenter_debug->ctrlJoint(joint_name, ctrl_type, torque, pos, vel, kp, kd);
}

void MainWindow::allJointDisable() {
  for (auto joint_name : joints) {
    comcenter_debug->enableJoint(joint_name.toStdString(), false);
  }
}

void MainWindow::allJointEnable() {
  for (auto joint_name : joints) {
    comcenter_debug->enableJoint(joint_name.toStdString(), true);
  }
}

void MainWindow::connectCom() {
  connect(ui->com_select, &QComboBox::currentIndexChanged, this,
          [this](int idx) {
            if (idx > 0) {
              ui->com_type->setText(com_types[idx - 1]);
              comcenter_debug->com_type = com_types[idx - 1];
              if (com_types[idx - 1].contains("can")) {
                ui->canid_type->setEnabled(true);
                ui->com_send_canid->setEnabled(true);
              } else {
                ui->canid_type->setEnabled(false);
                ui->com_send_canid->setEnabled(false);
              }
            }
          });
  connect(ui->com_clear_btn, &QPushButton::clicked, this, [=]() {
    ui->com_send_history_id->clear();
    ui->com_send_history_data->clear();
    ui->com_receive_id->clear();
    ui->com_receive_data->clear();
  });
  connect(comcenter_debug, &ComcenterDebug::emitComData, this,
          [this](qint32 id, QByteArray data) {
            ui->com_receive_id->append(QString::number(id, 16));
            ui->com_receive_data->append(data.toHex().toUpper());
            ui->com_receive_id->append(QString("<br>"));
            ui->com_receive_data->append(QString("<br>"));
          });
  connect(ui->canid_type, &QComboBox::currentIndexChanged, comcenter_debug,
          &ComcenterDebug::changeCanIDType);
  connect(ui->com_select, &QComboBox::currentTextChanged, comcenter_debug,
          &ComcenterDebug::changeComName);
  connect(ui->com_send_btn, &QPushButton::clicked, this, &MainWindow::sendCom);
  com_send_timer = new QTimer;
  connect(com_send_timer, &QTimer::timeout, this, &MainWindow::sendCom);
  connect(ui->com_is_timer, &QCheckBox::checkStateChanged, this,
          [=](Qt::CheckState state) {
            if (state == Qt::CheckState::Checked) {
              float timer_time = ui->com_timer->text().toFloat();
              ui->com_timer->setEnabled(false);
              com_send_timer->setInterval(timer_time);
              com_send_timer->start();
            } else if (state == Qt::CheckState::Unchecked) {
              ui->com_timer->setEnabled(true);
              com_send_timer->stop();
            }
          });
}
void MainWindow::sendCom() {
  QString id = ui->com_send_canid->text();
  QByteArray data_ = ui->com_send_data->text().toLatin1();
  std::vector<uint8_t> data;
  for (auto i : data_)
    data.push_back(i);
  comcenter_debug->sendCom(id.toInt(), data);
  ui->com_send_history_id->append(id);
  ui->com_send_history_data->append(data_.toHex().toUpper());
  ui->com_send_history_id->append(QString("<br>"));
  ui->com_send_history_data->append(QString("<br>"));
}

void MainWindow::connectRemote() {
  gamepad_base = QImage(":/icon/images/gamepad_unable.png");
  gamepad_top = QImage(":/icon/images/gamepad_enable.png");
  lxy = QPoint(168, 123);
  rxy = QPoint(363, 199);
  l_brush = QBrush(Qt::black, Qt::SolidPattern);
  r_brush = QBrush(Qt::black, Qt::SolidPattern);
  font = QFont("", 18);
  auto img =
      overlayImages(gamepad_base, gamepad_top, QVector<QPolygon>(), lxy, rxy);
  ui->remote_img->setPixmap(QPixmap::fromImage(img));
  ui->remote_img->resize(img.size());
  ui->remote_img->move(0, 0);
  connect(ui->remote_select, &QComboBox::currentIndexChanged, this,
          [this](int idx) {
            if (idx > 0) {
              ui->remote_type->setText(remote_types[idx - 1]);
            }
          });
  connect(comcenter_debug, &ComcenterDebug::emitRemote, this,
          [=](QStringList key, QVector<float> value) {
            if (ui->remote_type->text() == "gamepad")
              updateGamepad(key, value);
          });
  // 重映射
  connect(ui->remote_mapping_btn, &QPushButton::clicked, this, [this]() {
    remappping = true;
    remapping_tip = "请按(please press):";
    setRemappingTip("a");
  });
  connect(ui->remote_jump_btn, &QPushButton::clicked, this, [this]() {
    gamepad_key_idx.push_back(-1);
    remapping_idx++;
    setRemappingTip(gamepad_keys[remapping_idx]);
  });
}

QImage MainWindow::overlayImages(QImage baseImage, QImage topImage,
                                 const QVector<QPolygon> &regions, QPoint l,
                                 QPoint r) {
  QImage result(baseImage.size(), QImage::Format_ARGB32_Premultiplied);
  result.fill(Qt::transparent);
  QPainter painter(&result);
  painter.setRenderHint(QPainter::Antialiasing, true);
  painter.drawImage(0, 0, baseImage);
  QPainterPath clipPath;
  for (const auto &polygon : regions) {
    clipPath.addPolygon(polygon);
  }
  painter.setClipPath(clipPath);
  painter.drawImage(0, 0, topImage);

  painter.setClipping(false);
  painter.setBrush(l_brush);
  painter.drawEllipse(l, 20, 20);
  painter.setBrush(r_brush);
  painter.drawEllipse(r, 20, 20);
  painter.setFont(font);
  painter.drawText(
      QPoint(baseImage.width() * 7 / 12, baseImage.height() * 6 / 7),
      "rt:" + QString::number(rt));
  painter.drawText(
      QPoint(baseImage.width() * 3 / 12, baseImage.height() * 6 / 7),
      "lt:" + QString::number(lt));
  return result;
}

void MainWindow::updateGamepad(QStringList key, QVector<float> value) {
  QVector<QPolygon> regions;
  QPoint lxy_, rxy_;
  l_brush.setColor(Qt::black);
  r_brush.setColor(Qt::black);
  if (!remappping) {
    for (int i = 0; i < value.size(); i++) {
      if (value[i] != 0) {
        if (key[i] == "xx") {
          if (value[i] > 0) {
            regions.append(gamepad_map["xx1"]);
          } else if (value[i] < 0) {
            regions.append(gamepad_map["xx2"]);
          }
        } else if (key[i] == "yy") {
          if (value[i] > 0) {
            regions.append(gamepad_map["yy1"]);
          } else if (value[i] < 0) {
            regions.append(gamepad_map["yy2"]);
          }
        } else if (key[i] == "lo") {
          l_brush.setColor(Qt::gray);
        }
        if (key[i] == "ro") {
          r_brush.setColor(Qt::gray);
        } else {
          if (gamepad_map.contains(key[i])) {
            regions.append(gamepad_map[key[i]]);
          }
        }
      }
      if (key[i] == "lx") {
        lxy_.setX(lxy.x() + (value[i] * 20 / 32767));
      } else if (key[i] == "ly") {
        lxy_.setY(lxy.y() + (value[i] * 20 / 32767));
      } else if (key[i] == "rx") {
        rxy_.setX(rxy.x() + (value[i] * 20 / 32767));
      } else if (key[i] == "ry") {
        rxy_.setY(rxy.y() + (value[i] * 20 / 32767));
      }
      if (key[i] == "lt") {
        lt = value[i];
      } else if (key[i] == "rt") {
        rt = value[i];
      }
    }
  } else {
    lxy_ = lxy;
    rxy_ = rxy;
    for (int i = 0; i < value.size(); i++) {
      if (value[i] != 0) {
        if (remapping_idx == gamepad_keys.size()) {
          succeedRemapping();
          return;
        }
        QString now_key = gamepad_keys[remapping_idx];
        if (now_key == "lx" || now_key == "ly" || now_key == "rx" ||
            now_key == "ry" || now_key == "xx" || now_key == "yy" ||
            now_key == "lt" || now_key == "rt") {
          if (value[i] > 32765) {
            temp_value = i;
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
          }

          if (now_key == "lx") {
            lxy_.setX(lxy.x() + (value[i] * 20 / 32767));
          } else if (now_key == "ly") {
            lxy_.setY(lxy.y() + (value[i] * 20 / 32767));
          } else if (now_key == "rx") {
            rxy_.setX(rxy.x() + (value[i] * 20 / 32767));
          } else if (now_key == "ry") {
            rxy_.setY(rxy.y() + (value[i] * 20 / 32767));
          }
          if (now_key == "lt") {
            lt = value[i];
          } else if (now_key == "rt") {
            rt = value[i];
          }
        } else {
          if (value[i] > 0)
            temp_value = i;
        }
        // 检查有没有重复
        bool is_succeed = false;
        for (auto val : gamepad_key_idx) {
          if (val == i)
            is_succeed = true;
        }
        if (!is_succeed && temp_value != -1) {
          qDebug() << gamepad_keys[remapping_idx] << remapping_idx;
          gamepad_key_idx.push_back(temp_value);
          regions.append(gamepad_map[gamepad_keys[remapping_idx]]);
          remapping_idx++;
          temp_value = -1;
          setRemappingTip(gamepad_keys[remapping_idx]);
        }
      }
    }
  }
  QImage result = overlayImages(gamepad_base, gamepad_top, regions, lxy_, rxy_);
  ui->remote_img->setPixmap(QPixmap::fromImage(result));
}

void MainWindow::setRemappingTip(QString key) {
  ui->remote_mappint_tip->clear();
  ui->remote_mappint_tip->setFont(font);
  ui->remote_mappint_tip->setText(remapping_tip + key);
}

void MainWindow::succeedRemapping() {
  remappping = false;
  remapping_idx = 0;
  ui->remote_mappint_tip->setFont(font);
  ui->remote_mappint_tip->setText("已完成重映射(succeed)!");
  QString new_gamepad_keys = "key = \"";
  for (auto idx : gamepad_key_idx) {
    if (idx == -1) {
      new_gamepad_keys.append("none");
    } else {
      new_gamepad_keys.append(gamepad_keys[idx]);
    }
    new_gamepad_keys.append(" ");
  }
  new_gamepad_keys.push_back("\"");
  ui->remote_mapping_keys->setText(new_gamepad_keys);
}

void MainWindow::connectVM() {}
