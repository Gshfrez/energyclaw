#include "pch.h"
#include <iostream> 
#include <math.h>
#include "NETAccess.H"
#include <vector>
#include "FOLDEREDIT.h"
#pragma comment(lib, "FOLDEREDIT.lib")
using namespace std;

struct RoadIntValue {
	int Type;
	int Sx;//此支路的性质，0是纯压阻模式，1代表有阀门，2代表强制流量模式。
	int Size;//这个支路上有多少模块,
	bool FrontSx;//上游节点是什么性质，源点是0节点则是1,
	int FrontNb;//上游源头的源点M号或者节点号。
	int FrontPort;//上游链接端口号。
	bool PostSx;//下节点是什么性质，源点是0节点则是1,
	int PostNb;//下游节点或者压力源点的模块号节点号。
	int PostPort;//下游节点或者压力源点的端口号。
	bool If_OK;//此支路是否已经结尾0是未1是已经.
	int Qznb;
	int Znnb;
	bool Rvkb;
};
struct RoadAccessValue {
	int mdnb;
	int tlnb;
};
static int CoreAccessNb = 0 ;//此项目有多少支路
static vector<RoadIntValue> CoreAccess(0);
static const char NodeName[6][8] = {//节点的名称和ID
	"FLUID",
	"INFO",
	"POWER",
	"MECH"
};
static const char JumpName[2][8] = {//节点的名称和ID
	"PAGEIN",
	"PAGEOUT"
};
static double Double_Esp = 1E-8;
static double Double_Esp_x2 = 1E-16;
static RoadAccessValue AccessZlKong = { -1,-1 };
static RoadIntValue AccessKong = { 0,0,0,false,-1,-1,false,-1,-1,false,-1,-1,false };
static ProjectCheck midpjtinfo = { 0 };

string midNetAccessRtn = "";
const char* NetAccessRtn(int pjtNb, int midNbSet, int midtype)
{
	if (midtype > 0)
	{
		if (midtype == 1)
		{
			midNetAccessRtn="出错啦,此模块所在支路环路不完整:MOD";
			midNetAccessRtn= midNetAccessRtn+IntToChar(midNbSet);
			midNetAccessRtn = midNetAccessRtn + " InstanceID:";
			midNetAccessRtn = midNetAccessRtn + midpjtinfo.ModuleSx[midNbSet].InstanceID;
			midNetAccessRtn = midNetAccessRtn + "\n";
		}
		else
		{
			if (midtype == 2)
			{
				midNetAccessRtn="出错啦,此节点所在管网缺少定压装置:NOD";
				midNetAccessRtn = midNetAccessRtn + IntToChar(midNbSet);
				midNetAccessRtn = midNetAccessRtn + " InstanceID:";
				midNetAccessRtn = midNetAccessRtn + midpjtinfo.NodeSx[midNbSet].InstanceID;
				midNetAccessRtn = midNetAccessRtn + "\n";
			}
		}
	}
	else
	{
		midNetAccessRtn = "解析成功并即将启动\n";
	}
	return midNetAccessRtn.c_str();
}

