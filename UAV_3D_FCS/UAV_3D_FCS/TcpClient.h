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


#include "ascs/ext/client.h"
using namespace ascs;
using namespace ascs::ext;



/*! @class
********************************************************************************
* 类名称   : CTcpClient
* 功能     : CTcpClient提供基于Asio(Non-Boost)完全异步加多线程的网络通信接口。
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
	* 功能     : MyConnector是基于Asio的connector拓展的tcp-socket，
				 作为类型传入tcp::client_base<MyConnector> m_client，
				 作为本项目的通信客户端对象。
	* 作者     : 陈登龙 南昌航空大学信息工程学院自动控制系
	* 当前版本 ：1.0
	* 作    者 ：陈登龙
	* 完成日期 ：2016-10-16
	*******************************************************************************/
	class MyConnector : public connector
	{
		public:
			MyConnector(asio::io_service& io_service_) : connector(io_service_)
			{

			}

		protected:
			bool on_msg_handle(out_msg_type& msg, bool link_down)
			{
				//自定义处理数据包。
				return true;
			} 
	};

private: 

	/* TCP客户端服务泵 */
	service_pump m_pump;

	/* TCP通信的客户端对象 */
	tcp::client_base<MyConnector> m_client;
};

