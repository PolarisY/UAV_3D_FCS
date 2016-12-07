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
			/*! @function
			********************************************************************************
			* ������   : on_msg_handle
			* ����     : ����ͨ��TCPЭ�鷢�͵����ն˵�MAVLink���ݰ�
			* ����     : msg ���յ���JSON��ʽ�����ݰ� 
			* ����ֵ   : void
			* ����     : �µ��� �ϲ����մ�ѧ��Ϣ����ѧԺ�Զ�����ϵ
			* ����     : 2016-12-6
			*******************************************************************************/
			virtual void on_msg_handle(MsgType& msg)
			{
				AfxMessageBox(_T("on_msg_handle"));

				DeSerializer dr;
				dr.Parse(msg.c_str());

				std::lock_guard<std::mutex> locker(m_MutexSendReq);

				//�����л����ݰ�
				dr.Deserialize(m_MFA, "MFA");
				m_MFADC.MFAToMFADC(m_MFA);

				//�����ݰ����͵���Ϣ������ 
				g_Bus.SendReq<void, const MFADC&>(m_MFADC, "MFADC");

				//֪ͨ���ݿ�ģ��洢Json��ʽ�����ݰ�
				g_Bus.SendReq<void, const MsgType&>(msg, "AddMsgToSQL");

				//���յ������ݰ�����
				g_MFAPackNum++;
			}
			 
			//virtual bool on_msg(MsgType& msg)
			//{
			//	AfxMessageBox(_T("on_msg"));
			//	return true;
			//} 

		private:
			std::mutex m_MutexSendReq;      //Ϊ��ͬ��ִ�У�����Ϣ������SendReqʱ����

		private:
			MFA m_MFA;
			MFADC m_MFADC;
	};


private: 

	/* TCP�ͻ��˷���� */
	st_service_pump  m_pump;

	/* TCPͨ�ŵĿͻ��˶��� */
	st_sclient<MyConnector> m_client;
};