void JSONWRITE(const char midaddin[], StringBuffer& midJsonIn)
{
	FILE* fp_WriteChar;
	errno_t err2 = fopen_s(&fp_WriteChar, midaddin, "wb");
	char midBOM[4] = { char(0xEF) ,char(0xBB) ,char(0xBF),char(0) };
	string miderite = midBOM;
	miderite = miderite + GbkToUtf8(midJsonIn.GetString());
	if (fp_WriteChar != NULL)
	{
		::fwrite(miderite.c_str(), miderite.length(), 1, fp_WriteChar);
		fclose(fp_WriteChar);
	}
}
bool Net_Access(int pjnb)
{
	//大规模归零处理
	CoreAccessNb = 0;//此时归零
	CoreAccess.resize(0);
	vector<bool>mid_linksx(midpjtinfo.LinkMax, 0);
	vector<bool>mid_pagelinksx(midpjtinfo.JumpLinkNb, 0);
	for (int zi = 0; zi < midpjtinfo.LinkMax; zi++)
	{
		if (midpjtinfo.LinkSx[zi].IfOn == true)
		{
			if (midpjtinfo.LinkSx[zi].Type != 1 && midpjtinfo.LinkSx[zi].Type != 3)//判断连线0是流体1是信息2是电力3是结构
			{
				if (midpjtinfo.LinkSx[zi].F_Sx == 3)
				{
					mid_linksx[zi] = true;
				}
				if (midpjtinfo.LinkSx[zi].S_Sx == 3)
				{
					mid_linksx[zi] = true;
				}
			}
			else
			{
				mid_linksx[zi] = true;
			}
		}
	}
	for (int zi = 0; zi < midpjtinfo.JumpLinkNb; zi++)
	{
		if (midpjtinfo.JumpLinkSx[zi].IfOn == true)
		{
			if (midpjtinfo.JumpLinkSx[zi].Type == 1 || midpjtinfo.JumpLinkSx[zi].Type == 3)//判断连线0是流体1是信息2是电力3是结构
			{
				mid_pagelinksx[zi] = true;
			}
		}
	}
	vector <vector<RoadAccessValue>> midAccessZl(0);
	//流体网络的解析之，寻找支路源头,确立每一条支路得上有源头。
	for (int zi = 0; zi < midpjtinfo.LinkMax; zi++)
	{
		if (midpjtinfo.LinkSx[zi].IfOn == true)
		{
			if (mid_linksx[zi] == false)
			{
				int midAccess = CoreAccessNb;
				if (midpjtinfo.LinkSx[zi].F_Sx == 1)//判断是模块，还是节点（1模块2节点）
				{
					if (midpjtinfo.LinkSx[zi].F_Type_2 == false)//若是容积型端口，则下一步
					{
						for (int ai = (int)CoreAccess.size(); ai <= midAccess; ai++)
						{
							CoreAccess.push_back(AccessKong);
							midAccessZl.push_back(vector<RoadAccessValue>(0));
						}
						int midmodnb_pre = midpjtinfo.LinkSx[zi].F_Nb;//读取前模块号
						int midportnb_pre = midpjtinfo.LinkSx[zi].F_PortNb;//获取前端口号
						int midmodnb_rear = midpjtinfo.LinkSx[zi].S_Nb;//读取后模块号
						int midportnb_rear = midpjtinfo.LinkSx[zi].S_PortNb;//获取后端口号
						CoreAccess[midAccess].Size = CoreAccess[midAccess].Size + 1;
						CoreAccess[midAccess].FrontSx = false;//上游是模块
						CoreAccess[midAccess].FrontNb = midmodnb_pre;
						CoreAccess[midAccess].FrontPort = midportnb_pre;
						for (int zli = (int)midAccessZl[midAccess].size(); zli <= 0; zli++)
						{
							midAccessZl[midAccess].push_back(AccessZlKong);
						}
						midAccessZl[midAccess][0].mdnb = midmodnb_rear;//支路特征储存值项目、支路、位置，MOD模块号、通路号。 
						midAccessZl[midAccess][0].tlnb = ModulePortInfo(pjnb, midmodnb_rear, midportnb_rear, 5).AisleNb;
						CoreAccess[midAccess].Type = midpjtinfo.LinkSx[zi].Type;
						CoreAccessNb = CoreAccessNb + 1;
						mid_linksx[zi] = true;
					}
				}
				if (midpjtinfo.LinkSx[zi].F_Sx == 2)//else//若是节点
				{
					for (int ai = (int)CoreAccess.size(); ai <= midAccess; ai++)
					{
						CoreAccess.push_back(AccessKong);
						midAccessZl.push_back(vector<RoadAccessValue>(0));
					}
					int midnodnb_pre = midpjtinfo.LinkSx[zi].F_Nb;//读取模块号
					int midportnb_pre = midpjtinfo.LinkSx[zi].F_PortNb;//获取端口号
					int midmodnb_rear = midpjtinfo.LinkSx[zi].S_Nb;//读取后模块号
					int midportnb_rear = midpjtinfo.LinkSx[zi].S_PortNb;//获取后端口号
					CoreAccess[midAccess].Size = CoreAccess[midAccess].Size + 1;
					CoreAccess[midAccess].FrontSx = true;//上游是节点
					CoreAccess[midAccess].FrontNb = midnodnb_pre;
					CoreAccess[midAccess].FrontPort = midportnb_pre;
					for (int zli = (int)midAccessZl[midAccess].size(); zli <= 0; zli++)
					{
						midAccessZl[midAccess].push_back(AccessZlKong);//, ZlInfoKong
					}
					midAccessZl[midAccess][0].mdnb = midmodnb_rear;//支路特征储存值项目、支路、位置，MOD模块号、通路号。 
					midAccessZl[midAccess][0].tlnb = ModulePortInfo(pjnb, midmodnb_rear, midportnb_rear, 5).AisleNb;
					CoreAccess[midAccess].Type = midpjtinfo.LinkSx[zi].Type;
					CoreAccessNb = CoreAccessNb + 1;
					mid_linksx[zi] = true;
				}
			}
		}
	}
	for (int zi = 0; zi < midpjtinfo.JumpLinkNb; zi++)
	{
		if (midpjtinfo.JumpLinkSx[zi].IfOn == true)
		{
			int midAccess = CoreAccessNb;
			if (midpjtinfo.JumpLinkSx[zi].F_Sx == 1)//判断是模块，还是节点（1模块2节点）
			{
				if (midpjtinfo.JumpLinkSx[zi].F_Type_2 == false)//若是容积型端口，则下一步
				{
					for (int ai = (int)CoreAccess.size(); ai <= midAccess; ai++)
					{
						CoreAccess.push_back(AccessKong);
						midAccessZl.push_back(vector<RoadAccessValue>(0));
					}
					int midmodnb_pre = midpjtinfo.JumpLinkSx[zi].F_Nb;//读取前模块号
					int midportnb_pre = midpjtinfo.JumpLinkSx[zi].F_PortNb;//获取前端口号
					int midmodnb_rear = midpjtinfo.JumpLinkSx[zi].S_Nb;//读取后模块号
					int midportnb_rear = midpjtinfo.JumpLinkSx[zi].S_PortNb;//获取后端口号
					CoreAccess[midAccess].Size = CoreAccess[midAccess].Size + 1;
					CoreAccess[midAccess].FrontSx = false;//上游是模块
					CoreAccess[midAccess].FrontNb = midmodnb_pre;
					CoreAccess[midAccess].FrontPort = midportnb_pre;
					for (int zli = (int)midAccessZl[midAccess].size(); zli <= 0; zli++)
					{
						midAccessZl[midAccess].push_back(AccessZlKong);
					}
					midAccessZl[midAccess][0].mdnb = midmodnb_rear;//支路特征储存值项目、支路、位置，MOD模块号、通路号。 
					midAccessZl[midAccess][0].tlnb = ModulePortInfo(pjnb, midmodnb_rear, midportnb_rear, 5).AisleNb;
					CoreAccess[midAccess].Type = midpjtinfo.LinkSx[zi].Type;
					CoreAccessNb = CoreAccessNb + 1;
					mid_pagelinksx[zi] = true;
				}
			}
			if (midpjtinfo.JumpLinkSx[zi].F_Sx == 2)//else//若是节点
			{
				for (int ai = (int)CoreAccess.size(); ai <= midAccess; ai++)
				{
					CoreAccess.push_back(AccessKong);
					midAccessZl.push_back(vector<RoadAccessValue>(0));//, ZlInfoKong
				}
				int midnodnb_pre = midpjtinfo.JumpLinkSx[zi].F_Nb;//读取模块号
				int midportnb_pre = midpjtinfo.JumpLinkSx[zi].F_PortNb;//获取端口号
				int midmodnb_rear = midpjtinfo.JumpLinkSx[zi].S_Nb;//读取后模块号
				int midportnb_rear = midpjtinfo.JumpLinkSx[zi].S_PortNb;//获取后端口号
				CoreAccess[midAccess].Size = CoreAccess[midAccess].Size + 1;
				CoreAccess[midAccess].FrontSx = true;//上游是节点
				CoreAccess[midAccess].FrontNb = midnodnb_pre;
				CoreAccess[midAccess].FrontPort = midportnb_pre;
				for (int zli = (int)midAccessZl[midAccess].size(); zli <= 0; zli++)
				{
					midAccessZl[midAccess].push_back(AccessZlKong);//, ZlInfoKong
				}
				midAccessZl[midAccess][0].mdnb = midmodnb_rear;//支路特征储存值项目、支路、位置，MOD模块号、通路号。 
				midAccessZl[midAccess][0].tlnb = ModulePortInfo(pjnb, midmodnb_rear, midportnb_rear, 5).AisleNb;
				CoreAccess[midAccess].Type = midpjtinfo.LinkSx[zi].Type;
				CoreAccessNb = CoreAccessNb + 1;
				mid_pagelinksx[zi] = true;
			}
		}
	}
	//针对每一条支路进行补齐解析，以及收尾，每条支路，最大24个通路。
	for (int midzi = 0; midzi < 256; midzi++)//为啥要重复24次呢？上面的开头，第一位已经有了，后面就是续接上下23个，然后还得来个收尾。
	{
		bool if_midbreak = true;
		for (int zi = 0; zi < midpjtinfo.LinkMax; zi++)
		{
			if (midpjtinfo.LinkSx[zi].IfOn == true)
			{
				if (mid_linksx[zi] == false)
				{
					if_midbreak = false;
					if (midpjtinfo.LinkSx[zi].F_Sx == 1)//判断上游的是模块，还是节点（1模块2节点）从前往后判断，判断上有是否连接模块，非模块不进入下一级
					{
						if (midpjtinfo.LinkSx[zi].F_Type_2 == true)//若上游是线性端口
						{
							int midmodnb_pre = midpjtinfo.LinkSx[zi].F_Nb;//读取前模块号
							int midportnb_pre = midpjtinfo.LinkSx[zi].F_PortNb;//获取前端口号
							int midmodnb_rear = midpjtinfo.LinkSx[zi].S_Nb;//读取后模块号
							int midportnb_rear = midpjtinfo.LinkSx[zi].S_PortNb;//获取后端口号
							for (int yi = 0; yi < CoreAccessNb; yi++)
							{
								if (CoreAccess[yi].If_OK == false)
								{
									int midBranch = CoreAccess[yi].Size - 1;
									for (int zli = (int)midAccessZl[yi].size(); zli <= midBranch; zli++)
									{
										midAccessZl[yi].push_back(AccessZlKong);//, ZlInfoKong
									}
									int midmodnb = midAccessZl[yi][midBranch].mdnb;//读取第N个位置得模块号，通路号,//支路特征储存值项目、支路、位置，MOD模块号、通路号。
									int midmodtl = midAccessZl[yi][midBranch].tlnb;//读取第N个位置得通路号，通路号,//支路特征储存值项目、支路、位置，MOD模块号、通路号。
									int midportnb = ModuleAisleSx(pjnb, midmodnb, midmodtl, 2).OutPutPortNb;//通道信息，分别是通道号、每一个通道的进口端口号、出口端口号、是否建立0是未建立1是建立。
									if (midportnb == midportnb_pre && midmodnb == midmodnb_pre)
									{
										if (midpjtinfo.LinkSx[zi].S_Sx == 1)//下游若是模块
										{
											if (midpjtinfo.LinkSx[zi].S_Type_2 == true)//若是线性型，则添加一个通路
											{
												int midBranch_1 = CoreAccess[yi].Size;
												for (int zli = (int)midAccessZl[yi].size(); zli <= midBranch_1; zli++)
												{
													midAccessZl[yi].push_back(AccessZlKong);//, ZlInfoKong
												}
												midAccessZl[yi][midBranch_1].mdnb = midmodnb_rear;//支路特征储存值项目、支路、位置，MOD模块号、通路号。 
												midAccessZl[yi][midBranch_1].tlnb = ModulePortInfo(pjnb, midmodnb_rear, midportnb_rear, 5).AisleNb;
												CoreAccess[yi].Size = CoreAccess[yi].Size + 1;
												mid_linksx[zi] = true;
											}
											else//若是容积型则认为可以收尾了
											{
												CoreAccess[yi].PostSx = false;//上游是模块
												CoreAccess[yi].PostNb = midmodnb_rear;
												CoreAccess[yi].PostPort = midportnb_rear;
												CoreAccess[yi].If_OK = true;//此支路已收尾
												mid_linksx[zi] = true;
											}
										}
										else//若下游是节点
										{
											CoreAccess[yi].PostSx = true;//上游是节点
											CoreAccess[yi].PostNb = midmodnb_rear;
											CoreAccess[yi].PostPort = midportnb_rear;
											CoreAccess[yi].If_OK = true;//此支路已收尾
											mid_linksx[zi] = true;//代表此线已处理
										}
									}
								}
							}
						}
					}
				}
			}
		}
		for (int zi = 0; zi < midpjtinfo.JumpLinkNb; zi++)
		{
			if (midpjtinfo.JumpLinkSx[zi].IfOn == true)
			{
				if (mid_pagelinksx[zi] == false)
				{
					if_midbreak = false;
					if (midpjtinfo.JumpLinkSx[zi].F_Sx == 1)//判断上游的是模块，还是节点（1模块2节点）从前往后判断，判断上有是否连接模块，非模块不进入下一级
					{
						if (midpjtinfo.JumpLinkSx[zi].F_Type_2 == true)//若上游是线性端口
						{
							int midmodnb_pre = midpjtinfo.JumpLinkSx[zi].F_Nb;//读取前模块号
							int midportnb_pre = midpjtinfo.JumpLinkSx[zi].F_PortNb;//获取前端口号
							int midmodnb_rear = midpjtinfo.JumpLinkSx[zi].S_Nb;//读取后模块号
							int midportnb_rear = midpjtinfo.JumpLinkSx[zi].S_PortNb;//获取后端口号
							for (int yi = 0; yi < CoreAccessNb; yi++)
							{
								if (CoreAccess[yi].If_OK == false)
								{
									int midBranch = CoreAccess[yi].Size - 1;
									for (int zli = (int)midAccessZl[yi].size(); zli <= midBranch; zli++)
									{
										midAccessZl[yi].push_back(AccessZlKong);//, ZlInfoKong
									}
									int midmodnb = midAccessZl[yi][midBranch].mdnb;//读取第N个位置得模块号，通路号,//支路特征储存值项目、支路、位置，MOD模块号、通路号。
									int midmodtl = midAccessZl[yi][midBranch].tlnb;//读取第N个位置得模块号，通路号,//支路特征储存值项目、支路、位置，MOD模块号、通路号。
									int midportnb = ModuleAisleSx(pjnb, midmodnb, midmodtl, 2).OutPutPortNb;//通道信息，分别是通道号、每一个通道的进口端口号、出口端口号、是否建立0是未建立1是建立。
									if (midportnb == midportnb_pre && midmodnb == midmodnb_pre)
									{
										if (midpjtinfo.JumpLinkSx[zi].S_Sx == 1)//若是模块
										{
											if (midpjtinfo.JumpLinkSx[zi].S_Type_2 == true)//若上游是线性，则添加一个通路
											{
												int midBranch_1 = CoreAccess[yi].Size;
												for (int zli = (int)midAccessZl[yi].size(); zli <= midBranch_1; zli++)
												{
													midAccessZl[yi].push_back(AccessZlKong);//, ZlInfoKong
												}
												midAccessZl[yi][midBranch_1].mdnb = midmodnb_rear;//支路特征储存值项目、支路、位置，MOD模块号、通路号。 
												midAccessZl[yi][midBranch_1].tlnb = ModulePortInfo(pjnb, midmodnb_rear, midportnb_rear, 5).AisleNb;
												CoreAccess[yi].Size = CoreAccess[yi].Size + 1;
												mid_pagelinksx[zi] = true;
											}
											else//若是容积型，则可以收尾了
											{
												CoreAccess[yi].PostSx = false;//上游是模块
												CoreAccess[yi].PostNb = midmodnb_rear;
												CoreAccess[yi].PostPort = midportnb_rear;
												CoreAccess[yi].If_OK = true;//此支路已收尾
												mid_pagelinksx[zi] = true;
											}
										}
										else//若下游是节点
										{
											CoreAccess[yi].PostSx = true;//上游是节点
											CoreAccess[yi].PostNb = midmodnb_rear;
											CoreAccess[yi].PostPort = midportnb_rear;
											CoreAccess[yi].If_OK = true;//此支路已收尾
											mid_pagelinksx[zi] = true;
										}
									}
								}
							}
						}
					}
				}
			}
		}
		if (if_midbreak)
		{
			break;
		}
	}
	for (int zi = 0; zi < CoreAccessNb; zi++)
	{
		if (CoreAccess[zi].If_OK == false)
		{
			return NetAccessRtn(pjnb, midAccessZl[zi][CoreAccess[zi].Size - 1].mdnb, 1);
		}
	}
	for (int zi = 0; zi < midpjtinfo.LinkMax; zi++)
	{
		if (midpjtinfo.LinkSx[zi].IfOn == true)
		{
			if (mid_linksx[zi] == false)
			{
				return NetAccessRtn(pjnb, midpjtinfo.LinkSx[zi].F_Nb, 1);
			}
		}
	}
	for (int zi = 0; zi < midpjtinfo.JumpLinkNb; zi++)
	{
		if (midpjtinfo.JumpLinkSx[zi].IfOn == true)
		{
			if (mid_pagelinksx[zi] == false)
			{
				return NetAccessRtn(pjnb, midpjtinfo.JumpLinkSx[zi].F_Nb, 1);
			}
		}
	}
	midAccessZl.clear();
	mid_linksx.clear();
	mid_pagelinksx.clear();
	return NetAccessRtn(pjnb, -1, 0);
}

