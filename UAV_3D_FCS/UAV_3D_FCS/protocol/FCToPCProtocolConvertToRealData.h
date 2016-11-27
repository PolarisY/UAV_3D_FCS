/***************************************************************
* Copyright (c) 2016, 陈登龙
* All rights reserved.
*
* 文件名称：FCToPCProtocolConvertToRealData.h
* 摘    要：用于将项目协议转换为实际值的文件
*
* 当前版本：1.0
* 作    者：陈登龙
* 完成日期：2016-11-27
***************************************************************/
#pragma once


#include "FCToPCProtocolStruct.hpp"


struct BaseDataDC
{
	virtual ~BaseDataDC(){}
}; 

struct MFADC : public BaseDataDC
{
	/*消息头*/
	MessageHeader  m_MessageHeader;

	double m_TimeBootMs;	/*< Timestamp (milliseconds since system boot) 自从系统启动后经过的时间ms*/
	double m_Roll;			/*< Roll angle (rad, -pi..+pi) 滚动角*/
	double m_Pitch;			/*< Pitch angle (rad, -pi..+pi) 俯仰角*/
	double m_Yaw;			/*< Yaw angle (rad, -pi..+pi) 偏航角*/
	double m_RollSpeed;		/*< Roll angular speed (rad/s) 滚动角速度*/
	double m_PitchSpeed;	/*< Pitch angular speed (rad/s) 俯仰角速度*/
	double m_YawSpeed;		/*< Yaw angular speed (rad/s) 偏航角速度*/

	boost::uint8_t m_LowCheckSum;	/*低位字节校验和*/
	boost::uint8_t m_HighCheckSum;	/*高位字节校验和*/

	void MFAToMFADC(const MFA& mfa);
};











