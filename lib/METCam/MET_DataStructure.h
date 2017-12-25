/************************************************************************/
/*
Date:			2015/12/21
Author:			Chunlan Ye
Compile Mode:	C
Function:		basic data structure define
*/
/************************************************************************/

#ifndef MET_DATASTRUCTURE_H
#define MET_DATASTRUCTURE_H
#include "MET_Macro.h"
#include "MET_MsgDataStructure.h"

#define MET_ADAS_FCW_OUTPUT_OBJNUM	32
#define MET_ADAS_FCW2ADB_OBJNUM		15
#define MET_ADAS_FCW2LDW_OBJNUM		32
#define MET_POLYGON_POINTNUM		256
#define MET_MAX_POINTNUM			100
#define MET_MAX_LANELINENUM			10

/************************************************************************/
/* Basic image process structure define                                 */
/************************************************************************/
typedef struct METSize
{
	short	w;
	short	h;
}METSize;

typedef struct METPoint		/*unit: pixel*/
{
	short	x;				/*horizontal coordinate*/
	short	y;				/*vertical coordinate*/
}METPoint;

typedef struct METPoint3D		/*unit: km,m,cm etc */
{
	short	x;
	short	y;
	short   z;
}METPoint3D;

typedef struct METPoint2D32f
{
	float x;
	float y;
}METPoint2D32f;

typedef struct METPoint3D32f
{
	float x;
	float y;
	float z;
}METPoint3D32f;

typedef struct METRect		/*unit: pixel*/
{
	short	x;				/*horizontal coordinate*/
	short	y;				/*vertical coordinate*/
	short	width;			/*width*/
	short	height;			/*height*/
}METRect;

typedef struct METRect32f		/*unit: pixel*/
{
	float	x;				/*horizontal coordinate*/
	float	y;				/*vertical coordinate*/
	float	width;			/*width*/
	float	height;			/*height*/
}METRect32f;

typedef struct METLineModel		/*Line Equation: y = K * x + B*/
{
	float	rateK;
	float	coefB;
}METLineModel;

typedef struct METLineModel2 /*Line Equation: Ax + By + C = 0*/
{
	float	coefA;
	float	coefB;
	float	coefC;
}METLineModel2;

/********** Connected Region ********/
typedef struct METConnectedRgion
{
	int centx;					/*pixel center point coordinate*/
	int centy;

	METPoint minPt;				/*top left point on the rectangle*/
	METPoint maxPt;				/*lower right point on the rectangle*/

	METPoint boundaryPts[4];	/*up-right-bottom-left*/

	unsigned int regionArea;	/*the amount of pixels in the connected region*/
	unsigned int rectArea;		/*rect area*/

	unsigned short tag;			/*connected region tag on tagMask*/
}METConnectedRgion;

typedef struct METCRLineTag
{
	short		startPos;
	short		endPos;
	short		yPos;
	short		len;
	short		tag;
}METCRLineTag;

typedef struct METCRLineRecord
{
	short		startID;
	short		endID;
	short		len;
}METCRLineRecord;

typedef struct METCRegionObj
{
	/***** Rst ******/
	int						regionNum;
	METConnectedRgion		*regionBuf;		/*regionBufLen*/

	/***** process Rst******/
	unsigned short			*tagMask;			/*imgW * imgH*/

	short					lineCnt;
	METCRLineTag			*lineBuf;			/*lineBufLen*/
	METCRLineRecord			*lineRecord;		/*imgH*/

	/**** Ctrl Info ****/
	int						regionBufLen;		/*<*/
	int						lineBufLen;			/*<*/
	unsigned char			valTh;				/*>=*/
}METCRegionObj;

/************************************************************************/
/*  Time structure define                                               */
/************************************************************************/
typedef struct METTime
{
	unsigned short wYear;
	unsigned short wMonth;
	unsigned short wDay;
	unsigned short wHour;
	unsigned short wMinute;
	unsigned short wSecond;
	unsigned short wMilliseconds;
}METTime;

/************************************************************************/
/* Vehicle Info define                                                  */
/************************************************************************/

//gearInfo
typedef enum METGearInfo
{
	MET_GEAR_UNKNOWN = -3,
	MET_GEAR_STOP,
	MET_GEAR_BACKUP,
	MET_GEAR_NEUTRAL,
	MET_GEAR_ADVANCE,
	MET_GEAR_LEVEL1,
	MET_GEAR_LEVEL2,
	MET_GEAR_LEVEL3,
	MET_GEAR_LEVEL4,
	MET_GEAR_LEVEL5,
	MET_GEAR_LEVEL6,
	MET_GEAR_LEVEL7,
	MET_GEAR_LEVEL8,
	MET_GEAR_LEVEL9,
	MET_GEAR_LEVEL10
}METGearInfo;


typedef struct METLowPassFilter //IIR
{
	char		initFlag;
	int			dim;
	float		*NL;
	float		*DL;
	int			cnt;
	float		*src;
	float		*des;
	float		inputData;
}METLowPassFilter;


typedef struct METVehicleGPSInfo
{
	int		longitude;
	int		latitude;
	float	height;
}METVehicleGPSInfo;


//vehicle information
typedef struct METVehicleInfo
{
	float			vehicle_speed;					/*speed: 0~500km/h, accuracy: 0.1km/h*/
	float			steering_wheel_angle;			/*steering wheel angle: -1000~1000 degree, accuracy: 0.1 degree*/

	float			accelerator_pedal_pos;			/*accelerator pedal position: 0~100%, accuracy: 0.1%*/
	short			accelerator_pedal_speed;		/*val:-5120~5080, unit:%/s*/
	float			brake_pedal_pos;				/*brake pedal position: 0~100%, accuracy: 0.1%*/

	float			vehicle_yaw_angle;				/*vehicle yaw angle: 0~360 degree, accuracy: 0.1 degree*/
	float			vehicle_yaw_rate;				/*vehicle yaw rate: -255~255 degree/s, accuracy: 0.1 degree/s*/

	float			vehicle_pitch_angle;			/*vehicle pitch angle: -45~45 degree, accuracy: 0.01 degree*/
	float			vehicle_pitch_rate;				/*vehicle pitch rate: -3000~3000 degree/s, accuracy: 0.1 degree/s*/

	unsigned char	Lft_turnlight_active;			/*left turn light active tag, 1-yes, 0-no*/
	unsigned char	Rght_turnlight_active;			/*right turn light active tag, 1-yes, 0-no*/

	unsigned char	windWiperStatus;				/*val:0-10, speed level*/

	short			light_sensor_val;				/*light sensor value*/
	unsigned char	rain_sensor_val;				/*rain sensor value*/

	unsigned char	lowBeamStatus;					/*0-closed, 1-open*/
	unsigned char	highBeamStatus;					/*0-closed, 1-open*/

	unsigned char	envirLightStatus;				/*0-unknown, 1- night, 2-day*/
	
	short			brakePedalGrd;					/*val:-5120~5080, unit:%/s*/
	unsigned char	brakePedalFlag;					/*val 0:no brake 1:brake */
	
	float			temperatureValue;				/*val:-40~87.5, unit: degree Celsius, accuracy: 0.5*/
	short			steeringWheelSpeed;				/*val:-2048~2057, unit:degree/s, accuracy: 1*/

	METGearInfo		gearInfo;						/*-3:unknown, -2:stop, -1:backup,0:neutral,1:advance,2:level1,
													3:level2, 4:level3, 5:level4, 6:level5, 7:level6, 8:level7, 9:level8,
													10:level9, 11:level10*/
	unsigned char	estimated_gear;
	int				mileage;						/*0~1000000, unit:km*/
	
	float			vehicle_roll_angle;				/*vehicle roll angle: -45~45 degree, accuracy: 0.01 degree*/
	float			vehicel_roll_rate;				/*vehicle roll rate: -3000~3000 degree/s, accuracy: 0.1 degree/s*/

	METVehicleGPSInfo	gpsInfo;
	/************************************************************************/
	/* ACC AEB LKA Related                                                  */
	/************************************************************************/
	/// AEB //////////////////////////////////////////////////////////////////
	unsigned char   aeb_brake_failed;
	short			engine_min_torque_value;
	short			engine_max_torque_value;
	short			engine_cur_torque_value;
	/// ACC //////////////////////////////////////////////////////////////////
	unsigned char	acc_brake_failed;
	unsigned char	cruise_control_enable;
	unsigned char	cruise_gap_switch_activation;
	unsigned char	cruise_secondary_switch_status;
	unsigned char	cruise_speed_limit_switch_status;
	/// LKA //////////////////////////////////////////////////////////////////
	unsigned char	lka_overlay_torque_status;
	float			lka_steering_total_torque;
	unsigned char	lka_handoff_steering_wheel_mode;
	unsigned char	lka_handoff_steering_wheel_stat;
	float			lka_steering_delta_torque;
	float			lka_driver_applied_torque;
	/************************************************************************/
	/* Special Car:Vehicle Inertia Dynamic Parameters                       */
	/************************************************************************/
	float			lateral_acceleration_primary;
	float			lateral_acceleration_secondary;
	float			longitudinal_acceleration_primary;
	float			filter_longitudinal_acceleration_primary;
	float			longitudinal_acceleration_secondary;
	float			filter_yawrate_primary;
	float			yawrate_primary;
	float			yawrate_secondary;
	float			wheel_brake_pressure_estimated;
	float			braking_actual_deceleration;
	float			braking_target_deceleration;
	unsigned char	gateway_button;
	unsigned char	wheel_status_feback_zcsd;
}METVehicleInfo;


/************************************************************************/
/* Camera parameter define                                              */
/************************************************************************/
//Melexis registers
typedef struct METMLXRegister
{
	int		Tint;						/*total exposure time: row register value*/
	short	vblank;
	int		BarrierHeight[6];			/*barrier height*/
	int		Indown_rtdata_start[6];		/*row register value*/
	int		En_vb_start[6];				/*col register value*/
}METMLXRegister;

