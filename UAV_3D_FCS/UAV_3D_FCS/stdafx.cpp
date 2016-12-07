
// stdafx.cpp : 只包括标准包含文件的源文件
// UAV_3D_FCS.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"


MessageBus g_Bus;				//消息总线全局变量
std::atomic<int> g_MFAPackNum;	//数据包全局原子变量