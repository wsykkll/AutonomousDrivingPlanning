/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *UI;
    QGraphicsView *graphicsView_local;
    QPushButton *pushButton_All;
    QPushButton *pushButton_BehaviorStatus;
    QPushButton *pushButton_OperationStatus;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_21;
    QLabel *label_29;
    QVBoxLayout *verticalLayout_26;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_12;
    QPushButton *pushButton_INSStatus;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_13;
    QPushButton *pushButton_LineStatus;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_9;
    QLabel *label_14;
    QPushButton *pushButton_ObsStatus;
    QVBoxLayout *verticalLayout_27;
    QLabel *label_15;
    QVBoxLayout *verticalLayout_15;
    QHBoxLayout *horizontalLayout_9;
    QVBoxLayout *verticalLayout_10;
    QLabel *label_21;
    QTextBrowser *textBrowser_LeftLeft_bExist;
    QTextBrowser *textBrowser_LeftLeft_iLength;
    QVBoxLayout *verticalLayout_11;
    QLabel *label_20;
    QTextBrowser *textBrowser_Left_bExist;
    QTextBrowser *textBrowser_Left_iLength;
    QVBoxLayout *verticalLayout_12;
    QLabel *label_22;
    QTextBrowser *textBrowser_Right_bExist;
    QTextBrowser *textBrowser_Right_iLength;
    QVBoxLayout *verticalLayout_13;
    QLabel *label_23;
    QTextBrowser *textBrowser_RightRight_bExist;
    QTextBrowser *textBrowser_RightRight_iLength;
    QVBoxLayout *verticalLayout_14;
    QLabel *label_16;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_17;
    QTextBrowser *textBrowser_dis2L;
    QLabel *label_18;
    QTextBrowser *textBrowser_dis2R;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_2;
    QTextBrowser *textBrowser_VehStatus;
    QHBoxLayout *horizontalLayout;
    QLabel *label_7;
    QTextBrowser *textBrowser_RealSpeed;
    QLabel *label_10;
    QTextBrowser *textBrowser_RealAngle;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_31;
    QTextBrowser *textBrowser_RealAcc;
    QLabel *label_30;
    QTextBrowser *textBrowser_Yawrate;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_9;
    QTextBrowser *textBrowser_Posture_lat;
    QTextBrowser *textBrowser_Posture_lon;
    QTextBrowser *textBrowser_Posture_heading;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_22;
    QLabel *label_32;
    QVBoxLayout *verticalLayout_20;
    QLabel *label_19;
    QHBoxLayout *horizontalLayout_10;
    QVBoxLayout *verticalLayout_16;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_27;
    QLabel *label_28;
    QVBoxLayout *verticalLayout_17;
    QLabel *label_24;
    QTextBrowser *textBrowser_Left_bSafety;
    QTextBrowser *textBrowser_Left_bPrior;
    QVBoxLayout *verticalLayout_18;
    QLabel *label_25;
    QTextBrowser *textBrowser_overtake;
    QTextBrowser *textBrowser_overtake_prior;
    QVBoxLayout *verticalLayout_19;
    QLabel *label_26;
    QTextBrowser *textBrowser_Right_bSafety;
    QTextBrowser *textBrowser_Right_bPrior;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_23;
    QLabel *label_33;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_8;
    QTextBrowser *textBrowser_DesignSpeed;
    QLabel *label_11;
    QTextBrowser *textBrowser_DesignAngle;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_12;
    QWidget *layoutWidget4;
    QVBoxLayout *verticalLayout_4;
    QPushButton *pushButton_ChangeLeft;
    QPushButton *pushButton_ChangeRight;
    QPushButton *pushButton_ResetSemiAuto;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_5;
    QSpinBox *spinBox_Speed;
    QWidget *layoutWidget5;
    QVBoxLayout *verticalLayout_3;
    QCheckBox *checkBox_SemiAuto;
    QCheckBox *checkBox_manual;
    QCheckBox *checkBox_Auto;
    QWidget *GlobalPlanning;
    QGraphicsView *graphicsView_global;
    QGroupBox *groupBox_GlobalOperation;
    QWidget *layoutWidget7;
    QHBoxLayout *horizontalLayout_5;
    QCheckBox *checkBox_scale;
    QCheckBox *checkBox_translate;
    QCheckBox *checkBox_view;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QStringLiteral("MainWindowClass"));
        MainWindowClass->resize(1409, 849);
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 1401, 791));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QStringLiteral("Arial Unicode MS"));
        tabWidget->setFont(font);
        UI = new QWidget();
        UI->setObjectName(QStringLiteral("UI"));
        graphicsView_local = new QGraphicsView(UI);
        graphicsView_local->setObjectName(QStringLiteral("graphicsView_local"));
        graphicsView_local->setGeometry(QRect(0, 10, 411, 741));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(graphicsView_local->sizePolicy().hasHeightForWidth());
        graphicsView_local->setSizePolicy(sizePolicy1);
        graphicsView_local->setMinimumSize(QSize(411, 741));
        graphicsView_local->setMaximumSize(QSize(411, 741));
        graphicsView_local->setAcceptDrops(false);
        graphicsView_local->setLineWidth(1);
        graphicsView_local->setMidLineWidth(0);
        graphicsView_local->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView_local->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView_local->setInteractive(false);
        graphicsView_local->setSceneRect(QRectF(0, 0, 411, 741));
        graphicsView_local->setTransformationAnchor(QGraphicsView::NoAnchor);
        pushButton_All = new QPushButton(UI);
        pushButton_All->setObjectName(QStringLiteral("pushButton_All"));
        pushButton_All->setGeometry(QRect(920, 20, 81, 31));
        pushButton_All->setMinimumSize(QSize(81, 31));
        pushButton_All->setMaximumSize(QSize(81, 31));
        pushButton_BehaviorStatus = new QPushButton(UI);
        pushButton_BehaviorStatus->setObjectName(QStringLiteral("pushButton_BehaviorStatus"));
        pushButton_BehaviorStatus->setGeometry(QRect(1030, 70, 51, 51));
        pushButton_BehaviorStatus->setMinimumSize(QSize(51, 51));
        pushButton_BehaviorStatus->setMaximumSize(QSize(51, 51));
        pushButton_OperationStatus = new QPushButton(UI);
        pushButton_OperationStatus->setObjectName(QStringLiteral("pushButton_OperationStatus"));
        pushButton_OperationStatus->setGeometry(QRect(850, 70, 51, 51));
        pushButton_OperationStatus->setMinimumSize(QSize(51, 51));
        pushButton_OperationStatus->setMaximumSize(QSize(51, 51));
        layoutWidget = new QWidget(UI);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(430, 20, 380, 540));
        verticalLayout_21 = new QVBoxLayout(layoutWidget);
        verticalLayout_21->setSpacing(6);
        verticalLayout_21->setContentsMargins(11, 11, 11, 11);
        verticalLayout_21->setObjectName(QStringLiteral("verticalLayout_21"));
        verticalLayout_21->setContentsMargins(0, 0, 0, 0);
        label_29 = new QLabel(layoutWidget);
        label_29->setObjectName(QStringLiteral("label_29"));
        QFont font1;
        font1.setPointSize(13);
        font1.setBold(true);
        font1.setWeight(75);
        label_29->setFont(font1);
        label_29->setAlignment(Qt::AlignCenter);

        verticalLayout_21->addWidget(label_29);

        verticalLayout_26 = new QVBoxLayout();
        verticalLayout_26->setSpacing(6);
        verticalLayout_26->setObjectName(QStringLiteral("verticalLayout_26"));
        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setMinimumSize(QSize(261, 26));
        label_6->setMaximumSize(QSize(261, 26));
        QFont font2;
        font2.setPointSize(11);
        font2.setBold(true);
        font2.setItalic(true);
        font2.setWeight(75);
        label_6->setFont(font2);

        verticalLayout_26->addWidget(label_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        label_12 = new QLabel(layoutWidget);
        label_12->setObjectName(QStringLiteral("label_12"));
        QFont font3;
        font3.setPointSize(10);
        label_12->setFont(font3);
        label_12->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(label_12);

        pushButton_INSStatus = new QPushButton(layoutWidget);
        pushButton_INSStatus->setObjectName(QStringLiteral("pushButton_INSStatus"));
        pushButton_INSStatus->setMinimumSize(QSize(51, 51));
        pushButton_INSStatus->setMaximumSize(QSize(51, 51));

        verticalLayout_7->addWidget(pushButton_INSStatus);


        horizontalLayout_7->addLayout(verticalLayout_7);

        horizontalSpacer = new QSpacerItem(30, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        label_13 = new QLabel(layoutWidget);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setFont(font3);
        label_13->setAlignment(Qt::AlignCenter);

        verticalLayout_8->addWidget(label_13);

        pushButton_LineStatus = new QPushButton(layoutWidget);
        pushButton_LineStatus->setObjectName(QStringLiteral("pushButton_LineStatus"));
        pushButton_LineStatus->setMinimumSize(QSize(51, 51));
        pushButton_LineStatus->setMaximumSize(QSize(51, 51));

        verticalLayout_8->addWidget(pushButton_LineStatus);


        horizontalLayout_7->addLayout(verticalLayout_8);

        horizontalSpacer_2 = new QSpacerItem(30, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_2);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        label_14 = new QLabel(layoutWidget);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setFont(font3);
        label_14->setAlignment(Qt::AlignCenter);

        verticalLayout_9->addWidget(label_14);

        pushButton_ObsStatus = new QPushButton(layoutWidget);
        pushButton_ObsStatus->setObjectName(QStringLiteral("pushButton_ObsStatus"));
        pushButton_ObsStatus->setMinimumSize(QSize(51, 51));
        pushButton_ObsStatus->setMaximumSize(QSize(51, 51));

        verticalLayout_9->addWidget(pushButton_ObsStatus);


        horizontalLayout_7->addLayout(verticalLayout_9);


        verticalLayout_26->addLayout(horizontalLayout_7);


        verticalLayout_21->addLayout(verticalLayout_26);

        verticalLayout_27 = new QVBoxLayout();
        verticalLayout_27->setSpacing(6);
        verticalLayout_27->setObjectName(QStringLiteral("verticalLayout_27"));
        label_15 = new QLabel(layoutWidget);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setMinimumSize(QSize(0, 26));
        label_15->setMaximumSize(QSize(16777215, 26));
        QFont font4;
        font4.setPointSize(11);
        font4.setBold(true);
        font4.setWeight(75);
        label_15->setFont(font4);

        verticalLayout_27->addWidget(label_15);

        verticalLayout_15 = new QVBoxLayout();
        verticalLayout_15->setSpacing(6);
        verticalLayout_15->setObjectName(QStringLiteral("verticalLayout_15"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        label_21 = new QLabel(layoutWidget);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setMinimumSize(QSize(66, 26));
        label_21->setMaximumSize(QSize(66, 26));
        label_21->setFont(font3);
        label_21->setAlignment(Qt::AlignCenter);

        verticalLayout_10->addWidget(label_21);

        textBrowser_LeftLeft_bExist = new QTextBrowser(layoutWidget);
        textBrowser_LeftLeft_bExist->setObjectName(QStringLiteral("textBrowser_LeftLeft_bExist"));
        textBrowser_LeftLeft_bExist->setMinimumSize(QSize(66, 26));
        textBrowser_LeftLeft_bExist->setMaximumSize(QSize(66, 26));

        verticalLayout_10->addWidget(textBrowser_LeftLeft_bExist);

        textBrowser_LeftLeft_iLength = new QTextBrowser(layoutWidget);
        textBrowser_LeftLeft_iLength->setObjectName(QStringLiteral("textBrowser_LeftLeft_iLength"));
        textBrowser_LeftLeft_iLength->setMinimumSize(QSize(66, 26));
        textBrowser_LeftLeft_iLength->setMaximumSize(QSize(66, 26));

        verticalLayout_10->addWidget(textBrowser_LeftLeft_iLength);


        horizontalLayout_9->addLayout(verticalLayout_10);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        label_20 = new QLabel(layoutWidget);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setMinimumSize(QSize(66, 26));
        label_20->setMaximumSize(QSize(66, 26));
        label_20->setFont(font3);
        label_20->setAlignment(Qt::AlignCenter);

        verticalLayout_11->addWidget(label_20);

        textBrowser_Left_bExist = new QTextBrowser(layoutWidget);
        textBrowser_Left_bExist->setObjectName(QStringLiteral("textBrowser_Left_bExist"));
        textBrowser_Left_bExist->setMinimumSize(QSize(66, 26));
        textBrowser_Left_bExist->setMaximumSize(QSize(66, 26));

        verticalLayout_11->addWidget(textBrowser_Left_bExist);

        textBrowser_Left_iLength = new QTextBrowser(layoutWidget);
        textBrowser_Left_iLength->setObjectName(QStringLiteral("textBrowser_Left_iLength"));
        textBrowser_Left_iLength->setMinimumSize(QSize(66, 26));
        textBrowser_Left_iLength->setMaximumSize(QSize(66, 26));

        verticalLayout_11->addWidget(textBrowser_Left_iLength);


        horizontalLayout_9->addLayout(verticalLayout_11);

        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        label_22 = new QLabel(layoutWidget);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setMinimumSize(QSize(66, 26));
        label_22->setMaximumSize(QSize(66, 26));
        label_22->setFont(font3);
        label_22->setAlignment(Qt::AlignCenter);

        verticalLayout_12->addWidget(label_22);

        textBrowser_Right_bExist = new QTextBrowser(layoutWidget);
        textBrowser_Right_bExist->setObjectName(QStringLiteral("textBrowser_Right_bExist"));
        textBrowser_Right_bExist->setMinimumSize(QSize(66, 26));
        textBrowser_Right_bExist->setMaximumSize(QSize(66, 26));

        verticalLayout_12->addWidget(textBrowser_Right_bExist);

        textBrowser_Right_iLength = new QTextBrowser(layoutWidget);
        textBrowser_Right_iLength->setObjectName(QStringLiteral("textBrowser_Right_iLength"));
        textBrowser_Right_iLength->setMinimumSize(QSize(66, 26));
        textBrowser_Right_iLength->setMaximumSize(QSize(66, 26));

        verticalLayout_12->addWidget(textBrowser_Right_iLength);


        horizontalLayout_9->addLayout(verticalLayout_12);

        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        label_23 = new QLabel(layoutWidget);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setMinimumSize(QSize(66, 26));
        label_23->setMaximumSize(QSize(66, 26));
        label_23->setFont(font3);
        label_23->setAlignment(Qt::AlignCenter);

        verticalLayout_13->addWidget(label_23);

        textBrowser_RightRight_bExist = new QTextBrowser(layoutWidget);
        textBrowser_RightRight_bExist->setObjectName(QStringLiteral("textBrowser_RightRight_bExist"));
        textBrowser_RightRight_bExist->setMinimumSize(QSize(66, 26));
        textBrowser_RightRight_bExist->setMaximumSize(QSize(66, 26));

        verticalLayout_13->addWidget(textBrowser_RightRight_bExist);

        textBrowser_RightRight_iLength = new QTextBrowser(layoutWidget);
        textBrowser_RightRight_iLength->setObjectName(QStringLiteral("textBrowser_RightRight_iLength"));
        textBrowser_RightRight_iLength->setMinimumSize(QSize(66, 26));
        textBrowser_RightRight_iLength->setMaximumSize(QSize(66, 26));

        verticalLayout_13->addWidget(textBrowser_RightRight_iLength);


        horizontalLayout_9->addLayout(verticalLayout_13);


        verticalLayout_15->addLayout(horizontalLayout_9);

        verticalLayout_14 = new QVBoxLayout();
        verticalLayout_14->setSpacing(6);
        verticalLayout_14->setObjectName(QStringLiteral("verticalLayout_14"));
        label_16 = new QLabel(layoutWidget);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setMinimumSize(QSize(0, 26));
        label_16->setMaximumSize(QSize(16777215, 26));
        label_16->setFont(font3);

        verticalLayout_14->addWidget(label_16);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_17 = new QLabel(layoutWidget);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setMinimumSize(QSize(51, 26));
        label_17->setMaximumSize(QSize(51, 26));
        label_17->setFont(font3);

        horizontalLayout_8->addWidget(label_17);

        textBrowser_dis2L = new QTextBrowser(layoutWidget);
        textBrowser_dis2L->setObjectName(QStringLiteral("textBrowser_dis2L"));
        textBrowser_dis2L->setMinimumSize(QSize(71, 26));
        textBrowser_dis2L->setMaximumSize(QSize(71, 26));
        textBrowser_dis2L->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textBrowser_dis2L->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        horizontalLayout_8->addWidget(textBrowser_dis2L);

        label_18 = new QLabel(layoutWidget);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setMinimumSize(QSize(51, 26));
        label_18->setMaximumSize(QSize(51, 26));
        label_18->setFont(font3);

        horizontalLayout_8->addWidget(label_18);

        textBrowser_dis2R = new QTextBrowser(layoutWidget);
        textBrowser_dis2R->setObjectName(QStringLiteral("textBrowser_dis2R"));
        textBrowser_dis2R->setMinimumSize(QSize(71, 26));
        textBrowser_dis2R->setMaximumSize(QSize(71, 26));

        horizontalLayout_8->addWidget(textBrowser_dis2R);


        verticalLayout_14->addLayout(horizontalLayout_8);


        verticalLayout_15->addLayout(verticalLayout_14);


        verticalLayout_27->addLayout(verticalLayout_15);


        verticalLayout_21->addLayout(verticalLayout_27);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(0, 26));
        label->setMaximumSize(QSize(16777215, 26));
        QFont font5;
        font5.setFamily(QStringLiteral("Arial Unicode MS"));
        font5.setPointSize(11);
        font5.setBold(true);
        font5.setItalic(true);
        font5.setWeight(75);
        label->setFont(font5);
        label->setLineWidth(10);

        verticalLayout_2->addWidget(label);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        label_2->setMinimumSize(QSize(81, 31));
        label_2->setMaximumSize(QSize(81, 31));
        label_2->setFont(font3);
        label_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_11->addWidget(label_2);

        textBrowser_VehStatus = new QTextBrowser(layoutWidget);
        textBrowser_VehStatus->setObjectName(QStringLiteral("textBrowser_VehStatus"));
        sizePolicy1.setHeightForWidth(textBrowser_VehStatus->sizePolicy().hasHeightForWidth());
        textBrowser_VehStatus->setSizePolicy(sizePolicy1);
        textBrowser_VehStatus->setMinimumSize(QSize(181, 31));
        textBrowser_VehStatus->setMaximumSize(QSize(181, 31));
        textBrowser_VehStatus->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textBrowser_VehStatus->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        horizontalLayout_11->addWidget(textBrowser_VehStatus);


        verticalLayout->addLayout(horizontalLayout_11);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        sizePolicy1.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy1);
        label_7->setMinimumSize(QSize(82, 31));
        label_7->setMaximumSize(QSize(81, 31));
        label_7->setFont(font3);
        label_7->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_7);

        textBrowser_RealSpeed = new QTextBrowser(layoutWidget);
        textBrowser_RealSpeed->setObjectName(QStringLiteral("textBrowser_RealSpeed"));
        sizePolicy1.setHeightForWidth(textBrowser_RealSpeed->sizePolicy().hasHeightForWidth());
        textBrowser_RealSpeed->setSizePolicy(sizePolicy1);
        textBrowser_RealSpeed->setMinimumSize(QSize(91, 31));
        textBrowser_RealSpeed->setMaximumSize(QSize(91, 31));
        textBrowser_RealSpeed->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textBrowser_RealSpeed->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        horizontalLayout->addWidget(textBrowser_RealSpeed);

        label_10 = new QLabel(layoutWidget);
        label_10->setObjectName(QStringLiteral("label_10"));
        sizePolicy1.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy1);
        label_10->setMinimumSize(QSize(81, 31));
        label_10->setMaximumSize(QSize(81, 31));
        label_10->setFont(font3);
        label_10->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_10);

        textBrowser_RealAngle = new QTextBrowser(layoutWidget);
        textBrowser_RealAngle->setObjectName(QStringLiteral("textBrowser_RealAngle"));
        sizePolicy1.setHeightForWidth(textBrowser_RealAngle->sizePolicy().hasHeightForWidth());
        textBrowser_RealAngle->setSizePolicy(sizePolicy1);
        textBrowser_RealAngle->setMinimumSize(QSize(91, 31));
        textBrowser_RealAngle->setMaximumSize(QSize(91, 31));
        textBrowser_RealAngle->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textBrowser_RealAngle->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        horizontalLayout->addWidget(textBrowser_RealAngle);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_31 = new QLabel(layoutWidget);
        label_31->setObjectName(QStringLiteral("label_31"));
        sizePolicy1.setHeightForWidth(label_31->sizePolicy().hasHeightForWidth());
        label_31->setSizePolicy(sizePolicy1);
        label_31->setMinimumSize(QSize(82, 31));
        label_31->setMaximumSize(QSize(81, 31));
        label_31->setFont(font3);
        label_31->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_31);

        textBrowser_RealAcc = new QTextBrowser(layoutWidget);
        textBrowser_RealAcc->setObjectName(QStringLiteral("textBrowser_RealAcc"));
        sizePolicy1.setHeightForWidth(textBrowser_RealAcc->sizePolicy().hasHeightForWidth());
        textBrowser_RealAcc->setSizePolicy(sizePolicy1);
        textBrowser_RealAcc->setMinimumSize(QSize(91, 31));
        textBrowser_RealAcc->setMaximumSize(QSize(91, 31));
        textBrowser_RealAcc->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textBrowser_RealAcc->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        horizontalLayout_2->addWidget(textBrowser_RealAcc);

        label_30 = new QLabel(layoutWidget);
        label_30->setObjectName(QStringLiteral("label_30"));
        sizePolicy1.setHeightForWidth(label_30->sizePolicy().hasHeightForWidth());
        label_30->setSizePolicy(sizePolicy1);
        label_30->setMinimumSize(QSize(81, 31));
        label_30->setMaximumSize(QSize(81, 31));
        label_30->setFont(font3);
        label_30->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_30);

        textBrowser_Yawrate = new QTextBrowser(layoutWidget);
        textBrowser_Yawrate->setObjectName(QStringLiteral("textBrowser_Yawrate"));
        sizePolicy1.setHeightForWidth(textBrowser_Yawrate->sizePolicy().hasHeightForWidth());
        textBrowser_Yawrate->setSizePolicy(sizePolicy1);
        textBrowser_Yawrate->setMinimumSize(QSize(91, 31));
        textBrowser_Yawrate->setMaximumSize(QSize(91, 31));
        textBrowser_Yawrate->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textBrowser_Yawrate->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        horizontalLayout_2->addWidget(textBrowser_Yawrate);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_9 = new QLabel(layoutWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        sizePolicy1.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy1);
        label_9->setMinimumSize(QSize(81, 31));
        label_9->setMaximumSize(QSize(81, 31));
        label_9->setFont(font3);
        label_9->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(label_9);

        textBrowser_Posture_lat = new QTextBrowser(layoutWidget);
        textBrowser_Posture_lat->setObjectName(QStringLiteral("textBrowser_Posture_lat"));
        sizePolicy1.setHeightForWidth(textBrowser_Posture_lat->sizePolicy().hasHeightForWidth());
        textBrowser_Posture_lat->setSizePolicy(sizePolicy1);
        textBrowser_Posture_lat->setMinimumSize(QSize(91, 31));
        textBrowser_Posture_lat->setMaximumSize(QSize(91, 31));
        textBrowser_Posture_lat->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textBrowser_Posture_lat->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        horizontalLayout_4->addWidget(textBrowser_Posture_lat);

        textBrowser_Posture_lon = new QTextBrowser(layoutWidget);
        textBrowser_Posture_lon->setObjectName(QStringLiteral("textBrowser_Posture_lon"));
        sizePolicy1.setHeightForWidth(textBrowser_Posture_lon->sizePolicy().hasHeightForWidth());
        textBrowser_Posture_lon->setSizePolicy(sizePolicy1);
        textBrowser_Posture_lon->setMinimumSize(QSize(91, 31));
        textBrowser_Posture_lon->setMaximumSize(QSize(91, 31));
        textBrowser_Posture_lon->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textBrowser_Posture_lon->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        horizontalLayout_4->addWidget(textBrowser_Posture_lon);

        textBrowser_Posture_heading = new QTextBrowser(layoutWidget);
        textBrowser_Posture_heading->setObjectName(QStringLiteral("textBrowser_Posture_heading"));
        sizePolicy1.setHeightForWidth(textBrowser_Posture_heading->sizePolicy().hasHeightForWidth());
        textBrowser_Posture_heading->setSizePolicy(sizePolicy1);
        textBrowser_Posture_heading->setMinimumSize(QSize(91, 31));
        textBrowser_Posture_heading->setMaximumSize(QSize(91, 31));
        textBrowser_Posture_heading->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textBrowser_Posture_heading->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        horizontalLayout_4->addWidget(textBrowser_Posture_heading);


        verticalLayout->addLayout(horizontalLayout_4);


        verticalLayout_2->addLayout(verticalLayout);


        verticalLayout_21->addLayout(verticalLayout_2);

        layoutWidget1 = new QWidget(UI);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(830, 470, 281, 153));
        verticalLayout_22 = new QVBoxLayout(layoutWidget1);
        verticalLayout_22->setSpacing(6);
        verticalLayout_22->setContentsMargins(11, 11, 11, 11);
        verticalLayout_22->setObjectName(QStringLiteral("verticalLayout_22"));
        verticalLayout_22->setContentsMargins(0, 0, 0, 0);
        label_32 = new QLabel(layoutWidget1);
        label_32->setObjectName(QStringLiteral("label_32"));
        label_32->setFont(font1);
        label_32->setAlignment(Qt::AlignCenter);

        verticalLayout_22->addWidget(label_32);

        verticalLayout_20 = new QVBoxLayout();
        verticalLayout_20->setSpacing(6);
        verticalLayout_20->setObjectName(QStringLiteral("verticalLayout_20"));
        label_19 = new QLabel(layoutWidget1);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setMinimumSize(QSize(0, 20));
        label_19->setMaximumSize(QSize(16777215, 20));
        label_19->setFont(font2);

        verticalLayout_20->addWidget(label_19);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        verticalLayout_16 = new QVBoxLayout();
        verticalLayout_16->setSpacing(6);
        verticalLayout_16->setObjectName(QStringLiteral("verticalLayout_16"));
        horizontalSpacer_3 = new QSpacerItem(51, 26, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_16->addItem(horizontalSpacer_3);

        label_27 = new QLabel(layoutWidget1);
        label_27->setObjectName(QStringLiteral("label_27"));
        label_27->setMinimumSize(QSize(51, 26));
        label_27->setMaximumSize(QSize(51, 26));
        label_27->setFont(font3);
        label_27->setAlignment(Qt::AlignCenter);

        verticalLayout_16->addWidget(label_27);

        label_28 = new QLabel(layoutWidget1);
        label_28->setObjectName(QStringLiteral("label_28"));
        label_28->setMinimumSize(QSize(51, 26));
        label_28->setMaximumSize(QSize(51, 26));
        label_28->setFont(font3);
        label_28->setAlignment(Qt::AlignCenter);

        verticalLayout_16->addWidget(label_28);


        horizontalLayout_10->addLayout(verticalLayout_16);

        verticalLayout_17 = new QVBoxLayout();
        verticalLayout_17->setSpacing(6);
        verticalLayout_17->setObjectName(QStringLiteral("verticalLayout_17"));
        label_24 = new QLabel(layoutWidget1);
        label_24->setObjectName(QStringLiteral("label_24"));
        label_24->setMinimumSize(QSize(66, 26));
        label_24->setMaximumSize(QSize(66, 26));
        label_24->setFont(font3);
        label_24->setAlignment(Qt::AlignCenter);

        verticalLayout_17->addWidget(label_24);

        textBrowser_Left_bSafety = new QTextBrowser(layoutWidget1);
        textBrowser_Left_bSafety->setObjectName(QStringLiteral("textBrowser_Left_bSafety"));
        textBrowser_Left_bSafety->setMinimumSize(QSize(66, 26));
        textBrowser_Left_bSafety->setMaximumSize(QSize(66, 26));

        verticalLayout_17->addWidget(textBrowser_Left_bSafety);

        textBrowser_Left_bPrior = new QTextBrowser(layoutWidget1);
        textBrowser_Left_bPrior->setObjectName(QStringLiteral("textBrowser_Left_bPrior"));
        textBrowser_Left_bPrior->setMinimumSize(QSize(66, 26));
        textBrowser_Left_bPrior->setMaximumSize(QSize(66, 26));

        verticalLayout_17->addWidget(textBrowser_Left_bPrior);


        horizontalLayout_10->addLayout(verticalLayout_17);

        verticalLayout_18 = new QVBoxLayout();
        verticalLayout_18->setSpacing(6);
        verticalLayout_18->setObjectName(QStringLiteral("verticalLayout_18"));
        label_25 = new QLabel(layoutWidget1);
        label_25->setObjectName(QStringLiteral("label_25"));
        label_25->setMinimumSize(QSize(66, 26));
        label_25->setMaximumSize(QSize(66, 26));
        label_25->setFont(font3);
        label_25->setAlignment(Qt::AlignCenter);

        verticalLayout_18->addWidget(label_25);

        textBrowser_overtake = new QTextBrowser(layoutWidget1);
        textBrowser_overtake->setObjectName(QStringLiteral("textBrowser_overtake"));
        textBrowser_overtake->setMinimumSize(QSize(66, 26));
        textBrowser_overtake->setMaximumSize(QSize(66, 26));

        verticalLayout_18->addWidget(textBrowser_overtake);

        textBrowser_overtake_prior = new QTextBrowser(layoutWidget1);
        textBrowser_overtake_prior->setObjectName(QStringLiteral("textBrowser_overtake_prior"));
        textBrowser_overtake_prior->setMinimumSize(QSize(66, 26));
        textBrowser_overtake_prior->setMaximumSize(QSize(66, 26));

        verticalLayout_18->addWidget(textBrowser_overtake_prior);


        horizontalLayout_10->addLayout(verticalLayout_18);

        verticalLayout_19 = new QVBoxLayout();
        verticalLayout_19->setSpacing(6);
        verticalLayout_19->setObjectName(QStringLiteral("verticalLayout_19"));
        label_26 = new QLabel(layoutWidget1);
        label_26->setObjectName(QStringLiteral("label_26"));
        label_26->setMinimumSize(QSize(66, 26));
        label_26->setMaximumSize(QSize(66, 26));
        label_26->setFont(font3);
        label_26->setAlignment(Qt::AlignCenter);

        verticalLayout_19->addWidget(label_26);

        textBrowser_Right_bSafety = new QTextBrowser(layoutWidget1);
        textBrowser_Right_bSafety->setObjectName(QStringLiteral("textBrowser_Right_bSafety"));
        textBrowser_Right_bSafety->setMinimumSize(QSize(66, 26));
        textBrowser_Right_bSafety->setMaximumSize(QSize(66, 26));

        verticalLayout_19->addWidget(textBrowser_Right_bSafety);

        textBrowser_Right_bPrior = new QTextBrowser(layoutWidget1);
        textBrowser_Right_bPrior->setObjectName(QStringLiteral("textBrowser_Right_bPrior"));
        textBrowser_Right_bPrior->setMinimumSize(QSize(66, 26));
        textBrowser_Right_bPrior->setMaximumSize(QSize(66, 26));

        verticalLayout_19->addWidget(textBrowser_Right_bPrior);


        horizontalLayout_10->addLayout(verticalLayout_19);


        verticalLayout_20->addLayout(horizontalLayout_10);


        verticalLayout_22->addLayout(verticalLayout_20);

        layoutWidget2 = new QWidget(UI);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(430, 610, 346, 64));
        verticalLayout_23 = new QVBoxLayout(layoutWidget2);
        verticalLayout_23->setSpacing(6);
        verticalLayout_23->setContentsMargins(11, 11, 11, 11);
        verticalLayout_23->setObjectName(QStringLiteral("verticalLayout_23"));
        verticalLayout_23->setContentsMargins(0, 0, 0, 0);
        label_33 = new QLabel(layoutWidget2);
        label_33->setObjectName(QStringLiteral("label_33"));
        label_33->setFont(font1);
        label_33->setAlignment(Qt::AlignCenter);

        verticalLayout_23->addWidget(label_33);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_8 = new QLabel(layoutWidget2);
        label_8->setObjectName(QStringLiteral("label_8"));
        sizePolicy1.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy1);
        label_8->setMinimumSize(QSize(71, 31));
        label_8->setMaximumSize(QSize(71, 31));
        label_8->setFont(font3);

        horizontalLayout_3->addWidget(label_8);

        textBrowser_DesignSpeed = new QTextBrowser(layoutWidget2);
        textBrowser_DesignSpeed->setObjectName(QStringLiteral("textBrowser_DesignSpeed"));
        sizePolicy1.setHeightForWidth(textBrowser_DesignSpeed->sizePolicy().hasHeightForWidth());
        textBrowser_DesignSpeed->setSizePolicy(sizePolicy1);
        textBrowser_DesignSpeed->setMinimumSize(QSize(91, 31));
        textBrowser_DesignSpeed->setMaximumSize(QSize(91, 31));
        textBrowser_DesignSpeed->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textBrowser_DesignSpeed->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        horizontalLayout_3->addWidget(textBrowser_DesignSpeed);

        label_11 = new QLabel(layoutWidget2);
        label_11->setObjectName(QStringLiteral("label_11"));
        sizePolicy1.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy1);
        label_11->setMinimumSize(QSize(71, 31));
        label_11->setMaximumSize(QSize(71, 31));
        label_11->setFont(font3);

        horizontalLayout_3->addWidget(label_11);

        textBrowser_DesignAngle = new QTextBrowser(layoutWidget2);
        textBrowser_DesignAngle->setObjectName(QStringLiteral("textBrowser_DesignAngle"));
        sizePolicy1.setHeightForWidth(textBrowser_DesignAngle->sizePolicy().hasHeightForWidth());
        textBrowser_DesignAngle->setSizePolicy(sizePolicy1);
        textBrowser_DesignAngle->setMinimumSize(QSize(91, 31));
        textBrowser_DesignAngle->setMaximumSize(QSize(91, 31));
        textBrowser_DesignAngle->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textBrowser_DesignAngle->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        horizontalLayout_3->addWidget(textBrowser_DesignAngle);


        verticalLayout_23->addLayout(horizontalLayout_3);

        layoutWidget3 = new QWidget(UI);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(0, 0, 203, 263));
        horizontalLayout_12 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        horizontalLayout_12->setContentsMargins(0, 0, 0, 0);
        layoutWidget4 = new QWidget(UI);
        layoutWidget4->setObjectName(QStringLiteral("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(970, 140, 112, 126));
        verticalLayout_4 = new QVBoxLayout(layoutWidget4);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        pushButton_ChangeLeft = new QPushButton(layoutWidget4);
        pushButton_ChangeLeft->setObjectName(QStringLiteral("pushButton_ChangeLeft"));
        pushButton_ChangeLeft->setEnabled(false);
        sizePolicy1.setHeightForWidth(pushButton_ChangeLeft->sizePolicy().hasHeightForWidth());
        pushButton_ChangeLeft->setSizePolicy(sizePolicy1);
        pushButton_ChangeLeft->setMinimumSize(QSize(106, 26));
        pushButton_ChangeLeft->setMaximumSize(QSize(106, 26));

        verticalLayout_4->addWidget(pushButton_ChangeLeft);

        pushButton_ChangeRight = new QPushButton(layoutWidget4);
        pushButton_ChangeRight->setObjectName(QStringLiteral("pushButton_ChangeRight"));
        pushButton_ChangeRight->setEnabled(false);
        sizePolicy1.setHeightForWidth(pushButton_ChangeRight->sizePolicy().hasHeightForWidth());
        pushButton_ChangeRight->setSizePolicy(sizePolicy1);
        pushButton_ChangeRight->setMinimumSize(QSize(106, 26));
        pushButton_ChangeRight->setMaximumSize(QSize(106, 26));

        verticalLayout_4->addWidget(pushButton_ChangeRight);

        pushButton_ResetSemiAuto = new QPushButton(layoutWidget4);
        pushButton_ResetSemiAuto->setObjectName(QStringLiteral("pushButton_ResetSemiAuto"));
        pushButton_ResetSemiAuto->setEnabled(false);
        pushButton_ResetSemiAuto->setMinimumSize(QSize(106, 26));
        pushButton_ResetSemiAuto->setMaximumSize(QSize(106, 26));

        verticalLayout_4->addWidget(pushButton_ResetSemiAuto);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_5 = new QLabel(layoutWidget4);
        label_5->setObjectName(QStringLiteral("label_5"));
        sizePolicy1.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy1);
        label_5->setMinimumSize(QSize(61, 26));
        label_5->setMaximumSize(QSize(61, 26));
        label_5->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(label_5);

        spinBox_Speed = new QSpinBox(layoutWidget4);
        spinBox_Speed->setObjectName(QStringLiteral("spinBox_Speed"));
        spinBox_Speed->setEnabled(false);
        spinBox_Speed->setMinimumSize(QSize(41, 26));
        spinBox_Speed->setMaximumSize(QSize(41, 26));
        spinBox_Speed->setValue(5);

        horizontalLayout_6->addWidget(spinBox_Speed);


        verticalLayout_4->addLayout(horizontalLayout_6);

        layoutWidget5 = new QWidget(UI);
        layoutWidget5->setObjectName(QStringLiteral("layoutWidget5"));
        layoutWidget5->setGeometry(QRect(850, 140, 103, 92));
        verticalLayout_3 = new QVBoxLayout(layoutWidget5);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        checkBox_SemiAuto = new QCheckBox(layoutWidget5);
        checkBox_SemiAuto->setObjectName(QStringLiteral("checkBox_SemiAuto"));
        checkBox_SemiAuto->setEnabled(false);
        sizePolicy1.setHeightForWidth(checkBox_SemiAuto->sizePolicy().hasHeightForWidth());
        checkBox_SemiAuto->setSizePolicy(sizePolicy1);
        checkBox_SemiAuto->setMinimumSize(QSize(101, 26));
        checkBox_SemiAuto->setMaximumSize(QSize(101, 26));

        verticalLayout_3->addWidget(checkBox_SemiAuto);

        checkBox_manual = new QCheckBox(layoutWidget5);
        checkBox_manual->setObjectName(QStringLiteral("checkBox_manual"));
        checkBox_manual->setEnabled(false);
        sizePolicy1.setHeightForWidth(checkBox_manual->sizePolicy().hasHeightForWidth());
        checkBox_manual->setSizePolicy(sizePolicy1);
        checkBox_manual->setMinimumSize(QSize(101, 26));
        checkBox_manual->setMaximumSize(QSize(101, 26));

        verticalLayout_3->addWidget(checkBox_manual);

        checkBox_Auto = new QCheckBox(layoutWidget5);
        checkBox_Auto->setObjectName(QStringLiteral("checkBox_Auto"));
        checkBox_Auto->setEnabled(false);
        sizePolicy1.setHeightForWidth(checkBox_Auto->sizePolicy().hasHeightForWidth());
        checkBox_Auto->setSizePolicy(sizePolicy1);
        checkBox_Auto->setMinimumSize(QSize(101, 26));
        checkBox_Auto->setMaximumSize(QSize(101, 26));

        verticalLayout_3->addWidget(checkBox_Auto);

        tabWidget->addTab(UI, QString());
        layoutWidget->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        graphicsView_local->raise();
        layoutWidget->raise();
        pushButton_All->raise();
        pushButton_BehaviorStatus->raise();
        pushButton_OperationStatus->raise();
        layoutWidget->raise();
        GlobalPlanning = new QWidget();
        GlobalPlanning->setObjectName(QStringLiteral("GlobalPlanning"));
        graphicsView_global = new QGraphicsView(GlobalPlanning);
        graphicsView_global->setObjectName(QStringLiteral("graphicsView_global"));
        graphicsView_global->setGeometry(QRect(50, 0, 1300, 700));
        graphicsView_global->setMinimumSize(QSize(1300, 700));
        graphicsView_global->setMaximumSize(QSize(1300, 700));
        graphicsView_global->viewport()->setProperty("cursor", QVariant(QCursor(Qt::PointingHandCursor)));
        graphicsView_global->setFocusPolicy(Qt::WheelFocus);
        graphicsView_global->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        graphicsView_global->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        graphicsView_global->setInteractive(false);
        groupBox_GlobalOperation = new QGroupBox(GlobalPlanning);
        groupBox_GlobalOperation->setObjectName(QStringLiteral("groupBox_GlobalOperation"));
        groupBox_GlobalOperation->setGeometry(QRect(230, 700, 251, 51));
        groupBox_GlobalOperation->setCursor(QCursor(Qt::PointingHandCursor));
        layoutWidget7 = new QWidget(groupBox_GlobalOperation);
        layoutWidget7->setObjectName(QStringLiteral("layoutWidget7"));
        layoutWidget7->setGeometry(QRect(30, 20, 192, 22));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget7);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        checkBox_scale = new QCheckBox(layoutWidget7);
        checkBox_scale->setObjectName(QStringLiteral("checkBox_scale"));

        horizontalLayout_5->addWidget(checkBox_scale);

        checkBox_translate = new QCheckBox(layoutWidget7);
        checkBox_translate->setObjectName(QStringLiteral("checkBox_translate"));

        horizontalLayout_5->addWidget(checkBox_translate);

        checkBox_view = new QCheckBox(layoutWidget7);
        checkBox_view->setObjectName(QStringLiteral("checkBox_view"));
        checkBox_view->setChecked(true);
        checkBox_view->setAutoExclusive(true);

        horizontalLayout_5->addWidget(checkBox_view);

        tabWidget->addTab(GlobalPlanning, QString());
        MainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1409, 23));
        MainWindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindowClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindowClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindowClass->setStatusBar(statusBar);

        retranslateUi(MainWindowClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "MainWindow", 0));
        pushButton_All->setText(QString());
        pushButton_BehaviorStatus->setText(QString());
        pushButton_OperationStatus->setText(QString());
        label_29->setText(QApplication::translate("MainWindowClass", "PERCEPTION MESSAGE", 0));
        label_6->setText(QApplication::translate("MainWindowClass", "Message Status:", 0));
        label_12->setText(QApplication::translate("MainWindowClass", "INS", 0));
        pushButton_INSStatus->setText(QString());
        label_13->setText(QApplication::translate("MainWindowClass", "Line", 0));
        pushButton_LineStatus->setText(QString());
        label_14->setText(QApplication::translate("MainWindowClass", "Obs", 0));
        pushButton_ObsStatus->setText(QString());
        label_15->setText(QApplication::translate("MainWindowClass", "Perception Line Message:", 0));
        label_21->setText(QApplication::translate("MainWindowClass", "LeftLeft", 0));
        label_20->setText(QApplication::translate("MainWindowClass", "Left Line", 0));
        label_22->setText(QApplication::translate("MainWindowClass", "Right Line", 0));
        label_23->setText(QApplication::translate("MainWindowClass", "RightRight", 0));
        label_16->setText(QApplication::translate("MainWindowClass", "Vehicle Distance to Line", 0));
        label_17->setText(QApplication::translate("MainWindowClass", "Left:", 0));
        label_18->setText(QApplication::translate("MainWindowClass", "Right", 0));
        label->setText(QApplication::translate("MainWindowClass", "VehicleInfo:", 0));
        label_2->setText(QApplication::translate("MainWindowClass", "Status:", 0));
        label_7->setText(QApplication::translate("MainWindowClass", "VehSpeed:", 0));
        label_10->setText(QApplication::translate("MainWindowClass", "WheelAngle:", 0));
        label_31->setText(QApplication::translate("MainWindowClass", "Acceleration:", 0));
        label_30->setText(QApplication::translate("MainWindowClass", "YawRate", 0));
        label_9->setText(QApplication::translate("MainWindowClass", "Posture:", 0));
        label_32->setText(QApplication::translate("MainWindowClass", "BEHAVIOR PLAN", 0));
        label_19->setText(QApplication::translate("MainWindowClass", "Lane Status", 0));
        label_27->setText(QApplication::translate("MainWindowClass", "Safety", 0));
        label_28->setText(QApplication::translate("MainWindowClass", "Priority", 0));
        label_24->setText(QApplication::translate("MainWindowClass", "Left", 0));
        label_25->setText(QApplication::translate("MainWindowClass", "Overtake", 0));
        label_26->setText(QApplication::translate("MainWindowClass", "Right", 0));
        label_33->setText(QApplication::translate("MainWindowClass", "CONTROL DATA", 0));
        label_8->setText(QApplication::translate("MainWindowClass", "DesSpeed:", 0));
        label_11->setText(QApplication::translate("MainWindowClass", "DesAngle:", 0));
        pushButton_ChangeLeft->setText(QApplication::translate("MainWindowClass", "Change Left", 0));
        pushButton_ChangeRight->setText(QApplication::translate("MainWindowClass", "Change Right", 0));
        pushButton_ResetSemiAuto->setText(QApplication::translate("MainWindowClass", "Reset", 0));
        label_5->setText(QApplication::translate("MainWindowClass", "Set Speed", 0));
        checkBox_SemiAuto->setText(QApplication::translate("MainWindowClass", "L2", 0));
        checkBox_manual->setText(QApplication::translate("MainWindowClass", "L3", 0));
        checkBox_Auto->setText(QApplication::translate("MainWindowClass", "L4", 0));
        tabWidget->setTabText(tabWidget->indexOf(UI), QApplication::translate("MainWindowClass", "UI", 0));
        groupBox_GlobalOperation->setTitle(QApplication::translate("MainWindowClass", "Operation", 0));
        checkBox_scale->setText(QApplication::translate("MainWindowClass", "Scale", 0));
        checkBox_translate->setText(QApplication::translate("MainWindowClass", "Translate", 0));
        checkBox_view->setText(QApplication::translate("MainWindowClass", "View", 0));
        tabWidget->setTabText(tabWidget->indexOf(GlobalPlanning), QApplication::translate("MainWindowClass", "GlobalPlanning", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