typedef struct METOV490Register
{
	unsigned char		validFlag;
	unsigned short		FrameNo;
	float				Temperature;
	unsigned short		FirmwareVersion;	//firmware version
	unsigned short		ExpVal[3];			//0-L, 1-S, 2-VS
	unsigned short		RealGain[3];
	unsigned short		DigitalGain[3];
	unsigned short		TargetBLC[3];

	unsigned short		LMeanY;
	unsigned short		SMeanY;
	unsigned short		MeanYUV[4][3]; //ROI:0~3; [][0]-mY, [][1]-mU, [][2]-mV
	unsigned int		HistBin[4][16];
}METOV490Register;

typedef struct METMLXCurveSeg
{
	int		pixelValue;
	float	slope;
}METMLXCurveSeg;

typedef union METCameraInfo
{
	METMLXRegister		melexis;
	METOV490Register	ov490Reg;
}METCameraInfo;

/************************************************************************/
/* Radar Object define                                                  */
/************************************************************************/
typedef struct METRadarElement
{
	unsigned char	trackMEDRangeMode;		//val: 0~3, 2 bit, factor:1
	unsigned char	trackBridgeObject;		//val: 0~0, 1 bit, factor:1
	float			trackLATRate;			//val:-8~7.75, 6 bit, factor:0.25
	unsigned char	trackRollingCount;		//val:0~1, 1 bit, factor:1
	unsigned char	trackStatus;			//val: 0~7, 3 bit, factor:1
	float			trackWidth;				//val:0~7.5, 4 bit, factor: 0.5, unit: m
	unsigned char	trackOnComing;			//val:0~0, 1 bit, factor: 1
	float			trackRange;				//val:0~204.7, 11 bit, float: 0.1, unit: m
	float			trackRangeRate;			//val:-81.92~81.91, 14 bit, factor: 0.01, unit: m/s
	float			trackRangeAccel;		//val:-25.6~25.55, 10 bit, factor: 0.05, unit:m/s/s
	float			trackAngle;				//val:-51.2~51.1, 10 bit, factor: 0.1; unit: degree
	unsigned char	trackGroupingChanged;	//val:0~0, 1 bit, factor: 1
}METRadarElement;

typedef struct METRadarObject
{
	unsigned char		objCount;
	unsigned char		ACC_Traget_ID;
	unsigned char		ACC_Stat_ID;
	unsigned char		CMBB_Move_ID;
	unsigned char		CMBB_Stat_ID;
	unsigned char		FCW_Move_ID;
	unsigned char		FCW_Stat_ID;
	char				radar_fcw_warn;		//only for benchmark, not write to image frame header
	METRadarElement		objList[64];
}METRadarObject;

/************************************************************************/
/* LightSensor                                                           */
/************************************************************************/
typedef struct METLightSensorObject
{
	unsigned char		envLightMode;		//environment luminance level
	
	unsigned char		roadType;
	unsigned char		fogLevel;

	unsigned char		camExposureMode;
	unsigned char		ihcMode;
	unsigned char		adbMode;
	unsigned char		fcwMode;
}METLightSensorObject;

/************************************************************************/
/* FrameHeader define                                                   */
/************************************************************************/

//image date captured before 2015-12-21, saveVideo size is 1024*515
typedef struct METFrameAttribute_melexis
{
	unsigned short	width;		/*unit: pixel*/
								/*imgData width*/
	unsigned short	height;		/*unit: pixel*/
								/*imgData height*/
	unsigned char	cameraType;	/*camera type, modify as frame header versionID*/

	METTime			time;		/*local time*/	

	/************************************************************************/
	/* Camera Special Parameter                                             */
	/************************************************************************/
	METMLXRegister	melexisRegister;

	/************************************************************************/
	/* Rect Objects: used for algorithm analysis                            */
	/* Note: cannot modify the data type									*/
	/************************************************************************/
	unsigned short	rectNum;								/*rect amount*/
	METRect	rects[MET_FRAMERECTS_NUM_MAX];			
	unsigned char rectType[MET_FRAMERECTS_NUM_MAX];	/*record rect attribute*/
}METFrameAttribute_melexis;



/************************************************************************/
/* Diagnose                                                             */
/************************************************************************/
typedef struct MET_Diagnose
{
	unsigned char cameraErr;
	unsigned char CAN0_err;
	unsigned char CAN1_err;
	unsigned char CAN2_err;
	unsigned char CAN3_err;
}MET_Diagnose;


/************************************************************************/
/* ImageSets                                                            */
/************************************************************************/
typedef struct MET_ImgSets
{
	unsigned char*	curr_imgsets[MET_IMG_PYRAMID_LEVEL_MAX_NUM];
	unsigned char*	pre1_imgsets[MET_IMG_PYRAMID_LEVEL_MAX_NUM];
	unsigned char*	pre2_imgsets[MET_IMG_PYRAMID_LEVEL_MAX_NUM];
	METSize			imgsizes[MET_IMG_PYRAMID_LEVEL_MAX_NUM];
	float			imgscalew[MET_IMG_PYRAMID_LEVEL_MAX_NUM];
	float			imgscaleh[MET_IMG_PYRAMID_LEVEL_MAX_NUM];
	int				levelnum;
}MET_ImgSets;

typedef struct MET_CamExtParams
{
	float position_x;				// meter, SAE positive in driving direction; range -5m to 0m; min resolution 0,1 m
	float position_y;				// meter, SAE positive to the right; range -2m to 2m; min resolution 0,1 m *1
	float position_z;				// meter, SAE positive downwards; range 0m to 5m; min resolution 0,1 m
	float yaw;						// radian, SAE positive upward; range ?/18*pi (?0?; min resolution 1/1800*pi (0.1?
	float roll;						// radian, SAE positive clockwise in driving direction; range ?/18*pi (?0?; min resolution 1/1800*pi (0.1? *1
	float pitch;					// radian, SAE positive to the right; range ?/18*pi (?0?; min resolution 1/1800*pi (0.1? *1
	short offsetY;					//unit:pixel, used for DeSay HD (default: 180), for others, setting as 0
}MET_CamExtParams;

typedef struct MET_CamIntParams
{
	float focal_length;				// meter; range +0.001 to 0.025m; min resolution 0.0001m
	short width;					// pixel, width of the image in pixel; range 0 to 1920; resolution 1
	short height;					// pixel, height of the image in pixel; range 0 to 1200; resolution 1
	float pixel_pitch_x;			// meter, width of a pixel; range 0 to 0.00001m (0 to 10祄); min resolution 0.0000001m (0.1祄)
	float pixel_pitch_y;			// meter, height of a pixel; range 0 to 0.00001m (0 to 10祄); min resolution 0.0000001m (0.1祄)
	float principal_point_x;		// pixel, position of principle point in x image direction; range 0 to 1920; resolution 1 *1
	float principal_point_y;		// pixel, position of principle point in y image direction; range 0 to 1200; resolution 1
	float radial_distortion[3];		// no unit, define the first and second coefficient of the radial lens distortion
	float tangential_distortion_1;	// according to Camera Calibration Toolbox for Matlab (kc(1) and kc(2), http://www.vision.caltech.edu/bouguetj)
	float tangential_distortion_2;	// corresponds to kc(5)
	char  RedPixelRow;
	char  RedPixelCol;
}MET_CamIntParams;

typedef struct MET_CamProjTable
{
	float dXdcol[MET_RAW_IMG_HEIGHT];
	float dYdcol[MET_RAW_IMG_HEIGHT];
	float dcoldY[MET_RAW_IMG_HEIGHT];
}MET_CamProjTable;

typedef struct MET_CamParams
{
	char initFlag;
	MET_CamExtParams	camExt;
	MET_CamIntParams	camInt;
	//////////////////////////////////////////////////////////////////////////
	float Cint[16];
	float CintInv[16];
	float Rrot[16];
	float RrotInv[16];
	float Ttrs[16];
	float TtrsInv[16];
	float K[16];
	float Kinv[16];
	float H[9];
	float Hinv[9];
	//////////////////////////////////////////////////////////////////////////
	MET_CamProjTable	pTable;
	float				distortionTable[MET_MAX_RADIUS_LENGTH];
}MET_CamParams;


//////////////////////////////////////////////////////////////////////////
typedef struct MET_VideoFileHeader
{
	unsigned short		imgWidth;
	unsigned short		imgHeight;
	unsigned char		frameRate;
	unsigned char		calFlag;
	unsigned char		extCalFlag;
	unsigned char		intCalFlag;
	char		videoformat[16];
	char		vehiclename[16];
	MET_CamExtParams	camExt;
	MET_CamIntParams	camInt;
	unsigned short		headerSize;
	unsigned int		frameNum;
	unsigned char		writeFlag;
}MET_VideoFileHeader;

typedef struct MET_LidarParams	//unit:cm
{
	float		w2lRotateMat[9];
	float		w2lTransMat[3];

	float		l2wRotateMat[9];	
	float		l2wTransMat[3];
}MET_LidarParams;
/************************************************************************/
/* BeamCalibParam                                                       */
/************************************************************************/
typedef struct METBeamCalibParam	/*manual rectify for Beam instllation*/
{
	int				xZeroPos;			//not load by ADASParam, update by met_beam_algo.lib
	float			rectifyLFAngleLft;	//unit: degree
	float			rectifyLFAngleRght;

	float			rectifyUDHeightLft;	
	float			rectifyUDHeightRght;
}METBeamCalibParam;

/////////////////////////////////////////////////////////////////////
/** FCW Result used in ADBLib **/
typedef struct METADBFCWInfo
{
	int				objNum;
	unsigned char	carStu[MET_ADAS_FCW2ADB_OBJNUM];
	METRect			carRect[MET_ADAS_FCW2ADB_OBJNUM];
}METADBFCWInfo;

