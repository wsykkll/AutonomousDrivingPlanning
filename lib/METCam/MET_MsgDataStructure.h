/************************************************************************/
/*
Date:			2016/08/09
Author:			Chunlan Ye
Compile Mode:	C/C++
Function:		MaxiEyeTech Communication Protocol DataStructure Define(OutPut Version)
*/
/************************************************************************/
#ifndef MET_MSGDATASTRUCTURE_H
#define MET_MSGDATASTRUCTURE_H

#define MET_MSG_VISIONOBJ_OBJNUM			15
#define MET_MSG_NOGLAREREGION_OBJNUM		6
#define MET_MSG_FUSIONOBJ_OBJNUM			64

#define MET_MSG_STATE_RADAR_ONLY			0
#define MET_MSG_STATE_VISION_ONLY			1
#define MET_MSG_STATE_RADAR_AND_VISION		2
/*********** environment status Msg **************/
typedef struct METMsgEnvStatus
{
	unsigned char		envLightMode;		//environment luminance level
	unsigned char		roadType;
	unsigned char		fogLevel;
	unsigned char		camExposureMode;
	unsigned char		ahsMode;
	unsigned char		adbMode;
	unsigned char		fcwMode;
}METMsgEnvStatus;

/*********** Lane Msg **************/
typedef struct METMsgLaneStatus
{
	char			relativeNum;
	float			vehiclePitch;		//unit: degree
	unsigned int	lftParallLaneAge;
	unsigned int	RgtParallLaneAge;
	unsigned int	lftIndivalLaneAge;
	unsigned int	RgtIndivalLaneAge;
	unsigned char	laneWarn;
}METMsgLaneStatus;

/** lane addition information **/
typedef struct METMsgLaneAInfo
{
	unsigned char		zebraValidFlag;
	float				zebraDist;		//unit: m
	float				zebraOrient;	//unit: degree

	unsigned char		stoplineValidFlag;
	float				stoplineDist;	//unit: m
	float				stoplineOrient; //unit: degree

	unsigned char		ptValidFlag;
	float				ptPosX;			//unit: m
	float				ptPosY;			//unit: m
}METMsgLaneAInfo;

typedef struct METMsgNeighborLane
{
	unsigned char		validFlagLft;
	float				offsetLft;		//unit: m
	unsigned char		confidenceLft;
	unsigned char		typeLft;
	unsigned int		ageLft;

	unsigned char		validFlagRght;
	float				offsetRght;		//unit: m
	unsigned char		confidenceRght;
	unsigned char		typeRgt;
	unsigned int		ageRgt;
}METMsgNeighborLane;

typedef struct METMsgLaneInfo
{
	unsigned char		validFlag;
	
	float				A0;				//y = A3 * x^3 / 6 + A2 * x^2 / 2 + A1 * x + A0, unit: m
	float				A1;				
	float				A2;
	float				A3;

	float				laneRange;		//unit: m
	unsigned char		laneColor;
	unsigned char		laneConfidence;
	unsigned char		laneType;
}METMsgLaneInfo;

typedef struct METMsgLaneObj
{
	METMsgLaneStatus		laneStatus;
	METMsgLaneAInfo			laneAInfo;

	METMsgNeighborLane		neighborLane;

	METMsgLaneInfo			curParallLaneLft;
	METMsgLaneInfo			curParallLaneRght;
	
	METMsgLaneInfo			curIndivalLaneLft;
	METMsgLaneInfo			curIndivalLaneRght;
}METMsgLaneObj;

/*********** Beam Msg **************/
typedef struct METMsgBeamCtrlInfo
{
	float					beamVerticalAngle;	//unit: degree
	unsigned char			lowBeamActive;
	unsigned char			highBeamActive;
	
	unsigned char			beamAFSActiveLft;
	float					beamAFSAngleLft;		//unit: degree
	unsigned char			beamAFSActiveRght;
	float					beamAFSAngleRght;		//unit: degree
}METMsgBeamCtrlInfo;

typedef struct METMsgNoGlareRegion
{
	unsigned char			validFlag;
	float					boundaryAngleLft;		//unit:degree
	float					boundaryAngleRght;		//unit: degree
}METMsgNoGlareRegion;

typedef struct METMsgBeamObj
{
	METMsgBeamCtrlInfo		beamCtrlInfo;
	float					dist;					//unit: m
	METMsgNoGlareRegion		noGlareRegion[MET_MSG_NOGLAREREGION_OBJNUM];
}METMsgBeamObj;

typedef struct METMsgFCWWarnInfo
{
	unsigned char			validFlag;
	float					dist;
	unsigned char			nearStatus;
	float					thwTime;
	float					TTC;
	unsigned char			ID;	//in METMsgVisionObjInfo List

	
	unsigned char			TTCWarn;
	unsigned char			nearWarn;
	unsigned char			stopCloseWarn;
	unsigned char			stopAwayWarn;
}METMsgFCWWarnInfo;

