#pragma once
#include <unordered_map>
#include <map>
#include<unordered_set>
#include <string>
#include "FirstAndFollow.h"
//#include <pair>
using namespace std;
using table_type = unordered_map<string, unordered_map<string, unordered_multimap<string, string>>>;
/// <summary>
/// Ԥ�������ʵ���� Ԥ�������ֻ֧��LL(1)�ķ���ʹ��֮ǰ��Ҫ����ķ� unordered_multimap��Ϊ��δ��֧����չ
/// </summary>
class PredictiveParsing
{
public:
	table_type predictiveAnalysisTable;
	void getPredictiveAnalysisTable(FirstAndFollow&);
};