typedef struct METLDWFCWInfo
{
	METRect				carRect[MET_ADAS_FCW2LDW_OBJNUM];
	float				objConfidence[MET_ADAS_FCW2LDW_OBJNUM];
	int					objNum;
}METLDWFCWInfo;

//add Radar to FCW
typedef struct METBMRadarElement
{
	unsigned char		status;		//0-no obj, 1-updated obj(trackCnt>=3), 2-missObj(minssCnt<=2)
	float				velocity;	//parallel vehicle, unit: m/s
	float				TTC;		//unit: s;
	float				wx;			//under vehicle coordinate system
	float				wy;
	short				ux;			//under image coordinate system
	short				uy;
	short				uw;

	float				vx;			//unit: m/s
	float				vy;			//unit: m/s
	float				ax;			//unit: m/s^2
	float				ay;			//unit: m/s^2
}METBMRadarElement;

typedef struct METBMFCWRadarInfo
{
	METBMRadarElement	objInfo[MET_ADAS_FCW_OUTPUT_OBJNUM];	//radar obj info
	unsigned char		matchId[MET_ADAS_FCW_OUTPUT_OBJNUM];	//0-no matchItem
	int					matchCnt[MET_ADAS_FCW_OUTPUT_OBJNUM];	//age for the same matched item
	float				scale[MET_ADAS_FCW_OUTPUT_OBJNUM];		//scale on same matched item
	float				dwx[MET_ADAS_FCW_OUTPUT_OBJNUM];
}METBMFCWRadarInfo;

/***************** ADAS Define *******************/
typedef struct METFCWInputInfo
{
	METBMFCWRadarInfo		*radarInfo;
	METVehicleInfo			*vehicleInfo;		//vehicle info, if no, set zero
	unsigned char			fcwMode;
}METFCWInputInfo;

typedef struct METLDWInputInfo
{
	METVehicleInfo			*vehicleInfo;		//vehicle info, if no, set zero
	MET_CamParams			*camParam;
	METLDWFCWInfo			*ldwfcwInfo;

	int						backLaneDist;		//unit:m
	unsigned char			senLevel;			//0-L1靠近，1-L1压线，2-L3越线
}METLDWInputInfo;

typedef struct METBCInputInfo	/*Beam Control - ADB, AHS*/
{
	unsigned char			beamMode;			/* 0- close all, 1-low beam, 2-adptive beam*/
	METVehicleInfo			*vehicleInfo;		//vehicle info, if no, set zero
	METADBFCWInfo			*fcwInfo;
	unsigned char			*hsvData;

	unsigned char			senLevel;
}METBCInputInfo;

typedef struct METLSInputInfo
{
	int						vblanks;			//MLXCamera, PC(128), DSP(129)
	METMLXRegister			*registerData;
	unsigned char			isManualExposure;
	METVehicleInfo			*vehicleInfo;

	METOV490Register		*regDataOV490;
}METLSInputInfo;

typedef struct METLidarInputInfo
{
	METVehicleInfo			*vehicleInfo;
}METLidarInputInfo;
/************************************************************************/
/* ADAS Config                                                          */
/************************************************************************/
//////////////////////////////////////////////////////////////////////////
typedef struct METLDWConfig
{
	float		carFWheel2VehHead;		//meter
	float		carWidth;
	float		carAxis;
	float		steerRatio;
	short		imgWidth;
	short		imgHeight;
	float		camFrameRate;
	float		std_lane_width;			// 3.80f meter
	float		min_lane_width;			// 2.50f meter
	float		max_lane_width;			// 5.50f meter
	float		min_mark_width;			// 0.08f meter
	float		std_mark_width;			// 0.20f meter
	float		max_mark_width;			// 0.60f meter
	float		min_zebra_width;		// 0.25f meter
	float		max_zebra_width;		// 0.50f meter
	float		real_max_mark_width;	// 0.50f meter
	float		real_min_mark_width;	// 0.08f meter
	float		min_detect_dist;		// 30.0f meter
	float		max_detect_dist;		// 60.0f meter
	float		mark_x_step;			// 0.25f meter
	float		min_radius;				// 100.0f meters
	float		max_radius;				// 2000.0f meters
	float		workSpeedThred;			// km/h
	float		quitSpeedThred;			// km/h
	unsigned char  sidelaneActive;		// 0/1
	unsigned char  zebraActive;			// 0/1
	unsigned char  yawratesensorvalid;	// 0:vehicle don't have yawrate signal 1:vehicle have yawrate signal
	unsigned char  ldwonly;				// 0:lane and other function. 1:lane function only
	unsigned char  usingsimyawrateflag; // 0:not using lane detection simulated yawrate 1.using lane detection simulated yawrate
	/// warning config ///////////////////////////////////////////////////////////////////////
	float					backLaneDist;		//unit:m
	unsigned char			senLevel;			//0-L1靠近，1-L1压线，2-L3越线
}METLDWConfig;

typedef struct METLSConfig
{
	float				camFrameRate;
	unsigned char		BeamFunc;
	char				lsClassifyPath[512];
	int					imgWidth;
	int					imgHeight;
}METLSConfig;

typedef struct METFCWConfig
{
	float		camFrameRate;
	float		camHFov;
	short		imgWidth;
	short		imgHeight;

	float		vehWidth;		//unit: m

	float		thwNearTimeTh;
	float		thwNearGapTRTh;
	float		thwMidTimeTh;
	float		thwMidGapTRTh;

	float		stopAwayScaleTh;
	float		stopAwayMovingDistTh;

	float		stopCloseScaleTh;
	float		stopCloseDistPercent;
	float		stopCloseMovingDistTh;

	float		ttc1TTCMin;
	float		ttc1TTCMax;
	float		ttc2SafeTime;
	float		ttc2MaxScale;
	float		ttc2MaxDistPercent;
}METFCWConfig;

typedef struct METCamConfig
{
	int			imgWidth;		//imgSize for Algo
	int			imgHeight;
	float		flength;
	float		pixel_pitch_x;
	float		pixel_pitch_y;
	float		princ_x;
	float		princ_y;
	float		k0;
	float		k1;
	float		k2;
	float		tangential_distortion_1;
	float		tangential_distortion_2;
	float		cam_pos_x;		/*unit: m*/
	float		cam_pos_y;
	float		cam_pos_z;
	float		roll;			/*unit: radian, save as degree*/
	float		yaw;
	float		pitch;

	int			imgHD_offsetY;	/*unit: pixel*/
}METCamConfig;

typedef struct METCamCalibConfig
{
	int			imgWidth;		//imgSize for Camera Calibration
	int			imgHeight;

	int			objImgHeight;	//HD:720, SD:512

	float		flength;		//camera inner parameters
	float		pixel_pitch_x;
	float		pixel_pitch_y;
	float		princ_x;
	float		princ_y;
	float		k0;
	float		k1;
	float		k2;
	float		tangential_distortion_1;
	float		tangential_distortion_2;

	short		cam_install_pos_x;		//unit: mm - 1mm
	short		cam_install_pos_y;
	short		cam_install_pos_height;
	float		cam_install_pos_pitch;	//unit: degree - 0.125degree
	float		cam_install_pos_yaw;
	float		cam_install_pos_roll;

	short		plate_pos_x;		//unit: mm - 1mm
	short		plate_pos_y;
	short		plate_pos_height;
	short		plate_side;
	//////////////////////////////////////////////////////////////////////////
	short		front_plate_lftpts_pos_x;	//unit: mm - 1mm
	short		front_plate_lftpts_pos_y;	//unit: mm - 1mm
	short		front_plate_lftpts_pos_z;	//unit: mm - 1mm
	short		front_plate_rgtpts_pos_x;	//unit: mm - 1mm
	short		front_plate_rgtpts_pos_y;	//unit: mm - 1mm
	short		front_plate_rgtpts_pos_z;	//unit: mm - 1mm
	short		back_plate_lftpts_pos_x;	//unit: mm - 1mm
	short		back_plate_lftpts_pos_y;	//unit: mm - 1mm
	short		back_plate_lftpts_pos_z;	//unit: mm - 1mm
	short		back_plate_rgtpts_pos_x;	//unit: mm - 1mm
	short		back_plate_rgtpts_pos_y;	//unit: mm - 1mm
	short		back_plate_rgtpts_pos_z;	//unit: mm - 1mm
	//////////////////////////////////////////////////////////////////////////
	char		calibrationMode;	// 0: one plate mode   1:two plate mode

}METCamCalibConfig;

typedef struct METLidarConfig
{
	unsigned char	versionID;
	char			ipAdr[20];
	unsigned int	port;
	float			lidarFrameRate;		/*unit: frames/s */

	float		lidar_pos_x;		/*unit: m*/
	float		lidar_pos_y;
	float		lidar_pos_z;
	float		lidar_roll;			/*unit: radian, save as degree*/
	float		lidar_yaw;
	float		lidar_pitch;

	float		vehWidth;			/*unit: m*/
	float		vehLength;
}METLidarConfig;

typedef struct METBeamConfig
{
	float					camFrameRate;
	float					camHFov;
	float					camPosZ;

	short					imgWidth;
	short					imgHeight;

	unsigned char			beamFeature;
	unsigned char			sensitivityLevel;

	float					beamHeightMin;	//unit: m
	float					beamHeightMax;	//unit: m
	float					roadFactor;		//for road model
	float					roadSlope;		//unit: degree, slope on distance of 100m
	float					beamCalibDistMin;	//unit: m
	float					beamCalibDistMax;	//unit: m
	int						beamDetectLaneNum;

	float					workVelocity;
	float					quitVelocity;

	METBeamCalibParam		beamCalibParam;
	float					calibErrAngle;	  //unit: degree = camera + beam
}METBeamConfig;

