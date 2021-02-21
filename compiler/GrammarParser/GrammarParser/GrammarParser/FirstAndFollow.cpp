#include "FirstAndFollow.h"
using namespace std;

FirstAndFollow::FirstAndFollow() {
	cout << "ʹ�ñ��๹��First��Follow���ϣ�����˳��Ϊinit(),splitProductions(),getFirst(),getFollow()" << endl;
}

void FirstAndFollow::init() {
	string line;
	ifstream in(fileName);
	if (in) {
		getline(in, line);
		productions.insert(line);
		//�ķ���ʼ���ŵ�follow���з���$
		//follow[line.substr(0, 1)].insert("$");
		cout << "�ļ��е������ǣ�"<<endl;
		cout << line << endl;
		while (getline(in, line)) {
			productions.insert(line);
			cout << line << endl;
		}
	}
	else {
		throw "Read config file wrong!";
	}
	
}

void FirstAndFollow::splitProductions() {
	int position = 0;
	if (productions.empty())
		throw "δ��ʼ�������ļ�����";
	for (const std::string& nowProductionRule : productions) {
		position = nowProductionRule.find("->");
		string leftProduction = nowProductionRule.substr(0, position);
		string rightProduction = nowProductionRule.substr(position + static_cast <unsigned __int64>(2));
		unordered_set<string> nowRule;

		string rightMolecular;
		for (int j = 0; j < rightProduction.length(); j++) {
			if (rightProduction[j] == '|') {
				nowRule.insert(rightMolecular);
				rightMolecular = "";
			}
			else
			{
				rightMolecular.append(rightProduction.substr(j, 1));
			}
		}
		nowRule.insert(rightMolecular);
		splitedProductions.insert(pair<string, unordered_set<string>>(leftProduction, nowRule));
	}
	/// <summary>
	/// ��Ԫ����
	/// </summary>
	cout << "�ֽ��Ĳ���ʽ���£�" << endl;
	for (auto & splitedProduction : splitedProductions) {
		cout << splitedProduction.first << "    ";
		for (const auto & ii : splitedProduction.second) {
			cout << ii << "    ";
		}
		cout << endl;
	}
}

void FirstAndFollow::findVtAndVn() {
	if (productions.empty())
		throw "δ��ʼ�������ļ�����";
	for (std::string temp : productions) {
		for (int i = 0; i < temp.length(); i++) {
			if (temp[i] == '-' || temp[i] == '>' || temp[i] == '|')
				continue;
			//�Ǵ�д��ĸ
			if (temp[i] >= 'A' && temp[i] <= 'Z') {
				//�����'
				if (temp[i + static_cast<unsigned __int64>(1)] == '\'') {
					noneTerminal.insert(temp.substr(i, 2));
					i++;
				}
				else {
					noneTerminal.insert(temp.substr(i, 1));
				}
			}
			//���ս��
			else
			{
				terminalSymbol.insert(temp.substr(i, 1));
			}
		}
	}
	cout << "���ս��" << endl;
	for (const auto & it : noneTerminal) {
		cout << it << endl;
	}
	cout << "�ս��" << endl;
	for (const auto & it : terminalSymbol) {
		cout << it << endl;
	}
}

bool FirstAndFollow::isVn(const string& s) const {
	if (noneTerminal.empty())
		throw "δ��ʼ�����ս������";
	if (noneTerminal.find(s) !=noneTerminal.end()) {
		return true;
	}
	return false;
}
bool FirstAndFollow::isVt(const string& s) const{
	if (terminalSymbol.empty())
		throw "δ��ʼ���ս������";
	if (terminalSymbol.find(s) != terminalSymbol.end()) {
		return true;
	}
	return false;
}
unordered_set<string> FirstAndFollow::getOneFirst(string s) {
	if (splitedProductions.count(s) <= 0)	throw "�ս�����ʽ�������δ��ʼ��";
	else {
		unordered_set<string> nowProduction = splitedProductions[s];
		for (const auto& it : nowProduction) {
			string nowRightPart = it;
			if (nowRightPart == "#")
				first[s].insert("#");
			else {
				int allIsNull = 0;
				for (int i = 0; i < nowRightPart.length(); i++) {
					//��ǰ���ս����#
					int flag = 0;
					if (nowRightPart[i + static_cast <unsigned __int64>(1)] == '\'') {
						unordered_set<string> nextFirst = getOneFirst(nowRightPart.substr(i, 2));
						for (const auto& next : nextFirst) {
							//��ʱҪ������һ������
							if (next == "#")
								flag = 1;
							else first[s].insert(next);
						}
						i++;
					}
					else if (isVn(nowRightPart.substr(i, 1))) {
						unordered_set<string> nextFirst = getOneFirst(nowRightPart.substr(i, 1));
						for (const auto& next : nextFirst) {
							//��ʱҪ������һ������
							if (next == "#")
								flag = 1;
							else first[s].insert(next);
						}
					}
					else if(isVt(nowRightPart.substr(i, 1))){
						string terminalTemp = nowRightPart.substr(i, 1);
						first[s].insert(terminalTemp);
					}
					if (i==nowRightPart.length()-1&&flag ==1)
					{
						allIsNull = 1;
					}
					if (flag == 0)
						break;
				}
				if (allIsNull)
					first[s].insert("#");
			}
		}
	}
	return first[s];
}


