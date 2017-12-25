#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent),
	m_bIsControlOn(false)
{
	ui.setupUi(this);

	this->ui.pushButton_ChangeLeft->setEnabled(false);
	this->ui.pushButton_ChangeRight->setEnabled(false);
	this->ui.pushButton_ResetSemiAuto->setEnabled(false);

	connect(ui.checkBox_Auto, SIGNAL(stateChanged(int)), this, SLOT(OnDriveOperation()));
	connect(ui.checkBox_manual, SIGNAL(stateChanged(int)), this, SLOT(OnDriveOperation()));
	connect(ui.checkBox_SemiAuto, SIGNAL(stateChanged(int)), this, SLOT(OnDriveOperation()));
	connect(ui.pushButton_All, SIGNAL(clicked()), this, SLOT(OnOpenControlButton()));
	connect(ui.pushButton_ChangeLeft, SIGNAL(clicked(bool)), this, SLOT(OnChangeLeftOperation()));
	connect(ui.pushButton_ChangeRight, SIGNAL(clicked(bool)), this, SLOT(OnChangeRightOperation()));
	connect(ui.pushButton_ResetSemiAuto, SIGNAL(clicked(bool)), this, SLOT(OnResetBehaviorSemiAuto()));
	connect(ui.spinBox_Speed, SIGNAL(valueChanged(int)), this, SLOT(OnSpeedSetOperation(int)));

	m_pVehImg = new QPixmap();
	m_pIndicatorRedLamp = new QPixmap();
	m_pIndicatorGreenLamp = new QPixmap();
	m_pIndicatorBlueLamp = new QPixmap();
	m_pIndicatorYellowLamp = new QPixmap();
	m_pStatusKeepLane = new QPixmap();
	m_pStatusChangeLeft = new QPixmap();
	m_pStatusChangeRight = new QPixmap();
	m_pButtonOn = new QPixmap();
	m_pButtonOff = new QPixmap();
	m_pStatusL0 = new QPixmap();
	m_pStatusL2 = new QPixmap();
	m_pStatusL3 = new QPixmap();
	m_pStatusL4 = new QPixmap();

	m_pLineLeft = new QGraphicsPathItem();
	m_pLineLeftLeft = new QGraphicsPathItem();
	m_pLineRight = new QGraphicsPathItem();
	m_pLineRightRight = new QGraphicsPathItem();
	m_pLineMiddle = new QGraphicsPathItem();

	m_pGridLinem30 = new QGraphicsLineItem();
	m_pGridLine0 = new QGraphicsLineItem();
	m_pGridLine30 = new QGraphicsLineItem();
	m_pGridLine60 = new QGraphicsLineItem();
	m_pGridLine90 = new QGraphicsLineItem();
	m_pGridLine120 = new QGraphicsLineItem();
	m_pStopLine = new QGraphicsLineItem();

	m_pGridMarkm30 = new QGraphicsTextItem();
	m_pGridMark0 = new QGraphicsTextItem();
	m_pGridMark30 = new QGraphicsTextItem();
	m_pGridMark60 = new QGraphicsTextItem();
	m_pGridMark90 = new QGraphicsTextItem();
	m_pGridMark120 = new QGraphicsTextItem();

	m_pVehRect = new QGraphicsRectItem();

	m_pNavPath = new QGraphicsPathItem();
	m_pLocalPath = new QGraphicsPathItem();
	m_pGlobalLocalPath = new QGraphicsPathItem();
	m_pGlobalPath = new QGraphicsPathItem();
	m_pGlobalCurrentPath = new QGraphicsPathItem();
	m_pSelfTrajectory = new QGraphicsPathItem();
	m_pSceneGlobalItem = new QGraphicsItemGroup();
	m_pSceneLocalItem = new QGraphicsItemGroup();
	m_pSceneLocal = new QGraphicsScene();
	m_pSceneGlobal = new QGraphicsScene();
}

MainWindow::~MainWindow()
{
	delete m_pVehImg;
	delete m_pIndicatorYellowLamp;
	delete m_pIndicatorRedLamp;
	delete m_pIndicatorGreenLamp;
	delete m_pIndicatorBlueLamp;
	delete m_pStatusKeepLane;
	delete m_pStatusChangeLeft;
	delete m_pStatusChangeRight;
	delete m_pButtonOff;
	delete m_pButtonOn;
	delete m_pStatusL0;
	delete m_pStatusL2;
	delete m_pStatusL3;
	delete m_pStatusL4;

	delete m_pLineLeft;
	delete m_pLineLeftLeft;
	delete m_pLineMiddle;
	delete m_pLineRight;
	delete m_pLineRightRight;

	delete m_pGridMark0;
	delete m_pGridMark30;
	delete m_pGridMarkm30;
	delete m_pGridMark60;
	delete m_pGridMark90;
	delete m_pGridMark120;
	delete m_pStopLine;
	delete m_pGridLine0;
	delete m_pGridLine30;
	delete m_pGridLinem30;
	delete m_pGridLine60;
	delete m_pGridLine90;
	delete m_pGridLine120;
	delete m_pVehRect;

	delete m_pNavPath;
	delete m_pLocalPath;
	delete m_pGlobalCurrentPath;
	delete m_pGlobalLocalPath;
	delete m_pGlobalPath;
	delete m_pSelfTrajectory;
	delete m_pSceneGlobalItem;
	delete m_pSceneGlobal;
	delete m_pSceneLocalItem;
	delete m_pSceneLocal;
}

