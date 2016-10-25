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

#include "stdafx.h"
#include "communication/st_asio_wrapper_base.h"
#include "communication/st_asio_wrapper_tcp_client.h"

#undef  MAX_MSG_NUM
#define MAX_MSG_NUM	   1500
#define FORCE_TO_USE_MSG_RECV_BUFFER  //force to use the msg recv buffer

using namespace st_asio_wrapper;



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
				 作为本项目的TCP通信客户端对象。
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

			void on_msg_handle(MsgType& msg)
			{
				//自定义处理数据包。
				AfxMessageBox(_T("on_msg_handle->rec msg!"));
			}  
	};

private: 

	/* TCP客户端服务泵 */
	st_service_pump  m_pump;

	/* TCP通信的客户端对象 */
	st_sclient<MyConnector> m_client;
};

#undef FORCE_TO_USE_MSG_RECV_BUFFER