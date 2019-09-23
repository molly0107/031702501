// addressbook.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include<Windows.h>
#include <iostream>
#include<cstdio>
#include<string>
#include<cctype>
#include<fstream>
#include<cstdlib>
using namespace std;

class Person {
public:
	string total;
	string name;
	string telnum;
	wstring province; //省
	wstring city; //市/直辖市
	wstring county; //区/县/县级市
	wstring street; //街道/镇/乡
	wstring detailaddr; //详细地址
	Person() {
		total = " "; name = " ";  telnum = " "; province = L""; city = L""; county = L""; street = L""; detailaddr = L"";
	};
};
Person addr[50];
//建立省、直辖市、自治区表
wstring direct_pro[4] = { L"北京",L"上海",L"天津",L"重庆" };
wstring autop[5] = { L"内蒙古",L"宁夏回族",L"西藏",L"广西壮族",L"新疆维吾尔" };
wstring provincebook[22] = { L"河北",L"山西",L"辽宁",L"吉林",L"江苏",L"浙江",L"安徽",L"福建",L"江西",L"山东",L"河南",L"湖北",L"湖南",L"广东",L"海南",L"四川",L"贵州",L"云南",L"陕西",L"甘肃",L"青海",L"台湾" };
wstring city[] = { L"﻿唐山",L"秦皇岛",L"邯郸",L"邢台",L"保定",L"张家口",L"承德",L"沧州",L"廊坊",L"衡水",L"太原",L"大同",L"阳泉",L"长治",L"晋城",L"朔州",L"晋中",L"运城",L"忻州",L"临汾",L"吕梁",L"呼和浩特",L"包头",L"乌海",L"赤峰",L"通辽",L"鄂尔多斯",L"呼伦贝尔",L"巴彦淖尔",L"乌兰察布",L"兴安",L"锡林郭勒",L"阿拉善",L"沈阳",L"大连",L"鞍山",L"抚顺",L"本溪",L"丹东",L"锦州",L"营口",L"阜新",L"辽阳",L"盘锦",L"铁岭",L"朝阳",L"葫芦岛",L"长春",L"吉林",L"四平",L"辽源",L"通化",L"白山",L"松原",L"白城",L"延边",L"哈尔滨",L"齐齐哈尔",L"鸡西",L"鹤岗",L"双鸭山",L"大庆",L"伊春",L"佳木斯",L"七台河",L"牡丹江",L"黑河",L"绥化",L"大兴安岭",L"南京",L"无锡",L"徐州",L"常州",L"苏州",L"南通",L"连云港",L"淮安",L"盐城",L"扬州",L"镇江",L"泰州",L"宿迁",L"杭州",L"宁波",L"温州",L"嘉兴",L"湖州",L"绍兴",L"金华",L"衢州",L"舟山",L"台州",L"丽水",L"合肥",L"芜湖",L"蚌埠",L"淮南",L"马鞍山",L"淮北",L"铜陵",L"安庆",L"黄山",L"滁州",L"阜阳",L"宿州",L"巢湖",L"六安",L"亳州",L"池州",L"宣城",L"福州",L"厦门",L"莆田",L"三明",L"泉州",L"漳州",L"南平",L"龙岩",L"宁德",L"南昌",L"景德镇",L"萍乡",L"九江",L"新余",L"鹰潭",L"赣州",L"吉安",L"宜春",L"抚州",L"上饶",L"济南",L"青岛",L"淄博",L"枣庄",L"东营",L"烟台",L"潍坊",L"威海",L"济宁",L"泰安",L"日照",L"莱芜",L"临沂",L"德州",L"聊城",L"滨州",L"菏泽",L"郑州",L"开封",L"洛阳",L"平顶山",L"焦作",L"鹤壁",L"新乡",L"安阳",L"濮阳",L"许昌",L"漯河",L"三门峡",L"南阳",L"商丘",L"信阳",L"周口",L"驻马店",L"武汉",L"黄石",L"襄樊",L"十堰",L"荆州",L"宜昌",L"荆门",L"鄂州",L"孝感",L"黄冈",L"咸宁",L"随州",L"恩施",L"长沙",L"株洲",L"湘潭",L"衡阳",L"邵阳",L"岳阳",L"常德",L"张家界",L"益阳",L"郴州",L"永州",L"怀化",L"娄底",L"湘西",L"广州",L"深圳",L"珠海",L"汕头",L"韶关",L"佛山",L"江门",L"湛江",L"茂名",L"肇庆",L"惠州",L"梅州",L"汕尾",L"河源",L"阳江",L"清远",L"东莞",L"中山",L"潮州",L"揭阳",L"云浮",L"南宁",L"柳州",L"桂林",L"梧州",L"北海",L"防城港",L"钦州",L"贵港",L"玉林",L"百色",L"贺州",L"河池",L"来宾",L"崇左",L"海口",L"三亚",L"成都",L"自贡",L"攀枝花",L"泸州",L"德阳",L"绵阳",L"广元",L"遂宁",L"内江",L"乐山",L"南充",L"宜宾",L"广安",L"达州",L"眉山",L"雅安",L"巴中",L"资阳",L"阿坝",L"甘孜",L"凉山",L"贵阳",L"六盘水",L"遵义",L"安顺",L"铜仁",L"毕节",L"黔西南",L"黔东南",L"黔南",L"昆明",L"曲靖",L"玉溪",L"保山",L"昭通",L"丽江",L"普洱",L"临沧",L"文山",L"红河",L"西双版纳",L"楚雄",L"大理",L"德宏",L"怒江",L"迪庆",L"拉萨",L"昌都",L"山南",L"日喀则",L"那曲",L"阿里",L"林芝",L"西北地区",L"西安",L"铜川",L"宝鸡",L"咸阳",L"渭南",L"延安",L"汉中",L"榆林",L"安康",L"商洛",L"兰州",L"嘉峪关",L"金昌",L"白银",L"天水",L"武威",L"张掖",L"平凉",L"酒泉",L"庆阳",L"定西",L"陇南",L"临夏",L"甘南",L"西宁",L"海东",L"海北",L"黄南",L"海南",L"果洛",L"玉树",L"海西",L"银川",L"石嘴山",L"吴忠",L"固原",L"中卫",L"乌鲁木齐",L"克拉玛依",L"吐鲁番",L"哈密",L"和田",L"阿克苏",L"喀什",L"克孜勒苏柯尔克孜",L"巴音郭楞蒙古",L"昌吉",L"博尔塔拉蒙古",L"伊犁哈萨克",L"塔城",L"阿勒泰" };

