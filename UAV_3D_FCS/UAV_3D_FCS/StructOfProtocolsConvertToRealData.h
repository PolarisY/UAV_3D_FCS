#pragma once
/***************************************************************
* Copyright (c) 2016, �µ���
* All rights reserved.
*
* �ļ����ƣ�StructOfProtocolsConvertToRealData.h
* ժ    Ҫ��Ϊ����Ŀ�����ͨ��Э��ʵ������ֵ���ļ���
*
* ��ǰ�汾��1.0
* ��    �ߣ��µ���
* ������ڣ�2016-10-15
***************************************************************/


#include "StructOfProtocols.h"


/*! @struct
***************************************************************
* ����  : BaseRealData
* ����	: BaseRealData��ΪЭ���ṩ����ʵ������ֵ�Ľṹ�塣
* ����  : �µ��� �ϲ����մ�ѧ��Ϣ����ѧԺ�Զ�����ϵ��
* ʱ��  : 2016-10-15
***************************************************************/
struct BaseDataDC
{
	virtual ~BaseDataDC() {}
};


/*! @struct
***************************************************************
* ����  : TSPIDC
* ����	: TSPIDC��ΪЭ���ṩʵ�ʷ�����̬����ֵ�Ľṹ�塣
* ����  : �µ��� �ϲ����մ�ѧ��Ϣ����ѧԺ�Զ�����ϵ��
* ʱ��  : 2016-10-15
***************************************************************/
struct TSPIDC : public BaseDataDC
{
	MessageHeader   m_MessageHeader;     //��Ϣͷ
	boost::uint16_t m_ID = 0;              //�ɻ����  3��4
	boost::uint16_t m_DID = 0;             //Ŀ�ı��  5��6
	double m_LOTD = 0.0;                   //��ʱ����  7��8��9��10
	double m_LATD = 0.0;                   //��ʱγ��  11��12��13��14
	double m_SPH = 0.0;                    //��׼��ѹ�߶�  15��16
	double m_PRH = 0.0;                    //��ѹ�����߶�  17��18
	double m_RH = 0.0;                     //���ߵ�߶�  19��20
	double m_VS = 0.0;                     //�����  21��22
	double m_IVS = 0.0;                    //ָʾ����  23��24
	double m_TH = 0.0;                     //�溽��  25��26
	double m_ANGP = 0.0;                   //������  27��28
	double m_ANGR = 0.0;                   //�����  29��30
	double m_ANGPS = 0.0;                  //����������  31��32
	double m_ANGRS = 0.0;                  //���������  33��34

	TSPIDC& operator= (const TSPIDC& obj)
	{
		m_MessageHeader = obj.m_MessageHeader;
		m_ID = obj.m_ID;
		m_DID = obj.m_DID;
		m_LOTD = obj.m_LOTD;
		m_LATD = obj.m_LATD;
		m_SPH = obj.m_SPH;
		m_PRH = obj.m_PRH;
		m_RH = obj.m_RH;
		m_VS = obj.m_VS;
		m_IVS = obj.m_IVS;
		m_TH = obj.m_TH;
		m_ANGP = obj.m_ANGP;
		m_ANGR = obj.m_ANGR;
		m_ANGPS = obj.m_ANGPS;
		m_ANGRS = obj.m_ANGRS;

		return *this;
	}
	  

	void TSPIToTSPIDC(const TSPI& bsd, const bool isToEngUint);

private:
	void ConvertToEnglishUnits();
};




