#include "PredictiveAnalysis.h"

//<summary>
//���캯����begin�ǿ�ʼ����
//</summary>
//<param name="begin"></param>
PredictiveAnalysis::PredictiveAnalysis(const string& begin, const FirstAndFollow* ff,const  PredictiveParsing* pp) :S({ "#",begin }), iter(0), ff(ff), pp(pp) {

}
void PredictiveAnalysis::init() {
	printf("�������ַ���������<50����#�Ž�����:\n");
	cin >> sentense;
	loopAndAnalyze();
}

void PredictiveAnalysis::loopAndAnalyze() {
	a = sentense.at(iter);
	string nowTop = S.top();
	S.pop();
	//�ս����Vt�����ս����Vn
	//���ս��
	if (ff->isVt(nowTop)) {
		if (nowTop == "#" && a == "#") {
			cout << "ƥ��ɹ���" << endl;
			return;
		}
		else if (nowTop == a) {
			iter++;
			loopAndAnalyze();
		}
		else error();
	}
	//���ս��
	else {
		/*if (nowTop == "#" && a == "#") {
			return;
		}
		else*/ 
		{
		//
		auto tmpNow = pp->predictiveAnalysisTable.at(nowTop).at(a);
		if (tmpNow.empty()) {
			error();
		}
		else {
			string rightPart = tmpNow.find(nowTop)->second;
			if (rightPart != "#") {
				stack<string> tmpStack;
				for (int i = 0; i < rightPart.size(); i++) {
					if (i + 1 <= rightPart.size() && rightPart[i + 1] == '\'') {
						tmpStack.push(string({ rightPart[i] }).append("'"));
						i++;
					}
					else tmpStack.push(string({ rightPart[i] }));
				}
				while (!tmpStack.empty()) {
					S.push(tmpStack.top());
					tmpStack.pop();
				}
				//if(*(iter.operator*)=="#")
				
			}
			//���ս�����ص�
			loopAndAnalyze();
		}
		}
	}
}
void PredictiveAnalysis::error() {
	throw "Predictive analysis error!";
}