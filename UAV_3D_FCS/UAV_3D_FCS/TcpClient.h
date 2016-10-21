#pragma once
/***************************************************************
* Copyright (c) 2016, �µ���
* All rights reserved.
*
* �ļ����ƣ�TcpClient.h
* ժ    Ҫ�����ڱ���Ŀ��TCPͨ���ࡣ
*
* ��ǰ�汾��1.0
* ��    �ߣ��µ���
* ������ڣ�2016-10-16
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
* ������   : CTcpClient
* ����     : CTcpClient�ṩ����Boost.Asio��ȫ�첽�Ӷ��̵߳�����ͨ�Žӿڡ�
* ����     : �µ��� �ϲ����մ�ѧ��Ϣ����ѧԺ�Զ�����ϵ
* ��ǰ�汾 ��1.0
* ��    �� ���µ���
* ������� ��2016-10-16
*******************************************************************************/
class CTcpClient
{

public:
	CTcpClient();
	~CTcpClient();

public:
	/* ����TCP�����ӵ�ַ */
	void SetConnectAddr(unsigned short port, const std::string& ip);

	/* ����TCP���� */
	void StartTcpConnect();

	/* ֹͣTCP���� */
	void StopTcpConnect();

	/* �ж�TCP��ǰ�Ƿ��Ѿ����� */
	bool IsTcpConnecting();

private:
	/*! @class
	********************************************************************************
	* ������   : MyConnector
	* ����     : MyConnector�ǻ���Boost.Asio��st_connector��չ��tcp-socket��
				 ��Ϊ���ʹ���st_sclient<MyConnector> m_client,
				 ��Ϊ����Ŀ��ͨ�ſͻ��˶���
	* ����     : �µ��� �ϲ����մ�ѧ��Ϣ����ѧԺ�Զ�����ϵ
	* ��ǰ�汾 ��1.0
	* ��    �� ���µ���
	* ������� ��2016-10-17
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
				//�Զ��崦�����ݰ���
				AfxMessageBox(_T("on_msg_handle->rec msg!"));
			}  
	};

private: 

	/* TCP�ͻ��˷���� */
	st_service_pump  m_pump;

	/* TCPͨ�ŵĿͻ��˶��� */
	st_sclient<MyConnector> m_client;
};

#undef FORCE_TO_USE_MSG_RECV_BUFFER