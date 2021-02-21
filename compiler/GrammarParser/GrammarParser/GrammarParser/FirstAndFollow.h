#pragma once
#include<iostream>
#include<string>
#include<set>
#include<map>
#include <Windows.h>
#include <fstream>
#include<vector>
#include <unordered_map>
#include <unordered_set>
#include "Config.h"
using namespace std;
/// <summary>
/// ʹ�ñ��๹��First��Follow���ϣ�����˳��Ϊinit(),splitProductions(),getFirst(),getFollow()
/// </summary>
class FirstAndFollow {
public:
	string fileName = PRODUCTIONRULE; 
	FirstAndFollow();
	/// <summary>
	/// ����ʽ����
	/// </summary>
	/// un
	unordered_set<string> productions;
	
	/// <summary>
	/// �ֽ��Ĳ���ʽ����
	/// </summary>
	unordered_map<string, unordered_set<string>> splitedProductions;
	/// <summary>
	/// �ս������
	/// </summary>
	unordered_set<string> terminalSymbol;
	/// <summary>
	/// ���ս������
	/// </summary>
	unordered_set<string> noneTerminal;
	/// <summary>
	/// First��
	/// </summary>
	unordered_map<string, unordered_set<string>> first;
	/// <summary>
	/// Follow��
	/// </summary>
	unordered_map<string, unordered_set<string>> follow;
	/// <summary>
	/// ����Ŀ¼
	/// </summary>
	/// <param name="name"></param>
	void setFileName(const string& name) { this->fileName = name; }
	/// <summary>
	/// ���ļ���ȡ����ʽ
	/// </summary>
	void init();
	/// <summary>
	/// �ֽ����ʽ
	/// </summary>
	void splitProductions();
	/// <summary>
	/// ����ս���ͷ��ս��
	/// </summary>
	void findVtAndVn();
	/// <summary>
	/// �ж��Ƿ��Ƿ��ս��
	/// </summary>
	/// <param name="s">�ַ���s</param>
	/// <returns></returns>
	bool isVn(const string& s) const;
	/// <summary>
	/// �ж��Ƿ����ս��
	/// </summary>
	/// <param name="s">�ַ���s</param>
	/// <returns></returns>
	bool isVt(const string& s) const;
	unordered_set<string> getOneFirst(string s);//��õ������ս��first��
	void getFirst();//������з��ս��first��
	/// <summary>
	/// ��ȡ�ַ�����First����
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	unordered_set<string> getSymbolStringFirst(const string&);
	void getFollow();//������з��ս��follow��
};