/*********** Vision Detect Obj Msg **************/
typedef struct METMsgVisionObjInfo
{
	unsigned char			status;			
	unsigned char			trackID;		
	unsigned char			type;
	unsigned char			confidence;
	float					dist;			//unit: m
	float					angle;			//unit: degree
	float					horizonDim;		//unit: m
	float					velocity;		//unit: m/s
	unsigned char			cutInOut;
	unsigned char			turnLightStatus;
	unsigned char			brakeLightStatus;
}METMsgVisionObjInfo;

typedef struct METMsgVisionObj
{
	unsigned char			objNum;
	METMsgVisionObjInfo		objInfo[MET_MSG_VISIONOBJ_OBJNUM];
}METMsgVisionObj;

/*********** Fusion Obj Msg **************/
typedef struct METMsgFusionObjInfo //use Radar Coordinate
{
	unsigned char			status;			//current use Radar
	unsigned char			type;			//0- vision only, 1-radar only, 2-vision & radar
	float					trackRange;		//unit: m
	float					trackAngle;		//unit: degree
	float					trackLatRate;	//unit: degree/s
	float					trackWidth;		//unit: m
	float					rangeRate;		//unit: m/s
	float					rangeAccel;		//unit: m/s/s
}METMsgFusionObjInfo;

typedef struct METMsgFusionObj
{
	unsigned char			objNum;
	unsigned char			cipvID;		//0~MET_MSG_FUSIONOBJ_OBJNUM-1 , valid
	unsigned char			ACC_Traget_ID;
	unsigned char			CMBB_Move_ID;
	unsigned char			CMBB_Stat_ID;
	unsigned char			FCW_Move_ID;
	unsigned char			FCW_Stat_ID;
	METMsgFusionObjInfo		objInfo[MET_MSG_FUSIONOBJ_OBJNUM];
}METMsgFusionObj;

typedef struct METMsgDebugRecv	// 0x15
{
	unsigned char			warnFlag;
	unsigned char			calRecCode;
	unsigned char			cfa_time;
	unsigned char			ldw_time;
	unsigned char			fcw_time;
	unsigned char			adb_time;
	long long				receiveTime;
}METMsgDebugRecv;

typedef struct METMsgDebugSend	// 0x20
{
	unsigned char			pic_save;
	unsigned char			video_save;
	unsigned char			debug_mode;		// 1:static debug 2.dynamic debug
	unsigned char			cam_cal;		
	unsigned char			send_enable;	// 0x55. disable SFV send 0 enable SFV send
}METMsgDebugSend;

/******* Road Target *******/
typedef struct METMsgRoadTarget
{
	float				velocityLong;			//V_long_obj, unit:m/s
	float				velocityLat;			//V_lat_obj, unit:m/s
	
	float				locationLong;			//L_long_rel, unit:m
	float				locationLat;			//L_lat_rel, unit:m
	float				accelLong;				//A_long_obj, unit:m/s^2
	float				accelLat;				//A_lat_obj, unit:m/s^2
	unsigned char		radarTrackId;			//TrackID, Val- 0:1:63, used as Status, 0-invalid, other-valid
	unsigned char		visionTrackId;			//visTrkID, Val- 0:1:15 
	unsigned char		mcAge;					//MC_Age
	unsigned char		mcObjClass;				//MC_object_class, Mean: 0-undetermined, 1-car
	unsigned char		mcPosConfidence;		//MC_positionConfidence
	unsigned char		mcStageAge;				//MC_stage_age
	
	unsigned char		msgCounterA;			//RT1A_MessageCounter
	unsigned char		msgCounterB;			//RT1B_MessageCounter
	unsigned char		msgCounterC;			//RT1C_MessageCounter
	unsigned char		msgCounterD;			//RT1D_MessageCounter

	unsigned char		tagFarLftRght;			//FARLeftRight
	float				farCornerLong;			//FARcorner_long, unit:m
	float				farCornerLat;			//FARcorner_lat, unit:m
	float				lftCornerLong;			//LEFTcorner_long, unit:m
	float				lftCornerLat;			//LEFTcorner_lat, unit:m
	float				rghtCornerLong;			//RIGHTcorner_long, unit:m
	float				rghtCornerLat;			//RIGHTcorner_lat, unit:m

	float				objPosOfLaneCenterLat;	//RT1B_XOLC_ETSEL_CMbB_FCW, unit:m
	float				objPosOfHostPredictLat;	//RT1B_XOHP_ETSEL_CMbB_FCW, unit:m

	unsigned char		status;					//Status, not used now, use radarTrackId to instead of
	unsigned char		moveMent;				//Movement, 0-Static, 1-Moving
	float				objWidth;				//Width, unit:m
	unsigned char		detectSensorType;		//DetectionSensor, only use 2-vision only, 3-tracklets and vision.
}METMsgRoadTarget;




/************************************************************************/
/* Output Msg Define                                                    */
/************************************************************************/
typedef struct METOutputMsg
{
	METMsgEnvStatus			evnStatusMsg;
	METMsgLaneObj			laneMsg;
	METMsgBeamObj			beamMsg;
	METMsgFCWWarnInfo		fcwWarnInfo;
	METMsgVisionObj			visionObjMsg;
	METMsgFusionObj			fusionObjMsg;
	METMsgDebugRecv			debugRecv;
	METMsgDebugSend			debugSend;
	METMsgRoadTarget		roadTarget;
}METOutputMsg;
#endif