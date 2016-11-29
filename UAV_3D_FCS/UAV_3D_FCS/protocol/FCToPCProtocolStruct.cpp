#include "stdafx.h"
#include "FCToPCProtocolStruct.hpp"

static bool UcharToStrHex(std::string &hexStr, const unsigned char uchar)
{
	char buffer[4] = { '\0' };

	sprintf_s(buffer, 4, "%02X", static_cast<boost::uint8_t>(uchar));
	hexStr = buffer;

	return true;
}


static void DecNumToHexString(int num, std::string & str, int bytes, int dir = 1)
{
	str.clear();
	int index = 0;
	int i = 0;
	unsigned int n = num;
	std::string tstr;
	n %= (1 << (bytes * 8));
	while (index < 2 * bytes)
	{
		char c[2] = { '\0' };
		sprintf_s<2>(c, "%x", n % 16);
		tstr = c + tstr;
		if (index % 2 == 1)
		{
			//一个字节
			if (dir == 1)
			{
				//大端
				str = tstr + str;
			}
			else
			{
				//小端
				str = str + tstr;
			}
			tstr.clear();
		}
		n /= 16;
		index++;
	}
}


void MFA::GetMsgHeaderStr(const MessageHeader &headerInfo, std::string &headerStr)
{
	headerStr.clear();
	string TempStr("");
	 
	UcharToStrHex(TempStr, headerInfo.StartSign);
	headerStr += TempStr;
	UcharToStrHex(TempStr, headerInfo.PayloadLength);
	headerStr += TempStr;
	UcharToStrHex(TempStr, headerInfo.SequenceNumber);
	headerStr += TempStr;
	UcharToStrHex(TempStr, headerInfo.SystemID);
	headerStr += TempStr;
	UcharToStrHex(TempStr, headerInfo.ComponentID);
	headerStr += TempStr;
	UcharToStrHex(TempStr, headerInfo.MessageID);
	headerStr += TempStr;

}


void MFA::ConvertToHexString(std::string& str)
{
	str.clear();
	string MsgHeader;
	string TempMsg;
	string RealStr;

	//消息头初始化
	m_MessageHeader.ComponentID = 1;
	m_MessageHeader.MessageID = 1;
	m_MessageHeader.PayloadLength = 1;
	m_MessageHeader.SequenceNumber = 1;
	m_MessageHeader.StartSign = 1;
	m_MessageHeader.SystemID = 1;

	//转换消息头为消息头字符串
	GetMsgHeaderStr(m_MessageHeader, MsgHeader);

	//加上消息头
	RealStr += MsgHeader;
	
	//加上消息体
	DecNumToHexString(m_TimeBootMs, TempMsg, sizeof(m_TimeBootMs), -1);
	RealStr += TempMsg;
	DecNumToHexString(m_Roll, TempMsg, sizeof(m_Roll), -1);
	RealStr += TempMsg;
	DecNumToHexString(m_Pitch, TempMsg, sizeof(m_Pitch), -1);
	RealStr += TempMsg;
	DecNumToHexString(m_Yaw, TempMsg, sizeof(m_Yaw), -1);
	RealStr += TempMsg;
	DecNumToHexString(m_RollSpeed, TempMsg, sizeof(m_RollSpeed), -1);
	RealStr += TempMsg;
	DecNumToHexString(m_PitchSpeed, TempMsg, sizeof(m_PitchSpeed), -1);
	RealStr += TempMsg;
	DecNumToHexString(m_YawSpeed, TempMsg, sizeof(m_YawSpeed), -1);
	RealStr += TempMsg;
	
	//加上校验和
	DecNumToHexString(m_LowCheckSum, TempMsg, sizeof(m_LowCheckSum), -1);
	RealStr += TempMsg;
	DecNumToHexString(m_HighCheckSum, TempMsg, sizeof(m_HighCheckSum), -1);
	RealStr += TempMsg;
	
	//最终的消息字符串
	str = RealStr;
	
}


template <typename T>
bool MFA::StrHexToIntDec(T &iDec, const std::string &strHex)
{ 
	const std::string::size_type strHexLen = strHex.size();
	iDec = 0;
	T count = 1;
	T num[16] = { 0 };

	//字符串为空或者超出了预期字符数表示转换失败，返回false
	if (0 == strHexLen || sizeof(T)* 2 < strHexLen)
	{
		return false;
	}

	std::string::size_type i;

	//检查字符的有效性，即是否在[0,9] [a,f] [A,F]之间
	for (i = 0; i < strHexLen; i++)
	{
		if (!(('0' <= strHex[i] && '9' >= strHex[i])
			|| ('a' <= strHex[i] && 'f' >= strHex[i])
			|| ('A' <= strHex[i] && 'F' >= strHex[i])))
		{
			return false;
		}
	}

	for (i = strHexLen; i > 0; i--)
	{
		if ((strHex[i - 1] >= '0') && (strHex[i - 1] <= '9'))
		{
			num[i - 1] = strHex[i - 1] - 48;  //字符0的ASCII值为48   
		}
		else if ((strHex[i - 1] >= 'a') && (strHex[i - 1] <= 'f'))
		{
			num[i - 1] = strHex[i - 1] - 'a' + 10;
		}
		else if ((strHex[i - 1] >= 'A') && (strHex[i - 1] <= 'F'))
		{
			num[i - 1] = strHex[i - 1] - 'A' + 10;
		}
		else
		{
			num[i - 1] = 0;
		}

		iDec = iDec + num[i - 1] * count;
		count = count * 16;  //十六进制(如果是八进制就在这里乘以8)       
	}

	return true; 
}

 

bool MFA::HexStrToAsciiStr(std::string &asciiStr, const std::string &hexStr)
{
	unsigned char byteTmp = 0;
	std::string strTmp;
	asciiStr = "";  //重置

	for (decltype(hexStr.size()) i = 0; i < hexStr.size() / 2; i++)
	{
		strTmp = hexStr[i * 2];
		strTmp += hexStr[i * 2 + 1];

		if (!StrHexToIntDec<unsigned char>(byteTmp, strTmp))
			return false;

		asciiStr += byteTmp;
	}

	return true;
}
