void MainWindow::Init()
{
//local view
	m_pVehImg->load(VEHICLE_IMAGE_PATH);
	m_pIndicatorRedLamp->load(INDICATORLAMP_RED_PATH);
	m_pIndicatorGreenLamp->load(INDICATORLAMP_GREEN_PATH);
	m_pIndicatorBlueLamp->load(INDICATORLAMP_BLUE_PATH);
	m_pIndicatorYellowLamp->load(INDICATORLAMP_YELLOW_PATH);
	m_pStatusKeepLane->load(BEHAVIOR_KEEPLANE_PATH);
	m_pStatusChangeLeft->load(BEHAVIOR_LEFTCHANGE_PATH);
	m_pStatusChangeRight->load(BEHAVIOR_RIGHTCHANGE_PATH);
	m_pButtonOn->load(POWERON_PATH);
	m_pButtonOff->load(POWEROFF_PATH);
	m_pStatusL0->load(DRIVE_STATUSL0_PATH);
	m_pStatusL2->load(DRIVE_STATUSL2_PATH);
	m_pStatusL3->load(DRIVE_STATUSL3_PATH);
	m_pStatusL4->load(DRIVE_STATUSL4_PATH);

	ui.pushButton_INSStatus->setIcon(*m_pIndicatorRedLamp);
	ui.pushButton_INSStatus->setIconSize(QSize(ui.pushButton_INSStatus->width(), ui.pushButton_INSStatus->height()));
	ui.pushButton_LineStatus->setIcon(*m_pIndicatorRedLamp);
	ui.pushButton_LineStatus->setIconSize(QSize(ui.pushButton_LineStatus->width(), ui.pushButton_LineStatus->height()));
	ui.pushButton_ObsStatus->setIcon(*m_pIndicatorRedLamp);
	ui.pushButton_ObsStatus->setIconSize(QSize(ui.pushButton_ObsStatus->width(), ui.pushButton_ObsStatus->height()));
	ui.pushButton_BehaviorStatus->setIcon(*m_pStatusKeepLane);
	ui.pushButton_BehaviorStatus->setIconSize(QSize(ui.pushButton_BehaviorStatus->width(), ui.pushButton_BehaviorStatus->height()));
	ui.pushButton_OperationStatus->setIcon(*m_pStatusL0);
	ui.pushButton_OperationStatus->setIconSize(QSize(ui.pushButton_OperationStatus->width(), ui.pushButton_OperationStatus->height()));
	SetButton();

	m_qtPen.setColor(Qt::gray);
	m_pGridLinem30->setPen(m_qtPen);
	m_pGridLine0->setPen(m_qtPen);
	m_pGridLine30->setPen(m_qtPen);
	m_pGridLine60->setPen(m_qtPen);
	m_pGridLine90->setPen(m_qtPen);
	m_pGridLine120->setPen(m_qtPen);
	m_qtPen.setColor(Qt::red);
	m_pStopLine->setPen(m_qtPen);

	m_pGridLinem30->setLine(DrawLine(-GRIDLINE_WIDTH,  0, GRIDLINE_WIDTH, 0));
	m_pGridMarkm30->setPlainText("-30M");
	m_pGridMarkm30->setRotation(180);
	m_pGridMarkm30->setPos(GRIDLINE_WIDTH*WIDTH_FACTOR, 3 * HEIGHT_FACTOR);

	m_pGridLine0->setLine(DrawLine(-GRIDLINE_WIDTH, 1 * GRIDLINE_HEIGHT, GRIDLINE_WIDTH, 1 * GRIDLINE_HEIGHT));
	m_pGridMark0->setPlainText("0M");
	m_pGridMark0->setRotation(180);
	m_pGridMark0->setPos(GRIDLINE_WIDTH*WIDTH_FACTOR, 1 * (GRIDLINE_HEIGHT)*HEIGHT_FACTOR + 3 * HEIGHT_FACTOR);

	m_pGridLine30->setLine(DrawLine(-GRIDLINE_WIDTH, 2 * GRIDLINE_HEIGHT, GRIDLINE_WIDTH, 2 * GRIDLINE_HEIGHT));
	m_pGridMark30->setPlainText("30M");
	m_pGridMark30->setRotation(180);
	m_pGridMark30->setPos(GRIDLINE_WIDTH*WIDTH_FACTOR, 2 * (GRIDLINE_HEIGHT)*HEIGHT_FACTOR + 3 * HEIGHT_FACTOR);

	m_pGridLine60->setLine(DrawLine(-GRIDLINE_WIDTH, 3 * GRIDLINE_HEIGHT, GRIDLINE_WIDTH, 3 * GRIDLINE_HEIGHT));
	m_pGridMark60->setPlainText("60M");
	m_pGridMark60->setRotation(180);
	m_pGridMark60->setPos(GRIDLINE_WIDTH*WIDTH_FACTOR, 3 * (GRIDLINE_HEIGHT)*HEIGHT_FACTOR + 3 * HEIGHT_FACTOR);

	m_pGridLine90->setLine(DrawLine(-GRIDLINE_WIDTH, 4 * GRIDLINE_HEIGHT, GRIDLINE_WIDTH, 4 * GRIDLINE_HEIGHT));
	m_pGridMark90->setPlainText("90M");
	m_pGridMark90->setRotation(180);
	m_pGridMark90->setPos(GRIDLINE_WIDTH*WIDTH_FACTOR, 4 * (GRIDLINE_HEIGHT)*HEIGHT_FACTOR + 3 * HEIGHT_FACTOR);

	m_pGridLine120->setLine(DrawLine(-GRIDLINE_WIDTH, 5 * GRIDLINE_HEIGHT, GRIDLINE_WIDTH, 5 * GRIDLINE_HEIGHT));
	m_pGridMark120->setPlainText("120M");
	m_pGridMark120->setRotation(180);
	m_pGridMark120->setPos(GRIDLINE_WIDTH*WIDTH_FACTOR, 5 * (GRIDLINE_HEIGHT)*HEIGHT_FACTOR + 3 * HEIGHT_FACTOR);

	m_qtPen.setColor(Qt::black);
	m_pVehRect->setPen(m_qtPen);
	m_pVehRect->setRect(DrawRectangle(0, kVehicleWidth / 2 + GRIDLINE_HEIGHT, kVehicleWidth, kVehicleLength));

	m_qtPen.setColor(Qt::red);
	m_pNavPath->setPen(m_qtPen);
	m_pNavPath->setPath(m_qtNaviPath);
	m_qtPen.setColor(Qt::blue);
	m_pLocalPath->setPen(m_qtPen);
	m_pLocalPath->setPath(m_qtLocalPath);
	m_qtPen.setColor(Qt::yellow);
	m_pGlobalLocalPath->setPen(m_qtPen);
	m_pGlobalLocalPath->setPath(m_qtGlobalLocalPath);

	QList<QGraphicsItem*> localSceneList;
	localSceneList.push_back(m_pLineLeftLeft);
	localSceneList.push_back(m_pLineLeft);
	localSceneList.push_back(m_pLineMiddle);
	localSceneList.push_back(m_pLineRight);
	localSceneList.push_back(m_pLineRightRight);
	localSceneList.push_back(m_pGridLinem30);
	localSceneList.push_back(m_pGridLine0); 
	localSceneList.push_back(m_pGridLine30); 
	localSceneList.push_back(m_pGridLine60);
	localSceneList.push_back(m_pGridLine90);
	localSceneList.push_back(m_pGridLine120);
	localSceneList.push_back(m_pStopLine);
	localSceneList.push_back(m_pGridMarkm30);
	localSceneList.push_back(m_pGridMark0);
	localSceneList.push_back(m_pGridMark30);
	localSceneList.push_back(m_pGridMark60);
	localSceneList.push_back(m_pGridMark90);
	localSceneList.push_back(m_pGridMark120);
	localSceneList.push_back(m_pVehRect);
	localSceneList.push_back(m_pNavPath);
	localSceneList.push_back(m_pGlobalLocalPath);
	localSceneList.push_back(m_pLocalPath);
	localSceneList.push_back(m_pSelfTrajectory);

	m_pSceneLocalItem = m_pSceneLocal->createItemGroup(localSceneList);

	int iwidth = ui.graphicsView_local->width();
	int iheight = ui.graphicsView_local->height();
	m_pSceneLocalItem->setPos(iwidth / 2, 30);
//global view
	m_qtPen.setColor(Qt::blue);
	m_pGlobalPath->setPen(m_qtPen);
	m_pGlobalPath->setPath(m_qtGlobalPath);
	m_qtPen.setColor(Qt::red);
	m_pGlobalCurrentPath->setPen(m_qtPen);
	m_pGlobalCurrentPath->setPath(m_qtGlobalCurrentPath);

	QList<QGraphicsItem*> globalSceneList;
	globalSceneList.push_back(m_pGlobalPath);
	globalSceneList.push_back(m_pGlobalCurrentPath);
	m_pSceneGlobalItem = m_pSceneGlobal->createItemGroup(globalSceneList);
	iwidth = ui.graphicsView_global->width();
	iheight = ui.graphicsView_global->height();
	m_pSceneGlobalItem->setPos(iwidth / 2, iheight / 2);
	ui.graphicsView_global->rotate(180);
	ui.graphicsView_local->rotate(180);

	ui.graphicsView_global->setScene(m_pSceneGlobal);
	ui.graphicsView_global->show();

	ui.graphicsView_local->setScene(m_pSceneLocal);
	ui.graphicsView_local->show();
}

