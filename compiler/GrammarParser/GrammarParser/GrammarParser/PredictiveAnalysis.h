#pragma once
#include <string>
#include <stack>
#include "FirstAndFollow.h"
#include "PredictiveParsing.h"
using namespace std;
/// <summary>
/// Ԥ�������ʵ����
/// </summary>
class PredictiveAnalysis
{
public:
	/// <summary>
	/// Sջ�����ڴ�űȶԷ���
	/// </summary>
	stack<string> S;
	/// <summary>
	/// ��ǰ�������
	/// </summary>
	string a;
	/// <summary>
	/// ������ָ��
	/// </summary>
	int iter;
	/// <summary>
	/// �������
	/// </summary>
	string sentense;
	explicit PredictiveAnalysis(const string& begin,  const FirstAndFollow* ff,const  PredictiveParsing* pp);
	void loopAndAnalyze();
	void error();
	void init();
	const FirstAndFollow* ff;
	const PredictiveParsing* pp;
};