//////////////////////////////////////////////////////////////////////////
typedef struct METLidarFrameHeader
{
	unsigned char			LidarType;		

	//Lidar Attribute
	unsigned short			layerNum;
	int						layerPtsNum;	/*the number of sampling points for one layer*/
	float					*layerAngle;	/*Vertical angle for each layer*/
	float					hFovAngle;		/*unit: degree,  Horizontal FOV*/
	float					initAngle;		/*unit: degree*/

	//Lidar Config Attribute
	float					frameRate;		/*unit: frames/s */

	//install position
	float					pitch;		/*unit: degree*/
	float					yaw;
	float					roll;
	float					wPosx;		/*unit: m*/
	float					wPosy;
	float					wPosz;
}METLidarFrameHeader;

typedef struct METLidarFrame_M8Quanergy
{
	METLidarFrameHeader		basicInfo;

	METTime					captureTime;
	unsigned char			*validFlag;							/* 0- inValid, 1-valid*/
	unsigned short			*distance[8];	/*unit: cm*/
	unsigned char			*intensity[8];
}METLidarFrame_M8Quanergy;

typedef enum METACCCtrlMode
{
	MET_CTRL_NONE_CTRL,
	MET_CTRL_GOSTATE_CTRL,
	MET_CTRL_STOP_CTRL,
	MET_CTRL_BRAKE_CTRL,
	MET_CTRL_SPEED_CTRL
}METACCCtrlMode;

//////////////////////////////////////////////////////////////////////////
typedef struct METControlData
{
	//////////////////////////////////////////////////////////////////////////
	unsigned char	lka_on;
	unsigned char	aeb_on;
	unsigned char	acc_on;
	unsigned char	apa_on;
	/// LKA ///////////////////////////////////////////////////////////////////////
	unsigned char	lka_activeFlag;
	float			lka_currSteeringAngle;
	float			lka_targetWheelAngle;
	float			lka_targetSteeringAngle;
	float			lka_torqueChangeSpeed;
	float			lka_baseTorque;				// steering model
	float			lka_torquePID_P;
	float			lka_torquePID_I;
	float			lka_torquePID_D;
	/// APA //////////////////////////////////////////////////////////////////////
	float			apa_AngleChangeSpeed;
	float			apa_tgtangle;
	unsigned char	apa_activeFlag;
	/// ACC ///////////////////////////////////////////////////////////////////////
	METACCCtrlMode	accCtrlMode;
	unsigned char	accCIPVValid;
	unsigned char	accCIPVLevel;
	unsigned char	accBrakeType;
	float			accSetSpeed;
	float			accSetAccel;
	float			accSpeed;
	unsigned char	accFollowMode;
	/// ACC DEBUG /////////////////////////////////////////////////////////////////
	float			realbrakeaccleration;
	float			realenginevalue;
	/// AEB ///////////////////////////////////////////////////////////////////////
	unsigned char	aebReq;
	unsigned char	aebBrkTyp;
	short			aebBrkAccel;
}METControlData;

/*
	Vision only Sign Typez
	Type: Enum
	Note: The values in the “Meaning” are the Traffic Sign (speed sign) Numerical
	Values. There is no reference to Speed Format (km/h or mph).
*/

typedef enum METMEDataC2270VOST
{
	MET_C2270VOST_00=0,//standard regular 10
	MET_C2270VOST_01=1, //standard regular 20
	MET_C2270VOST_02=2, //standard regular 30
	MET_C2270VOST_03=3, //standard regular 40
	MET_C2270VOST_04=4, //standard regular 50
	MET_C2270VOST_05=5, //standard regular 60
	MET_C2270VOST_06=6, //standard regular 70
	MET_C2270VOST_07=7, //standard regular 80
	MET_C2270VOST_08=8, //standard regular 90
	MET_C2270VOST_09=9, //standard regular 100
	MET_C2270VOST_10=10, //standard regular 110
	MET_C2270VOST_11=11, //standard regular 120
	MET_C2270VOST_12=12, //standard regular 130
	MET_C2270VOST_13=13, //standard regular 140
	MET_C2270VOST_20=20, //Standard regular end restriction of number e.g 60 end of restriction.
	MET_C2270VOST_28=28, //standard electronic 10
	MET_C2270VOST_29=29, //standard electronic 20
	MET_C2270VOST_30=30, //standard electronic 30
	MET_C2270VOST_31=31, //standard electronic 40
	MET_C2270VOST_32=32, //standard electronic 50
	MET_C2270VOST_33=33, //standard electronic 60
	MET_C2270VOST_34=34, //standard electronic 70
	MET_C2270VOST_35=35, //standard electronic 80
	MET_C2270VOST_36=36, //standard electronic 90
	MET_C2270VOST_37=37, //standard electronic 100
	MET_C2270VOST_38=38, //standard electronic 110Page 20 of 36
	MET_C2270VOST_39=39, //standard electronic 120
	MET_C2270VOST_40=40, //standard electronic 130
	MET_C2270VOST_41=41, //standard electronic 140
	MET_C2270VOST_50=50, //standard electronic end restriction of number e.g 60 end of restriction.
	MET_C2270VOST_64=64, //standard regular general end all restriction.
	MET_C2270VOST_65=65, //standard electronic general end all restriction.
	MET_C2270VOST_100=100, //standard regular 5
	MET_C2270VOST_101=101, //standard regular 15
	MET_C2270VOST_102=102, //standard regular 25
	MET_C2270VOST_103=103, //standard regular 35
	MET_C2270VOST_104=104, //standard regular 45
	MET_C2270VOST_105=105, //standard regular 55
	MET_C2270VOST_106=106, //standard regular 65
	MET_C2270VOST_107=107, //standard regular 75
	MET_C2270VOST_108=108, //standard regular 85
	MET_C2270VOST_109=109, //standard regular 95
	MET_C2270VOST_110=110, //standard regular 105
	MET_C2270VOST_111=111, //standard regular 115
	MET_C2270VOST_112=112, //standard regular 125
	MET_C2270VOST_113=113, //standard regular 135
	MET_C2270VOST_114=114, //standard regular 145
	MET_C2270VOST_115=115, //standard electronic 5
	MET_C2270VOST_116=116, //standard electronic 15
	MET_C2270VOST_117=117, //standard electronic 25
	MET_C2270VOST_118=118, //standard electronic 35
	MET_C2270VOST_119=119, //standard electronic 45
	MET_C2270VOST_120=120, //standard electronic 55
	MET_C2270VOST_121=121, //standard electronic 65
	MET_C2270VOST_122=122, //standard electronic 75
	MET_C2270VOST_123=123, //standard electronic 85
	MET_C2270VOST_124=124, //standard electronic 95
	MET_C2270VOST_125=125, //standard electronic 105
	MET_C2270VOST_126=126, //standard electronic 115
	MET_C2270VOST_127=127, //standard electronic 125
	MET_C2270VOST_128=128, //standard electronic 135
	MET_C2270VOST_129=129, //standard electronic 145
	MET_C2270VOST_171=171, //standard regular motorWay begin
	MET_C2270VOST_172=172, //standard regular end of MotorWay
	MET_C2270VOST_173=173, //standard regular expressWay begin
	MET_C2270VOST_174=174, //standard regular end of ExpressWay
	MET_C2270VOST_175=175, //standard regular Playground area begin
	MET_C2270VOST_176=176, //standard regular End of playground area
	MET_C2270VOST_200=200, //standard regular no passing start
	MET_C2270VOST_201=201, //standard regular end of no passing
	MET_C2270VOST_220=220, //standard electronic no passing start
	MET_C2270VOST_221=221, //standard electronic end of no passing
	MET_C2270VOST_254=254, //No sign detected
	MET_C2270VOST_255=255  //e_invalid_sigPage 20 of 36

}METMEDataC2270VOST;

/* 
	Vision only Supplementary Sign Type
*/
typedef enum METMEDataC2270VOSST
{
	MET_C2270VOSST_01=1,//Rain
	MET_C2270VOSST_02=2,//Snow
	MET_C2270VOSST_03=3,//Trailer
	MET_C2270VOSST_04=4,//Time
	MET_C2270VOSST_05=5,//Arrow left
	MET_C2270VOSST_06=6,//Arrow right
	MET_C2270VOSST_07=7,//Bend arrow left
	MET_C2270VOSST_08=8,//Bend arrow right
	MET_C2270VOSST_09=9,//Truck
	MET_C2270VOSST_10=10,//Distance arrow
	MET_C2270VOSST_11=11,//Weight
	MET_C2270VOSST_12=12,//Distance inPage 22 of 36
	MET_C2270VOSST_13=13,//Tractor
	MET_C2270VOSST_14=14,//Snow rain
	MET_C2270VOSST_15=15,//School
	MET_C2270VOSST_16=16,//Rain cloud
	MET_C2270VOSST_17=17,//Fog
	MET_C2270VOSST_18=18,//Hazardous material
	MET_C2270VOSST_19=19,//Night
	MET_C2270VOSST_255=255//Not in us

}METMEDataC2270VOSST;

/*
	Type: Enum
	Meaning: The reason for filtering the sign. External filter, filtering visible signs to due	irrelevance.
*/
typedef enum METMEDataC2270FilterType
{
	MET_C2270FT1 =1 ,//Irrelevant to the host
	MET_C2270FT2 = 2,//TS on vehicle (truck or bus …)
	MET_C2270FT3 = 3//Embedded
}METMEDataC2270FilterType;

