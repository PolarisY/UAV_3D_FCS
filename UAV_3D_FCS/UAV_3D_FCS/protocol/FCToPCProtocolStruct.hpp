/***************************************************************
* Copyright (c) 2016, 陈登龙
* All rights reserved.
*
* 文件名称：FCToPCProtocolStruct.hpp
* 摘    要：本项目的协议文件
*
* 当前版本：1.0
* 作    者：陈登龙
* 完成日期：2016-11-25
***************************************************************/
#pragma once


#include <boost/cstdint.hpp>

#include "../kapok/Kapok.hpp" 


/*! @struct
********************************************************************************
<PRE>
类名称   : BaseData
功能	 : BaseData是对应协议的基类结构体  
作者     : 陈登龙 南昌航空大学信息工程学院自动控制系
时间     : 2016-11-25 22:00:00
</PRE> 
*******************************************************************************/
struct BaseData
{
	virtual ~BaseData(){}
};

/*! @struct
********************************************************************************
<PRE>
类名称   : MessageHeader
功能	 : MessageHeader是对应协议的消息头结构体 
作者     : 陈登龙 南昌航空大学信息工程学院自动控制系
时间     : 2016-11-25 22:00:00
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

	/*序列化*/
	META(StartSign, PayloadLength, SequenceNumber, SystemID, ComponentID, MessageID)
}; 

/*! @struct
********************************************************************************
<PRE>
类名称   : MFA
功能	 : MFA是对应协议的飞行姿态数据包
作者     : 陈登龙 南昌航空大学信息工程学院自动控制系
时间     : 2016-11-25 22:00:00
</PRE>
*******************************************************************************/
struct MFA : public BaseData
{
	/*消息头*/
	MessageHeader  m_MessageHeader;

	boost::uint32_t m_TimeBootMs;	/*< Timestamp (milliseconds since system boot) 自从系统启动后经过的时间ms*/
	boost::int32_t m_Roll;			/*< Roll angle (rad, -pi..+pi) 滚动角*/
	boost::int32_t m_Pitch;			/*< Pitch angle (rad, -pi..+pi) 俯仰角*/
	boost::int32_t m_Yaw;			/*< Yaw angle (rad, -pi..+pi) 偏航角*/
	boost::int32_t m_RollSpeed;		/*< Roll angular speed (rad/s) 滚动角速度*/
	boost::int32_t m_PitchSpeed;	/*< Pitch angular speed (rad/s) 俯仰角速度*/
	boost::int32_t m_YawSpeed;		/*< Yaw angular speed (rad/s) 偏航角速度*/
	
	boost::uint8_t m_LowCheckSum;	/*低位字节校验和*/
	boost::uint8_t m_HighCheckSum;	/*高位字节校验和*/

	/*序列化*/
	META(m_MessageHeader, m_TimeBootMs, m_Roll, m_Pitch, m_Yaw, m_RollSpeed, m_PitchSpeed, m_YawSpeed, m_LowCheckSum, m_HighCheckSum)

	void GetMsgHeaderStr(const MessageHeader &headerInfo, std::string &headerStr);
	void ConvertToHexString(std::string& str);
	template <typename T>
	bool StrHexToIntDec(T &iDec, const std::string &strHex);
	bool HexStrToAsciiStr(std::string &asciiStr, const std::string &hexStr);
};



#if 0


/*! @struct
********************************************************************************
<PRE>
类名称   : MavlinkFlightAttitude
功能	 : MavlinkFlightAttitude是对应协议的飞行姿态数据结构体 
作者     : 陈登龙 南昌航空大学信息工程学院自动控制系
时间     : 2016-11-25 22:00:00
</PRE>
*******************************************************************************/
struct MavlinkFlightAttitude
{
	boost::uint32_t m_TimeBootMs;	/*< Timestamp (milliseconds since system boot) 自从系统启动后经过的时间ms*/
	boost::int32_t m_Roll;			/*< Roll angle (rad, -pi..+pi) 滚动角*/
	boost::int32_t m_Pitch;			/*< Pitch angle (rad, -pi..+pi) 俯仰角*/
	boost::int32_t m_Yaw;			/*< Yaw angle (rad, -pi..+pi) 偏航角*/
	boost::int32_t m_RollSpeed;		/*< Roll angular speed (rad/s) 滚动角速度*/
	boost::int32_t m_PitchSpeed;	/*< Pitch angular speed (rad/s) 俯仰角速度*/
	boost::int32_t m_YawSpeed;		/*< Yaw angular speed (rad/s) 偏航角速度*/

	META(m_TimeBootMs, m_Roll, m_Pitch, m_Yaw, m_RollSpeed, m_PitchSpeed, m_YawSpeed)
};