void MainWindow::SetButton()
{
	if (m_bIsControlOn)
	{
		ui.pushButton_All->setIcon(*m_pButtonOn);
		ui.checkBox_Auto->setEnabled(true);
		ui.checkBox_manual->setEnabled(true);
		ui.checkBox_SemiAuto->setEnabled(true);
	}
	else
	{
		ui.pushButton_All->setIcon(*m_pButtonOff);
		ui.checkBox_Auto->setEnabled(false);
		ui.checkBox_manual->setEnabled(false);
		ui.checkBox_SemiAuto->setEnabled(false);
	}
	ui.pushButton_All->setIconSize(QSize(ui.pushButton_All->width(), ui.pushButton_All->height()));
}

void MainWindow::OnDriveOperation()
{
	if (ui.checkBox_Auto->checkState() == Qt::Checked)
	{
		ui.pushButton_OperationStatus->setIcon(*m_pStatusL4);
		ui.pushButton_OperationStatus->setIconSize(QSize(ui.pushButton_OperationStatus->width(), ui.pushButton_OperationStatus->height()));
		ui.checkBox_SemiAuto->setCheckState(Qt::Unchecked);
		ui.checkBox_manual->setCheckState(Qt::Unchecked);
		m_stGuiData.enOperateStatus = AUTOMATIC;
		m_stGuiData.enBehaviorStatus = KEEP_LANE;
	}
	if (ui.checkBox_manual->checkState() == Qt::Checked)
	{
		ui.pushButton_OperationStatus->setIcon(*m_pStatusL3);
		ui.pushButton_OperationStatus->setIconSize(QSize(ui.pushButton_OperationStatus->width(), ui.pushButton_OperationStatus->height()));
		ui.checkBox_SemiAuto->setCheckState(Qt::Unchecked);
		ui.checkBox_Auto->setCheckState(Qt::Unchecked);
		m_stGuiData.enOperateStatus = MANUAL;
		m_stGuiData.enBehaviorStatus = KEEP_LANE;
	}
	if (ui.checkBox_SemiAuto->checkState() == Qt::Checked)
	{
		ui.pushButton_OperationStatus->setIcon(*m_pStatusL2);
		ui.pushButton_OperationStatus->setIconSize(QSize(ui.pushButton_OperationStatus->width(), ui.pushButton_OperationStatus->height()));
		ui.checkBox_manual->setCheckState(Qt::Unchecked);
		ui.checkBox_Auto->setCheckState(Qt::Unchecked);
		m_stGuiData.enOperateStatus = SEMI_AUTOMATIC;
		ui.pushButton_ChangeLeft->setEnabled(true);
		ui.pushButton_ChangeRight->setEnabled(true);
		ui.pushButton_ResetSemiAuto->setEnabled(true);
		ui.spinBox_Speed->setEnabled(true);
		m_stGuiData.enBehaviorStatus = KEEP_LANE;
	}

	unique_lock<shared_mutex> guiLock(gGUIMutex);
	gGUIData.enOperateStatus = m_stGuiData.enOperateStatus;
	gGUIData.enBehaviorStatus = m_stGuiData.enBehaviorStatus;
	guiLock.unlock();
}