/*
	Vision only Sign Type – Display 1 - 4
	Type: Enum
	Range: 0-255
	Invalid value = 0xFF = 255 – No speed limit sign was detected.
	Note: The values are the Traffic Sign (speed sign) Numerical Values. There
	is no reference to Speed Format (kmh or mph).
*/
typedef enum METMEDataC2270VOSTD
{
	MET_C2270VOSTD_000=0, //standard regular 10
	MET_C2270VOSTD_001=1, //standard regular 20
	MET_C2270VOSTD_002=2, // standard regular 30
	MET_C2270VOSTD_003=3, // standard regular 40
	MET_C2270VOSTD_004=4, // standard regular 50
	MET_C2270VOSTD_005=5, // standard regular 60
	MET_C2270VOSTD_006=6, // standard regular 70
	MET_C2270VOSTD_007=7, // standard regular 80
	MET_C2270VOSTD_008=8, // standard regular 90
	MET_C2270VOSTD_009=9, // standard regular 100
	MET_C2270VOSTD_010=10, // standard regular 110
	MET_C2270VOSTD_011=11, // standard regular 120
	MET_C2270VOSTD_012=12, // standard regular 130
	MET_C2270VOSTD_013=13, // standard regular 140
	MET_C2270VOSTD_020=20, // Standard regular end restriction of number e.g 60 end of restriction.
	MET_C2270VOSTD_028=28, // standard electronic 10
	MET_C2270VOSTD_029=29, // standard electronic 20
	MET_C2270VOSTD_030=30, // standard electronic 30
	MET_C2270VOSTD_031=31, // standard electronic 40
	MET_C2270VOSTD_032=32, // standard electronic 50
	MET_C2270VOSTD_033=33, // standard electronic 60
	MET_C2270VOSTD_034=34, // standard electronic 70
	MET_C2270VOSTD_035=35, // standard electronic 80
	MET_C2270VOSTD_036=36, // standard electronic 90
	MET_C2270VOSTD_037=37, // standard electronic 100
	MET_C2270VOSTD_038=38, // standard electronic 110
	MET_C2270VOSTD_039=39, // standard electronic 120Page 25 of 36
	MET_C2270VOSTD_040=40, // standard electronic 130
	MET_C2270VOSTD_041=41, // standard electronic 140
	MET_C2270VOSTD_050=50, // standard electronic end restriction of number e.g 60 end of restriction.
	MET_C2270VOSTD_064=64, // standard regular general end all restriction.
	MET_C2270VOSTD_065=65, // standard electronic general end all restriction.
	MET_C2270VOSTD_100=100, // standard regular 5
	MET_C2270VOSTD_101=101, // standard regular 15
	MET_C2270VOSTD_102=102, // standard regular 25
	MET_C2270VOSTD_103=103, // standard regular 35
	MET_C2270VOSTD_104=104, // standard regular 45
	MET_C2270VOSTD_105=105, // standard regular 55
	MET_C2270VOSTD_106=106, // standard regular 65
	MET_C2270VOSTD_107=107, // standard regular 75
	MET_C2270VOSTD_108=108, // standard regular 85
	MET_C2270VOSTD_109=109, // standard regular 95
	MET_C2270VOSTD_110=110, // standard regular 105
	MET_C2270VOSTD_111=111, // standard regular 115
	MET_C2270VOSTD_112=112, // standard regular 125
	MET_C2270VOSTD_113=113, // standard regular 135
	MET_C2270VOSTD_114=114, // standard regular 145
	MET_C2270VOSTD_115=115, // standard electronic 5
	MET_C2270VOSTD_116=116, // standard electronic 15
	MET_C2270VOSTD_117=117, // standard electronic 25
	MET_C2270VOSTD_118=118, // standard electronic 35
	MET_C2270VOSTD_119=119, // standard electronic 45
	MET_C2270VOSTD_120=120, // standard electronic 55
	MET_C2270VOSTD_121=121, // standard electronic 65
	MET_C2270VOSTD_122=122, // standard electronic 75
	MET_C2270VOSTD_123=123, // standard electronic 85
	MET_C2270VOSTD_124=124, // standard electronic 95
	MET_C2270VOSTD_125=125, // standard electronic 105
	MET_C2270VOSTD_126=126, // standard electronic 115
	MET_C2270VOSTD_127=127, // standard electronic 125Page 26 of 36
	MET_C2270VOSTD_128=128, // standard electronic 135
	MET_C2270VOSTD_129=129, // standard electronic 145
	MET_C2270VOSTD_171=171, // standard regular motorWay begin
	MET_C2270VOSTD_172=172, // standard regular end of fMotorWay
	MET_C2270VOSTD_173=173, // standard regular expressWay begin
	MET_C2270VOSTD_174=174, // standard regular end of ExpressWay
	MET_C2270VOSTD_175=175, // standard regular Playground area begin
	MET_C2270VOSTD_176=176, // standard regular End of playground area
	MET_C2270VOSTD_200=200, // standard regular no passing start
	MET_C2270VOSTD_201=201, // standard regular end of no passing
	MET_C2270VOSTD_220=220, // standard electronic no passing start
	MET_C2270VOSTD_221=221, // standard electronic end of no passing
	MET_C2270VOSTD_254=254, // No sign detected
	MET_C2270VOSTD_255=255 //e_invalid_sign

}METMEDataC2270VOSTD;

/*
	Vision only Supplementary Sign Type – Display 1-4
	Type: Enum
	Range: 0-255
	Invalid value = 0xFF = 255 – No speed limit sign was detected.
*/
typedef enum METMEDataC2270VOSSTD
{
	MET_C2270VOSSTD_001=1,//Rain
	MET_C2270VOSSTD_002=2,//Snow
	MET_C2270VOSSTD_003=3,//Trailer
	MET_C2270VOSSTD_004=4,//Time
	MET_C2270VOSSTD_005=5,//Arrow left
	MET_C2270VOSSTD_006=6,//Arrow right
	MET_C2270VOSSTD_007=7,//Bend arrow left
	MET_C2270VOSSTD_008=8,//Bend arrow right
	MET_C2270VOSSTD_009=9,//Truck
	MET_C2270VOSSTD_010=10,//Distance arrow
	MET_C2270VOSSTD_011=11,//Weight
	MET_C2270VOSSTD_012=12,//Distance in
	MET_C2270VOSSTD_013=13,//TractorPage 27 of 36
	MET_C2270VOSSTD_014=14,//Snow rain
	MET_C2270VOSSTD_015=15,//School
	MET_C2270VOSSTD_016=16,//Rain cloud
	MET_C2270VOSSTD_017=17,//Fog
	MET_C2270VOSSTD_018=18,//Hazardous material
	MET_C2270VOSSTD_019=19,//Night
	MET_C2270VOSSTD_255=255//Not in use

}METMEDataC2270VOSSTD;