void FirstAndFollow::getFirst() {
	for (auto& split_production : splitedProductions) {
		getOneFirst(split_production.first);
	}
	for (auto& terminal : terminalSymbol) {
		first[terminal].insert(terminal);
	}
	/// <summary>
	/// ��Ԫ����
	/// </summary>
	cout << "First��" << endl;
	for (auto& it : first) {
		cout << it.first <<((it.first.length()==1)?"  ":" ")<< ": { ";
		for (const auto & ii : it.second)
		{
			cout <<" "<< ii << " ;";
		}
		cout <<"\b"<<" }"<< endl;
	}
}

unordered_set<string> FirstAndFollow::getSymbolStringFirst(const string& symbolString){
	decltype(getSymbolStringFirst(symbolString)) First;
	if (symbolString == "#")
		return { "#" };
	string nowString;
	bool continueFlag = true;
	for (int i = 0; i < symbolString.size()&& continueFlag; i++) {
		continueFlag = false;
		if (i + 1 <= symbolString.size() - 1 && symbolString[i + 1] == '\'') {
			nowString = symbolString.substr(i, 2);
			if (first.find(nowString) != first.end()) {
				auto copyString = first[nowString];
				for (const auto& j :copyString) {
					if (j == "#") {
						continueFlag = true;
						if(i+1==symbolString.size())
							First.insert("#");
					}
					else First.insert(j);
				}
			}
			i++;
		}
		else{
			nowString = symbolString.substr(i,1);
			if (first.find(nowString) != first.end()) {
				auto copyString = first[nowString];
				for (const auto& j : copyString) {
					if (j == "#")
					{
						if (i  == symbolString.size())
							First.insert("#");
						continueFlag = true;
					}
					
					else First.insert(j);
				}
			}
		}
	}
	return First;
}

