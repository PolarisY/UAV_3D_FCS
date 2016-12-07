#pragma once
/***************************************************************
* Copyright (c) 2016, 陈登龙
* All rights reserved.
*
* 文件名称：TcpClient.h
* 摘    要：用于本项目的TCP通信类。
*
* 当前版本：1.0
* 作    者：陈登龙
* 完成日期：2016-10-16
***************************************************************/

//configuration
#define SERVER_PORT    9527
#define SERVER_IP      "127.10.10.16"
#undef MAX_MSG_NUM
#define MAX_MSG_NUM	   1500
#define FORCE_TO_USE_MSG_RECV_BUFFER  //force to use the msg recv buffer

#include <string>
#include <mutex>

#include "stdafx.h" 
#include "communication/st_asio_wrapper_base.h"
#include "communication/st_asio_wrapper_tcp_client.h"
#include "kapok/DeSerializer.hpp"


using namespace st_asio_wrapper;
extern MessageBus g_Bus;
extern std::atomic<int> g_MFAPackNum;


/*! @class
********************************************************************************
* 类名称   : CTcpClient
* 功能     : CTcpClient提供基于Boost.Asio完全异步加多线程的网络通信接口。
* 作者     : 陈登龙 南昌航空大学信息工程学院自动控制系
* 当前版本 ：1.0
* 作    者 ：陈登龙
* 完成日期 ：2016-10-16
*******************************************************************************/
class CTcpClient
{

public:
	CTcpClient();
	~CTcpClient();

public:
	/* 设置TCP的连接地址 */
	void SetConnectAddr(unsigned short port, const std::string& ip);

	/* 开启TCP连接 */
	void StartTcpConnect();

	/* 停止TCP连接 */
	void StopTcpConnect();

	/* 判断TCP当前是否已经连接 */
	bool IsTcpConnecting();

private:
	/*! @class
	********************************************************************************
	* 类名称   : MyConnector
	* 功能     : MyConnector是基于Boost.Asio的st_connector拓展的tcp-socket，
				 作为类型传入st_sclient<MyConnector> m_client,
				 作为本项目的通信客户端对象。
	* 作者     : 陈登龙 南昌航空大学信息工程学院自动控制系
	* 当前版本 ：1.0
	* 作    者 ：陈登龙
	* 完成日期 ：2016-10-17
	*******************************************************************************/
	class MyConnector : public st_connector
	{
		 
		public:
			MyConnector(boost::asio::io_service& io_service_) : st_connector(io_service_)
			{

			}

		protected:
			typedef std::string MsgType;
			/*! @function
			********************************************************************************
			* 函数名   : on_msg_handle
			* 功能     : 接收通过TCP协议发送到本终端的MAVLink数据包
			* 参数     : msg 接收到的JSON格式的数据包 
			* 返回值   : void
			* 作者     : 陈登龙 南昌航空大学信息工程学院自动控制系
			* 日期     : 2016-12-6
			*******************************************************************************/
			virtual void on_msg_handle(MsgType& msg)
			{
				AfxMessageBox(_T("on_msg_handle"));

				DeSerializer dr;
				dr.Parse(msg.c_str());

				std::lock_guard<std::mutex> locker(m_MutexSendReq);

				//反序列化数据包
				dr.Deserialize(m_MFA, "MFA");
				m_MFADC.MFAToMFADC(m_MFA);

				//将数据包发送到消息总线上 
				g_Bus.SendReq<void, const MFADC&>(m_MFADC, "MFADC");

				//通知数据库模块存储Json格式的数据包
				g_Bus.SendReq<void, const MsgType&>(msg, "AddMsgToSQL");

				//对收到的数据包计数
				g_MFAPackNum++;
			}
			 
			//virtual bool on_msg(MsgType& msg)
			//{
			//	AfxMessageBox(_T("on_msg"));
			//	return true;
			//} 

		private:
			std::mutex m_MutexSendReq;      //为了同步执行，给消息总线在SendReq时加锁

		private:
			MFA m_MFA;
			MFADC m_MFADC;
	};


private: 

	/* TCP客户端服务泵 */
	st_service_pump  m_pump;

	/* TCP通信的客户端对象 */
	st_sclient<MyConnector> m_client;
};

