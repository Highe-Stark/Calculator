#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <queue>
#include "Grammer.h"
#include "Token.h"
#include "Function.h"

int main()
{
	using namespace std;

	while (true) {
		cout << "Enter q to exit.\n>";
		string all;
		//    >��ȡ��ʽ������û�������ַ������һ���ַ�����';'��Ҫ���û���������
		//    >����û�����'q'����������
		while (all.empty() || all[all.size() - 1] != ';') {
			if (all[0] == 'q') break;
			string append;
			getline(cin, append);
			all += append;
		}
		//    >�˳�����
		if (all[0] == 'q') break;
		//    >��queue�洢�����ʽ
		queue<string> expres;
		//    >����';'�ָ��ַ�������������ʽ����queue��
		size_t pre(0), end(0);
		for (size_t i = 0; i != all.size(); ++i) {
			if (all[i] == ';') {
				end = i;
				expres.push(extract(all, pre, end));
				pre = end + 1;
			}
		}
		//    >����queue�е���ʽ,ֱ��queueΪ��
		while (!expres.empty()) {
			//    >��ǰ��������ʽ
			string& curr = expres.front();
			TokenStream ts(curr);
			//     >������ʽ
			try {
				double res = Expression(ts);
				//     >�����ʽ���� 'M'���洢������
				if (curr[curr.size() - 1] == 'M') {
					M = res;
				}
				cout << "=" << res << "\n" << endl;
			}
			//     >�����������г�����ѧ������������Ϣ
			catch (runtime_error err) {
				cout << err.what() << "\n" << endl;
			}
			//     >������ǰ��ʽ
			expres.pop();
		}
	}
	return 0;
}