typedef struct MET_MEDataC2270
{
	/*
	0 silent 
	1 LDW Left	
	2 LDW Right	
	3 HW1 
	4 TSR (if enabled via EyeWatch in C2-270 only) 
	5 UFCW	
	6 FCW+PCW
	*/
	unsigned char ucSoundtype;
	/*
	“00” Day is indicated.
	“01” Dusk is indicated.
	“10” Night is indicated
	*/
	int  nTimeIndicator;
	/* Host vehicle is stopped */
	unsigned char bZeroSpeed;
	/* When CIPV is detected Headway Valid is ON (bit=1) */
	unsigned char bHeadWayValid;
	/* Unit: 0.1 s (unit value is presented in Hex – ex: 1.0 = 0A) Range: 0 … 9.9 */
	unsigned char ucHeadwayMeasurement;
	/* When Error Valid bit is on, the Error Code filed will contain an error code */
	unsigned char bErrorCodeValid;
	int  nErrorCode;
	/* Lane Departure Warnings are disabled when the value is equal 1 */
	unsigned char bLDWOFF;
	/* 
	Indicator of Left/Right LDW event.
	Note: The LDW will be ON for 5 consecutive frames, no matter how long the eventreally is
	*/
	unsigned char bLeftLDWON;
	unsigned char bRightLDWON;
	/* 
	Indicator of FCW event.
	Note:The FCW will be ON for the entire warning length.
	*/
	unsigned char bFCWon;
	/* Indicator of internal error. See User Manual */
	unsigned char bMaintenance;
	/* Indicator of one of the internal FailSafe modes 
	(blur image, 
	saturatedimage, 
	low sun, 
	partial blockage, 
	partial transparent)
	*/
	unsigned char bFailsafe;
	/*
	Meaning: Peds in DZ (Danger Zone)
	1= Pedestrian in DZ/warning on pedestrian/waning (FCW) on vehicle
	0= Pedestrian not in DZ/no warning
	*/
	unsigned char bPedsFCW;
	unsigned char bPedsinDZ;
	/*
	When 0 = No Tamper Alert
	When 1 = Tamper Alert is ON
	Note: Tamper Alert will be activated if there is no vehicle or lane detection for duration
	of 10 minutes. Tamper Alert is active above 15 km/h (9 mph).
	*/
	unsigned char bTamperAlert;
	/*
	Meaning: TSR feature is ON.
	Note: TSR is always ON (bit=1).
	*/
	unsigned char bTSRenabled;
	/*
	Every time the vehicle speed is greater than the Legal Speed limit Sign by 5 (km/h or
	mph) then a BIT will turn On and will grow by +1 with every 5 (km/h or mph) growth.
	This is limited up to 35 (km/h or mph)
	When Speed <= road speed , TSR Warning level= 0
	When Speed > road speed +[0-5kmh], TSR Warning level= 1
	When Speed > road speed +[5-10kmh], TSR Warning level= 2
	When Speed > road speed +[10-15kmh], TSR Warning level= 3
	When Speed > road speed +[15-20kmh], TSR Warning level= 4
	When Speed > road speed +[20-25kmh], TSR Warning level= 5
	When Speed > road speed +[25-30kmh], TSR Warning level= 6
	When Speed > road speed +[30-35kmh], TSR Warning level= 7
	When Speed > road speed +35, TSR Warning level= 7
	*/
	int  nTSRWarningLevel;
	/*
	Unit: HW Level (0-2).
	Note: changes according to warning scheme setup. Default values:
	o When no CIPV is present, HW Level = 0
	(When NO vehicle is detected “0” is indicated).
	o When a CIPV is present with HW > HW Config, HW Level = 1
	(When HW Distance is > then the configured HW “1” is indicated. This indicates a
	Green Car Icon on the Display unit).
	o When a CIPV is present with HW ≤ HW Config, HW Level = 2
	(When HW Distance is ≤ then the configured HW “2” is indicated. This indicates a
	Red Car Icon on the Display unit).
	o When a CIPV is present with HW < 0.6, HW Level = 2 ()
	When HW Distance is < 0.6 HW seconds “2” is indicated. This indicates a Red Car
	Icon on the Display unit (regardless of your HW configuration)
	*/
	unsigned char bHeadwayWarningLevel;
	/*
	Meaning: HW Repeatable feature is ON if configured (1=ON)
	Note: HW Repeatable configuration is possible only during system
	Configuration/Installation process (via Mobileye Setup Wizard)
	*/
	int  nHWrepeatableEnabled;
	/*
	Type: bit
	Unit and range: 1 if right turn signal is on, 0 if off.
	*/
	unsigned char bBrakes;
	/*
	Type: bit
	Unit and range: 1 if left turn signal is on, 0 if off.
	*/
	unsigned char bLeftSignal;
	/*
	Type: bit
	Unit and range: 1 if right turn signal is on, 0 if off.
	*/
	unsigned char bRightSignal;
	/*
	Type: bit
	Unit and range: 1 when a Wiper passes the windshield, 0 if a wiper is static.
	*/
	unsigned char bWipers;
	/*
	Type: bit
	Unit and range: 1 if Low Beam on, 0 if off.
	*/
	unsigned char bLowBeam;
	/*
	Type: bit
	Unit and range: 1 if High Beam on, 0 if off.
	*/
	unsigned char bHighBeam;
	/*
	Type: bit
	Unit and Range: 1 if Wipers available
	*/
	unsigned char bWipersAvailable;
	/*
	Type: bit
	Unit and range: 1 if Low Beam available
	*/
	unsigned char bLowBeamAvailable;
	/*
	Type: bit
	Unit and range: 1 if High Beam available
	*/
	unsigned char bHighBeamAvailable;
	/*
	Type: bit
	Unit and range: 1 if Speed available
	*/
	unsigned char bSpeedAvailable;
	/*
	Unit: km/h
	Range: 0-255 Km/h
	*/
	int nSpeed;
	//0x720
	/*
	Vision only Sign Typez
	Type: Enum
	Note: The values in the “Meaning” are the Traffic Sign (speed sign) Numerical
	Values. There is no reference to Speed Format (km/h or mph).
	*/
	METMEDataC2270VOST eMETMEDataC2270VOST;
	/* 
	 Vision only Supplementary Sign Type
	 Type: Enum
	*/
	METMEDataC2270VOSST eMETMEDataC2270VOSST;
	/*
	Type: unsigned Int
	Range: 0…122
	Resolution: 0.5 meter
	Meaning: The longitude position of the sign in the real world in meters.
	*/
	unsigned int nSignPositionX;
	/*
	Type: Signed Int
	Range: -32… 31
	Resolution: 0.5 meter
	Meaning : The lateral position of the sign in the real world in meters.
	Negative refers to left and positive to right.
	*/
	int nSignPositionY;
	/*
	Type: signed Int
	Range: -16… 16
	Resolution: 0.5 meter
	Meaning : The height of the sign in the real world in meters, relative to the camera
	location. Positive value refers to above the camera. Negative is below the camera.
	*/
	int nSignPositionZ;
	/*
	Type: Enum
	Meaning: The reason for filtering the sign. External filter, filtering visible signs to due	irrelevance.
	*/
	METMEDataC2270FilterType eMETMEDataC2270FT;
	//0x727
	/*
	Vision only Sign Type – Display 1 - 4
	Type: Enum
	Range: 0-255
	Invalid value = 0xFF = 255 – No speed limit sign was detected.
	Note: The values are the Traffic Sign (speed sign) Numerical Values. There
	is no reference to Speed Format (kmh or mph).
	*/
	METMEDataC2270VOSTD eMETMEDataC2270VOSTD1;
	METMEDataC2270VOSTD eMETMEDataC2270VOSTD2;
	METMEDataC2270VOSTD eMETMEDataC2270VOSTD3;
	METMEDataC2270VOSTD eMETMEDataC2270VOSTD4;
	/*
	Vision only Supplementary Sign Type – Display 1-4
	Type: Enum
	Range: 0-255
	Invalid value = 0xFF = 255 – No speed limit sign was detected.
	*/
	METMEDataC2270VOSSTD eMETMEDataC2270VOSSTD1;
	METMEDataC2270VOSSTD eMETMEDataC2270VOSSTD2;
	METMEDataC2270VOSSTD eMETMEDataC2270VOSSTD3;
	METMEDataC2270VOSSTD eMETMEDataC2270VOSSTD4;

}MET_MEDataC2270;

typedef enum METMoveOrientation
{
	MET_MOVE_UNKNOWN=0,
	MET_MOVE_OUT=1,
	MET_MOVE_IN=2,
	MET_MOVE_LEFT=3,
	MET_MOVE_RIGHT=4,
}METMoveOrientation;

typedef enum METLightSource
{
	MET_LIGHTSOURCE_UNKNOWN=0,
	MET_LIGHTSOURCE_VISIBLE=1,
	MET_LIGHTSOURCE_INFRARED=2
}METLightSource;

typedef enum METColor
{
	MET_COLOR_UNKNOWN=0,
	MET_COLOR_YELLOW=1,
	MET_COLOR_RED=2,
	MET_COLOR_BLUE=3,
	MET_COLOR_GREEN=4,
	MET_COLOR_WHITE=5,
	MET_COLOR_BLACK=6
}METColor;

/********************* Vehicle Sample  ***********************************/
typedef enum METVehicleKind
{
	MET_VEHICLE_KIND_UNKNOWN=0,
	MET_VEHICLE_KIND_CAR=1,
	MET_VEHICLE_KIND_TRUCK=2,
	MET_VEHICLE_KIND_BUS=3,
	MET_VEHICLE_KIND_SUV=4,
	MET_VEHICLE_KIND_VAN=5,
	MET_VEHICLE_KIND_SPECIALCAR=6
}METVehicleKind;

typedef enum METVehicleBeamState
{
	MET_VEHICLE_BEAMSTATE_UNKNOWN=0,
	MET_VEHICLE_BEAMSTATE_OFF=1,
	MET_VEHICLE_BEAMSTATE_TAILBEAM=2,
	MET_VEHICLE_BEAMSTATE_BRAKEBEAM=3,
	MET_VEHICLE_BEAMSTATE_LOWBEAM=4,
	MET_VEHICLE_BEAMSTATE_HIGHBEAM=5
}METVehicleBeamState;

typedef enum METVehicleGesture
{
	MET_VEHICLE_Gesture_UNKNOWN=0,
	MET_VEHICLE_Gesture01=1,//只看到车尾部
	MET_VEHICLE_Gesture02=2,//看到车尾部和驾驶室
	MET_VEHICLE_Gesture03=3,//只看到驾驶室
	MET_VEHICLE_Gesture04=4,//看到车头部和驾驶室
	MET_VEHICLE_Gesture05=5,//只看到车头部
	MET_VEHICLE_Gesture06=6,//看到车头部和副驾驶室
	MET_VEHICLE_Gesture07=7,//只看到副驾驶室
	MET_VEHICLE_Gesture08=8//看到车尾部和副驾驶室
}METVehicleGesture;

typedef enum METVehicleKeepOut
{
	MET_VEHICLE_KEEPOUT_UNKNOWN=0,
	MET_VEHICLE_KEEPOUT_NORMAL=1,
	MET_VEHICLE_KEEPOUT_BECOVERED=2,
}METVehicleKeepOut;

typedef struct METVehicleSampleElement
{
	METVehicleKind		vehicleKind;
	METMoveOrientation	vehicleMoveOrientation;
	METVehicleBeamState	vehilceBeamState;
	METRect				vehicleRect;
	METPoint			sideCorner;
	METPoint			sideCornerUp;
	char				sideFlag;
	METVehicleGesture	eGesture;
	METVehicleKeepOut	eKeepOut;

	unsigned char ucDrawMode;

}METVehicleSampleElement;

/*********************  Pedestrian  Sample   ***************************/
typedef enum METPedestrianKeepOut
{
	MET_PEDESTRIAN_KEEPOUT_UNKNOWN=0,
	MET_PEDESTRIAN_KEEPOUT_NORMAL=1,
	MET_PEDESTRIAN_KEEPOUT_BECOVERED=2,
}METPedestrianKeepOut;

typedef enum METPedestrianGesture
{
	MET_PDGESTURE_UNKNOWN=0,
	MET_PDGESTURE_STAND=1,
	MET_PDGESTURE_WALK=2,
	MET_PDGESTURE_RUN=3,
	MET_PDGESTURE_OTHER=4
}METPedestrianGesture;

typedef struct METPedestrianSampleElement
{
	METPoint	objHandPts[2];
	METPoint	objFootPts[2];

	METPedestrianKeepOut	eKeepOut;

	METMoveOrientation		MoveOrientation;
	METLightSource			lightSource;
	METPedestrianGesture	pedestrianGesture;

	METRect					pedestrianRect;
	METRect					headRect;

	unsigned char ucDrawMode;
}METPedestrianSampleElement;

/************************ Biker ***********************************/
typedef enum METBikerKeepOut
{
	MET_BIKER_KEEPOUT_UNKNOWN=0,
	MET_BIKER_KEEPOUT_NORMAL=1,
	MET_BIKER_KEEPOUT_BECOVERED=2,
}METBikerKeepOut;

