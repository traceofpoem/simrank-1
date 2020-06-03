#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "../simrank.hpp"

using namespace std;


void split(const string& s, vector<string>& sv, const char flag = ' ') {
	sv.clear();
	istringstream iss(s);
	string temp;

	while (getline(iss, temp, flag)) {
		sv.push_back(temp);
		//sv.push_back(stoi(temp));
	}
	return;
}


int main(int argc, char *argv[]) {
	SimRank<std::string> example(5, 0.8);
	ifstream ifs;
	ofstream ofs;
	string buf;

	vector<string> sv;
	string fname;
	string fout;
	double weight = 1.0;
	bool outflag = false;
	bool inflag = false;

	//string s("长江证券_韩轶超,002352.SZ");
	//vector<string> sv;
	//cout << sv[0] << endl;
	//for (const auto& s : sv) {
	//	cout << s << endl;
	//}

	//return 0;
	outflag = false;
	if (argc == 1)
	{
		example.add_edge("liup", "1", weight);
		example.add_edge("liup", "2", weight);
		//example.add_edge("djh", "2");
		//example.add_edge("djh", "5");
		//example.add_edge("lcj", "1");
		//example.add_edge("lcj", "4");
	}
	else
	{
		fname = argv[1];
		fout = argv[2];
		inflag = true;
		outflag = true;
	}
	if (inflag)
		ifs.open(fname,ios::in);
	if (outflag)
		ofs.open(fout, ios::out);
	if (inflag && !ifs.is_open())
	{
		cout << "输入文件打开失败！" << endl;
		return 0;
	}

	if (outflag && !ofs.is_open())
	{
		cout << "输出文件打开失败！" << endl;
		return 0;
	}
	
	while (getline(ifs, buf))
	{
		split(buf, sv, ',');
		weight = stod(sv[2]);
		cout << buf <<","<< weight << endl;
		example.add_edge(sv[0], sv[1],weight);
		//cout << buf << endl;
	}
	ifs.close();
	//return 0;

	

	cout << "开始计算" << endl;
	example.calculate_simrank();

	for (std::string a : example.nodes()) {
		for (std::string b : example.nodes()) {
			if (a >= b) { continue; }
			double s = example.similarity(a, b);
			if (s > 0) {
				if(outflag)
					ofs << a << ","<< b<<","<< s << std::endl;
				else
					std::cout << "similarity(" << a << ", " << b << ") = " << s << std::endl;

			}
		}
	}
	ofs.close();

	return 0;
}