//把string转换成wstring
wstring stringtowstring(string str)
{
	wstring result;
	//获取缓冲区大小，并申请空间，缓冲区大小按字符计算  
	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
	TCHAR* buffer = new TCHAR[len + 1];
	//多字节编码转换成宽字节编码  
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
	buffer[len] = '\0';             //添加字符串结尾  
	//删除缓冲区并返回值  
	result.append(buffer);
	delete[] buffer;
	return result;
}
//把wstring转成string
string wstringtostring(wstring wstr)
{
	string result;
	//获取缓冲区大小，并申请空间，缓冲区大小事按字节计算的  
	int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), NULL, 0, NULL, NULL);
	char* buffer = new char[len + 1];
	//宽字节编码转换成多字节编码  
	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), buffer, len, NULL, NULL);
	buffer[len] = '\0';
	//删除缓冲区并返回值  
	result.append(buffer);
	delete[] buffer;
	return result;
}
//判断一级地址并且赋予person.province
int select_pro(string obj, int p) {
	wstring t = L"", obj_;
	obj_ = stringtowstring(obj);
	//判断直辖市
	t += obj_[0]; t += obj_[1];//取地址前两位
	for (int i = 0; i < 4; i++) {
		if (t == direct_pro[i]) {
			addr[p].province = t; addr[p].city = t; addr[p].city += L"市";
			if (obj_[2] == L'市') { return 3; }
			else return 2;
			break;
		}
	}
	//判断自治区
	wstring z; z += obj_[0]; z += obj_[1];
	if (z == autop[2]) { addr[p].province = L"西藏自治区"; return 5; }
	z += obj_[2];
	if (z == autop[0]) { addr[p].province = L"内蒙古自治区"; return 6; }
	z += obj_[3];
	if (z == autop[1]) { addr[p].province = L"宁夏回族自治区"; return 7; }
	else if (z == autop[3]) { addr[p].province = L"广西壮族自治区"; return 7; }
	z += obj_[4];
	if (z == autop[4]) { addr[p].province = L"新疆维吾尔自治区"; return 8; }
	//判断普通省份
	else {
		if (obj_[0] == L'黑') {
			if (obj_[3] != L'省') {
				addr[p].province = L"黑龙江省";
				return 3;
			}
			else { addr[p].province = L"黑龙江省"; return 4; }
		}//判断是否为黑龙江省
		else {
			for (int j = 0; j < 22; j++) {
				if (t == provincebook[j]) {
					t += L"省";
					if (obj_[2] == L'省') { addr[p].province = t; return 3; break; }
					else { addr[p].province = t; return 2; break; }
				}
			}
		}
	}
	return 0;
}
int select_city(wstring obj, int c) {
	wstring city_ = L""; int i;
	city_ += obj[0]; city_ += obj[1];
	for (i = 0; i < 332; i++) {
		if (city_ == city[i]) {
			city_ += L"市";
			addr[c].city = city_;
			if (obj[2] == L'市') {
				return 3; break;
			}
			else {
				  return 2; break; 
			}	
		}
	}
	city_ += obj[2];
	for (i = 0; i < 332; i++) {
		if (city_ == city[i]) {
			city_ += L"市";
			addr[c].city = city_;
			if (obj[3] == L'市') {
				return 4; break;
			}
			else {
				return 3; break;
			}
		}
	}
	city_ += obj[3];
	for (i = 0; i < 332; i++) {
		if (city_ == city[i]) {
			city_ += L"市";
			addr[c].city = city_;
			if (obj[4] == L'市') {
				return 5; break;
			}
			else {
				return 4; break;
			}
		}
	}
	return 0;
}
//判断二级地址并赋值给city
//int select_city(wstring obj, int c) {
//	wstring city_ = L"";
	//识别“市”关键字
