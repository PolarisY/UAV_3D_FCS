/***************************************************************
* Copyright (c) 2016, �µ���
* All rights reserved.
*
* �ļ����ƣ�StructOfProtocolsConvertToRealData.cpp
* ժ    Ҫ��Ϊ����Ŀ�����ͨ��Э��ʵ������ֵ��ʵ���ļ���
*
* ��ǰ�汾��1.0
* ��    �ߣ��µ���
* ������ڣ�2016-10-15
***************************************************************/

#include "stdafx.h"
#include "StructOfProtocolsConvertToRealData.h"


/*! @function
************************************************************************
* ������   : TSPIToTSPIDC
* ����     : ��Э��ֵTSPIת����ʵ������ֵ
* ����     :	tspi Э��ṹ��
				isToEngUint	�Ƿ���Ҫת����Ӣ��
* ����ֵ   : void
* ����     : �µ��� �ϲ����մ�ѧ��Ϣ����ѧԺ�Զ�����ϵ
* ����     : 2016-10-15
************************************************************************/
void TSPIDC::TSPIToTSPIDC(const TSPI& tspi, const bool isToEngUint)
{
	m_MessageHeader = tspi.m_MessageHeader;       //��Ϣͷ
	m_ID = tspi.m_ID;
	m_DID = tspi.m_DID;
	m_LOTD = (double)(((boost::int32_t)tspi.m_LLOTD + (boost::int32_t)(tspi.m_HLOTD << 16)) * 90.0 / 1073741824.0);
	m_LATD = (double)(((boost::int32_t)tspi.m_LLATD + (boost::int32_t)(tspi.m_HLATD << 16)) * 45.0 / 1073741824.0);
	m_SPH = (double)tspi.m_SPH;
	m_PRH = (double)tspi.m_PRH;
	m_RH = (double)tspi.m_RH;
	m_VS = (double)tspi.m_VS / 8;
	m_IVS = (double)tspi.m_IVS / 8;
	m_TH = (double)tspi.m_TH * 90.0 / 16384.0;
	m_ANGP = (double)tspi.m_ANGP * 45.0 / 16384.0;
	m_ANGR = (double)tspi.m_ANGR * 90.0 / 16384.0;
	m_ANGPS = (double)tspi.m_ANGPS * 90.0 / 16384.0;
	m_ANGRS = (double)tspi.m_ANGRS * 180.0 / 16384.0;

	for (; !((m_TH > -0.000001) && (m_TH < 360.000001));)
	{
		m_TH = (m_TH < -0.000001) ? (m_TH + 360.00000000) : (m_TH - 360.00000000);
	}

	if (isToEngUint)
		ConvertToEnglishUnits();

}



/*! @function
************************************************************************
* ������   : ConvertToEnglishUnits
* ����     : ����Ҫת����Э��ֵTSPIת����Ӣ��
* ����     : void
* ����ֵ   : void
* ����     : �µ��� �ϲ����մ�ѧ��Ϣ����ѧԺ�Զ�����ϵ
* ����     : 2016-10-15
************************************************************************/
void TSPIDC::ConvertToEnglishUnits()
{
	m_SPH /= 0.3048;
	m_PRH /= 0.3048;
	m_RH  /= 0.3048;
	m_VS  /= 1.852;
	m_IVS /= 1.852;
}