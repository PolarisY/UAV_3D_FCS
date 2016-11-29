/***************************************************************
* Copyright (c) 2016, �µ���
* All rights reserved.
*
* �ļ����ƣ�FCToPCProtocolConvertToRealData.h
* ժ    Ҫ�����ڽ���ĿЭ��ת��Ϊʵ��ֵ���ļ�
*
* ��ǰ�汾��1.0
* ��    �ߣ��µ���
* ������ڣ�2016-11-27
***************************************************************/
#pragma once


#include "FCToPCProtocolStruct.hpp"


struct BaseDataDC
{
	virtual ~BaseDataDC(){}
}; 

struct MFADC : public BaseDataDC
{
	/*��Ϣͷ*/
	MessageHeader  m_MessageHeader;

	double m_TimeBootMs;	/*< Timestamp (milliseconds since system boot) �Դ�ϵͳ�����󾭹���ʱ��ms*/
	double m_Roll;			/*< Roll angle (rad, -pi..+pi) ������*/
	double m_Pitch;			/*< Pitch angle (rad, -pi..+pi) ������*/
	double m_Yaw;			/*< Yaw angle (rad, -pi..+pi) ƫ����*/
	double m_RollSpeed;		/*< Roll angular speed (rad/s) �������ٶ�*/
	double m_PitchSpeed;	/*< Pitch angular speed (rad/s) �������ٶ�*/
	double m_YawSpeed;		/*< Yaw angular speed (rad/s) ƫ�����ٶ�*/

	boost::uint8_t m_LowCheckSum;	/*��λ�ֽ�У���*/
	boost::uint8_t m_HighCheckSum;	/*��λ�ֽ�У���*/

	void MFAToMFADC(const MFA& mfa); 
	void MFADDCToMFA(MFADC& mfadc);
};











