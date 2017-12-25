#include "mainwindow.h"
#include <QtWidgets/QApplication>
#include "PerceptionLines.h"
#include "VehPlanning.h"
#include "VehicleInfo.h"
#include "RTKInfo.h"
#include "global.hpp"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.setWindowIcon(QIcon("..\\data\\plan.ico"));
	w.Init();

	CRTKInfo stRTKInfoProcess;
	if (!stRTKInfoProcess.InitializeLCM())
	{
		return EXIT_FAILURE;
	}
	stRTKInfoProcess.m_pLCM->subscribe("GPSFront", &CRTKInfo::LCMHandler, &stRTKInfoProcess);

	CVehicleInfo stVehicleInfoProcess;
	if (!stVehicleInfoProcess.InitializeLCM())
	{
		return EXIT_FAILURE;
	}
	stVehicleInfoProcess.m_pLCM->subscribe("VehicleInfo_.*",&CVehicleInfo::LCMHandler,&stVehicleInfoProcess);

	CPerceptionLines stPerceptionLines;
	if (!stPerceptionLines.InitializeLCM())
	{
		return EXIT_FAILURE;
	}
	stPerceptionLines.m_pLCM->subscribe("MAP_LINES", &CPerceptionLines::LCMHandler, &stPerceptionLines);
	CVehPlanning* pVehiclePlanning = new CVehPlanning();
	pVehiclePlanning->Init();

	qRegisterMetaType<PointXY>("PointXY");
	qRegisterMetaType< list<PointXY> >("list<PointXY>");
	qRegisterMetaType< vector<PointXY> >("vector<PointXY>");
	qRegisterMetaType<DisplayData>("DisplayData");

	QObject::connect(pVehiclePlanning, SIGNAL(DisplayVehData(DisplayData)), &w, SLOT(OnDisplayVehData(DisplayData)));
	QObject::connect(pVehiclePlanning, SIGNAL(DisplayNaviPath(vector<PointXY>)), &w, SLOT(OnDisplayNaviPath(vector<PointXY>)));
	QObject::connect(pVehiclePlanning, SIGNAL(DisplayLocalPath(vector<PointXY>)), &w, SLOT(OnDisplayLocalPath(vector<PointXY>)));
	QObject::connect(pVehiclePlanning, SIGNAL(DisplayGlobalLocalPath(vector<PointXY>)), &w, SLOT(OnDisplayGlobalLocalPath(vector<PointXY>)));
	QObject::connect(pVehiclePlanning, SIGNAL(DisplayGlobalPath(vector<PointXY>)), &w, SLOT(OnDisplayGlobalPath(vector<PointXY>)));
	QObject::connect(pVehiclePlanning, SIGNAL(DisplayGlobalCurrentPath(PointXY)), &w, SLOT(OnDisplayGlobalCurrentPath(PointXY)));

	//thread_group stThreadGroup;
	//stThreadGroup.create_thread(bind(&CVehicleInfo::VehicleInfoRun, stVehicleInfoProcess));
	//stThreadGroup.create_thread(bind(&CPerceptionLines::LineThreadRun, stPerceptionLines));
	//stThreadGroup.create_thread(bind(&CRTKInfo::RTKInfoRun, stRTKInfoProcess));
	//stThreadGroup.create_thread(bind(&CVehPlanning::PlanningThreadRun, stVehiclePlanning));

	thread ThreadRTKInfo(bind(&CRTKInfo::RTKInfoRun, &stRTKInfoProcess));
	thread ThreadPerceptionLines(bind(&CPerceptionLines::LineThreadRun, stPerceptionLines));
	thread ThreadVehiceleInfo(bind(&CVehicleInfo::VehicleInfoRun, stVehicleInfoProcess));
	thread ThreadVehPlanning(bind(&CVehPlanning::PlanningThreadRun, pVehiclePlanning));
	//w.showMaximized();
	w.show();
	a.exec();
	stPerceptionLines.SetThreadState(false);
	ThreadPerceptionLines.join();
	stRTKInfoProcess.SetThreadState(false);
	ThreadRTKInfo.join();
	stVehicleInfoProcess.SetThreadState(false);
	ThreadVehiceleInfo.join();
	pVehiclePlanning->SetThreadState(false);
	//ThreadVehPlanning.join();
	//stThreadGroup.join_all();
	return 0;
}
