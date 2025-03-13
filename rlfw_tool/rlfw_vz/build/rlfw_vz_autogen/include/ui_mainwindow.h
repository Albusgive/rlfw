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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
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
    QTabWidget *tabWidget;
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
    QLabel *label_7;
    QComboBox *add_joint_combox;
    QLabel *label_5;
    QComboBox *joint_select_para;
    QComboBox *del_joint_box;
    QLabel *label_6;
    QWidget *widget_4;
    QGridLayout *gridLayout_6;
    QWidget *widget_5;
    QGridLayout *gridLayout_5;
    QTextEdit *vel;
    QTextEdit *pos;
    QTextEdit *kp;
    QTextEdit *torque;
    QLabel *label_9;
    QLabel *label_4;
    QTextEdit *kd;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_10;
    QComboBox *ctrl_joint_type;
    QPushButton *all_joint_stop;
    QPushButton *send_joint;
    QLabel *label_8;
    QLabel *label_14;
    QComboBox *ctrl_joint;
    QPushButton *all_joint_enable;
    QCheckBox *is_timer;
    QLabel *label_13;
    QTextEdit *timer;
    QWidget *joint_plot;
    QWidget *com;
    QWidget *remote;
    QMenuBar *menubar;
    QMenu *menufile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1015, 603);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout_4 = new QGridLayout(centralwidget);
        gridLayout_4->setObjectName("gridLayout_4");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(143, 240, 164);"));
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

        formLayout->setWidget(0, QFormLayout::FieldRole, coms_text_edit);

        label_2 = new QLabel(widget);
        label_2->setObjectName("label_2");

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        joints_text_edit = new QTextEdit(widget);
        joints_text_edit->setObjectName("joints_text_edit");

        formLayout->setWidget(1, QFormLayout::FieldRole, joints_text_edit);

        label_3 = new QLabel(widget);
        label_3->setObjectName("label_3");

        formLayout->setWidget(3, QFormLayout::LabelRole, label_3);

        remotes_text_edit = new QTextEdit(widget);
        remotes_text_edit->setObjectName("remotes_text_edit");

        formLayout->setWidget(3, QFormLayout::FieldRole, remotes_text_edit);


        gridLayout_3->addWidget(widget, 0, 0, 1, 1);

        widget_3 = new QWidget(config);
        widget_3->setObjectName("widget_3");
        verticalLayout = new QVBoxLayout(widget_3);
        verticalLayout->setObjectName("verticalLayout");
        get_cfg_btn = new QPushButton(widget_3);
        get_cfg_btn->setObjectName("get_cfg_btn");
        get_cfg_btn->setMinimumSize(QSize(200, 200));

        verticalLayout->addWidget(get_cfg_btn);

        able_cfg_btn = new QPushButton(widget_3);
        able_cfg_btn->setObjectName("able_cfg_btn");
        able_cfg_btn->setMinimumSize(QSize(200, 200));

        verticalLayout->addWidget(able_cfg_btn);


        gridLayout_3->addWidget(widget_3, 0, 1, 1, 1);

        tabWidget->addTab(config, QString());
        joint = new QWidget();
        joint->setObjectName("joint");
        gridLayout_2 = new QGridLayout(joint);
        gridLayout_2->setObjectName("gridLayout_2");
        widget_2 = new QWidget(joint);
        widget_2->setObjectName("widget_2");
        widget_2->setMinimumSize(QSize(0, 0));
        widget_2->setMaximumSize(QSize(400, 16777215));
        widget_2->setStyleSheet(QString::fromUtf8("background-color: rgb(153, 193, 241);"));
        gridLayout = new QGridLayout(widget_2);
        gridLayout->setObjectName("gridLayout");
        label_7 = new QLabel(widget_2);
        label_7->setObjectName("label_7");

        gridLayout->addWidget(label_7, 2, 0, 1, 1);

        add_joint_combox = new QComboBox(widget_2);
        add_joint_combox->addItem(QString());
        add_joint_combox->setObjectName("add_joint_combox");

        gridLayout->addWidget(add_joint_combox, 0, 1, 1, 1);

        label_5 = new QLabel(widget_2);
        label_5->setObjectName("label_5");

        gridLayout->addWidget(label_5, 0, 0, 1, 1);

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

        del_joint_box = new QComboBox(widget_2);
        del_joint_box->addItem(QString());
        del_joint_box->setObjectName("del_joint_box");

        gridLayout->addWidget(del_joint_box, 1, 1, 1, 1);

        label_6 = new QLabel(widget_2);
        label_6->setObjectName("label_6");

        gridLayout->addWidget(label_6, 1, 0, 1, 1);


        gridLayout_2->addWidget(widget_2, 0, 1, 1, 1);

        widget_4 = new QWidget(joint);
        widget_4->setObjectName("widget_4");
        widget_4->setMinimumSize(QSize(0, 0));
        widget_4->setMaximumSize(QSize(400, 16777215));
        widget_4->setStyleSheet(QString::fromUtf8("background-color: rgb(181, 131, 90);"));
        gridLayout_6 = new QGridLayout(widget_4);
        gridLayout_6->setObjectName("gridLayout_6");
        gridLayout_6->setContentsMargins(-1, 0, -1, -1);
        widget_5 = new QWidget(widget_4);
        widget_5->setObjectName("widget_5");
        widget_5->setMinimumSize(QSize(30, 0));
        widget_5->setMaximumSize(QSize(16777215, 80));
        widget_5->setStyleSheet(QString::fromUtf8("background-color: rgb(222, 221, 218);"));
        gridLayout_5 = new QGridLayout(widget_5);
        gridLayout_5->setObjectName("gridLayout_5");
        gridLayout_5->setHorizontalSpacing(9);
        gridLayout_5->setVerticalSpacing(2);
        vel = new QTextEdit(widget_5);
        vel->setObjectName("vel");
        vel->setMinimumSize(QSize(40, 0));
        vel->setMaximumSize(QSize(60, 16777215));

        gridLayout_5->addWidget(vel, 0, 7, 1, 1);

        pos = new QTextEdit(widget_5);
        pos->setObjectName("pos");
        pos->setMinimumSize(QSize(40, 0));
        pos->setMaximumSize(QSize(60, 16777215));

        gridLayout_5->addWidget(pos, 0, 3, 1, 1);

        kp = new QTextEdit(widget_5);
        kp->setObjectName("kp");
        kp->setMinimumSize(QSize(40, 0));
        kp->setMaximumSize(QSize(60, 16777215));

        gridLayout_5->addWidget(kp, 1, 1, 1, 1);

        torque = new QTextEdit(widget_5);
        torque->setObjectName("torque");
        torque->setMinimumSize(QSize(40, 0));
        torque->setMaximumSize(QSize(60, 16777215));

        gridLayout_5->addWidget(torque, 0, 1, 1, 1);

        label_9 = new QLabel(widget_5);
        label_9->setObjectName("label_9");
        label_9->setMinimumSize(QSize(50, 0));
        label_9->setMaximumSize(QSize(50, 16777215));

        gridLayout_5->addWidget(label_9, 0, 2, 1, 1);

        label_4 = new QLabel(widget_5);
        label_4->setObjectName("label_4");
        label_4->setMinimumSize(QSize(50, 0));
        label_4->setMaximumSize(QSize(50, 16777215));

        gridLayout_5->addWidget(label_4, 0, 0, 1, 1);

        kd = new QTextEdit(widget_5);
        kd->setObjectName("kd");
        kd->setMinimumSize(QSize(40, 0));
        kd->setMaximumSize(QSize(60, 16777215));

        gridLayout_5->addWidget(kd, 1, 3, 1, 1);

        label_11 = new QLabel(widget_5);
        label_11->setObjectName("label_11");
        label_11->setMinimumSize(QSize(50, 0));
        label_11->setMaximumSize(QSize(50, 16777215));

        gridLayout_5->addWidget(label_11, 1, 0, 1, 1);

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


        gridLayout_6->addWidget(widget_5, 1, 0, 1, 5);

        ctrl_joint_type = new QComboBox(widget_4);
        ctrl_joint_type->addItem(QString());
        ctrl_joint_type->addItem(QString());
        ctrl_joint_type->addItem(QString());
        ctrl_joint_type->addItem(QString());
        ctrl_joint_type->addItem(QString());
        ctrl_joint_type->setObjectName("ctrl_joint_type");

        gridLayout_6->addWidget(ctrl_joint_type, 0, 4, 1, 1);

        all_joint_stop = new QPushButton(widget_4);
        all_joint_stop->setObjectName("all_joint_stop");

        gridLayout_6->addWidget(all_joint_stop, 3, 0, 1, 1);

        send_joint = new QPushButton(widget_4);
        send_joint->setObjectName("send_joint");

        gridLayout_6->addWidget(send_joint, 2, 4, 1, 1);

        label_8 = new QLabel(widget_4);
        label_8->setObjectName("label_8");
        label_8->setMaximumSize(QSize(70, 16777215));

        gridLayout_6->addWidget(label_8, 0, 0, 1, 1);

        label_14 = new QLabel(widget_4);
        label_14->setObjectName("label_14");

        gridLayout_6->addWidget(label_14, 2, 3, 1, 1);

        ctrl_joint = new QComboBox(widget_4);
        ctrl_joint->addItem(QString());
        ctrl_joint->setObjectName("ctrl_joint");

        gridLayout_6->addWidget(ctrl_joint, 0, 1, 1, 2);

        all_joint_enable = new QPushButton(widget_4);
        all_joint_enable->setObjectName("all_joint_enable");

        gridLayout_6->addWidget(all_joint_enable, 3, 4, 1, 1);

        is_timer = new QCheckBox(widget_4);
        is_timer->setObjectName("is_timer");

        gridLayout_6->addWidget(is_timer, 2, 0, 1, 2);

        label_13 = new QLabel(widget_4);
        label_13->setObjectName("label_13");
        label_13->setMaximumSize(QSize(70, 16777215));

        gridLayout_6->addWidget(label_13, 0, 3, 1, 1);

        timer = new QTextEdit(widget_4);
        timer->setObjectName("timer");
        timer->setMaximumSize(QSize(100, 30));

        gridLayout_6->addWidget(timer, 2, 2, 1, 1);


        gridLayout_2->addWidget(widget_4, 2, 1, 1, 1);

        joint_plot = new QWidget(joint);
        joint_plot->setObjectName("joint_plot");
        joint_plot->setMinimumSize(QSize(600, 0));
        joint_plot->setStyleSheet(QString::fromUtf8("background-color: rgb(220, 138, 221);"));

        gridLayout_2->addWidget(joint_plot, 0, 0, 3, 1);

        tabWidget->addTab(joint, QString());
        com = new QWidget();
        com->setObjectName("com");
        tabWidget->addTab(com, QString());
        remote = new QWidget();
        remote->setObjectName("remote");
        tabWidget->addTab(remote, QString());

        gridLayout_4->addWidget(tabWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1015, 27));
        menufile = new QMenu(menubar);
        menufile->setObjectName("menufile");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menufile->menuAction());

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt;\">coms:</span></p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt;\">joints:</span></p></body></html>", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt;\">remotes:</span></p></body></html>", nullptr));
        get_cfg_btn->setText(QCoreApplication::translate("MainWindow", "\350\216\267\345\217\226\351\205\215\347\275\256", nullptr));
        able_cfg_btn->setText(QCoreApplication::translate("MainWindow", "\345\272\224\347\224\250\351\205\215\347\275\256", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(config), QCoreApplication::translate("MainWindow", "config", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt;\">parameter:</span></p></body></html>", nullptr));
        add_joint_combox->setItemText(0, QCoreApplication::translate("MainWindow", "None", nullptr));

        label_5->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt;\">add Joint:</span></p></body></html>", nullptr));
        joint_select_para->setItemText(0, QCoreApplication::translate("MainWindow", "None", nullptr));
        joint_select_para->setItemText(1, QCoreApplication::translate("MainWindow", "pos", nullptr));
        joint_select_para->setItemText(2, QCoreApplication::translate("MainWindow", "number_laps", nullptr));
        joint_select_para->setItemText(3, QCoreApplication::translate("MainWindow", "vel", nullptr));
        joint_select_para->setItemText(4, QCoreApplication::translate("MainWindow", "torque", nullptr));
        joint_select_para->setItemText(5, QCoreApplication::translate("MainWindow", "current", nullptr));
        joint_select_para->setItemText(6, QCoreApplication::translate("MainWindow", "temperature", nullptr));
        joint_select_para->setItemText(7, QCoreApplication::translate("MainWindow", "state", nullptr));

        del_joint_box->setItemText(0, QCoreApplication::translate("MainWindow", "None", nullptr));

        label_6->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt;\">del Joint:</span></p></body></html>", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "pos:", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "torque:", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "kp:", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "kd:", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "vel:", nullptr));
        ctrl_joint_type->setItemText(0, QCoreApplication::translate("MainWindow", "None", nullptr));
        ctrl_joint_type->setItemText(1, QCoreApplication::translate("MainWindow", "MIT", nullptr));
        ctrl_joint_type->setItemText(2, QCoreApplication::translate("MainWindow", "POS", nullptr));
        ctrl_joint_type->setItemText(3, QCoreApplication::translate("MainWindow", "VEL", nullptr));
        ctrl_joint_type->setItemText(4, QCoreApplication::translate("MainWindow", "POS_VEL", nullptr));

        all_joint_stop->setText(QCoreApplication::translate("MainWindow", "\346\211\200\346\234\211\347\224\265\346\234\272\345\201\234\346\255\242", nullptr));
        send_joint->setText(QCoreApplication::translate("MainWindow", "send", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt;\">Joint:</span></p></body></html>", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>time(ms)</p></body></html>", nullptr));
        ctrl_joint->setItemText(0, QCoreApplication::translate("MainWindow", "None", nullptr));

        all_joint_enable->setText(QCoreApplication::translate("MainWindow", "\346\211\200\346\234\211\347\224\265\346\234\272\345\244\261\350\203\275", nullptr));
        is_timer->setText(QCoreApplication::translate("MainWindow", "\345\256\232\346\227\266\345\217\221\351\200\201", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:18pt;\">type:</span></p></body></html>", nullptr));
        timer->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">50</p></body></html>", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(joint), QCoreApplication::translate("MainWindow", "joint", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(com), QCoreApplication::translate("MainWindow", "com", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(remote), QCoreApplication::translate("MainWindow", "remote", nullptr));
        menufile->setTitle(QCoreApplication::translate("MainWindow", "file", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
