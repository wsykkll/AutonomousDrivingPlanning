/************************************************************************/
/*
Date:			2016/01/04
Author:			Shengyan Zhou
Compile Mode:	C (Static Library)
Function:		load & analyze off-line data to process
*/
/************************************************************************/
#ifndef MET_CAM_H
#define MET_CAM_H

/************************************************************************/
/* include file                                                         */
/************************************************************************/
#include "MET_DataStructure.h"


#ifdef __cplusplus
extern "C"
{
#endif
	/************************************************************************/
	/* Header File                                                          */
	/************************************************************************/
	//////////////////////////////////////////////////////////////////////////
	void met_cam_InitCamera( MET_CamParams* camera, METCamConfig *camConfig);
	/// Return 0:sucess. 1:false  ////////////////////////////////////////////
	char met_cam_InitCameraIntMatrix( MET_CamParams* camera );
	/// Return 0:sucess. 1:false  ////////////////////////////////////////////
	char met_cam_InitCameraExtMatrix( MET_CamParams* camera );
	/// W2I: world to image///////////////////////////////////////////////////
	void met_cam_ProjectW2I( MET_CamParams* camera, float x, float y, float z, float* pixelx, float* pixely );
	/// G2I: ground to image//////////////////////////////////////////////////
	void met_cam_ProjectG2I( MET_CamParams* camera, float x, float y, float* pixelx, float* pixely );
	/// I2G: image to ground//////////////////////////////////////////////////
	void met_cam_ProjectI2G( MET_CamParams* camera, float pX, float pY, float* wX, float* wY );
	/// GWW2IW: ground world width to image width ////////////////////////////
	float met_cam_ProjectGWW2IW( MET_CamParams* camera, float distance, float width );
	/// IWGW2G: ground world width and image width to ground /////////////////
	void met_cam_ProjectIWGW2G( MET_CamParams* camera, float pwidth, float gwidth, float px, float* wX, float* wY );
	/// GWW2IW: ground world width to image width ////////////////////////////
	void met_cam_ProjectIL2GL( MET_CamParams* camera, float i_slope, float i_intercept, float *w_slope, float *w_intercept );
	/// IW2GWW: ground world width to image width ////////////////////////////
	void met_cam_ProjectGL2IL( MET_CamParams* camera, float w_slope, float w_intercept, float *i_slope, float *i_intercept );
	/// undistortion /////////////////////////////////////////////////////////
	void met_cam_Undistortion( MET_CamParams* camera, float px, float py, float *outpx, float* outpy );
	/************************************************************************/
	/*   
	w_minw:��С������			w_maxw:���������
	roadminslope:��·������¶�	roadmaxslope:��·������¶�
	carminpitch:������С������	carmaxpitch:�����������
	maxleft_w:������������	maxright_w:���ұ��������
	w_h:Ŀ������߶�			p_w:Ŀ�����ؿ��			roi:ROI���     */
	/************************************************************************/
	float met_cam_ROIprojection( MET_CamParams* camera, 
		float w_minw, float w_maxw, 
		float roadminslope, float roadmaxslope,
		float carminpitch, float carmaxpitch,
		float maxleft_w, float maxright_w,
		float obj_w_h, float obj_p_w,
		METRect* roi );

#ifdef __cplusplus
};
#endif
#endif