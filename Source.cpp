#include <iostream>
#include <vector>
#include <string>
#include "Token.h"
#include "Function.h"
#include "Grammer.h"
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;

int main()
{
	cout << "Enter q to exit." << endl;
	vector<TokenStream>::size_type pos(-1);
	while(true) {
		string readin;
		vector<TokenStream> vec_tk;
		cout << ">";
		getline(cin, readin);
		if (readin[0] == 'q') break;
		while (readin[readin.size() - 1] != ';') {
			string temp;
			getline(cin, temp);
			readin += temp;
		}
		string::size_type pre(0), end(0);
		for (string::size_type ix = 0; ix != readin.size(); ++ix) {
			if (readin[ix] == ';') {
				end = ix;
				string transfer = extract(readin, pre, end);
				if (transfer[transfer.size() - 1] == 'M') pos = vec_tk.size();
				TokenStream ts;
				ts.con_stream(transfer);
				vec_tk.push_back(ts);
				pre = end + 1;
			}
		}
		for (vector<TokenStream>::size_type it = 0; it != vec_tk.size(); ++it) {
			try {
				double res = Expression(vec_tk[it]);
				if (it == pos) {
					M = res;
					pos = -1;
				}
				cout << "=" << res << "\n" << endl;
			}
			catch (runtime_error err) {
				cout << err.what() << endl;
			}
		}

	}
	system("pause");
	return 0;
}