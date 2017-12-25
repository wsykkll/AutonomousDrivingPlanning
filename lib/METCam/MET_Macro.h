/************************************************************************/
/*
Date:			2015/12/21
Author:			Chunlan Ye
Compile Mode:	C
Function:		basic macro define
*/
/************************************************************************/

#ifndef MET_MACRO_H
#define MET_MACRO_H

#include <stdlib.h>
/************************************************************************/
/* Basic math common parameter define                                   */
/************************************************************************/
#ifndef PI
#define PI			3.1415926
#endif

#ifndef MET_EPS
#define MET_EPS			0.00015f
#endif


/************************************************************************/
/* Basic image Info define                                              */
/************************************************************************/
#define MET_CAMERA_MODE_SD		0	/*Standard Camera*/
#define MET_CAMERA_MODE_HD		1	/*HD Camera */

//Raw image size
#define MET_RAW_IMG_WIDTH	1024	/*unit: pixel*/
#define MET_RAW_IMG_HEIGHT	512		/*unit: pixel*/

#define MET_RAW_HD_IMG_WIDTH	1280	/*unit: pixel*/
#define MET_RAW_HD_IMG_HEIGHT	720		/*unit: pixel*/

#define MET_MAX_RADIUS_LENGTH				900
#define MET_IMG_PYRAMID_LEVEL_MAX_NUM		30

/************************************************************************/
/* Basic camera setting define                                          */
/************************************************************************/
//Frame Rate
#define MET_FRAME_TIME	33.0f		//unit: ms/frame

/*****************FrameHeader define********************/
//VersionID
#define MET_FRAMEHEADER_VERSION_0	0	/*image date captured before 2015-12-21, image size: 1024*515 */
#define MET_FRAMEHEADER_VERSION_1	1	/*initVersion with melexis camera + delphi radar + vehicle Info + sampleObj*/

//sample number
#define MET_FRAMERECTS_NUM_MAX		256	/*unit: ea, used for data captured before 2015-12-21*/
#define MET_SAMPLEOBJ_MAXCOUNT		128 /*unit: ea, used for sample calibration & recording*/

/************************************************************************/
/*	BEAM Relative Info						                            */
/************************************************************************/
#define MET_BEAMMODE_CLOSE		0	/*low beam off, high beam off*/
#define MET_BEAMMODE_READY		1	/*low beam on, high beam off, Feature Ready*/
#define MET_BEAMMODE_WORK		2	/*low beam on, high beam adaptive*/

#define MET_BEAMFUNC_TGM		1		/*ADB: TiGuan Motor*/
#define MET_BEAMFUNC_IHC		2		/* AHS, IHC */
#define MET_BEAMFUNC_ADB		3		/* ADB - 6 no glare regions*/

/************************************************************************/
/* Basic LIDAR Info define                                              */
/************************************************************************/

/*** Lidar type ***/
#define MET_LIDARTYPE_M8QUANERGY		0	/*Quanergy M8*/

/************************************************************************/
/* FCW Mode                                                             */
/************************************************************************/
#define MET_FCWMODE_NIGHT			0
#define MET_FCWMODE_DUSK			1
#define MET_FCWMODE_CLOUDY			2
#define MET_FCWMODE_SUNNY			3
#define MET_FCWMODE_STRONGSUNNY		4

/************************************************************************/
/* Sample Label                                                         */
/************************************************************************/
#define MET_LANLINE_MAX_INNEROBJNUM 256
#define MET_MAX_OBJNUM				256

/************************************************************************/
/* Warn                                                                 */
/************************************************************************/
#define MET_WARN_KEEP_CNT			5

/************************************************************************/
/* Macro function define                                                */
/************************************************************************/
#ifndef MIN
#define MIN(a,b)  ((a) > (b) ? (b) : (a))
#endif

#ifndef MAX
#define MAX(a,b)  ((a) < (b) ? (b) : (a))
#endif

#ifndef ABS
#define ABS(a)	  ((a) < 0 ? 0-(a):(a))
#endif

#ifndef PROTECTVAL // keep x in [minVal, maxVal]
#define PROTECTVAL(x, minVal, maxVal)	((x) < (minVal) ? (minVal) : ((x) > (maxVal) ? (maxVal) : (x)))
#endif

#endif