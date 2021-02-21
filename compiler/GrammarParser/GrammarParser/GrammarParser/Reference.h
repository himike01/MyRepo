#pragma once
#include<iostream>
#include<string>
#include<set>
#include<map>
#include <Windows.h>
#include <fstream>

using namespace std;

/*
���з��ս����Ϊ�����ַ���#����մ�
E->TE'
E'->+TE'|#
T->FT'
T'->*FT'|#
F->(E)|i
*/

class FF {
public:
	string fileName = "productions.txt";
	set<string> productions;//����ʽ����
	map<string, set<string>> split_productions;//�ֽ��Ĳ���ʽ����
	set<string> Vt;//�ս������
	set<string> Vn;//���ս������
	map<string, set<string>> first;//First��
	map<string, set<string>> follow;//Follow��

	void init();//���ļ���ȡ����ʽ
	void splitProductions();//�ֽ����ʽ
	void findVtAndVn();//����ս���ͷ��ս��
	bool isVn(string s);
	bool isVt(string s);
	set<string> getOneFirst(string s);//��õ������ս��first��
	void getFirst();//������з��ս��first��
	void getFollow();//������з��ս��follow��
	void SSS();//��folloe���Ĳ���3
};

void FF::init() {
	string line;
	ifstream in(fileName);
	if (in) {
		//�ķ���ʼ���ŵ�follow���з���$
		getline(in, line);
		productions.insert(line);
		follow[line.substr(0, 1)].insert("$");
		cout << line << endl;
		while (getline(in, line)) {
			productions.insert(line);
			cout << line << endl;
		}
	}
}
void FF::splitProductions() {
	int position = 0;
	for (set<string>::iterator it = productions.begin(); it != productions.end(); it++) {
		string temp = *it;
		for (int i = 0; i < temp.length(); i++) {
			position = temp.find("->");
			string s = temp.substr(0, position);
			string ss = temp.substr(position + 2);
			set<string>sss;
			string t;
			for (int j = 0; j < ss.length(); j++) {
				if (ss[j] == '|') {
					sss.insert(t);
					t = "";
				}
				else
				{
					t.append(ss.substr(j, 1));
				}

			}
			sss.insert(t);
			split_productions.insert(pair<string, set<string>>(s, sss));
		}
	}
	for (map<string, set<string>>::iterator it = split_productions.begin(); it != split_productions.end(); it++) {
		cout << it->first << "    ";
		for (set<string>::iterator ii = it->second.begin(); ii != it->second.end(); ii++) {
			cout << *ii << "    ";
		}
		cout << endl;
	}


}
void FF::findVtAndVn() {
	for (set<string>::iterator it = productions.begin(); it != productions.end(); it++) {
		string temp = *it;
		for (int i = 0; i < temp.length(); i++) {
			if (temp[i] == '-' || temp[i] == '>' || temp[i] == '|')
				continue;
			//�Ǵ�д��ĸ
			if (temp[i] >= 'A' && temp[i] <= 'Z') {
				//�����'
				if (temp[i + 1] == '\'') {
					Vn.insert(temp.substr(i, 2));
					i++;
				}
				else {
					Vn.insert(temp.substr(i, 1));
				}
			}
			//���ս��
			else
			{
				Vt.insert(temp.substr(i, 1));
			}
		}
	}

	cout << "���ս��" << endl;
	for (set<string>::iterator it = Vn.begin(); it != Vn.end(); it++) {
		cout << *it << endl;
	}

	cout << "�ս��" << endl;
	for (set<string>::iterator it = Vt.begin(); it != Vt.end(); it++) {
		cout << *it << endl;
	}
}
bool FF::isVn(string s) {
	if (Vn.find(s) != Vn.end()) {
		return true;
	}
	return false;
}
bool FF::isVt(string s) {
	if (Vt.find(s) != Vt.end()) {
		return true;
	}
	return false;
}
unordered_set<string> FF::getOneFirst(string s) {
	if (split_productions.count(s) > 0) {
		unordered_set<string>temp = split_productions[s];
		for (unordered_set<string>::iterator it = temp.begin(); it != temp.end(); it++) {
			string stemp = *it;
			if (stemp == "#") {
				first[s].insert("#");
			}
			else {
				int flagAll = 0;//���еķ��ս����first������#��
				for (int i = 0; i < stemp.length(); i++) {
					int flag = 0;//��ǰ�ķ��ս����first����#��
					if (stemp[i + 1] == '\'') {//��'�ķ��ս��
						unordered_set<string>t1 = getOneFirst(stemp.substr(i, 2));
						for (unordered_set<string>::iterator ii = t1.begin(); ii != t1.end(); ii++) {
							if (*ii == "#") {//��ʱ�մ����ɲ���
								flag = 1;
							}
							else {
								first[s].insert(*ii);
							}
						}
						i++;
					}
					else if (isVn(stemp.substr(i, 1)))//�������ս��
					{
						unordered_set<string>t2 = getOneFirst(stemp.substr(i, 1));
						for (unordered_set<string>::iterator ii = t2.begin(); ii != t2.end(); ii++) {
							if (*ii == "#") {//��ʱ�մ����ɲ���
								flag = 1;
							}
							else {
								first[s].insert(*ii);
							}
						}
					}
					else {//�ս��
						first[s].insert(stemp.substr(i, 1));
					}
					if (i == stemp.length() - 1 && flag == 1) {
						flagAll = 1;
					}
					if (flag == 0)
						break;
				}
				if (flagAll == 1) {
					first[s].insert("#");
				}
			}
		}
	}
	return first[s];
}
void FF::getFirst() {
	for (auto & split_production : split_productions) {
		getOneFirst(split_production.first);
	}
	cout << "First��" << endl;
	for (auto & it : first) {
		cout << it.first << "  :  ";
		for (unordered_set<string>::iterator ii = it.second.begin(); ii != it.second.end(); ii++)
		{
			cout << *ii << "    ";
		}
		cout << endl;
	}

}
void FF::getFollow() {
	for (map<string, unordered_set<string>>::iterator it = split_productions.begin(); it != split_productions.end(); it++) {
		string left = it->first;
		unordered_set<string>right = it->second;
		for (unordered_set<string>::iterator ii = right.begin(); ii != right.end(); ii++) {
			string temp = *ii;

			for (int i = 0; i < temp.length(); i++) {
				if (isVt(temp.substr(i, 1))) {//�ս��
					continue;
				}
				else if (i + 1 < temp.length() && temp[i + 1] == '\'') {//���С��ķ��ս��
					if (isVt(temp.substr(i + 2, 1))) {//���ս���������ս��
						follow[temp.substr(i, 2)].insert(temp.substr(i + 2, 1));
						i++;
					}
					else {//���ս�������Ƿ��ս��s
						//�Ѻ�����ս����first��ff����follow����
						string s;
						if (i + 3 < temp.length() && temp[i + 3] == '\'') {
							s = temp.substr(i + 2, 2);
						}
						else {
							s = temp.substr(i + 2, 1);
						}
						unordered_set<string> ff = first[s];
						for (unordered_set<string>::iterator nn = ff.begin(); nn != ff.end(); nn++) {
							if (*nn != "#")
								follow[temp.substr(i, 2)].insert(*nn);
						}
					}
				}
				else {//�������ķ��ս��

					if (i + 1 < temp.length() && isVt(temp.substr(i + 1, 1))) {//���ս���������ս��
						follow[temp.substr(i, 1)].insert(temp.substr(i + 1, 1));
						i++;
					}
					else {//���ս�������Ƿ��ս��s
						//�Ѻ�����ս����first��ff����follow����
						string s;
						if (i + 2 < temp.length() && temp[i + 2] == '\'') {
							s = temp.substr(i + 1, 2);
						}
						else {
							s = temp.substr(i + 1, 1);
						}
						unordered_set<string> ff = first[s];
						for (unordered_set<string>::iterator nn = ff.begin(); nn != ff.end(); nn++) {
							if (*nn != "#")
								follow[temp.substr(i, 1)].insert(*nn);
						}
					}
				}
			}
		}
	}
	//��һ����Ҫ����м��Σ���Ϊfollow�ǲ���������
	SSS();
	SSS();

	cout << "Follow��" << endl;
	for (map<string, unordered_set<string>>::iterator it = follow.begin(); it != follow.end(); it++) {
		cout << it->first << "  :  ";
		for (unordered_set<string>::iterator ii = it->second.begin(); ii != it->second.end(); ii++)
		{
			cout << *ii << "    ";
		}
		cout << endl;
	}
}
void FF::SSS() {
	for (map<string, unordered_set<string>>::iterator it = split_productions.begin(); it != split_productions.end(); it++) {
		string left = it->first;
		unordered_set<string>right = it->second;
		for (unordered_set<string>::iterator ii = right.begin(); ii != right.end(); ii++) {
			string temp = *ii;
			for (int j = temp.length() - 1; j > 0; j--) {
				string now;
				if (temp[j] == '\'') {
					now = temp.substr(j - 1, 2);
					j--;
				}
				else now = temp.substr(j, 1);
				if (isVt(now)) {//����ʽ������ս��
					break;
				}
				else {//����ʽ����Ƿ��ս��
					unordered_set<string>aa = follow[left];
					for (unordered_set<string>::iterator pp = aa.begin(); pp != aa.end(); pp++) {
						follow[now].insert(*pp);
					}
				}
				if (first[now].find("#") == first[now].end())
					break;
			}
		}
	}
}
//int main() {
//	FF ff;
//	ff.init();
//	ff.splitProductions();
//	ff.findVtAndVn();
//	ff.getFirst();
//	ff.getFollow();
//}