typedef enum METBikerMoveOrientation
{
	MET_BIKER_MOVEORIENTATION_UNKNOWN=0,
	MET_BIKER_MOVEORIENTATION01=1,
	MET_BIKER_MOVEORIENTATION02=2,
	MET_BIKER_MOVEORIENTATION03=3,
	MET_BIKER_MOVEORIENTATION04=4,
	MET_BIKER_MOVEORIENTATION05=5,
	MET_BIKER_MOVEORIENTATION06=6,
	MET_BIKER_MOVEORIENTATION07=7,
	MET_BIKER_MOVEORIENTATION08=8

}METBikerMoveOrientation;

typedef struct METBicycleElement
{
	METMoveOrientation	bicycleMoveOrientation;

	METPoint	objWheelPts[2];

	METBikerKeepOut eKeepOut;

	METRect	bicycleRect;
	METRect	headRect;

}METBicycleElement;

typedef struct METBikerElement
{
	METBikerMoveOrientation	eMoveOrientation;
	METBikerKeepOut eKeepOut;
	METPoint	objWheelPts[2];
	METRect	objMainRect;
	METRect	objHeadRect;

}METBikerElement;

/************************ Traffic Sign *******************************/
typedef enum METTrafficSignKind
{
	MET_TRAFFICSIGN_KIND_UNKNOWN=0,
	MET_TRAFFICSIGN_KIND_WARNINGSIGN=1,			//警告标志
	MET_TRAFFICSIGN_KIND_BANSIGN=2,				//禁令标志
	MET_TRAFFICSIGN_KIND_INDICATIONSIGN=3,		//指示标志
	MET_TRAFFICSIGN_KIND_ROADSIGN=4,			//指路标志
	MET_TRAFFICSIGN_KIND_TOURISTAREASIGN=5,		//旅游标志
	MET_TRAFFICSIGN_KIND_CONSTRUCTIONSIGN=6,	//道路施工标志
	MET_TRAFFICSIGN_KIND_ASSISTSIGN=7			//辅助标志

}METTrafficSignKind;

typedef enum METTrafficSignShape
{
	MET_TRAFFICSIGN_UNKNOWN=0,
	MET_TRAFFICSIGN_SHAPE_CIRCLE=1,
	MET_TRAFFICSIGN_SHAPE_TRIANGLE=2,
	MET_TRAFFICSIGN_SHAPE_SQUARE=3,
	MET_TRAFFICSIGN_SHAPE_RECTANGLE=4,
	MET_TRAFFICSIGN_SHAPE_POLYGON=5

}METTrafficSignShape;

typedef enum METTrafficSignMeaning
{
	MET_TRASIGMEA_UNKNOWN=0,//未知
	MET_TRASIGMEA_BAN0001=1,//禁止通行
	MET_TRASIGMEA_BAN0002=2,//禁止驶入
	MET_TRASIGMEA_BAN0003=3,//禁止机动车通行
	MET_TRASIGMEA_BAN0004=4,//禁止载货汽车通行
	MET_TRASIGMEA_BAN0005=5,//禁止三轮机动车通行
	MET_TRASIGMEA_BAN0006=6,//禁止大型客车通行
	MET_TRASIGMEA_BAN0007=7,//禁止小型客车通行
	MET_TRASIGMEA_BAN0008=8,//禁止汽车拖，挂车通行
	MET_TRASIGMEA_BAN0009=9,//禁止拖拉机通行
	MET_TRASIGMEA_BAN0010=10,//禁止农用运输车通行
	MET_TRASIGMEA_BAN0011=11,//禁止两用摩托车通行
	MET_TRASIGMEA_BAN0012=12,//禁止某两种车通行
	MET_TRASIGMEA_BAN0013=13,//禁止非机动车通行
	MET_TRASIGMEA_BAN0014=14,//禁止畜力车通行
	MET_TRASIGMEA_BAN0015=15,//禁止人力货运三轮车通行
	MET_TRASIGMEA_BAN0016=16,//禁止人力客运三轮车通行
	MET_TRASIGMEA_BAN0017=17,//禁止骑自行车下坡
	MET_TRASIGMEA_BAN0018=18,//禁止自行车上坡
	MET_TRASIGMEA_BAN0019=19,//禁止人力车通行
	MET_TRASIGMEA_BAN0020=20,//禁止行人通行
	MET_TRASIGMEA_BAN0021=21,//禁止右转弯
	MET_TRASIGMEA_BAN0022=22,//禁止左转弯
	MET_TRASIGMEA_BAN0023=23,//禁止直行
	MET_TRASIGMEA_BAN0024=24,//禁止向左向右转弯
	MET_TRASIGMEA_BAN0025=25,//禁止直行和向左转弯
	MET_TRASIGMEA_BAN0026=26,//禁止直行和向右转弯
	MET_TRASIGMEA_BAN0027=27,//禁止掉头
	MET_TRASIGMEA_BAN0028=28,//禁止超车
	MET_TRASIGMEA_BAN0029=29,//解除禁止超车
	MET_TRASIGMEA_BAN0030=30,//禁止车辆临时或长时停放
	MET_TRASIGMEA_BAN0031=31,//禁止车辆长时停放
	MET_TRASIGMEA_BAN0032=32,//禁止鸣喇叭
	MET_TRASIGMEA_BAN0033=33,//限制宽度
	MET_TRASIGMEA_BAN0034=34,//限制高度
	MET_TRASIGMEA_BAN0035=35,//限制质量
	MET_TRASIGMEA_BAN0036=36,//限制轴重
	MET_TRASIGMEA_BAN0037=37,//限制速度
	MET_TRASIGMEA_BAN0038=38,//解除限制速度
	MET_TRASIGMEA_BAN0049=39,//停车检查
	MET_TRASIGMEA_BAN0040=40,//停车让行
	MET_TRASIGMEA_BAN0041=41,//会车让行
	MET_TRASIGMEA_BAN0042=42,//减速让行
	////////////////////////////////////
	MET_TRASIGMEA_WAR0001=201,//十字交叉
	MET_TRASIGMEA_WAR0002=202,//T形交叉
	MET_TRASIGMEA_WAR0003=203,//T形交
	MET_TRASIGMEA_WAR0004=204,//T形交叉
	MET_TRASIGMEA_WAR0005=205,//Y形交叉
	MET_TRASIGMEA_WAR0006=206,//环形交叉
	MET_TRASIGMEA_WAR0007=207,//向右急弯路
	MET_TRASIGMEA_WAR0008=208,//反向弯路
	MET_TRASIGMEA_WAR0009=209,//连续弯路
	MET_TRASIGMEA_WAR0010=210,//上陡坡
	MET_TRASIGMEA_WAR0011=211,//下陡坡
	MET_TRASIGMEA_WAR0012=212,//两侧变窄
	MET_TRASIGMEA_WAR0013=213,//左侧变窄
	MET_TRASIGMEA_WAR0014=214,//窄桥
	MET_TRASIGMEA_WAR0015=215,//双向交通
	MET_TRASIGMEA_WAR0016=216,//注意行人
	MET_TRASIGMEA_WAR0017=217,//注意儿童
	MET_TRASIGMEA_WAR0018=218,//注意牲畜
	MET_TRASIGMEA_WAR0019=219,//注意落石
	MET_TRASIGMEA_WAR0020=220,//注意落石
	MET_TRASIGMEA_WAR0021=221,//注意横风
	MET_TRASIGMEA_WAR0022=222,//易滑 
	MET_TRASIGMEA_WAR0023=223,//傍山险路
	MET_TRASIGMEA_WAR0024=224,//傍山险路
	MET_TRASIGMEA_WAR0025=225,//堤坝路
	MET_TRASIGMEA_WAR0026=226,//村庄
	MET_TRASIGMEA_WAR0027=227,//隧道
	MET_TRASIGMEA_WAR0028=228,//渡口
	MET_TRASIGMEA_WAR0029=229,//驼峰桥
	MET_TRASIGMEA_WAR0030=230,//路面不平
	MET_TRASIGMEA_WAR0031=231,//有人看守铁路道口
	MET_TRASIGMEA_WAR0032=232,//无人看守铁路道口
	MET_TRASIGMEA_WAR0033=233,//叉形符号
	MET_TRASIGMEA_WAR0034=234,//斜杠符号
	MET_TRASIGMEA_WAR0035=235,//斜杠符号
	MET_TRASIGMEA_WAR0036=236,//斜杠符号
	MET_TRASIGMEA_WAR0037=237,//事故易发路段
	MET_TRASIGMEA_WAR0038=238,//慢行
	MET_TRASIGMEA_WAR0039=239,//左右绕行
	MET_TRASIGMEA_WAR0040=240,//左侧绕行
	MET_TRASIGMEA_WAR0041=241,//右侧绕行
	MET_TRASIGMEA_WAR0042=242,//施工
	MET_TRASIGMEA_WAR0043=243,//右侧变窄
	MET_TRASIGMEA_WAR0044=244,//注意信号灯
	MET_TRASIGMEA_WAR0045=245,//堤坝路
	MET_TRASIGMEA_WAR0046=246,//过水路面
	MET_TRASIGMEA_WAR0047=247,//注意非机动车
	MET_TRASIGMEA_WAR0048=248,//注意危险
	MET_TRASIGMEA_WAR0049=249,//向左急转弯
	//////////////////////////////////////
	MET_TRASIGMEA_IND0001=401,//直行
	MET_TRASIGMEA_IND0002=402,//向左转弯
	MET_TRASIGMEA_IND0003=403,//向右转弯
	MET_TRASIGMEA_IND0004=404,//直行和向左转弯
	MET_TRASIGMEA_IND0005=405,//直行和向右转弯
	MET_TRASIGMEA_IND0006=406,//向左和向右转弯
	MET_TRASIGMEA_IND0007=407,//靠右侧道路行驶
	MET_TRASIGMEA_IND0008=408,//靠左侧道路行驶
	MET_TRASIGMEA_IND0009=409,//立交直行和左转弯行驶
	MET_TRASIGMEA_IND0010=410,//立交直行和右转弯行驶
	MET_TRASIGMEA_IND0011=411,//环岛行驶
	MET_TRASIGMEA_IND0012=412,//单行路(向左或向右)
	MET_TRASIGMEA_IND0013=413,//单行路(直行)
	MET_TRASIGMEA_IND0014=414,//步行
	MET_TRASIGMEA_IND0015=415,//鸣喇叭
	MET_TRASIGMEA_IND0016=416,//最低限速
	MET_TRASIGMEA_IND0017=417,//干路先行
	MET_TRASIGMEA_IND0018=418,//会车先行
	MET_TRASIGMEA_IND0019=419,//人行横道
	MET_TRASIGMEA_IND0020=420,//右转车道
	MET_TRASIGMEA_IND0021=421,//直行车道
	MET_TRASIGMEA_IND0022=422,//直行和右转合用车道
	MET_TRASIGMEA_IND0023=423,//分向行驶车道
	MET_TRASIGMEA_IND0024=424,//公交路线专用车道
	MET_TRASIGMEA_IND0025=425,//机动车行驶
	MET_TRASIGMEA_IND0026=426,//机动车车道
	MET_TRASIGMEA_IND0027=427,//非机动车行驶
	MET_TRASIGMEA_IND0028=428,//非机动车车道
	MET_TRASIGMEA_IND0029=429,//允许掉头
	//////////////////////////////////////
	MET_TRASIGMEA_ROA0001=601,//直行
	MET_TRASIGMEA_ROA0002=602,//向左转弯

}METTrafficSignMeaning;

