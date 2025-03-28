/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_4;
    QTabWidget *virtualmotor;
    QWidget *config;
    QGridLayout *gridLayout_3;
    QWidget *widget;
    QFormLayout *formLayout;
    QLabel *label;
    QTextEdit *coms_text_edit;
    QLabel *label_2;
    QTextEdit *joints_text_edit;
    QLabel *label_3;
    QTextEdit *remotes_text_edit;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout;
    QPushButton *get_cfg_btn;
    QPushButton *able_cfg_btn;
    QWidget *joint;
    QGridLayout *gridLayout_2;
    QWidget *widget_2;
    QGridLayout *gridLayout;
    QLabel *label_5;
    QLabel *label_7;
    QLabel *label_6;
    QComboBox *del_joint_box;
    QComboBox *joint_select_para;
    QComboBox *add_joint_combox;
    QWidget *widget_4;
    QGridLayout *gridLayout_6;
    QLabel *label_8;
    QComboBox *ctrl_joint;
    QLabel *label_13;
    QComboBox *ctrl_joint_type;
    QWidget *widget_5;
    QGridLayout *gridLayout_5;
    QLabel *label_11;
    QLabel *label_4;
    QLabel *label_12;
    QLabel *label_10;
    QLabel *label_9;
    QLineEdit *pos;
    QLineEdit *torque;
    QLineEdit *vel;
    QLineEdit *kp;
    QLineEdit *kd;
    QCheckBox *is_timer;
    QLineEdit *timer;
    QLabel *label_14;
    QPushButton *send_joint;
    QPushButton *setZerobtn;
    QPushButton *joint_enable;
    QPushButton *joint_disable;
    QPushButton *all_joint_enable;
    QPushButton *all_joint_disable;
    QWidget *joint_plot;
    QWidget *com;
    QGridLayout *gridLayout_9;
    QWidget *widget_6;
    QGridLayout *gridLayout_7;
    QLabel *label_15;
    QLabel *label_24;
    QTextEdit *com_send_history_id;
    QLabel *label_17;
    QLabel *label_22;
    QLineEdit *com_send_canid;
    QLineEdit *com_send_data;
    QLabel *label_16;
    QLabel *label_23;
    QTextEdit *com_receive_id;
    QTextEdit *com_receive_data;
    QTextEdit *com_send_history_data;
    QWidget *widget_7;
    QGridLayout *gridLayout_8;
    QPushButton *com_send_btn;
    QLabel *label_19;
    QLabel *label_20;
    QLineEdit *com_type;
    QComboBox *com_select;
    QLabel *label_18;
    QLineEdit *com_timer;
    QPushButton *com_clear_btn;
    QCheckBox *com_is_timer;
    QComboBox *canid_type;
    QLabel *label_21;
    QSpacerItem *verticalSpacer;
    QWidget *remote;
    QGridLayout *gridLayout_11;
    QLabel *remote_img;
    QWidget *widget_8;
    QGridLayout *gridLayout_10;
    QPushButton *remote_mapping_btn;
    QLineEdit *remote_type;
    QLabel *label_26;
    QLabel *label_27;
    QComboBox *remote_select;
    QTextEdit *remote_mapping_keys;
    QLabel *label_25;
    QPushButton *remote_jump_btn;
    QLabel *remote_mappint_tip;
    QMenuBar *menubar;
    QMenu *menufile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1057, 623);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(183, 242, 226);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout_4 = new QGridLayout(centralwidget);
        gridLayout_4->setObjectName("gridLayout_4");
        virtualmotor = new QTabWidget(centralwidget);
        virtualmotor->setObjectName("virtualmotor");
        virtualmotor->setStyleSheet(QString::fromUtf8("background-color: rgb(183, 242, 226);"));
        config = new QWidget();
        config->setObjectName("config");
        gridLayout_3 = new QGridLayout(config);
        gridLayout_3->setObjectName("gridLayout_3");
        widget = new QWidget(config);
        widget->setObjectName("widget");
        formLayout = new QFormLayout(widget);
        formLayout->setObjectName("formLayout");
        label = new QLabel(widget);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        coms_text_edit = new QTextEdit(widget);
        coms_text_edit->setObjectName("coms_text_edit");
        coms_text_edit->setStyleSheet(QString::fromUtf8("background-color: rgb(204, 255, 244);"));

        formLayout->setWidget(0, QFormLayout::FieldRole, coms_text_edit);

        label_2 = new QLabel(widget);
        label_2->setObjectName("label_2");

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        joints_text_edit = new QTextEdit(widget);
        joints_text_edit->setObjectName("joints_text_edit");
        joints_text_edit->setStyleSheet(QString::fromUtf8("background-color: rgb(204, 255, 244);"));

        formLayout->setWidget(1, QFormLayout::FieldRole, joints_text_edit);

        label_3 = new QLabel(widget);
        label_3->setObjectName("label_3");

        formLayout->setWidget(3, QFormLayout::LabelRole, label_3);

        remotes_text_edit = new QTextEdit(widget);
        remotes_text_edit->setObjectName("remotes_text_edit");
        remotes_text_edit->setStyleSheet(QString::fromUtf8("background-color: rgb(204, 255, 244);"));

        formLayout->setWidget(3, QFormLayout::FieldRole, remotes_text_edit);


        gridLayout_3->addWidget(widget, 0, 0, 1, 1);

        widget_3 = new QWidget(config);
        widget_3->setObjectName("widget_3");
        verticalLayout = new QVBoxLayout(widget_3);
        verticalLayout->setObjectName("verticalLayout");
        get_cfg_btn = new QPushButton(widget_3);
        get_cfg_btn->setObjectName("get_cfg_btn");
        get_cfg_btn->setMinimumSize(QSize(200, 200));
        get_cfg_btn->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(get_cfg_btn);

        able_cfg_btn = new QPushButton(widget_3);
        able_cfg_btn->setObjectName("able_cfg_btn");
        able_cfg_btn->setMinimumSize(QSize(200, 200));

        verticalLayout->addWidget(able_cfg_btn);


        gridLayout_3->addWidget(widget_3, 0, 1, 1, 1);

        virtualmotor->addTab(config, QString());
        joint = new QWidget();
        joint->setObjectName("joint");
        gridLayout_2 = new QGridLayout(joint);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        widget_2 = new QWidget(joint);
        widget_2->setObjectName("widget_2");
        widget_2->setMinimumSize(QSize(0, 0));
        widget_2->setMaximumSize(QSize(500, 16777215));
        widget_2->setStyleSheet(QString::fromUtf8("background-color: rgb(153, 193, 241);"));
        gridLayout = new QGridLayout(widget_2);
        gridLayout->setObjectName("gridLayout");
        label_5 = new QLabel(widget_2);
        label_5->setObjectName("label_5");

        gridLayout->addWidget(label_5, 0, 0, 1, 1);

        label_7 = new QLabel(widget_2);
        label_7->setObjectName("label_7");

        gridLayout->addWidget(label_7, 2, 0, 1, 1);

        label_6 = new QLabel(widget_2);
        label_6->setObjectName("label_6");

        gridLayout->addWidget(label_6, 1, 0, 1, 1);

        del_joint_box = new QComboBox(widget_2);
        del_joint_box->addItem(QString());
        del_joint_box->setObjectName("del_joint_box");

        gridLayout->addWidget(del_joint_box, 1, 1, 1, 1);

        joint_select_para = new QComboBox(widget_2);
        joint_select_para->addItem(QString());
        joint_select_para->addItem(QString());
        joint_select_para->addItem(QString());
        joint_select_para->addItem(QString());
        joint_select_para->addItem(QString());
        joint_select_para->addItem(QString());
        joint_select_para->addItem(QString());
        joint_select_para->addItem(QString());
        joint_select_para->setObjectName("joint_select_para");

        gridLayout->addWidget(joint_select_para, 2, 1, 1, 1);

        add_joint_combox = new QComboBox(widget_2);
        add_joint_combox->addItem(QString());
        add_joint_combox->setObjectName("add_joint_combox");

        gridLayout->addWidget(add_joint_combox, 0, 1, 1, 1);


        gridLayout_2->addWidget(widget_2, 0, 1, 1, 1);

        widget_4 = new QWidget(joint);
        widget_4->setObjectName("widget_4");
        widget_4->setMinimumSize(QSize(0, 0));
        widget_4->setMaximumSize(QSize(500, 16777215));
        widget_4->setStyleSheet(QString::fromUtf8("background-color: rgb(68, 112, 199);"));
        gridLayout_6 = new QGridLayout(widget_4);
        gridLayout_6->setObjectName("gridLayout_6");
        gridLayout_6->setContentsMargins(3, 3, 3, 3);
        label_8 = new QLabel(widget_4);
        label_8->setObjectName("label_8");
        label_8->setMaximumSize(QSize(70, 16777215));

        gridLayout_6->addWidget(label_8, 0, 0, 1, 1);

        ctrl_joint = new QComboBox(widget_4);
        ctrl_joint->addItem(QString());
        ctrl_joint->setObjectName("ctrl_joint");

        gridLayout_6->addWidget(ctrl_joint, 0, 2, 1, 2);

        label_13 = new QLabel(widget_4);
        label_13->setObjectName("label_13");
        label_13->setMaximumSize(QSize(70, 16777215));

        gridLayout_6->addWidget(label_13, 0, 4, 1, 1);

        ctrl_joint_type = new QComboBox(widget_4);
        ctrl_joint_type->addItem(QString());
        ctrl_joint_type->addItem(QString());
        ctrl_joint_type->addItem(QString());
        ctrl_joint_type->addItem(QString());
        ctrl_joint_type->addItem(QString());
        ctrl_joint_type->setObjectName("ctrl_joint_type");

        gridLayout_6->addWidget(ctrl_joint_type, 0, 5, 1, 1);

        widget_5 = new QWidget(widget_4);
        widget_5->setObjectName("widget_5");
        widget_5->setMinimumSize(QSize(30, 0));
        widget_5->setMaximumSize(QSize(16777215, 80));
        widget_5->setStyleSheet(QString::fromUtf8("background-color: rgb(222, 221, 218);"));
        gridLayout_5 = new QGridLayout(widget_5);
        gridLayout_5->setObjectName("gridLayout_5");
        gridLayout_5->setHorizontalSpacing(9);
        gridLayout_5->setVerticalSpacing(2);
        label_11 = new QLabel(widget_5);
        label_11->setObjectName("label_11");
        label_11->setMinimumSize(QSize(50, 0));
        label_11->setMaximumSize(QSize(50, 16777215));

        gridLayout_5->addWidget(label_11, 1, 0, 1, 1);

        label_4 = new QLabel(widget_5);
        label_4->setObjectName("label_4");
        label_4->setMinimumSize(QSize(50, 0));
        label_4->setMaximumSize(QSize(50, 16777215));

        gridLayout_5->addWidget(label_4, 0, 0, 1, 1);

        label_12 = new QLabel(widget_5);
        label_12->setObjectName("label_12");
        label_12->setMinimumSize(QSize(50, 0));
        label_12->setMaximumSize(QSize(50, 16777215));

        gridLayout_5->addWidget(label_12, 1, 2, 1, 1);

        label_10 = new QLabel(widget_5);
        label_10->setObjectName("label_10");
        label_10->setMinimumSize(QSize(50, 0));
        label_10->setMaximumSize(QSize(50, 16777215));

        gridLayout_5->addWidget(label_10, 0, 4, 1, 1);

        label_9 = new QLabel(widget_5);
        label_9->setObjectName("label_9");
        label_9->setMinimumSize(QSize(50, 0));
        label_9->setMaximumSize(QSize(50, 16777215));

        gridLayout_5->addWidget(label_9, 0, 2, 1, 1);

        pos = new QLineEdit(widget_5);
        pos->setObjectName("pos");
        pos->setMinimumSize(QSize(40, 0));
        pos->setMaximumSize(QSize(60, 16777215));

        gridLayout_5->addWidget(pos, 0, 3, 1, 1);

        torque = new QLineEdit(widget_5);
        torque->setObjectName("torque");
        torque->setMinimumSize(QSize(40, 0));
        torque->setMaximumSize(QSize(60, 16777215));

        gridLayout_5->addWidget(torque, 0, 1, 1, 1);

        vel = new QLineEdit(widget_5);
        vel->setObjectName("vel");
        vel->setMinimumSize(QSize(40, 0));
        vel->setMaximumSize(QSize(60, 16777215));

        gridLayout_5->addWidget(vel, 0, 5, 1, 1);

        kp = new QLineEdit(widget_5);
        kp->setObjectName("kp");
        kp->setMinimumSize(QSize(40, 0));
        kp->setMaximumSize(QSize(60, 16777215));

        gridLayout_5->addWidget(kp, 1, 1, 1, 1);

        kd = new QLineEdit(widget_5);
        kd->setObjectName("kd");
        kd->setMinimumSize(QSize(40, 0));
        kd->setMaximumSize(QSize(60, 16777215));

        gridLayout_5->addWidget(kd, 1, 3, 1, 1);


        gridLayout_6->addWidget(widget_5, 1, 0, 1, 6);

        is_timer = new QCheckBox(widget_4);
        is_timer->setObjectName("is_timer");

        gridLayout_6->addWidget(is_timer, 2, 0, 1, 2);

        timer = new QLineEdit(widget_4);
        timer->setObjectName("timer");
        timer->setMinimumSize(QSize(40, 0));
        timer->setMaximumSize(QSize(60, 16777215));

        gridLayout_6->addWidget(timer, 2, 2, 1, 2);

        label_14 = new QLabel(widget_4);
        label_14->setObjectName("label_14");

        gridLayout_6->addWidget(label_14, 2, 4, 1, 1);

        send_joint = new QPushButton(widget_4);
        send_joint->setObjectName("send_joint");

        gridLayout_6->addWidget(send_joint, 2, 5, 1, 1);

        setZerobtn = new QPushButton(widget_4);
        setZerobtn->setObjectName("setZerobtn");

        gridLayout_6->addWidget(setZerobtn, 3, 0, 1, 1);

        joint_enable = new QPushButton(widget_4);
        joint_enable->setObjectName("joint_enable");

        gridLayout_6->addWidget(joint_enable, 3, 1, 1, 2);

        joint_disable = new QPushButton(widget_4);
        joint_disable->setObjectName("joint_disable");

        gridLayout_6->addWidget(joint_disable, 3, 3, 1, 1);

        all_joint_enable = new QPushButton(widget_4);
        all_joint_enable->setObjectName("all_joint_enable");

        gridLayout_6->addWidget(all_joint_enable, 3, 4, 1, 1);

        all_joint_disable = new QPushButton(widget_4);
        all_joint_disable->setObjectName("all_joint_disable");

        gridLayout_6->addWidget(all_joint_disable, 3, 5, 1, 1);


        gridLayout_2->addWidget(widget_4, 1, 1, 1, 1);

        joint_plot = new QWidget(joint);
        joint_plot->setObjectName("joint_plot");
        joint_plot->setMinimumSize(QSize(400, 0));
        joint_plot->setStyleSheet(QString::fromUtf8("background-color: rgb(187, 212, 86);"));

        gridLayout_2->addWidget(joint_plot, 0, 0, 2, 1);

        virtualmotor->addTab(joint, QString());
        com = new QWidget();
        com->setObjectName("com");
        gridLayout_9 = new QGridLayout(com);
        gridLayout_9->setObjectName("gridLayout_9");
        widget_6 = new QWidget(com);
        widget_6->setObjectName("widget_6");
        widget_6->setStyleSheet(QString::fromUtf8("background-color: rgb(251, 151, 184);"));
        gridLayout_7 = new QGridLayout(widget_6);
        gridLayout_7->setObjectName("gridLayout_7");
        label_15 = new QLabel(widget_6);
        label_15->setObjectName("label_15");
        label_15->setMaximumSize(QSize(150, 16777215));

        gridLayout_7->addWidget(label_15, 0, 0, 1, 1);

        label_24 = new QLabel(widget_6);
        label_24->setObjectName("label_24");

        gridLayout_7->addWidget(label_24, 0, 2, 1, 1);

        com_send_history_id = new QTextEdit(widget_6);
        com_send_history_id->setObjectName("com_send_history_id");
        com_send_history_id->setMaximumSize(QSize(150, 16777215));
        com_send_history_id->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 219, 219);"));

        gridLayout_7->addWidget(com_send_history_id, 1, 0, 1, 1);

        label_17 = new QLabel(widget_6);
        label_17->setObjectName("label_17");
        label_17->setMaximumSize(QSize(100, 16777215));

        gridLayout_7->addWidget(label_17, 2, 0, 1, 1);

        label_22 = new QLabel(widget_6);
        label_22->setObjectName("label_22");

        gridLayout_7->addWidget(label_22, 2, 1, 1, 1);

        com_send_canid = new QLineEdit(widget_6);
        com_send_canid->setObjectName("com_send_canid");
        com_send_canid->setMaximumSize(QSize(150, 16777215));
        com_send_canid->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 219, 219);"));

        gridLayout_7->addWidget(com_send_canid, 3, 0, 1, 1);

        com_send_data = new QLineEdit(widget_6);
        com_send_data->setObjectName("com_send_data");
        com_send_data->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 219, 219);"));

        gridLayout_7->addWidget(com_send_data, 3, 1, 1, 2);

        label_16 = new QLabel(widget_6);
        label_16->setObjectName("label_16");
        label_16->setMaximumSize(QSize(100, 16777215));

        gridLayout_7->addWidget(label_16, 4, 0, 1, 1);

        label_23 = new QLabel(widget_6);
        label_23->setObjectName("label_23");

        gridLayout_7->addWidget(label_23, 4, 1, 1, 2);

        com_receive_id = new QTextEdit(widget_6);
        com_receive_id->setObjectName("com_receive_id");
        com_receive_id->setMaximumSize(QSize(150, 16777215));
        com_receive_id->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 219, 219);"));

        gridLayout_7->addWidget(com_receive_id, 5, 0, 1, 1);

        com_receive_data = new QTextEdit(widget_6);
        com_receive_data->setObjectName("com_receive_data");
        com_receive_data->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 219, 219);"));

        gridLayout_7->addWidget(com_receive_data, 5, 1, 1, 2);

        com_send_history_data = new QTextEdit(widget_6);
        com_send_history_data->setObjectName("com_send_history_data");
        com_send_history_data->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 219, 219);"));

        gridLayout_7->addWidget(com_send_history_data, 1, 1, 1, 2);


        gridLayout_9->addWidget(widget_6, 0, 0, 2, 1);

        widget_7 = new QWidget(com);
        widget_7->setObjectName("widget_7");
        widget_7->setMaximumSize(QSize(300, 16777215));
        widget_7->setStyleSheet(QString::fromUtf8("background-color: rgb(154, 153, 150);"));
        gridLayout_8 = new QGridLayout(widget_7);
        gridLayout_8->setObjectName("gridLayout_8");
        com_send_btn = new QPushButton(widget_7);
        com_send_btn->setObjectName("com_send_btn");
        com_send_btn->setMaximumSize(QSize(100, 16777215));
        com_send_btn->setStyleSheet(QString::fromUtf8("background-color: rgb(192, 191, 188);"));

        gridLayout_8->addWidget(com_send_btn, 3, 0, 1, 1);

        label_19 = new QLabel(widget_7);
        label_19->setObjectName("label_19");

        gridLayout_8->addWidget(label_19, 1, 0, 1, 1);

        label_20 = new QLabel(widget_7);
        label_20->setObjectName("label_20");
        label_20->setMaximumSize(QSize(200, 16777215));

        gridLayout_8->addWidget(label_20, 4, 2, 1, 1);

        com_type = new QLineEdit(widget_7);
        com_type->setObjectName("com_type");
        com_type->setMaximumSize(QSize(200, 16777215));
        com_type->setStyleSheet(QString::fromUtf8("background-color: rgb(192, 191, 188);"));
        com_type->setReadOnly(true);

        gridLayout_8->addWidget(com_type, 1, 1, 1, 2);

        com_select = new QComboBox(widget_7);
        com_select->addItem(QString());
        com_select->setObjectName("com_select");
        com_select->setMaximumSize(QSize(200, 16777215));
        com_select->setStyleSheet(QString::fromUtf8("background-color: rgb(192, 191, 188);"));

        gridLayout_8->addWidget(com_select, 0, 1, 1, 2);

        label_18 = new QLabel(widget_7);
        label_18->setObjectName("label_18");

        gridLayout_8->addWidget(label_18, 0, 0, 1, 1);

        com_timer = new QLineEdit(widget_7);
        com_timer->setObjectName("com_timer");
        com_timer->setMinimumSize(QSize(40, 0));
        com_timer->setMaximumSize(QSize(60, 16777215));
        com_timer->setStyleSheet(QString::fromUtf8("background-color: rgb(222, 221, 218);"));

        gridLayout_8->addWidget(com_timer, 4, 1, 1, 1);

        com_clear_btn = new QPushButton(widget_7);
        com_clear_btn->setObjectName("com_clear_btn");
        com_clear_btn->setMaximumSize(QSize(100, 16777215));
        com_clear_btn->setStyleSheet(QString::fromUtf8("background-color: rgb(192, 191, 188);"));

        gridLayout_8->addWidget(com_clear_btn, 3, 1, 1, 2);

        com_is_timer = new QCheckBox(widget_7);
        com_is_timer->setObjectName("com_is_timer");
        com_is_timer->setMaximumSize(QSize(100, 16777215));
        com_is_timer->setStyleSheet(QString::fromUtf8("background-color: rgb(192, 191, 188);"));

        gridLayout_8->addWidget(com_is_timer, 4, 0, 1, 1);

        canid_type = new QComboBox(widget_7);
        canid_type->addItem(QString());
        canid_type->addItem(QString());
        canid_type->setObjectName("canid_type");
        canid_type->setStyleSheet(QString::fromUtf8("background-color: rgb(192, 191, 188);"));

        gridLayout_8->addWidget(canid_type, 2, 1, 1, 2);

        label_21 = new QLabel(widget_7);
        label_21->setObjectName("label_21");

        gridLayout_8->addWidget(label_21, 2, 0, 1, 1);


        gridLayout_9->addWidget(widget_7, 0, 1, 1, 1);

        verticalSpacer = new QSpacerItem(268, 380, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_9->addItem(verticalSpacer, 1, 1, 1, 1);

        virtualmotor->addTab(com, QString());
        remote = new QWidget();
        remote->setObjectName("remote");
        gridLayout_11 = new QGridLayout(remote);
        gridLayout_11->setObjectName("gridLayout_11");
        remote_img = new QLabel(remote);
        remote_img->setObjectName("remote_img");
        remote_img->setMinimumSize(QSize(598, 422));
        remote_img->setStyleSheet(QString::fromUtf8("background-color: rgb(143, 240, 164);"));

        gridLayout_11->addWidget(remote_img, 1, 0, 1, 1);

        widget_8 = new QWidget(remote);
        widget_8->setObjectName("widget_8");
        gridLayout_10 = new QGridLayout(widget_8);
        gridLayout_10->setObjectName("gridLayout_10");
        remote_mapping_btn = new QPushButton(widget_8);
        remote_mapping_btn->setObjectName("remote_mapping_btn");

        gridLayout_10->addWidget(remote_mapping_btn, 2, 0, 1, 2);

        remote_type = new QLineEdit(widget_8);
        remote_type->setObjectName("remote_type");
        remote_type->setReadOnly(true);

        gridLayout_10->addWidget(remote_type, 1, 2, 1, 1);

        label_26 = new QLabel(widget_8);
        label_26->setObjectName("label_26");

        gridLayout_10->addWidget(label_26, 1, 0, 1, 1);

        label_27 = new QLabel(widget_8);
        label_27->setObjectName("label_27");

        gridLayout_10->addWidget(label_27, 3, 0, 1, 1);

        remote_select = new QComboBox(widget_8);
        remote_select->addItem(QString());
        remote_select->setObjectName("remote_select");

        gridLayout_10->addWidget(remote_select, 0, 1, 1, 2);

        remote_mapping_keys = new QTextEdit(widget_8);
        remote_mapping_keys->setObjectName("remote_mapping_keys");
        remote_mapping_keys->setStyleSheet(QString::fromUtf8("background-color: rgb(248, 228, 92);"));

        gridLayout_10->addWidget(remote_mapping_keys, 4, 0, 1, 3);

        label_25 = new QLabel(widget_8);
        label_25->setObjectName("label_25");

        gridLayout_10->addWidget(label_25, 0, 0, 1, 1);

        remote_jump_btn = new QPushButton(widget_8);
        remote_jump_btn->setObjectName("remote_jump_btn");

        gridLayout_10->addWidget(remote_jump_btn, 2, 2, 1, 1);


        gridLayout_11->addWidget(widget_8, 0, 1, 2, 1);

        remote_mappint_tip = new QLabel(remote);
        remote_mappint_tip->setObjectName("remote_mappint_tip");
        remote_mappint_tip->setMaximumSize(QSize(16777215, 50));
        remote_mappint_tip->setStyleSheet(QString::fromUtf8("background-color: rgb(143, 240, 164);"));

        gridLayout_11->addWidget(remote_mappint_tip, 0, 0, 1, 1);

        virtualmotor->addTab(remote, QString());

        gridLayout_4->addWidget(virtualmotor, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1057, 27));
        menufile = new QMenu(menubar);
        menufile->setObjectName("menufile");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menufile->menuAction());

        retranslateUi(MainWindow);

        virtualmotor->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "rlfw_vz", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt;\">coms:</span></p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt;\">joints:</span></p></body></html>", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt;\">remotes:</span></p></body></html>", nullptr));
        get_cfg_btn->setText(QCoreApplication::translate("MainWindow", "\350\216\267\345\217\226\351\205\215\347\275\256", nullptr));
        able_cfg_btn->setText(QCoreApplication::translate("MainWindow", "\345\272\224\347\224\250\351\205\215\347\275\256", nullptr));
        virtualmotor->setTabText(virtualmotor->indexOf(config), QCoreApplication::translate("MainWindow", "config", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt;\">add Joint:</span></p></body></html>", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt;\">parameter:</span></p></body></html>", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt;\">del Joint:</span></p></body></html>", nullptr));
        del_joint_box->setItemText(0, QCoreApplication::translate("MainWindow", "None", nullptr));

        joint_select_para->setItemText(0, QCoreApplication::translate("MainWindow", "None", nullptr));
        joint_select_para->setItemText(1, QCoreApplication::translate("MainWindow", "pos", nullptr));
        joint_select_para->setItemText(2, QCoreApplication::translate("MainWindow", "number_laps", nullptr));
        joint_select_para->setItemText(3, QCoreApplication::translate("MainWindow", "vel", nullptr));
        joint_select_para->setItemText(4, QCoreApplication::translate("MainWindow", "torque", nullptr));
        joint_select_para->setItemText(5, QCoreApplication::translate("MainWindow", "current", nullptr));
        joint_select_para->setItemText(6, QCoreApplication::translate("MainWindow", "temperature", nullptr));
        joint_select_para->setItemText(7, QCoreApplication::translate("MainWindow", "state", nullptr));

        add_joint_combox->setItemText(0, QCoreApplication::translate("MainWindow", "None", nullptr));

        label_8->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt;\">Joint:</span></p></body></html>", nullptr));
        ctrl_joint->setItemText(0, QCoreApplication::translate("MainWindow", "None", nullptr));

        label_13->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:18pt;\">type:</span></p></body></html>", nullptr));
        ctrl_joint_type->setItemText(0, QCoreApplication::translate("MainWindow", "None", nullptr));
        ctrl_joint_type->setItemText(1, QCoreApplication::translate("MainWindow", "MIT", nullptr));
        ctrl_joint_type->setItemText(2, QCoreApplication::translate("MainWindow", "POS", nullptr));
        ctrl_joint_type->setItemText(3, QCoreApplication::translate("MainWindow", "VEL", nullptr));
        ctrl_joint_type->setItemText(4, QCoreApplication::translate("MainWindow", "POS_VEL", nullptr));

        label_11->setText(QCoreApplication::translate("MainWindow", "kp:", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "torque:", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "kd:", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "vel:", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "pos:", nullptr));
        pos->setText(QCoreApplication::translate("MainWindow", "0.0", nullptr));
        torque->setText(QCoreApplication::translate("MainWindow", "0.0", nullptr));
        vel->setText(QCoreApplication::translate("MainWindow", "0.0", nullptr));
        kp->setText(QCoreApplication::translate("MainWindow", "0.0", nullptr));
        kd->setText(QCoreApplication::translate("MainWindow", "0.0", nullptr));
        is_timer->setText(QCoreApplication::translate("MainWindow", "\345\256\232\346\227\266\345\217\221\351\200\201", nullptr));
        timer->setText(QCoreApplication::translate("MainWindow", "50.0", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>time(ms)</p></body></html>", nullptr));
        send_joint->setText(QCoreApplication::translate("MainWindow", "send", nullptr));
        setZerobtn->setText(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256\351\233\266\347\202\271", nullptr));
        joint_enable->setText(QCoreApplication::translate("MainWindow", "\347\224\265\346\234\272\344\275\277\350\203\275", nullptr));
        joint_disable->setText(QCoreApplication::translate("MainWindow", "\347\224\265\346\234\272\345\244\261\350\203\275", nullptr));
        all_joint_enable->setText(QCoreApplication::translate("MainWindow", "\346\211\200\346\234\211\347\224\265\346\234\272\344\275\277\350\203\275", nullptr));
        all_joint_disable->setText(QCoreApplication::translate("MainWindow", "\346\211\200\346\234\211\347\224\265\346\234\272\345\244\261\350\203\275", nullptr));
        virtualmotor->setTabText(virtualmotor->indexOf(joint), QCoreApplication::translate("MainWindow", "joint", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:16pt;\">send history id:</span></p></body></html>", nullptr));
        label_24->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:16pt;\">send history data:</span></p></body></html>", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:16pt;\">CAN ID:</span></p></body></html>", nullptr));
        label_22->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:16pt;\">DATA:</span></p></body></html>", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:16pt;\">receive id:</span></p></body></html>", nullptr));
        label_23->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:16pt;\">receive data:</span></p></body></html>", nullptr));
        com_send_btn->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:16pt;\">Com type:</span></p></body></html>", nullptr));
        label_20->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>time(ms)</p></body></html>", nullptr));
        com_type->setText(QCoreApplication::translate("MainWindow", "None", nullptr));
        com_select->setItemText(0, QCoreApplication::translate("MainWindow", "None", nullptr));

        label_18->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:16pt;\">Com:</span></p></body></html>", nullptr));
        com_timer->setText(QCoreApplication::translate("MainWindow", "100.0", nullptr));
        com_clear_btn->setText(QCoreApplication::translate("MainWindow", "\346\270\205\347\220\206\346\225\260\346\215\256", nullptr));
        com_is_timer->setText(QCoreApplication::translate("MainWindow", "\345\256\232\346\227\266\345\217\221\351\200\201", nullptr));
        canid_type->setItemText(0, QCoreApplication::translate("MainWindow", "STD", nullptr));
        canid_type->setItemText(1, QCoreApplication::translate("MainWindow", "EXT", nullptr));

        label_21->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:16pt;\">CAN TYPE\357\274\232</span></p></body></html>", nullptr));
        virtualmotor->setTabText(virtualmotor->indexOf(com), QCoreApplication::translate("MainWindow", "com", nullptr));
        remote_img->setText(QString());
        remote_mapping_btn->setText(QCoreApplication::translate("MainWindow", "\351\207\215\346\230\240\345\260\204", nullptr));
        label_26->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:16pt;\">Remote type:</span></p></body></html>", nullptr));
        label_27->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:16pt;\">mapping:</span></p></body></html>", nullptr));
        remote_select->setItemText(0, QCoreApplication::translate("MainWindow", "None", nullptr));

        label_25->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:16pt;\">Remote:</span></p></body></html>", nullptr));
        remote_jump_btn->setText(QCoreApplication::translate("MainWindow", "\350\267\263\350\277\207\350\257\245\346\230\240\345\260\204\345\200\274", nullptr));
        remote_mappint_tip->setText(QString());
        virtualmotor->setTabText(virtualmotor->indexOf(remote), QCoreApplication::translate("MainWindow", "remote", nullptr));
        menufile->setTitle(QCoreApplication::translate("MainWindow", "file", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
