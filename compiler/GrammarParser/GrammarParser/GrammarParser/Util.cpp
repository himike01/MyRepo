#include "Util.h"
#include <string>
unordered_map<string, unordered_set<string>> Util::eliminateTheLeftRecursion(unordered_set<string> noneTerminal,unordered_map<string, unordered_set<string>>& splitedProductions) {
	//ѭ����������ݹ�
	vector<string> order;
	for (const auto& a : noneTerminal)
		order.push_back(a);
	int size = noneTerminal.size();
	for (int i=0; i < size; i++) {
		//���ݹ�ķ��ս��
		string Si = order[i];
		//�˷��ս���Ĳ���ʽ
		unordered_set<string> nowRight = splitedProductions[Si];
		for (int j = 0; j < i; j++) {
			//��ǰ���Ĳ���ʽ�󲿵ķ���
			std::string Sj = order[j];
			unordered_set<string> nowReplaceRight = splitedProductions[Sj];
			pair<string, unordered_set<string>> returnPair;
			auto tmpTraverse = nowReplaceRight;
			for (const auto& rightPart : tmpTraverse) {
				//���ֳ�ͻ
				if (rightPart.size() >= Si.length()&&Si == rightPart.substr(0, Si.length())) {
					string tmpStr = rightPart.substr(Si.length(), rightPart.size()- Si.length());
					//ɾ���������ʽ
					nowReplaceRight.erase(rightPart);
					for (auto replacePart : nowRight) {
						if (replacePart=="#")
						{
							replacePart = "";
						}
						//�����滻���ֱ����ݹ����ʽ
						nowReplaceRight.insert(replacePart + tmpStr);
					}
				}
			}
			splitedProductions.erase(Sj);
			//�����ȫ������ʽ֮���滻Ϊ�µĹ���
			
			splitedProductions.insert(pair<string, unordered_set<string>>(Sj, nowReplaceRight));
		}
		
	}
	//����ֱ����ݹ�
	//S->Sabc|abc|bc|c
	eliminateTheDirectLeftRecursion(splitedProductions);
	return splitedProductions;
}

unordered_map<string, unordered_set<string>> Util::eliminateTheDirectLeftRecursion(unordered_map<string, unordered_set<string>>& splitedProductions) {

	for (const auto& nowProduction : splitedProductions) {
		bool flag = false;
		string nowLeft = nowProduction.first;
		unordered_set<string> nowRight = nowProduction.second;
		string possibleNewLeft = nowLeft ;
		unordered_set<string> possibleNewRight;
		string possiblAddLeft = nowLeft + "'";
		unordered_set<string> possibleAddRight;
		string possibleRight;
		for (const auto& nowRightPart : nowRight){
			if (nowLeft ==nowRightPart.substr(0,nowLeft.length())) {
				//���ֳ�ͻ����������
				flag = true;
				break;
			}
		}
		if (flag) {
			splitedProductions.erase(nowLeft);
			for (const auto& nowRightPart : nowRight) {
				//��λ���
				if (nowLeft == nowRightPart.substr(0, nowLeft.length())) {
					
					possibleAddRight.insert(nowRightPart.substr(nowLeft.length(), nowRightPart.length() - nowLeft.length())+ possiblAddLeft);
				}
				else {
					if (nowRightPart == "#")
						possibleNewRight.insert(possiblAddLeft);
					else
					possibleNewRight.insert(nowRightPart+possiblAddLeft );
				}
			}
			possibleAddRight.insert("#");
			splitedProductions.insert(pair<string, unordered_set<string>>(possibleNewLeft, possibleNewRight));
			splitedProductions.insert(pair<string, unordered_set<string>>(possiblAddLeft, possibleAddRight));
		}


	}

	return splitedProductions;
}