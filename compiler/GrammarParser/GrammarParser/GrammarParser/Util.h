#pragma once
#include "FirstAndFollow.h"
class Util
{
public:
	/// <summary>
	/// ������ݹ�
	/// </summary>
	/// <param name=""></param>
	static unordered_map<string, unordered_set<string>> eliminateTheLeftRecursion(unordered_set<string> ,unordered_map<string, unordered_set<string>>&);
	/// <summary>
	/// ����ֱ����ݹ�
	/// </summary>
	static unordered_map<string, unordered_set<string>> eliminateTheDirectLeftRecursion(unordered_map<string, unordered_set<string>>&);
	/// <summary>
	/// �ж��Ƿ���LL��1���ķ�
	/// 1.�ķ���������ݹ�
	//	2.�ķ���ÿһ�����ս������ʽ��ÿһ����ѡʽ��FIRST���������ཻ�����Է�����ȡ���������ӽ����������
	//	3.����ķ��е�ÿһ�����ս����FIRST�������Цţ���ÿһ����ѡʽ��FIRST���͸÷��ս����FOLLOW�����ཻ
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	bool judLL1(FirstAndFollow&);

};

