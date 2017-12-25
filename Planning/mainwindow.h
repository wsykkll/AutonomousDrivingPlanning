#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
#include "CoordinateTrans.h"
#include "VehPlanning.h"
#include "QtGraphicDraw.h"

#define VEHICLE_IMAGE_PATH "../data/image/igs.png"
#define INDICATORLAMP_RED_PATH "../data/image/red.png"
#define INDICATORLAMP_BLUE_PATH "../data/image/blue.png"
#define INDICATORLAMP_GREEN_PATH "../data/image/green.png"
#define INDICATORLAMP_YELLOW_PATH "../data/image/yellow.png"
#define BEHAVIOR_LEFTCHANGE_PATH "../data/image/Left.png"
#define BEHAVIOR_RIGHTCHANGE_PATH "../data/image/Right.png"
#define BEHAVIOR_KEEPLANE_PATH "../data/image/KeepLane.png"
#define POWERON_PATH "../data/image/On.png"
#define POWEROFF_PATH "../data/image/OFF.png"
#define DRIVE_STATUSL0_PATH "../data/image/L0.png"
#define DRIVE_STATUSL2_PATH "../data/image/L2.png"
#define DRIVE_STATUSL3_PATH "../data/image/L3.png"
#define DRIVE_STATUSL4_PATH "../data/image/L4.png"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

	void Init();
private:
	Ui::MainWindowClass ui;

	vector<PointXY> vec_gRecordPath;
	QPen m_qtPen;
	QBrush m_qtBrush;
	QPixmap* m_pVehImg;
	QPixmap* m_pIndicatorRedLamp;
	QPixmap* m_pIndicatorGreenLamp;
	QPixmap* m_pIndicatorBlueLamp;
	QPixmap* m_pIndicatorYellowLamp;
	QPixmap* m_pStatusChangeLeft;
	QPixmap* m_pStatusChangeRight;
	QPixmap* m_pStatusKeepLane;
	QPixmap* m_pButtonOn;
	QPixmap* m_pButtonOff;
	QPixmap* m_pStatusL0;
	QPixmap* m_pStatusL2;
	QPixmap* m_pStatusL3;
	QPixmap* m_pStatusL4;

	bool m_bIsControlOn;

	QPainterPath m_qtPath;
	QPainterPath m_qtNaviPath;
	QPainterPath m_qtGlobalPath;
	QPainterPath m_qtLocalPath;
	QPainterPath m_qtGlobalLocalPath;

	QGraphicsLineItem* m_pGridLinem30;
	QGraphicsLineItem* m_pGridLine0;
	QGraphicsLineItem* m_pGridLine30;
	QGraphicsLineItem* m_pGridLine60;
	QGraphicsLineItem* m_pGridLine90;
	QGraphicsLineItem* m_pGridLine120;

	QGraphicsLineItem* m_pStopLine;

	QGraphicsTextItem* m_pGridMarkm30;
	QGraphicsTextItem* m_pGridMark0;
	QGraphicsTextItem* m_pGridMark30;
	QGraphicsTextItem* m_pGridMark60;
	QGraphicsTextItem* m_pGridMark90;
	QGraphicsTextItem* m_pGridMark120;

	PointXY m_stLastPosition;
	QPainterPath m_qtGlobalCurrentPath;

	QGraphicsPathItem* m_pNavPath;
	QGraphicsPathItem* m_pHppPath;
	QGraphicsPathItem* m_pLocalPath;
	QGraphicsPathItem* m_pGlobalLocalPath;
	QGraphicsPathItem* m_pSelfTrajectory;
	//QGraphicsPathItem* m_pLeftObstacleTrajectory[kMaxLeftlaneObstacleNumber];
	//QGraphicsPathItem* m_pRightObstacleTrajectory[kMaxRightlaneObstacleNumber];
	//QGraphicsPathItem* m_pMiddleObstacleTrajectory[kMaxMiddlelaneObstacleNumber];
	//QGraphicsPathItem* m_pOutObstacleTrajectory[kMaxOutlaneObstacleNumber];

	QGraphicsPathItem* m_pGlobalPath;
	QGraphicsPathItem* m_pGlobalCurrentPath;

	QGraphicsPathItem* m_pLineLeftLeft;
	QGraphicsPathItem* m_pLineLeft;
	QGraphicsPathItem* m_pLineRight;
	QGraphicsPathItem* m_pLineRightRight;
	QGraphicsPathItem* m_pLineMiddle;

	QGraphicsRectItem* m_pVehRect;
	//QGraphicsRectItem* m_Obstacle_LeftLane[kMaxLeftlaneObstacleNumber];
	//QGraphicsRectItem* m_Obstacle_RightLane[kMaxRightlaneObstacleNumber];
	//QGraphicsRectItem* m_Obstacle_MiddleLane[kMaxMiddlelaneObstacleNumber];
	//QGraphicsRectItem* m_Obstacle_OutLane[kMaxOutlaneObstacleNumber];

	QGraphicsItemGroup* m_pSceneLocalItem;
	QGraphicsItemGroup* m_pSceneGlobalItem;
	QGraphicsScene* m_pSceneLocal;
	QGraphicsScene* m_pSceneGlobal;

	GUIData m_stGuiData;

	void SetButton();

public slots:
	void OnDisplayVehData(DisplayData);
	void OnDisplayNaviPath(vector<PointXY>);
	void OnDisplayLocalPath(vector<PointXY>);
	void OnDisplayGlobalLocalPath(vector<PointXY>);
	void OnDisplayGlobalPath(vector<PointXY>);
	void OnDisplayGlobalCurrentPath(PointXY);

	void OnDriveOperation();
	void OnSpeedSetOperation(int);
	void OnChangeLeftOperation();
	void OnChangeRightOperation();
	void OnResetBehaviorSemiAuto();

	void OnOpenControlButton();

	void MouseMoveEvent(QMouseEvent *event);
	void WheelEvent(QWheelEvent* event);
	PointXY SetPosInLocalSceneList(Obstacle obs);
};

#endif // MAINWINDOW_H
