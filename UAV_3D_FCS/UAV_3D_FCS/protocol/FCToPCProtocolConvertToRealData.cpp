/***************************************************************
* Copyright (c) 2016, �µ���
* All rights reserved.
*
* �ļ����ƣ�FCToPCProtocolConvertToRealData.h
* ժ    Ҫ�����ڽ���ĿЭ��ת��Ϊʵ��ֵ��cpp�ļ�
*
* ��ǰ�汾��1.0
* ��    �ߣ��µ���
* ������ڣ�2016-11-27
***************************************************************/

#include "stdafx.h"
#include "FCToPCProtocolConvertToRealData.h"


/*! @function
********************************************************************************
* ������   : MFAToMFADC
* ����     : ��������̬���ݰ�ת��Ϊʵ�ʵ�����ֵ�����ݰ�
* ����     : mfa ��ת����Э�����ݰ�
* ����ֵ   : void
* ����     : �µ��� �ϲ����մ�ѧ��Ϣ����ѧԺ�Զ�����ϵ
* ����     : 2016-11-27
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


/*! @function
********************************************************************************
* ������   : MFADDCToMFA
* ����     : ��������̬�������ݰ�ת��ΪЭ������ݰ�
* ����     : mfadc ��ת����Э��w����ֵ���ݰ�
* ����ֵ   : void
* ����     : �µ��� �ϲ����մ�ѧ��Ϣ����ѧԺ�Զ�����ϵ
* ����     : 2016-11-29
*******************************************************************************/
void MFADC::MFADDCToMFA(MFADC& mfadc)
{
	m_MessageHeader = mfadc.m_MessageHeader;
	m_TimeBootMs = mfadc.m_TimeBootMs;
	m_Roll = mfadc.m_Roll;
	m_Pitch = mfadc.m_Pitch;
	m_Yaw = mfadc.m_Yaw;
	m_RollSpeed = mfadc.m_RollSpeed;
	m_PitchSpeed = mfadc.m_PitchSpeed;
	m_YawSpeed = mfadc.m_YawSpeed;
	m_LowCheckSum = mfadc.m_LowCheckSum;
	m_HighCheckSum = mfadc.m_HighCheckSum;
}