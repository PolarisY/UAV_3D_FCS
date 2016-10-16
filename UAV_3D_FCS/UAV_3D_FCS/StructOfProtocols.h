#pragma once
/***************************************************************
* Copyright (c) 2016, �µ���
* All rights reserved.
*
* �ļ����ƣ�StructOfProtocols.h
* ժ    Ҫ��Ϊ����Ŀ�����ͨ��Э�顣
*
* ��ǰ�汾��1.0
* ��    �ߣ��µ���
* ������ڣ�2016-10-15
***************************************************************/

#include "kapok/Kapok.hpp"
//#include "UAV/cstdint.hpp"

namespace UAV { 
	typedef			 char      int8_t;
	typedef unsigned char      uint8_t;
	typedef			 short     int16_t;
	typedef unsigned short     uint16_t;
	typedef			 int       int32_t;
	typedef	unsigned int       uint32_t;
}



/*! @struct
*************************************************************** 
* ����  : BaseData
* ����	: BaseData��ΪЭ���ṩ����Ľṹ�塣
* ����  : �µ��� �ϲ����մ�ѧ��Ϣ����ѧԺ�Զ�����ϵ��
* ʱ��  : 2016-10-15
***************************************************************/
struct BaseData 
{
	virtual ~BaseData() {};
};

/*! @struct
***************************************************************
* ����  : MessageHeader
* ����	: MessageHeader��ΪЭ���ṩ��Ϣͷ�Ľṹ�塣
* ����  : �µ��� �ϲ����մ�ѧ��Ϣ����ѧԺ�Զ�����ϵ��
* ʱ��  : 2016-10-15
***************************************************************/
struct MessageHeader
{
	UAV::uint16_t MESSAGE_CODE = 0;         //��Ϣ���룺3002
	UAV::uint16_t MSG_Length = 0;           //���ĳ���
	UAV::uint16_t MESSAGE_COUNTER = 0;      //����
	UAV::uint16_t LogicSendID = 0;          //�����豸ID�����ܷ�������ȡֵ501
	UAV::uint16_t LogicReceID = 0;          //�շ��豸ID������Ӧ��ϵͳ��ȡֵ401
	UAV::uint8_t  MESSAGE_LENGTH = 0;       //��Ϣ�峤��
	UAV::uint16_t MESSAGE_NUMBER = 0;       //����
	UAV::uint8_t  COMM_SOURCE_ADDR = 0;     //����ƽ̨��ַ���ɻ���ţ�
	UAV::uint8_t  COMM_TARGET_ADDR = 0;     //����ƽ̨��ַ
	UAV::uint8_t  date = 0;                 //�Ƿ����������
	UAV::uint8_t  hour = 0;                 //24Сʱ�Ƶ�ʱ
	UAV::uint8_t  minute = 0;               //��
	UAV::uint8_t  second = 0;               //��
	UAV::uint16_t millSecond = 0;           //����
	UAV::uint16_t PID = 0;                  //�ɻ����

	META(MESSAGE_CODE, MSG_Length, MESSAGE_COUNTER, LogicSendID,
		LogicReceID, MESSAGE_LENGTH, MESSAGE_NUMBER,
		COMM_SOURCE_ADDR, COMM_TARGET_ADDR,
		date, hour, minute, second, millSecond,
		PID)

		MessageHeader& operator=(const MessageHeader&obj)
	{
		MESSAGE_CODE = obj.MESSAGE_CODE;
		MSG_Length = obj.MSG_Length;
		MESSAGE_COUNTER = obj.MESSAGE_COUNTER;
		LogicSendID = obj.LogicSendID;
		LogicReceID = obj.LogicReceID;
		MESSAGE_LENGTH = obj.MESSAGE_LENGTH;
		MESSAGE_NUMBER = obj.MESSAGE_NUMBER;
		COMM_SOURCE_ADDR = obj.COMM_SOURCE_ADDR;
		COMM_TARGET_ADDR = obj.COMM_TARGET_ADDR;
		date = obj.date;
		hour = obj.hour;
		minute = obj.minute;
		second = obj.second;
		millSecond = obj.millSecond;
		PID = obj.PID;

		return *this;
	}

	bool operator!=(const MessageHeader&obj)
	{
		if ((date != obj.date) || (hour != obj.hour) || (minute != obj.minute) ||
			(second != obj.second) || (millSecond != obj.millSecond))
			return true;
		else
			return false;
	}
};


/*! @struct
***************************************************************
* ����  : TSPI
* ����	: TSPI�Ƕ������˻�������̬��Э�����ݵĽṹ�塣
* ����  : �µ��� �ϲ����մ�ѧ��Ϣ����ѧԺ�Զ�����ϵ��
* ʱ��  : 2016-10-15
* ��ע  : ���˻�Э����Ҫ������
***************************************************************/
struct TSPI : public BaseData
{
	MessageHeader   m_MessageHeader;     //��Ϣͷ
	UAV::uint16_t m_ID = 0;            //�ɻ����  3��4
	UAV::uint16_t m_DID = 0;           //Ŀ�ı��  5��6
	UAV::uint16_t m_LLOTD = 0;         //��ʱ���ȵ�λ  7��8
	UAV::uint16_t m_HLOTD = 0;         //��ʱ���ȸ�λ  9��10
	UAV::uint16_t m_LLATD = 0;         //��ʱγ�ȵ�λ  11��12
	UAV::uint16_t m_HLATD = 0;         //��ʱγ�ȸ�λ  13��14
	UAV::int16_t m_SPH = 0;            //��׼��ѹ�߶�  15��16
	UAV::int16_t m_PRH = 0;            //��ѹ�����߶�  17��18
	UAV::int16_t m_RH = 0;             //���ߵ�߶�  19��20
	UAV::int16_t m_VS = 0;             //�����  21��22
	UAV::int16_t m_IVS = 0;            //ָʾ����  23��24
	UAV::int16_t m_TH = 0;             //�溽��  25��26
	UAV::int16_t m_ANGP = 0;           //������  27��28
	UAV::int16_t m_ANGR = 0;           //�����  29��30
	UAV::int16_t m_ANGPS = 0;          //����������  31��32
	UAV::int16_t m_ANGRS = 0;          //���������  33��34

	META(m_MessageHeader, m_ID, m_DID, m_LLOTD, m_HLOTD,
		m_LLATD, m_HLATD, m_SPH, m_PRH,
		m_RH, m_VS, m_IVS, m_TH,
		m_ANGP, m_ANGR, m_ANGPS, m_ANGRS)

		TSPI& operator= (const TSPI& obj)
	{
		m_MessageHeader = obj.m_MessageHeader;
		m_ID = obj.m_ID;
		m_DID = obj.m_DID;
		m_LLOTD = obj.m_LLOTD;
		m_HLOTD = obj.m_HLOTD;
		m_LLATD = obj.m_LLATD;
		m_HLATD = obj.m_HLATD;
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
};

/*! @struct
***************************************************************
* ����  : ProtocolData
* ����	: ProtocolData�Ƕ������˻�����������̬��Э�����ݵĽṹ�塣
* ����  : �µ��� �ϲ����մ�ѧ��Ϣ����ѧԺ�Զ�����ϵ��
* ʱ��  : 2016-10-15
* ��ע  : ���˻�Э����Ҫ������
***************************************************************/
struct ProtocolData
{ 
	TSPI m_TSPI;

	ProtocolData& operator=(const ProtocolData& obj)
	{
		m_TSPI = obj.m_TSPI; 
	} 

	META(m_TSPI)
};
