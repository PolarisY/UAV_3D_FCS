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


#include "ascs/ext/client.h"
using namespace ascs;
using namespace ascs::ext;



/*! @class
********************************************************************************
* ������   : CTcpClient
* ����     : CTcpClient�ṩ����Asio(Non-Boost)��ȫ�첽�Ӷ��̵߳�����ͨ�Žӿڡ�
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
	* ����     : MyConnector�ǻ���Asio��connector��չ��tcp-socket��
				 ��Ϊ���ʹ���tcp::client_base<MyConnector> m_client��
				 ��Ϊ����Ŀ��ͨ�ſͻ��˶���
	* ����     : �µ��� �ϲ����մ�ѧ��Ϣ����ѧԺ�Զ�����ϵ
	* ��ǰ�汾 ��1.0
	* ��    �� ���µ���
	* ������� ��2016-10-16
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
				//�Զ��崦�����ݰ���
				return true;
			} 
	};

private: 

	/* TCP�ͻ��˷���� */
	service_pump m_pump;

	/* TCPͨ�ŵĿͻ��˶��� */
	tcp::client_base<MyConnector> m_client;
};

