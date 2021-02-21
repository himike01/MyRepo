#pragma once
#include "FirstAndFollow.h"
/// <summary>
// �ݹ��½��﷨��ʵ���࣬ʹ�õ��﷨��
/// E->TE'
/// E'->+TE' | #
/// T->FT'
/// T'->*FT' | #
//	F->(E) | i
/// </summary>
class FirstRecursiveDescentImpl 
{
public:
	FirstRecursiveDescentImpl(FirstAndFollow&);
	/// <summary>
	/// ��ǰ��������
	/// </summary>
	int schedule;
	string tokens;
	char analysisw[50];
	FirstAndFollow ff;
	/// <summary>
	/// ��ǰ�����Ĵ����������ķ�λ��
	/// </summary>
	int temp;
	/// <summary>
	/// �ж���û��ƥ����
	/// </summary>
	bool jud;
	void error();
	void output(int count);
	void parse_EE();
	void parse_E();
	void parse_T();
	void parse_TT();
	void parse_F();
	void parse_plus();
	void parse_star();
	void parse_leftBracket();
	void parse_rightBracket();
	void parse_i();
};