/*! @struct
********************************************************************************
<PRE>
类名称   : MavlinkRawImu
功能	 : MavlinkRawImu是对应协议的原生传感器数据结构体 
作者     : 陈登龙 南昌航空大学信息工程学院自动控制系
时间     : 2016-11-25 22:00:00
</PRE>
*******************************************************************************/
struct MavlinkRawImu
{
	boost::uint64_t m_TimeUsec;  /*< Timestamp (microseconds since UNIX epoch or microseconds since system boot) 自从系统启动后经过的时间ms*/
	boost::int16_t m_Xacc;		 /*< X acceleration (raw) X轴加速度*/
	boost::int16_t m_Yacc;		 /*< Y acceleration (raw) Y轴加速度*/
	boost::int16_t m_Zacc;	     /*< Z acceleration (raw) Z轴加速度*/
	boost::int16_t m_Xgyro;		 /*< Angular speed around X axis (raw) 围绕X轴的角速度(millirad /sec)*/
	boost::int16_t m_Ygyro;		 /*< Angular speed around Y axis (raw) 围绕Y轴的角速度(millirad /sec)*/
	boost::int16_t m_Zgyro;		 /*< Angular speed around Z axis (raw) 围绕Z轴的角速度(millirad /sec)*/
	boost::int16_t m_Xmag;		 /*< X Magnetic field (raw) X磁场*/
	boost::int16_t m_Ymag;		 /*< Y Magnetic field (raw) Y磁场*/
	boost::int16_t m_Zmag;		 /*< Z Magnetic field (raw) Z磁场*/

	META(m_TimeUsec, m_Xacc, m_Yacc, m_Zacc, m_Xgyro, m_Ygyro, m_Zgyro, m_Xmag, m_Ymag, m_Zmag)
};



/*! @struct
********************************************************************************
<PRE>
类名称   : MavlinkAttitudeTarget
功能	 : MavlinkAttitudeTarget是对应协议的飞行姿态目标数据结构体 
作者     : 陈登龙 南昌航空大学信息工程学院自动控制系
时间     : 2016-11-25 22:00:00
</PRE>
*******************************************************************************/
struct MavlinkAttitudeTarget
{
	boost::uint32_t m_TimeBootMs;		/*< Timestamp in milliseconds since system boot 自从系统启动后经过的时间ms*/
	boost::int32_t m_Q[4];				/*< Attitude quaternion (w, x, y, z order, zero-rotation is 1, 0, 0, 0) 飞行姿态四元组*/
	boost::int32_t m_BodyRollRate;		/*< Body roll rate in radians per second 滚动侧倾率，单位为弧度/秒*/
	boost::int32_t m_BodyPitchRate;		/*< Body roll rate in radians per second 俯仰侧倾率，单位为弧度/秒*/
	boost::int32_t m_BodyYawRate;		/*< Body roll rate in radians per second 偏航侧倾率，单位为弧度/秒*/
	boost::int32_t m_Thrust;			/*< Collective thrust, normalized to 0 .. 1 (-1 .. 1 for vehicles capable of reverse trust) 集体推力*/
	boost::uint8_t m_TypeMask;			/*< Mappings: If any of these bits are set, the corresponding input should be ignored: bit 1: body roll rate, bit 2: body pitch rate, bit 3: body yaw rate. bit 4-bit 7: reserved, bit 8: attitude*/

	META(m_TimeBootMs, m_Q, m_BodyRollRate, m_BodyPitchRate, m_BodyYawRate, m_Thrust, m_TypeMask)
};


/*! @struct
********************************************************************************
<PRE>
类名称   : CheckSum
功能	 : CheckSum是对应协议的校验和数据结构体 
作者     : 陈登龙 南昌航空大学信息工程学院自动控制系
时间     : 2016-11-25 22:00:00
</PRE>
*******************************************************************************/
struct CheckSum
{
	boost::uint8_t LowCheckSum;
	boost::uint8_t HighCheckSum;
	/*序列化*/
	META(LowCheckSum, HighCheckSum)
};


/*! @struct
********************************************************************************
<PRE>
类名称   : MRI
功能	 : MRI是对应协议的原生传感器数据包
作者     : 陈登龙 南昌航空大学信息工程学院自动控制系
时间     : 2016-11-25 22:00:00
</PRE>
*******************************************************************************/
struct MRI : public BaseData
{
	/*消息头*/
	MessageHeader  m_MessageHeader;

	/*飞行原生传感器数据*/
	MavlinkRawImu m_MavlinkRawImu;

	/*校验和*/
	CheckSum	   m_CheckSum;

	/*序列化*/
	META(m_MessageHeader, m_MavlinkRawImu, m_CheckSum)
};

/*! @struct
********************************************************************************
<PRE>
类名称   : MAT
功能	 : MAT是对应协议的飞行姿态目标数据包
作者     : 陈登龙 南昌航空大学信息工程学院自动控制系
时间     : 2016-11-25 22:00:00
</PRE>
*******************************************************************************/
struct MAT : public BaseData
{
	/*消息头*/
	MessageHeader  m_MessageHeader;

	/*飞行姿态目标数据*/
	MavlinkAttitudeTarget m_MavlinkAttitudeTarget;

	/*校验和*/
	CheckSum	   m_CheckSum;

	/*序列化*/
	META(m_MessageHeader, m_MavlinkAttitudeTarget, m_CheckSum)
};

#endif

