void FirstAndFollow::getFollow() {
	bool isFirst = true;
	size_t begSize = 0;
	size_t endSize = 0;
	for(const auto& var : follow)
	{
		begSize += (var.second.size());
	}
	for (const auto& nowProduction : splitedProductions) {
		
		if (isFirst) {
			follow[nowProduction.first].emplace(string{ "#" });
			isFirst = false;
		}
		unordered_set<string>  RightPart = nowProduction.second;
		for (const string& nowRightPart : RightPart) {
			for (int i = 0; i < nowRightPart.size(); i++) {
	//			//���һ��Ԫ�أ�С��i������'
				if (i == nowRightPart.size()-1 && isVn({ nowRightPart[i] })) {
					for(const auto& nowCopy: follow[nowProduction.first])
						follow[to_string(nowRightPart[i])].emplace(nowCopy);
					//existFollow.emplace(follow(nowProduction.first));
				}
				//����'�ķ��ս��
				else if (nowRightPart[i + static_cast < unsigned __int64>(1)] == '\'') {
					string nowB = string({nowRightPart[i]}).append("'");
					//����û��Ԫ����
					if (i + static_cast < unsigned __int64>(1) == nowRightPart.size() - 1) {
						for (const auto& nowCopy : follow[nowProduction.first])
							follow[nowB].emplace(nowCopy);
					}
					//��������������Ԫ��
					else if (i + 3 <= nowRightPart.size() - 1) {
						if (nowRightPart[i + 3] == '\'') {
							//��һ�����ս����first���ϰ���#
							string tmpB = string({nowRightPart[i + 2]}).append("'");
							if (first[tmpB].find("#") != first[tmpB].end()) {
								for (const auto& nowCopy : follow[nowProduction.first])
									follow[nowB].emplace(nowCopy);
							}
							//������#
							{
								unordered_set<string> tmpFirst = first[tmpB];
								tmpFirst.erase("#");
								for (const auto& nowCopy : tmpFirst)
									follow[nowB].emplace(nowCopy);
							}
						}
						else/* if (isVn({nowRightPart[i + 2]}))*/ {
							string tmpB = {nowRightPart[i + 2]};
							if (first[tmpB].find("#") != first[tmpB].end()) {
								for (const auto& nowCopy : follow[nowProduction.first])
									follow[nowB].emplace(nowCopy);
							}
							{
								unordered_set<string> tmpFirst = first[tmpB];
								tmpFirst.erase("#");
								for (const auto& nowCopy : tmpFirst)
									follow[nowB].emplace(nowCopy);
							}
						}
					}
					//����ֻ��һ��Ԫ��
					else /*if (isVn({nowRightPart[i + 2]}))*/ {
						string tmpB ={ nowRightPart[i + 2]};
						if (first[tmpB].find("#") != first[tmpB].end()) {
							for (const auto& nowCopy : follow[nowProduction.first])
								follow[nowB].emplace(nowCopy);
						}
						 {
							unordered_set<string> tmpFirst = first[tmpB];
							tmpFirst.erase("#");
							for (const auto& nowCopy : tmpFirst)
								follow[nowB].emplace(nowCopy);
						}
					}
					i++;
				}
				//��ͨ�ķ��ս��
				else if (isVn({nowRightPart[i]})) {
					string nowB ={ nowRightPart[i]};
					//����û��Ԫ����
					if (i  == nowRightPart.size() - 1) {
						for (const auto& nowCopy : follow[nowProduction.first])
							follow[nowB].emplace(nowCopy);

					}
					//��������������Ԫ��
					else if (i + 2 <= nowRightPart.size() - 1) {
						if (nowRightPart[i + 2] == '\'') {
							//��һ�����ս����first���ϰ���#
							string tmpB = string({ nowRightPart[i + 1] }).append("'");
							if (first[tmpB].find("#") != first[tmpB].end()) {
								for (const auto& nowCopy : follow[nowProduction.first])
									follow[nowB].emplace(nowCopy);
							}
							{
								unordered_set<string> tmpFirst = first[tmpB];
								tmpFirst.erase("#");
								for (const auto& nowCopy : tmpFirst)
									follow[nowB].emplace(nowCopy);
							}
						}
						else /*if (isVn({nowRightPart[i + 1]}))*/ {
							string tmpB ={ nowRightPart[i + 1]};
							if (first[tmpB].find("#") != first[tmpB].end()) {
								for (const auto& nowCopy : follow[nowProduction.first])
									follow[nowB].emplace(nowCopy);
							}
							{
								unordered_set<string> tmpFirst = first[tmpB];
								tmpFirst.erase("#");
								for (const auto& nowCopy : tmpFirst)
									follow[nowB].emplace(nowCopy);
							}
						}
					}
					//����ֻ��һ��Ԫ��
					else /*if (isVn({nowRightPart[i + 1]})) */{
						string tmpB ={ nowRightPart[i + 1]};
						if (first[tmpB].find("#") != first[tmpB].end()) {
							for (const auto& nowCopy : follow[nowProduction.first])
								follow[nowB].emplace(nowCopy);
						}
						{
							unordered_set<string> tmpFirst = first[tmpB];
							tmpFirst.erase("#");
							for (const auto& nowCopy : tmpFirst)
								follow[nowB].emplace(nowCopy);
						}
					}
				}
				//�ս��
				else {
					continue;
				}
			}
		}

	}
	for (const auto& var : follow)
	{
		endSize += (var.second.size());
	}
	if (begSize != endSize) {
		getFollow();
		return;
	}
	/// <summary>
	/// ��Ԫ����
	/// </summary>
	cout << "Follow��" << endl;
	for (auto& it : follow) {
		cout << it.first << ((it.first.length() == 1) ? "  " : " ") << ": { ";
		for (const auto& ii : it.second)
		{
			cout << " " << ii << " ;";
		}
		cout << "\b" << " }" << endl;
	}
}