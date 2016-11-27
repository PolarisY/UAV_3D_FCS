#pragma once
/***************************************************************
* Copyright (c) 2016, �µ���
* All rights reserved.
*
* �ļ����ƣ�UdpClient.h
* ժ    Ҫ�����ڱ���Ŀ��UDPͨ���ࡣ
*
* ��ǰ�汾��1.0
* ��    �ߣ��µ���
* ������ڣ�2016-10-25
***************************************************************/

#include "communication/st_asio_wrapper_base.h"
#include "communication/st_asio_wrapper_udp_socket.h"
#include "communication/st_asio_wrapper_udp_client.h"
#include "communication/st_asio_wrapper_client.h"

using namespace st_asio_wrapper;


/*! @class
********************************************************************************
* ������   : CUdpClient
* ����     : CUdpClient�ṩ����Boost.Asio��ȫ�첽�Ӷ��̵߳�����ͨ�Žӿڡ�
* ����     : �µ��� �ϲ����մ�ѧ��Ϣ����ѧԺ�Զ�����ϵ
* ��ǰ�汾 ��1.0
* ��    �� ���µ���
* ������� ��2016-10-16
*******************************************************************************/
class CUdpClient
{
public:
	CUdpClient();
	~CUdpClient();

public:
	/* ����UDP���� */
	void StartUdpConnect();

	/* �Ͽ�UDP���� */
	void StopUdpConnect();
	
	/* ����UDP�ı��ض˿� */
	void SetLocalPort(const unsigned short LocalPort);
	
	/* �������ӵ�UDP�������˿�ip��port */
	void SetUdpAddr(const std::string& ip,  const unsigned short PeerPort);

private:
	/*! @class
	********************************************************************************
	* ������   : MyUdpConnector
	* ����     : MyUdpConnector�ǻ���Boost.Asio��st_udp_socket��չ��usp-socket��
				 ��Ϊ���ʹ���st_sclient<MyUdpConnector> m_client,
				 ��Ϊ����Ŀ��UDPͨ�ſͻ��˶���
	* ����     : �µ��� �ϲ����մ�ѧ��Ϣ����ѧԺ�Զ�����ϵ
	* ��ǰ�汾 ��1.0
	* ��    �� ���µ���
	* ������� ��2016-10-17
	*******************************************************************************/
	class MyUdpConnector : public st_udp_socket
	{
		public:
			MyUdpConnector(boost::asio::io_service& io_service_): st_udp_socket(io_service_) {}
		protected:
			virtual bool on_msg(msg_type& msg)
			{
				//�Զ��崦����Ϣ
				return true;
			}
	};

private:
	/* UDP����� */
	st_service_pump m_Pump;

	/* UDP�ͻ��˶��� */
	st_sclient<MyUdpConnector> m_client;

	/* UDP�����ĵ�ַ */
	boost::asio::ip::udp::endpoint m_PeerAddr;
};