typedef enum METTriVerDir
{
	MET_TRIVERDIR_UNKNOWN=0,
	MET_TRIVERDIR_UP=1,
	MET_TRIVERDIR_DOWN=2,
}METTriVerDir;

typedef struct METTrafficSignElement
{
	METTriVerDir			eTriVerDir;
	METTrafficSignKind		eKind;
	METColor				eBaseColor;
	METColor				eEdgeCcolor;
	METColor				ePatternColor;
	METColor				eBarColor;
	METTrafficSignShape		eShape;
	METTrafficSignMeaning	eMeaning;
	unsigned char			nNumVal;
	unsigned char			nNeedNumValu;

	METRect					objRectPst;
	METPoint				objPointPts[4];
	METPoint				objLogoPts;
}METTrafficSignElement;

typedef struct METTrafficSignElement_Circle
{
	METTrafficSignKind		trafficSignKind;
	METColor				trafficSignColor;
	unsigned short			trafficSignMeaning;

	METRect					trafficSignRect;
}METTrafficSignElement_Circle;

typedef struct METTrafficSignElement_Triangle
{
	METTrafficSignKind		trafficSignKind;
	METColor				trafficSignColor;
	unsigned short			trafficSignMeaning;

	METPoint				trafficSignPts[3];	//0-up, 1-botton_left, 2-botton_right;	
}METTrafficSignElement_Triangle;

typedef struct METTrafficSignElement_Square
{
	METTrafficSignKind		trafficSignKind;
	METColor				trafficSignColor;
	unsigned short			trafficSignMeaning;

	METPoint				trafficSignPts[4];	//0-up_left, 1-up_right, 2-button_left, 3-button_right;	
}METTrafficSignElement_Square;

/********************* Traffic Light ***********************************/
typedef enum METTrafficLightKeepOut
{
	MET_TRAFFICLIGHT_KEEPOUT_UNKNOWN=0,
	MET_TRAFFICLIGHT_KEEPOUT_NORMAL=1,
	MET_TRAFFICLIGHT_KEEPOUT_BECOVERED=2,
}METTrafficLightKeepOut;

typedef enum METTrafficLightAmount
{
	MET_TRAFFICLIGHT_AMOUNT_UNKNOWN=-1,
	MET_TRAFFICLIGHT_AMOUNT_ONE=0,
	MET_TRAFFICLIGHT_AMOUNT_TWO=1,
	MET_TRAFFICLIGHT_AMOUNT_THREE=2

}METTrafficLightAmount;

typedef enum METTrafficLightDirection
{
	MET_TLD_UNKNOWN=0,
	MET_TLD_RIGHT=1,
	MET_TLD_LEFT=2,
	MET_TLD_FRONT=3

}METTrafficLightDirection;

typedef enum METTrafficLightType
{
	MET_TRAFFICLIGHTTYPE_UNKNOWN=0,
	MET_TRAFFICLIGHTTYPE_01=1,
	MET_TRAFFICLIGHTTYPE_02=2,
	MET_TRAFFICLIGHTTYPE_03=3,
	MET_TRAFFICLIGHTTYPE_04=4,
	MET_TRAFFICLIGHTTYPE_05=5,
	MET_TRAFFICLIGHTTYPE_06=6,
	MET_TRAFFICLIGHTTYPE_07=7,
	MET_TRAFFICLIGHTTYPE_08=8

}METTrafficLightType;

typedef struct METTrafficLightElement
{
	METTrafficLightAmount	lightAmount;
	METTrafficLightDirection	lightDirection;
	METColor	trafficLightColor;
	METRect	lightSetsRect;
	METRect	lightRect;
	METTrafficLightType	eType;
	unsigned char	ucBoxFlag;
	short	sTime;
	METPoint	objAssistInfPts;
	METTrafficLightKeepOut	eKeepOut;

}METTrafficLightElement;
/********************* Driving Area ***********************************/
typedef struct METDrivingAreaElement
{
	METPoint		objPointPts[MET_POLYGON_POINTNUM];
	unsigned char   ucPointNum;

}METDrivingAreaElement;

/********************* LaneLine ***********************************/
typedef enum METConnectedDomainType
{
	MET_CONDOMTYPE_UNKNOWN=0,
	MET_CONDOMTYPE_LANELINE=1,		//车道线
	MET_CONDOMTYPE_STOPMARK=2,		//停止线
	MET_CONDOMTYPE_ZEBRACROSSING=3,	//斑马线
	MET_CONDOMTYPE_ARROWS=4,		//箭头
	MET_CONDOMTYPE_MASKONROAD=5,	//masknoroad
	MET_CONDOMTYPE_MASKNOT=6		//masknote

}METConnectedDomainType;

typedef enum METLineLineType
{
	MET_LANELINETYPE_UNKNOWN=0,
	MET_LANELINETYPE_FULLLINE=1,		//实线
	MET_LANELINETYPE_IMAGINARYLINE=2,	//虚线
	MET_LANELINETYPE_CROSSAREA=3,		//交叉区

}METLineLineType;

typedef struct METConnectedDomain
{
	METColor	eColor;
	unsigned char ucFillFlag;

	METLineLineType	eLaneLineType;
	METConnectedDomainType	eType;

	METPoint*	objpPointPts;
	short	sObjIndex;
	short	sPointNum;

	unsigned char	ucSelected;
	METPoint	objTextPts;

}METConnectedDomain;

typedef struct METLaneLineElement
{
	METColor	eColor;
	unsigned char ucFillFlag;

	METLineLineType eType;

	METPoint* objpPointPts;
	short	sObjIndex;
	short	sPointNum;

	unsigned char ucSelected;
	METPoint	objTextPts;

}METLaneLineElement;

/************************* Sample Info  **********************************/
typedef union METSampleInfo
{
	METVehicleSampleElement			vehicleSample;
	METPedestrianSampleElement		pedestrianSample;
	METBicycleElement				bicycleSample;
	METTrafficSignElement_Circle	trafficSignCircleSample;
	METTrafficSignElement_Triangle	trafficSignTriangleSample;
	METTrafficSignElement_Square	trafficSignSquareSample;
	METTrafficLightElement			trafficLightSample;
	METTrafficSignElement			trafficSignSample;
	METDrivingAreaElement			drivingAreaSample;
	METLaneLineElement				laneLineSample;
	METConnectedDomain				connectedDomain;
	METBikerElement					bikerSample;
}METSampleInfo;

typedef enum METSampleType//now
{
	MET_SAMPLETYPE_NONE=0,
	MET_SAMPLETYPE_VEHICLE=1,
	MET_SAMPLETYPE_PEDESTRIAN=2,
	MET_SAMPLETYPE_BIKER=3,
	MET_SAMPLETYPE_MOTORCYCLE=4,
	MET_SAMPLETYPE_TRAFFICSIGN_CIRCLE=5,
	MET_SAMPLETYPE_TRAFFICSIGN_TRIANGLE=6,
	MET_SAMPLETYPE_TRAFFICSIGN_SQUARE=7,
	MET_SAMPLETYPE_TRAFFICLIGHT=8,
	MET_SAMPLETYPE_TRAFFICSIGN=9,
	MET_SAMPLETYPE_GUARDBAR,
	MET_SAMPLETYPE_DRIVINGAREA=10,
	MET_SAMPLETYPE_CONNECTEDDOMAIN=11

}METSampleType;

typedef struct METSampleElement
{
	METSampleType	sampleType;
	METSampleInfo	sampleInfo;
}METSampleElement;

typedef struct METSampleObject
{
	unsigned short		objCount;
	METSampleElement	sampleList[MET_SAMPLEOBJ_MAXCOUNT];
}METSampleObject;


typedef struct METImageFrameHeader
{
	/************** image basic Info *****************/
	unsigned short			imgWidth;
	unsigned short			imgHeight;

	/************** Version Info *****************/
	unsigned char			versionID;

	/************** Capture time *****************/
	METTime					captureTime;


	/************** Camera Info *****************/
	METCameraInfo			cameraInfo;

	/************** Vehicle Info *****************/
	METVehicleInfo			vehicleInfo;

	/************** Radar Object *****************/
	METRadarObject			radarObj;

	/************** Sample Object *****************/
	METSampleObject			sampleObj;

	/************ Light Sensor Recording ***********/
	METLightSensorObject	lightSensorObj;
}METImageFrameHeader;

#endif