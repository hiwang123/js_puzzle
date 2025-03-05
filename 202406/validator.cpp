// hi
#include <bits/stdc++.h>
using namespace std;
#define PB push_back
#define MP make_pair
#define F first
#define S second
using LL = int64_t;
vector<int> score = {
	39538223,
	29145505,
	21538187,
	20201249,
	13002700,
	12812508,
	11799448,
	10711908,
	10439388,
	10077331,
	9288994,
	8631393,
	7705281,
	7151502,
	7029917,
	6910840,
	6785528,
	6177224,
	6154913,
	5893718,
	5773714,
	5706494,
	5118425,
	5024279,
	4657757,
	4505836,
	4237256,
	3959353,
	3605944,
	3271616,
	3190369,
	3104614,
	3011524,
	2961279,
	2937880,
	2117522,
	1961504,
	1839106,
	1793716,
	1455271,
	1377529,
	1362359,
	1097379,
	1084225,
	989948,
	886667,
	779094,
	733391,
	643077,
	576851};
vector<string> cities = {
	"california",
	"texas",
	"florida",
	"newyork",
	"pennsylvania",
	"illinois",
	"ohio",
	"georgia",
	"northcarolina",
	"michigan",
	"newjersey",
	"virginia",
	"washington",
	"arizona",
	"massachusetts",
	"tennessee",
	"indiana",
	"maryland",
	"missouri",
	"wisconsin",
	"colorado",
	"minnesota",
	"southcarolina",
	"alabama",
	"louisiana",
	"kentucky",
	"oregon",
	"oklahoma",
	"connecticut",
	"utah",
	"iowa",
	"nevada",
	"arkansas",
	"mississippi",
	"kansas",
	"newmexico",
	"nebraska",
	"idaho",
	"westvirginia",
	"hawaii",
	"newhampshire",
	"maine",
	"rhodeisland",
	"montana",
	"delaware",
	"southdakota",
	"northdakota",
	"alaska",
	"vermont",
	"wyoming" };
constexpr int n = 5;
vector<vector<char>> buildMap(const string& str) {
	vector<vector<char>> ret(n, vector<char>(n));
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			ret[i][j] = str[i*n+j];
	return ret;
}
constexpr int dx[8]={-1, -1, -1, 0, 0, 1, 1, 1};
constexpr int dy[8]={-1, 0, 1, -1, 1, -1, 0, 1};
bool dfs(int l, pair<int,int> pos, const vector<vector<char>> &mp, const string &str) {
	if(l == str.length()) return true;
	bool ret = false;
	for(int d=0;d<8;d++) {
		int nx = pos.first + dx[d];
		int ny = pos.second + dy[d];
		if(nx <0 || nx >=n || ny < 0 || ny >=n) continue;
		if(mp[nx][ny] == str[l]) {
			ret |= dfs(l+1, {nx, ny}, mp, str);
		}
	}
	return ret;
}

string search(const vector<vector<char>> &mp, const string &city) {
	for(int i=0;i<city.length();i++) {
		string tmp = city;
		for(int j=0;j<26;j++) {
			tmp[i] = j + 'a';
			for(int x = 0; x < n; x++)
				for(int y=0; y<n; y++)
					if(mp[x][y]==tmp[0] && dfs(1, {x, y}, mp, tmp))
						return tmp;
		}
	}
	return "";
}
int main(void) {
	string ans = "utewkhcnrgwoaiomislfxecoa";
	vector<vector<char>> mp = buildMap(ans);
	int tot=0;
	for(int i=0;i<score.size();i++) {
		string sim = search(mp, cities[i]);
		if(sim.length()) {
			tot += score[i];
			cout << cities[i] << " <-- " << sim << endl;
		}
	}
	cout << tot << endl;
    return 0;
}
