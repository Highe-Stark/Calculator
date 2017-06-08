#include <iostream>
#include <string>
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
		//    >获取算式，如果用户输入的字符串最后一个字符不是';'，要求用户继续输入
		//    >如果用户输入'q'，结束程序
		while (all.empty() || all[all.size() - 1] != ';') {
			if (all[0] == 'q') break;
			string append;
			getline(cin, append);
			all += append;
		}
		//    >退出程序
		if (all[0] == 'q') break;
		//    >用queue存储多个算式
		queue<string> expres;
		//    >根据';'分割字符串，将单个算式放入queue中
		size_t pre(0), end(0);
		for (size_t i = 0; i != all.size(); ++i) {
			if (all[i] == ';') {
				end = i;
				expres.push(extract(all, pre, end));
				pre = end + 1;
			}
		}
		//    >计算queue中的算式,直到queue为空
		while (!expres.empty()) {
			//    >当前待计算算式
			string& curr = expres.front();
			TokenStream ts(curr);
			//     >计算算式
			try {
				double res = Expression(ts);
				//     >如果算式最后带 'M'，存储计算结果
				if (curr[curr.size() - 1] == 'M') {
					M = res;
				}
				cout << "=" << res << "\n" << endl;
			}
			//     >如果计算过程中出现数学错误，输错错误信息
			catch (runtime_error err) {
				cout << err.what() << "\n" << endl;
			}
			//     >弹出当前算式
			expres.pop();
		}
	}
	return 0;
}