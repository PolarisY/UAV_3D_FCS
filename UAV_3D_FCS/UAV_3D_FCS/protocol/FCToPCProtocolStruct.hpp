/***************************************************************
* Copyright (c) 2016, �µ���
* All rights reserved.
*
* �ļ����ƣ�FCToPCProtocolStruct.hpp
* ժ    Ҫ������Ŀ��Э���ļ�
*
* ��ǰ�汾��1.0
* ��    �ߣ��µ���
* ������ڣ�2016-11-25
***************************************************************/
#pragma once

#include <boost/cstdint.hpp>

#include "../kapok/Kapok.hpp" 


/*! @struct
********************************************************************************
<PRE>
������   : BaseData
����	 : BaseData�Ƕ�ӦЭ��Ļ���ṹ��  
����     : �µ��� �ϲ����մ�ѧ��Ϣ����ѧԺ�Զ�����ϵ
ʱ��     : 2016-11-25 22:00:00
</PRE> 
*******************************************************************************/
struct BaseData
{
	virtual ~BaseData(){}
};

/*! @struct
********************************************************************************
<PRE>
������   : MessageHeader
����	 : MessageHeader�Ƕ�ӦЭ�����Ϣͷ�ṹ�� 
����     : �µ��� �ϲ����մ�ѧ��Ϣ����ѧԺ�Զ�����ϵ
ʱ��     : 2016-11-25 22:00:00
</PRE>
*******************************************************************************/
struct MessageHeader
{
	boost::uint8_t StartSign;
	boost::uint8_t PayloadLength;
	boost::uint8_t SequenceNumber;
	boost::uint8_t SystemID;
	boost::uint8_t ComponentID;
	boost::uint8_t MessageID;

	/*���л�*/
	META(StartSign, PayloadLength, SequenceNumber, SystemID, ComponentID, MessageID)
};


/*! @struct
********************************************************************************
<PRE>
������   : MavlinkFlightAttitude
����	 : MavlinkFlightAttitude�Ƕ�ӦЭ��ķ�����̬���ݽṹ�� 
����     : �µ��� �ϲ����մ�ѧ��Ϣ����ѧԺ�Զ�����ϵ
ʱ��     : 2016-11-25 22:00:00
</PRE>
*******************************************************************************/
struct MavlinkFlightAttitude
{
	boost::uint32_t m_TimeBootMs;	/*< Timestamp (milliseconds since system boot) �Դ�ϵͳ�����󾭹���ʱ��ms*/
	boost::int32_t m_Roll;			/*< Roll angle (rad, -pi..+pi) ������*/
	boost::int32_t m_Pitch;			/*< Pitch angle (rad, -pi..+pi) ������*/
	boost::int32_t m_Yaw;			/*< Yaw angle (rad, -pi..+pi) ƫ����*/
	boost::int32_t m_RollSpeed;		/*< Roll angular speed (rad/s) �������ٶ�*/
	boost::int32_t m_PitchSpeed;	/*< Pitch angular speed (rad/s) �������ٶ�*/
	boost::int32_t m_YawSpeed;		/*< Yaw angular speed (rad/s) ƫ�����ٶ�*/

	META(m_TimeBootMs, m_Roll, m_Pitch, m_Yaw, m_RollSpeed, m_PitchSpeed, m_YawSpeed)
};

/*! @struct
********************************************************************************
<PRE>
������   : MavlinkRawImu
����	 : MavlinkRawImu�Ƕ�ӦЭ���ԭ�����������ݽṹ�� 
����     : �µ��� �ϲ����մ�ѧ��Ϣ����ѧԺ�Զ�����ϵ
ʱ��     : 2016-11-25 22:00:00
</PRE>
*******************************************************************************/
struct MavlinkRawImu
{
	boost::uint64_t m_TimeUsec;  /*< Timestamp (microseconds since UNIX epoch or microseconds since system boot) �Դ�ϵͳ�����󾭹���ʱ��ms*/
	boost::int16_t m_Xacc;		 /*< X acceleration (raw) X����ٶ�*/
	boost::int16_t m_Yacc;		 /*< Y acceleration (raw) Y����ٶ�*/
	boost::int16_t m_Zacc;	     /*< Z acceleration (raw) Z����ٶ�*/
	boost::int16_t m_Xgyro;		 /*< Angular speed around X axis (raw) Χ��X��Ľ��ٶ�(millirad /sec)*/
	boost::int16_t m_Ygyro;		 /*< Angular speed around Y axis (raw) Χ��Y��Ľ��ٶ�(millirad /sec)*/
	boost::int16_t m_Zgyro;		 /*< Angular speed around Z axis (raw) Χ��Z��Ľ��ٶ�(millirad /sec)*/
	boost::int16_t m_Xmag;		 /*< X Magnetic field (raw) X�ų�*/
	boost::int16_t m_Ymag;		 /*< Y Magnetic field (raw) Y�ų�*/
	boost::int16_t m_Zmag;		 /*< Z Magnetic field (raw) Z�ų�*/