//	for (int i = 0; i < 5; i++) {
//		city_ += obj[i];
//		if (obj[i] == L'市') {
//			addr[c].city = city_;
//			return i + 1; break;
//		}
//	}
//	return 0;
//}
//判断三级地址并赋值给couty
int select_county(wstring obj, int c) {
	wstring county_ = L"";
	int len = obj.length();
	//识别“区”、“县”关键字
	for (int i = 0; i < len; i++) {
		county_ += obj[i];
		if (obj[i] == L'县' || obj[i] == L'区') {
			addr[c].county = county_;
			return i + 1; break;
		}
	}
	return 0;
}
//判断四级地址并赋值给street
int select_street(wstring obj, int c) {
	wstring street_ = L"";
	int len = obj.length();
	//识别“街道”、“镇”、“乡”关键字
	for (int i = 0; i < len; i++) {
		street_ += obj[i];
		if (obj[i] == L'镇' || obj[i] == L'乡' || obj[i] == L'道') {
			addr[c].street = street_;
			return i + 1; break;
		}
	}
	return 0;
}
void select_detailaddr(wstring obj, int c) {
	int len = (int)obj.length();
	wstring detailaddr_ = L"";
	for (int i = 0; i < len - 1; i++) {
		detailaddr_ += obj[i];
	}
	addr[c].detailaddr = detailaddr_;
}
int main()
{

	ifstream inFile;
	inFile.open("C:\\vs\\1.txt", ios::in); 
	if (!inFile) {
		cout << "error opening source file." << endl;
	}
	//else {cout << "success" << endl;}
	ofstream outFile("2.txt", ios::out);
	if (!outFile) {
		inFile.close();
		cout << "error opening destination file." << endl;
		return 0;
	}
	//else {cout << "open success" << endl;}
	string temp;
	int i = 0;
	while (getline(inFile, temp)) {
		addr[i].total = temp;
		i++;
	}
	string c, name_, telnum_;
	wstring c_;
	int j, l, k, x;
	wcout.imbue(std::locale("chs"));
	wcout << L"[";
	outFile << "[";
	for (j = 0; j < i-1; j++)
	{
		c = addr[j].total;
		l = c.find(",");
		name_ = c.substr(0, l);//提取名字
		c.erase(0, l + 1);//删除名字和逗号
		k = c.find_first_of("1");
		telnum_ = c.substr(k, 11);//提取号码
		c.erase(k, 11);//删除号码
		addr[j].telnum = telnum_;
		addr[j].name = name_;
		x = select_pro(c, j);
		c.erase(0, x + x);//删除省份
		wstring c_ = stringtowstring(c);
		x = select_city(c_, j);
		c_.erase(0, x);//删除市
		x = select_county(c_, j);
		c_.erase(0, x);//删除县、区
		x = select_street(c_, j);
		c_.erase(0, x);//删除街道、镇、乡
		select_detailaddr(c_, j);
		wstring n = stringtowstring(addr[j].name), tel = stringtowstring(addr[j].telnum);
		string  s = wstringtostring(addr[j].province), ss = wstringtostring(addr[j].city), sss = wstringtostring(addr[j].county), ssss = wstringtostring(addr[j].street), sssss = wstringtostring(addr[j].detailaddr);
		wcout.imbue(std::locale("chs"));
		wcout<< L"{“姓名”:“" <<n<<  L"”，“手机”：“"<<tel<< L"”，“地址”：[“" << addr[j].province << L"”，“" << addr[j].city << L"”，“" << addr[j].county << L"”，“" << addr[j].street << L"”，“" << addr[j].detailaddr << L"”]}，" << endl;
		outFile << "{“姓名”:“" << addr[j].name << "”，“手机”：“" << addr[j].telnum << "”，“地址”：[“" << s << "”，“" << ss << "”，“" << sss << "”，“" << ssss << "”，“" << sssss << "”]}，" << endl;
	}
	//输出最后一行
	c = addr[j].total;
	l = (int)c.find(",");
	name_ = c.substr(0, l);//提取名字
	c.erase(0, l + 1);//删除名字和逗号
	k = (int)c.find_first_of("1");
	telnum_ = c.substr(k, 11);//提取号码
	c.erase(k, 11);//删除号码
	addr[j].telnum = telnum_;
	addr[j].name = name_;
	x = select_pro(c, j);
	c.erase(0, x + x);//删除省份
	wstring c2 = stringtowstring(c);
	x = select_city(c2, j);
	c2.erase(0, x);//删除市
	x = select_county(c2, j);
	c2.erase(0, x);//删除县、区
	x = select_street(c2, j);
	c2.erase(0, x);//删除街道、镇、乡
	select_detailaddr(c2, j);
	//addr[j].detailaddr = c_;
	wstring n = stringtowstring(addr[j].name), tel = stringtowstring(addr[j].telnum);
	string  s = wstringtostring(addr[j].province), ss = wstringtostring(addr[j].city), sss = wstringtostring(addr[j].county), ssss = wstringtostring(addr[j].street), sssss = wstringtostring(addr[j].detailaddr);
	wcout.imbue(std::locale("chs"));
	wcout << L"{“姓名”:“" << n << L"”，“手机”：“" << tel << L"”，“地址”：[“" << addr[j].province << L"”，“" << addr[j].city << L"”，“" << addr[j].county << L"”，“" << addr[j].street << L"”，“" << addr[j].detailaddr << L"”]}";
	outFile << "{“姓名”:“" << addr[j].name << "”，“手机”：“" << addr[j].telnum << "”，“地址”：[“" << s << "”，“" << ss << "”，“" << sss << "”，“" << ssss << "”，“" << sssss << "”]}";
	wcout << L"]";
	outFile << "]";
	inFile.close();
	outFile.close();
	return 0;
}