void MainWindow::OnSpeedSetOperation(int speed)
{
	m_stGuiData.iSpeed = speed;
	unique_lock<shared_mutex> guiLock(gGUIMutex);
	gGUIData.iSpeed = m_stGuiData.iSpeed;
	guiLock.unlock();
}

void MainWindow::OnChangeLeftOperation()
{
	m_stGuiData.enBehaviorStatus = CHANGE_LEFT;
	unique_lock<shared_mutex> guiLock(gGUIMutex);
	gGUIData.enBehaviorStatus = m_stGuiData.enBehaviorStatus;
	guiLock.unlock();
}

void MainWindow::OnChangeRightOperation()
{
	m_stGuiData.enBehaviorStatus = CHANGE_RIGHT;
	unique_lock<shared_mutex> guiLock(gGUIMutex);
	gGUIData.enBehaviorStatus = m_stGuiData.enBehaviorStatus;
	guiLock.unlock();
}

void MainWindow::OnResetBehaviorSemiAuto()
{
	m_stGuiData.bResetSemiAutoBehaviorStatus = true;
	unique_lock<shared_mutex> guiLock(gGUIMutex);
	gGUIData.bResetSemiAutoBehaviorStatus = m_stGuiData.bResetSemiAutoBehaviorStatus;
	guiLock.unlock();
}


void MainWindow::OnDisplayNaviPath(vector<PointXY> path)
{
	if (!m_bIsControlOn)
	{
		return;
	}
	m_qtNaviPath = DrawPath(path);
	m_pNavPath->setPath(m_qtNaviPath);
}

void MainWindow::OnDisplayLocalPath(vector<PointXY> path)
{
	if (!m_bIsControlOn)
	{
		return;
	}
	vector<PointXY>().swap(vec_gRecordPath);//vec_gRecordPath.clear();
	vec_gRecordPath = path;
	m_qtLocalPath = DrawPath(path);
	m_pLocalPath->setPath(m_qtLocalPath);
}

void MainWindow::OnDisplayGlobalLocalPath(vector<PointXY> path)
{
	if (!m_bIsControlOn)
	{
		return;
	}
	m_qtGlobalLocalPath = DrawPath(path);
	m_pGlobalLocalPath->setPath(m_qtGlobalLocalPath);
}

