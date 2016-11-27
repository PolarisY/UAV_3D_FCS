/***************************************************************
* Copyright (c) 2016, 陈登龙
* All rights reserved.
*
* 文件名称：FCToPCProtocolConvertToRealData.h
* 摘    要：用于将项目协议转换为实际值的cpp文件
*
* 当前版本：1.0
* 作    者：陈登龙
* 完成日期：2016-11-27
***************************************************************/

#include "stdafx.h"
#include "FCToPCProtocolConvertToRealData.h"


/*! @function
********************************************************************************
* 函数名   : MFAToMFADC
* 功能     : 将飞行姿态数据包转换为实际的物理值的数据包
* 参数     : mfa 待转换的协议数据包
* 返回值   : void
* 作者     : 陈登龙 南昌航空大学信息工程学院自动控制系
* 日期     : 2016-11-27
*******************************************************************************/
void MFADC::MFAToMFADC(const MFA& mfa)
{
	m_MessageHeader = mfa.m_MessageHeader;
	m_TimeBootMs = (double)mfa.m_TimeBootMs;
	m_Roll = (double)mfa.m_Roll;
	m_Pitch = (double)mfa.m_Pitch;
	m_Yaw = (double)mfa.m_Yaw;
	m_RollSpeed = (double)mfa.m_RollSpeed;
	m_PitchSpeed = (double)mfa.m_PitchSpeed;
	m_YawSpeed = (double)mfa.m_YawSpeed;
	m_LowCheckSum = mfa.m_LowCheckSum;
	m_HighCheckSum = mfa.m_HighCheckSum;
}