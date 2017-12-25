#ifndef MET_ADASPARAM_H
#define MET_ADASPARAM_H

#include "MET_DataStructure.h"

/************************************************************************/
/* DataStructure Define                                                 */
/************************************************************************/
typedef struct METADASParamObj
{
	int			imgWidth;		//image size
	int			imgHeight;

	float		camHFov;		//camera hFov, unit: degree
	float		camFrameRate;	//camera frameRate, unit: frames/s 

	float		vehWidth;		//unit: m
	float		vehLength;		//unit: m

	METBeamConfig			beamConfig;
	METCamConfig			camConfig;
	METLDWConfig			ldwConfig;
	METLSConfig				lsConfig;
	METFCWConfig			fcwConfig;
	METLidarConfig			lidar1Config;
	METLidarConfig			lidar2Config;
	METCamCalibConfig		ccConfig;
}METADASParamObj;

#ifdef __cplusplus
extern "C"
{
#endif
	/************************************************************************/
	/* Function declare                                                     */
	/************************************************************************/
	unsigned char met_param_LoadADASParam(METADASParamObj *adasParam, char *  fileName);
	unsigned char met_param_SaveADASParam2File(char *  fileName, METADASParamObj *adasParam);

	unsigned char met_param_LoadADASCamParam( METCamConfig *camParam, char* fileName );
	unsigned char met_param_SaveADASCamParam( char* fileName, METCamConfig *camParam );

	void met_param_PrintfADASParam( METADASParamObj *adasParam);

	/************************************************************************/
	/* Func: init adasParam without paramFile
		Input: camMode: 0-SD(1024*512), 1-HD(1280*720)
		Output: adasParam
	*/
	/************************************************************************/
	void met_param_InitADASParambyDefault(METADASParamObj *adasParam, unsigned char camMode);

#ifdef __cplusplus
};
#endif
#endif