void MainWindow::OnDisplayGlobalPath(vector<PointXY> path)
{
	m_qtGlobalPath = DrawGlobalPath(path);
	m_pGlobalPath->setPath(m_qtGlobalPath);
}

void MainWindow::OnDisplayGlobalCurrentPath(PointXY point)
{
	if (!m_bIsControlOn)
	{
		return;
	}
	double dDis = Distance(point.x, point.y, m_stLastPosition.x, m_stLastPosition.y);
	if (fabs(m_stLastPosition.x)<0.00005)
	{
		m_stLastPosition = point;
	}
	else if (dDis > 2.0 && dDis < 20.0)
	{
		m_qtGlobalCurrentPath.lineTo(point.x, point.y);
		m_pGlobalCurrentPath->setPath(m_qtGlobalCurrentPath);
		m_stLastPosition = point;
	}
}

void MainWindow::WheelEvent(QWheelEvent* event)
{
	if (ui.checkBox_scale->checkState() == Qt::Checked)
	{
		event->accept();
		if (event->delta() > 0)
		{
			ui.graphicsView_global->scale(1.21, 1.21);
		}
		else
		{
			ui.graphicsView_global->scale(1 / 1.21, 1 / 1.21);
		}
	}
	else
	{
		event->ignore();
	}
}

void MainWindow::MouseMoveEvent(QMouseEvent *event)
{
	if (ui.checkBox_translate->checkState() == Qt::Checked)
	{
		event->accept();
		if (event->button() & Qt::LeftButton)
		{
			ui.graphicsView_global->rotate(20);
		}
	}
	else
	{
		event->ignore();
	}
}

PointXY MainWindow::SetPosInLocalSceneList(Obstacle obs)
{
	PointXY tmpPoint;
	tmpPoint.x = obs.stCenterPoint.x * WIDTH_FACTOR;
	tmpPoint.y = (obs.stCenterPoint.y + GRIDLINE_HEIGHT)*HEIGHT_FACTOR;
	return tmpPoint;
}