static StringBuffer MidWriteBuffer;
const char * NetInfo_ToAI(int pjtNb)
{
	if (pjtNb < 0 || pjtNb > 7)
	{
		return 0;
	}
	char midpjtnm[64] = "";
	strcpy_s(midpjtnm, 64, ProjectNameGet(pjtNb));
	ProjectInfoGet(midpjtnm, midpjtinfo);//获取这个的项目信息

	ProjectInfoJumpLinkPressing(pjtNb);
	Document NewPjtJson;			//生成DOM元素
	NewPjtJson.SetObject();
	Document::AllocatorType& NewAllocator = NewPjtJson.GetAllocator();	//生成一个分配器
	//构建键值对
	Value DeviceInfo(kArrayType);//模块信息object
	Value ConnectionInfo(kArrayType);//链接object
	int addNb = 0;
	for (int zi = 0; zi < midpjtinfo.ModuleMax; zi++)
	{
		if (midpjtinfo.ModuleSx[zi].IfOn == 1)
		{
			Value ModuleSx(kObjectType);
			ModuleSx.AddMember("设备", addNb, NewAllocator);
			ModuleSx.AddMember("InstanceID", zi, NewAllocator);
			ModuleSx.AddMember("设备类型", StringRef(ModuleNameGbkGet(midpjtinfo.ModuleSx[zi].ID)), NewAllocator);
			ModuleSx.AddMember("BaseModuelID", ModuleOneIDGet(midpjtinfo.ModuleSx[zi].ID), NewAllocator);
			ModuleSx.AddMember("FluidType", 0, NewAllocator);
			ModuleSx.AddMember("PositionX", midpjtinfo.ModuleSx[zi].x, NewAllocator);
			ModuleSx.AddMember("PositionZ", midpjtinfo.ModuleSx[zi].y, NewAllocator);
			ModuleSx.AddMember("RoomID", 0, NewAllocator);
			ModuleSx.AddMember("ModelID", StringRef(midpjtinfo.ModuleSx[zi].Model_Name), NewAllocator);
			DeviceInfo.PushBack(ModuleSx, NewAllocator);
			addNb = addNb + 1;
		}
	}
	for (int zi = 0; zi < midpjtinfo.NodeMax; zi++)
	{
		if (midpjtinfo.NodeSx[zi].IfOn == 1)
		{
			Value NodeSx(kObjectType);
			NodeSx.AddMember("节点", addNb, NewAllocator);
			NodeSx.AddMember("InstanceID", zi, NewAllocator);
			NodeSx.AddMember("设备类型", StringRef(NodeName[midpjtinfo.NodeSx[zi].ID]), NewAllocator);
			NodeSx.AddMember("BaseModuelID",midpjtinfo.NodeSx[zi].ID + 3000, NewAllocator);
			NodeSx.AddMember("FluidType", 0, NewAllocator);
			NodeSx.AddMember("PositionX", midpjtinfo.NodeSx[zi].x, NewAllocator);
			NodeSx.AddMember("PositionZ", midpjtinfo.NodeSx[zi].y, NewAllocator);
			NodeSx.AddMember("RoomID", 0, NewAllocator);
			NodeSx.AddMember("ModelID", "", NewAllocator);
			DeviceInfo.PushBack(NodeSx, NewAllocator);
			addNb = addNb + 1;
		}
	}
	for (int zi = 0; zi < midpjtinfo.JumpMax; zi++)
	{
		if (midpjtinfo.JumpSx[zi].IfOn == 1)
		{
			Value JumpSx(kObjectType);
			JumpSx.AddMember("跳转", addNb, NewAllocator);
			JumpSx.AddMember("InstanceID", zi, NewAllocator);
			JumpSx.AddMember("设备类型", StringRef(JumpName[midpjtinfo.JumpSx[zi].ID]), NewAllocator);
			JumpSx.AddMember("BaseModuelID",midpjtinfo.JumpSx[zi].ID + 4000, NewAllocator);
			JumpSx.AddMember("FluidType", 0, NewAllocator);
			JumpSx.AddMember("PositionX", midpjtinfo.JumpSx[zi].x, NewAllocator);
			JumpSx.AddMember("PositionZ", midpjtinfo.JumpSx[zi].y, NewAllocator);
			JumpSx.AddMember("RoomID", 0, NewAllocator);
			JumpSx.AddMember("ModelID", "Node", NewAllocator);
			DeviceInfo.PushBack(JumpSx, NewAllocator);
			addNb = addNb + 1;
		}
	}
	NewPjtJson.AddMember("DeviceNb", addNb, NewAllocator);
	NewPjtJson.AddMember("DeviceInfo", DeviceInfo, NewAllocator);


	//for (int zi = 0; zi < midpjtinfo.LinkMax; zi++)
	//{
	//	if (midpjtinfo.LinkSx[zi].IfOn == 1)
	//	{
	//		Value LinkSx(kObjectType);
	//		LinkSx.AddMember("ConnectionID", zi, NewAllocator);
	//		LinkSx.AddMember("ConnectionType",midpjtinfo.LinkSx[zi].Type, NewAllocator);
	//		LinkSx.AddMember("ConnectionPageNb",midpjtinfo.LinkSx[zi].PageNb, NewAllocator);
	//		//LinkSx.AddMember("StartDeviceInstanceID", midpjtinfo.LinkSx[zi].F_Sx, NewAllocator);
	//		LinkSx.AddMember("StartDeviceInstanceID", midpjtinfo.LinkSx[zi].F_Nb, NewAllocator);
	//		LinkSx.AddMember("StartPortID", midpjtinfo.LinkSx[zi].F_PortNb, NewAllocator);
	//		LinkSx.AddMember("ConnectionType", midpjtinfo.LinkSx[zi].F_Type_2, NewAllocator);
	//		LinkSx.AddMember("ConnectionType", midpjtinfo.LinkSx[zi].S_Sx, NewAllocator);
	//		LinkSx.AddMember("ConnectionType", midpjtinfo.LinkSx[zi].S_Nb, NewAllocator);
	//		LinkSx.AddMember("ConnectionType", midpjtinfo.LinkSx[zi].S_PortNb, NewAllocator);
	//		LinkSx.AddMember("ConnectionType", midpjtinfo.LinkSx[zi].S_Type_2, NewAllocator);
	//		ConnectionInfo.PushBack(LinkSx, NewAllocator);
	//	}
	//}
	string path = "../Csv/";
	path = path + midpjtinfo.ProjectName;
	path = path + ".json";
	MidWriteBuffer.Clear();
	PrettyWriter<StringBuffer> writer(MidWriteBuffer);//Pretty
	NewPjtJson.Accept(writer);
	JSONWRITE(path.c_str(), MidWriteBuffer);
	return MidWriteBuffer.GetString();
}