	META(m_TimeUsec, m_Xacc, m_Yacc, m_Zacc, m_Xgyro, m_Ygyro, m_Zgyro, m_Xmag, m_Ymag, m_Zmag)
};


/*! @struct
********************************************************************************
<PRE>
������   : MavlinkAttitudeTarget
����	 : MavlinkAttitudeTarget�Ƕ�ӦЭ��ķ�����̬Ŀ�����ݽṹ�� 
����     : �µ��� �ϲ����մ�ѧ��Ϣ����ѧԺ�Զ�����ϵ
ʱ��     : 2016-11-25 22:00:00
</PRE>
*******************************************************************************/
struct MavlinkAttitudeTarget
{
	boost::uint32_t m_TimeBootMs;		/*< Timestamp in milliseconds since system boot �Դ�ϵͳ�����󾭹���ʱ��ms*/
	boost::int32_t m_Q[4];				/*< Attitude quaternion (w, x, y, z order, zero-rotation is 1, 0, 0, 0) ������̬��Ԫ��*/
	boost::int32_t m_BodyRollRate;		/*< Body roll rate in radians per second ���������ʣ���λΪ����/��*/
	boost::int32_t m_BodyPitchRate;		/*< Body roll rate in radians per second ���������ʣ���λΪ����/��*/
	boost::int32_t m_BodyYawRate;		/*< Body roll rate in radians per second ƫ�������ʣ���λΪ����/��*/
	boost::int32_t m_Thrust;			/*< Collective thrust, normalized to 0 .. 1 (-1 .. 1 for vehicles capable of reverse trust) ��������*/
	boost::uint8_t m_TypeMask;			/*< Mappings: If any of these bits are set, the corresponding input should be ignored: bit 1: body roll rate, bit 2: body pitch rate, bit 3: body yaw rate. bit 4-bit 7: reserved, bit 8: attitude*/

	META(m_TimeBootMs, m_Q, m_BodyRollRate, m_BodyPitchRate, m_BodyYawRate, m_Thrust, m_TypeMask)
};


/*! @struct
********************************************************************************
<PRE>
������   : CheckSum
����	 : CheckSum�Ƕ�ӦЭ���У������ݽṹ�� 
����     : �µ��� �ϲ����մ�ѧ��Ϣ����ѧԺ�Զ�����ϵ
ʱ��     : 2016-11-25 22:00:00
</PRE>
*******************************************************************************/
struct CheckSum
{
	boost::uint8_t LowCheckSum;
	boost::uint8_t HighCheckSum;
	/*���л�*/
	META(LowCheckSum, HighCheckSum)
};

/*! @struct
********************************************************************************
<PRE>
������   : MFA
����	 : MFA�Ƕ�ӦЭ��ķ�����̬���ݰ�
����     : �µ��� �ϲ����մ�ѧ��Ϣ����ѧԺ�Զ�����ϵ
ʱ��     : 2016-11-25 22:00:00
</PRE>
*******************************************************************************/
struct MFA : public BaseData
{
	/*��Ϣͷ*/
	MessageHeader  m_MessageHeader;

	/*������̬����*/ 
	MavlinkFlightAttitude m_MavlinkFlightAttitude;

	/*У���*/
	CheckSum	   m_CheckSum;

	/*���л�*/
	META(m_MessageHeader, m_MavlinkFlightAttitude, m_CheckSum)
};

/*! @struct
********************************************************************************
<PRE>
������   : MRI
����	 : MRI�Ƕ�ӦЭ���ԭ�����������ݰ�
����     : �µ��� �ϲ����մ�ѧ��Ϣ����ѧԺ�Զ�����ϵ
ʱ��     : 2016-11-25 22:00:00
</PRE>
*******************************************************************************/
struct MRI : public BaseData
{
	/*��Ϣͷ*/
	MessageHeader  m_MessageHeader;

	/*����ԭ������������*/
	MavlinkRawImu m_MavlinkRawImu;

	/*У���*/
	CheckSum	   m_CheckSum;

	/*���л�*/
	META(m_MessageHeader, m_MavlinkRawImu, m_CheckSum)
};

/*! @struct
********************************************************************************
<PRE>
������   : MAT
����	 : MAT�Ƕ�ӦЭ��ķ�����̬Ŀ�����ݰ�
����     : �µ��� �ϲ����մ�ѧ��Ϣ����ѧԺ�Զ�����ϵ
ʱ��     : 2016-11-25 22:00:00
</PRE>
*******************************************************************************/
struct MAT : public BaseData
{
	/*��Ϣͷ*/
	MessageHeader  m_MessageHeader;

	/*������̬Ŀ������*/
	MavlinkAttitudeTarget m_MavlinkAttitudeTarget;

	/*У���*/
	CheckSum	   m_CheckSum;

	/*���л�*/
	META(m_MessageHeader, m_MavlinkAttitudeTarget, m_CheckSum)
};



