void MainWindow::OnDisplayVehData(DisplayData VehData)
{
	if (!m_bIsControlOn)
	{
		return;
	}
//show operation status
	switch (VehData.DisplayOperationStatus)
	{
	case AUTOMATIC:
		ui.textBrowser_VehStatus->setText("Auto");
		ui.textBrowser_VehStatus->setTextColor(Qt::red);
		break;
	case SEMI_AUTOMATIC:
		ui.textBrowser_VehStatus->setText("SemiAuto");
		ui.textBrowser_VehStatus->setTextColor(Qt::blue);
		break;
	case MANUAL:
		ui.textBrowser_VehStatus->setText("Manual");
		ui.textBrowser_VehStatus->setTextColor(Qt::green);
		break;
	default:
		ui.textBrowser_VehStatus->setText("Error");
		ui.textBrowser_VehStatus->setTextColor(Qt::yellow);
		break;
	}
	ui.textBrowser_VehStatus->setAlignment(Qt::AlignCenter);
//show behavior status
	m_stGuiData.enBehaviorStatus = VehData.DisplayBehaviorStatus;
	switch (VehData.DisplayBehaviorStatus)
	{
	case KEEP_LANE:
		//ui.textBrowser_VehBehavior->setText("KEEP_LANE");
		//ui.textBrowser_VehBehavior->setTextColor(Qt::green);
		ui.pushButton_BehaviorStatus->setIcon(*m_pStatusKeepLane);
		ui.pushButton_BehaviorStatus->setIconSize(QSize(ui.pushButton_BehaviorStatus->width(), ui.pushButton_BehaviorStatus->height()));
		break;
	case CHANGE_LEFT:
		//ui.textBrowser_VehBehavior->setText("CHANGE_LEFT");
		//ui.textBrowser_VehBehavior->setTextColor(Qt::blue);
		ui.pushButton_BehaviorStatus->setIcon(*m_pStatusChangeLeft);
		ui.pushButton_BehaviorStatus->setIconSize(QSize(ui.pushButton_BehaviorStatus->width(), ui.pushButton_BehaviorStatus->height()));
		break;
	case CHANGE_RIGHT:
		//ui.textBrowser_VehBehavior->setText("CHANGE_RIGHT");
		//ui.textBrowser_VehBehavior->setTextColor(Qt::blue);
		ui.pushButton_BehaviorStatus->setIcon(*m_pStatusChangeRight);
		ui.pushButton_BehaviorStatus->setIconSize(QSize(ui.pushButton_BehaviorStatus->width(), ui.pushButton_BehaviorStatus->height()));
		break;
	case OVER_LEFT:
		//ui.textBrowser_VehBehavior->setText("OVER_LEFT");
		//ui.textBrowser_VehBehavior->setTextColor(Qt::blue);
		break;
	case OVER_RIGHT:
		//ui.textBrowser_VehBehavior->setText("OVER_RIGHT");
		//ui.textBrowser_VehBehavior->setTextColor(Qt::blue);
		break;
	case HALF_OVER_LEFT:
		//ui.textBrowser_VehBehavior->setText("HALF_OVER_LEFT");
		//ui.textBrowser_VehBehavior->setTextColor(Qt::blue);
		break;
	case HALF_OVER_RIGHT:
		//ui.textBrowser_VehBehavior->setText("HALF_OVER_RIGHT");
		//ui.textBrowser_VehBehavior->setTextColor(Qt::blue);
		break;
	case STOP_IN_DISTANCE:
		//ui.textBrowser_VehBehavior->setText("STOP");
		//ui.textBrowser_VehBehavior->setTextColor(Qt::yellow);
		break;
	default:
		//ui.textBrowser_VehBehavior->setText("ERROR");
		//ui.textBrowser_VehBehavior->setTextColor(Qt::black);
		break;
	}
	//ui.textBrowser_VehBehavior->setAlignment(Qt::AlignCenter);
//Change Operation is not premitted when Auto semi_auto and Change lane 
	if (VehData.DisplayOperationStatus == SEMI_AUTOMATIC || VehData.DisplayOperationStatus == AUTOMATIC)
	{
		if (VehData.DisplayBehaviorStatus == CHANGE_LEFT || VehData.DisplayBehaviorStatus == CHANGE_RIGHT
			|| VehData.DisplayBehaviorStatus == OVER_LEFT || VehData.DisplayBehaviorStatus == OVER_RIGHT)
		{
			ui.checkBox_Auto->setEnabled(false);
			ui.checkBox_SemiAuto->setEnabled(false);
		}
		else
		{
			ui.checkBox_Auto->setEnabled(true);
			ui.checkBox_SemiAuto->setEnabled(true);
		}
	}
	else
	{
		ui.checkBox_Auto->setEnabled(true);
		ui.checkBox_SemiAuto->setEnabled(true);
	}
//Change lane need the destination lane safe
	if (VehData.DisplayOperationStatus == SEMI_AUTOMATIC && VehData.DisplayBehaviorStatus == KEEP_LANE)
	{
		if (VehData.DisplayBehaviorData.bLeftlaneSafe)
		{
			ui.pushButton_ChangeLeft->setEnabled(true);
		}
		else
		{
			ui.pushButton_ChangeLeft->setEnabled(false);
		}
		if (VehData.DisplayBehaviorData.bRightlaneSafe)
		{
			ui.pushButton_ChangeRight->setEnabled(true);
		}
		else
		{
			ui.pushButton_ChangeRight->setEnabled(false);
		}
	}
	else
	{
		ui.pushButton_ChangeLeft->setEnabled(false);
		ui.pushButton_ChangeRight->setEnabled(false);
	}

	if (VehData.DisplayOperationStatus == SEMI_AUTOMATIC)
	{
		if (VehData.DisplayBehaviorStatus == CHANGE_LEFT || VehData.DisplayBehaviorStatus == CHANGE_RIGHT)
		{
			ui.pushButton_ResetSemiAuto->setEnabled(true);
		}
		else
		{
			ui.pushButton_ResetSemiAuto->setEnabled(false);
		}
	}
	else
	{
		ui.pushButton_ResetSemiAuto->setEnabled(false);
	}
//show veh actual speed and steer
	ui.textBrowser_RealAngle->setText(QString::number(VehData.DisplayVehInfo.fSteeringWheelAngle));
	ui.textBrowser_RealAngle->setAlignment(Qt::AlignCenter);
	ui.textBrowser_RealSpeed->setText(QString::number(VehData.DisplayVehInfo.fSpeed/MS_KMH, 'f', 2));
	ui.textBrowser_RealSpeed->setAlignment(Qt::AlignCenter);
	ui.textBrowser_Yawrate->setText(QString::number(VehData.DisplayVehInfo.fYawRate, 'f', 2));
	ui.textBrowser_Yawrate->setAlignment(Qt::AlignCenter);
	ui.textBrowser_RealAcc->setText(QString::number(VehData.DisplayVehInfo.fAcc, 'f', 2));
	ui.textBrowser_RealAcc->setAlignment(Qt::AlignCenter);

	ui.textBrowser_DesignAngle->setText(QString::number(VehData.DisplayDesignSteer.iPosition));
	ui.textBrowser_DesignAngle->setAlignment(Qt::AlignCenter);
	ui.textBrowser_DesignSpeed->setText(QString::number(VehData.DisplayDesignSpeed.fSpeed*MS_KMH, 'f', 2));
	ui.textBrowser_DesignSpeed->setAlignment(Qt::AlignCenter);

	ui.textBrowser_Posture_lat->setText(QString::number((VehData.DisplayRTKInfo.dLatitude/100.0), 'f', 6));
	ui.textBrowser_Posture_lon->setText(QString::number((VehData.DisplayRTKInfo.dLongitude/100.0), 'f', 6));
	ui.textBrowser_Posture_heading->setText(QString::number(VehData.DisplayRTKInfo.fDirection, 'f', 2));
	ui.textBrowser_Posture_lat->setAlignment(Qt::AlignCenter);
	ui.textBrowser_Posture_lon->setAlignment(Qt::AlignCenter);
	ui.textBrowser_Posture_heading->setAlignment(Qt::AlignCenter);
//lane behavior
	if (VehData.DisplayBehaviorData.bOvertakeIntention)
	{
		ui.textBrowser_overtake->setText("YES");
	}
	else
	{
		ui.textBrowser_overtake->setText("NO");
	}
	ui.textBrowser_overtake->setAlignment(Qt::AlignCenter);
	//left lane elevation
	if (VehData.DisplayBehaviorData.bLeftlaneSafe)
	{
		ui.textBrowser_Left_bSafety->setText("||");
		ui.textBrowser_Left_bSafety->setTextColor(Qt::green);
	}
	else
	{
		ui.textBrowser_Left_bSafety->setText("||");
		ui.textBrowser_Left_bSafety->setTextColor(Qt::red);
	}
	if (VehData.DisplayBehaviorData.bLeftlaneBetter)
	{
		ui.textBrowser_Left_bPrior->setText("||");
		ui.textBrowser_Left_bPrior->setTextColor(Qt::green);
	}
	else
	{
		ui.textBrowser_Left_bPrior->setText("||");
		ui.textBrowser_Left_bPrior->setTextColor(Qt::red);
	}
	ui.textBrowser_Left_bSafety->setAlignment(Qt::AlignCenter);
	ui.textBrowser_Left_bPrior->setAlignment(Qt::AlignCenter);
	//right lane elevation
	if (VehData.DisplayBehaviorData.bRightlaneSafe)
	{
		ui.textBrowser_Right_bSafety->setText("||");
		ui.textBrowser_Right_bSafety->setTextColor(Qt::green);
	}
	else
	{
		ui.textBrowser_Right_bSafety->setText("||");
		ui.textBrowser_Right_bSafety->setTextColor(Qt::red);
	}
	if (VehData.DisplayBehaviorData.bRightlaneBetter)
	{
		ui.textBrowser_Right_bPrior->setText("||");
		ui.textBrowser_Right_bPrior->setTextColor(Qt::green);
	}
	else
	{
		ui.textBrowser_Right_bPrior->setText("||");
		ui.textBrowser_Right_bPrior->setTextColor(Qt::red);
	}
	ui.textBrowser_Right_bSafety->setAlignment(Qt::AlignCenter);
	ui.textBrowser_Right_bPrior->setAlignment(Qt::AlignCenter);

	//ui.textBrowser_Path_Type->setText("LINE");
	//ui.textBrowser_Path_Type->setAlignment(Qt::AlignCenter);
	//ui.textBrowser_Path_Angle->setText(QString::number(VehData.DisplaySteerCtrlFactor.fAngle, 'f', 2));
	//ui.textBrowser_Path_Angle->setAlignment(Qt::AlignCenter);
	//ui.textBrowser_Path_PreDis->setText(QString::number(VehData.DisplaySteerCtrlFactor.iPredictNum));
	//ui.textBrowser_Path_PreDis->setAlignment(Qt::AlignCenter);

//Perception Message lost
	if (VehData.DisplayObs.bMsgConnected)
	{
		if (VehData.DisplayObs.bMsgLost)
		{
			ui.pushButton_ObsStatus->setIcon(*m_pIndicatorYellowLamp);
		}
		else
		{
			ui.pushButton_ObsStatus->setIcon(*m_pIndicatorGreenLamp);
		}
	}
	else
	{
		ui.pushButton_ObsStatus->setIcon(*m_pIndicatorRedLamp);
	}
	ui.pushButton_ObsStatus->setIconSize(QSize(ui.pushButton_ObsStatus->width(), ui.pushButton_ObsStatus->height()));

	if (VehData.DisplayLine.bMsgConnected)
	{
		if (VehData.DisplayLine.bMsgLost)
		{
			ui.pushButton_LineStatus->setIcon(*m_pIndicatorYellowLamp);
		}
		else
		{
			ui.pushButton_LineStatus->setIcon(*m_pIndicatorGreenLamp);
		}
	}
	else
	{
		ui.pushButton_LineStatus->setIcon(*m_pIndicatorRedLamp);
	}
	ui.pushButton_LineStatus->setIconSize(QSize(ui.pushButton_LineStatus->width(), ui.pushButton_LineStatus->height()));

	if (VehData.DisplayRTKInfo.bMsgConnected)
	{
		if (VehData.DisplayRTKInfo.bMsgLost)
		{
			ui.pushButton_INSStatus->setIcon(*m_pIndicatorYellowLamp);
		}
		else
		{
			ui.pushButton_INSStatus->setIcon(*m_pIndicatorGreenLamp);
		}
	}
	else
	{
		ui.pushButton_INSStatus->setIcon(*m_pIndicatorRedLamp);
	}
	ui.pushButton_INSStatus->setIconSize(QSize(ui.pushButton_INSStatus->width(),ui.pushButton_INSStatus->height()));
//Perception Lines
	ui.textBrowser_dis2L->setText(QString::number(VehData.DisplayLine.fDis2LeftLine, 'f', 2));
	ui.textBrowser_dis2R->setText(QString::number(VehData.DisplayLine.fDis2RightLine, 'f', 2));
	ui.textBrowser_dis2L->setAlignment(Qt::AlignCenter);
	ui.textBrowser_dis2R->setAlignment(Qt::AlignCenter);
	QPainterPath nullPath;
	nullPath.moveTo(0, 0 + GRIDLINE_HEIGHT);
	//left left
	if (VehData.DisplayLine.stLeftLeft.bExist)
	{
		ui.textBrowser_LeftLeft_bExist->setText("REAL");
		ui.textBrowser_LeftLeft_bExist->setTextColor(Qt::green);
		m_qtPen.setColor(Qt::black);
		m_pLineLeftLeft->setPen(m_qtPen);
		m_qtPath = DrawPath(VehData.DisplayLine.stLeftLeft.vecLinePoints);
		m_pLineLeftLeft->setPath(m_qtPath);
		ui.textBrowser_LeftLeft_iLength->setText(QString::number(VehData.DisplayLine.stLeftLeft.vecLinePoints.size()));
	}
	else
	{
		ui.textBrowser_LeftLeft_bExist->setText("NON");
		ui.textBrowser_LeftLeft_bExist->setTextColor(Qt::red);
		m_qtPath = nullPath;
		m_pLineLeftLeft->setPath(m_qtPath);
		ui.textBrowser_LeftLeft_iLength->setText("0");
	}
	ui.textBrowser_LeftLeft_bExist->setAlignment(Qt::AlignCenter);
	ui.textBrowser_LeftLeft_iLength->setAlignment(Qt::AlignCenter);
	//left
	if (VehData.DisplayLine.stLeft.bExist)
	{
		ui.textBrowser_Left_bExist->setText("REAL");
		ui.textBrowser_Left_bExist->setTextColor(Qt::green);
		m_qtPen.setColor(Qt::black);
		m_pLineLeft->setPen(m_qtPen);
		m_qtPath = DrawPath(VehData.DisplayLine.stLeft.vecLinePoints);
		m_pLineLeft->setPath(m_qtPath);
		ui.textBrowser_Left_iLength->setText(QString::number(VehData.DisplayLine.stLeft.vecLinePoints.size()));
	}
	else
	{
		ui.textBrowser_Left_bExist->setText("NON");
		ui.textBrowser_Left_bExist->setTextColor(Qt::red);
		m_qtPath = nullPath;
		m_pLineLeft->setPath(m_qtPath);
		ui.textBrowser_Left_iLength->setText("0");
	}
	ui.textBrowser_Left_bExist->setAlignment(Qt::AlignCenter);
	ui.textBrowser_Left_iLength->setAlignment(Qt::AlignCenter);
	//right
	if (VehData.DisplayLine.stRight.bExist)
	{
		ui.textBrowser_Right_bExist->setText("REAL");
		ui.textBrowser_Right_bExist->setTextColor(Qt::green);
		m_qtPen.setColor(Qt::black);
		m_pLineRight->setPen(m_qtPen);
		m_qtPath = DrawPath(VehData.DisplayLine.stRight.vecLinePoints);
		m_pLineRight->setPath(m_qtPath);
		ui.textBrowser_Right_iLength->setText(QString::number(VehData.DisplayLine.stRight.vecLinePoints.size()));
	}
	else
	{
		ui.textBrowser_Right_bExist->setText("NON");
		ui.textBrowser_Right_bExist->setTextColor(Qt::red);
		m_qtPath = nullPath;
		m_pLineRight->setPath(m_qtPath);
		ui.textBrowser_Right_iLength->setText("0");
	}
	ui.textBrowser_Right_bExist->setAlignment(Qt::AlignCenter);
	ui.textBrowser_Right_iLength->setAlignment(Qt::AlignCenter);
	//right right
	if (VehData.DisplayLine.stRightRight.bExist)
	{
		ui.textBrowser_RightRight_bExist->setText("REAL");
		ui.textBrowser_RightRight_bExist->setTextColor(Qt::green);
		m_qtPen.setColor(Qt::black);
		m_pLineRightRight->setPen(m_qtPen);
		m_qtPath = DrawPath(VehData.DisplayLine.stRightRight.vecLinePoints);
		m_pLineRightRight->setPath(m_qtPath);
		ui.textBrowser_RightRight_iLength->setText(QString::number(VehData.DisplayLine.stRightRight.vecLinePoints.size()));
	}
	else
	{
		ui.textBrowser_RightRight_bExist->setText("NON");
		ui.textBrowser_RightRight_bExist->setTextColor(Qt::red);
		m_qtPath = nullPath;
		m_pLineRightRight->setPath(m_qtPath);
		ui.textBrowser_RightRight_iLength->setText("0");
	}
	ui.textBrowser_RightRight_bExist->setAlignment(Qt::AlignCenter);
	ui.textBrowser_RightRight_iLength->setAlignment(Qt::AlignCenter);
}

void MainWindow::OnOpenControlButton()
{
	m_bIsControlOn = !m_bIsControlOn;
	SetButton();
}
