// hi
#include <bits/stdc++.h>
using namespace std;
#define PB push_back
#define MP make_pair
#define F first
#define S second
using LL = int64_t;

/*
gcd 12345679 

395061728
061728395
728395061
950617283
283950617
617283950
839506172
506172839
172839506
*/

auto get_factors = [](int n) {
	int d = sqrt(n);
	vector<int> ret;
	for(int i = 2; i<=d;i++) {
		if(n%i==0) {
			ret.push_back(i);
			if(n/i != i)
				ret.push_back(n/i);
		}
	}
	return ret;
};
int tens[10];
inline int get_digit(int n, int d) {
	return (n / tens[d]) % 10;
}
vector<pair<int,int>> known[9];
inline bool is_row(int f, int id) {
	for(const auto& [c, num]: known[id])
		if(get_digit(f, c) != num) return false;
	for(int i=0;i<9;i++) {
		if(i==id) continue;
		for(const auto& [c, num]: known[i])
			if(get_digit(f, c) == num) return false;
	}
	int st = (id/3) * 3;
	for(int i = st; i < st+3; i++) {
		if(i==id) continue;
		for(const auto& [c, num]: known[i]) {
			int x = (c/3) * 3;
			if(get_digit(f, x) == num) return false;
			if(get_digit(f, x+1) == num) return false;
			if(get_digit(f, x+2) == num) return false;
		}
	}
	return true;
}
inline bool check_sudoku(int id, const vector<int>& mp) {
	// column
	for(int j=0;j<9;j++) {
		int x = get_digit(mp[id], j);
		for(int i=id-1;i>=0;i--)
			if(x == get_digit(mp[i], j))
				return false;
	}
	// 3 by 3
	for(int j=0;j<9;j++) {
		int x = get_digit(mp[id], j);
		int jj = (j / 3) * 3;
		for(int i=id-1;i>=(id/3) * 3;i--)
			if(x == get_digit(mp[i], jj) || x == get_digit(mp[i], jj+1) || x == get_digit(mp[i], jj+2))
				return false;
	}
	return true;
}
bool dfs(int gcd, int id, const vector<vector<int>>& rows, vector<int>& mp) {
	if(id == 9) {
		for(auto r: mp) printf("%d\n", r);
		printf("\n");
		return true;
	}
	for(auto r: rows[id]) {
		mp.push_back(r);
		if(check_sudoku(id, mp)) {
			bool ret = dfs(gcd, id+1, rows, mp);
			if(ret) return true;
		}
		mp.pop_back();
	}
	return false;
}
inline bool check(int gcd, const vector<int>& factors) {
	if(factors.size() < 9) return false;
	vector<vector<int>> row(9);
	for(auto f: factors) {
		for(int i=0;i<9;i++) {
			if(is_row(f, i)){
				row[i].push_back(f);
				break;
			}
		}
	}
	for(int i=0;i<9;i++) {
		if(i==4) continue;
		if(row[i].empty()) return false;
	}
	//debug
	printf("%d : ", gcd);
	for(int i=0;i<9;i++) printf("%2d ", row[i].size());
	printf("\n");
	//
	vector<int> mp;
	return dfs(gcd, 0, row, mp);
}
void fill(const vector<int>& digits_, multimap<int, vector<int>> &ret) {
	vector<int> digits=digits_;
	sort(digits.begin(), digits.end());
	vector<int> nums;
	
	for(auto d: digits) printf("%d ", d);
	printf("\n");
	
	map<int, vector<int>> mp;
	do{
		int n = 0;
		for(int d: digits) n = n * 10 + d;
		nums.push_back(n);
		auto factors = get_factors(n);
		for(int f: factors) mp[f].push_back(n);
	}while(next_permutation(digits.begin(), digits.end()));
	for(const auto& [k, v] : mp) {
		ret.insert({k, v});
	}
}
void sol(const multimap<int, vector<int>>& mp) {
	for(auto it= mp.rbegin(); it!=mp.rend(); it++) {
		if(!check(it->first, it->second)) continue;
		return;
	}
}
int main(void) {
	// init
	tens[0]=1;
	for(int i=1;i<10;i++) tens[i]=tens[i-1]*10;
	known[0].emplace_back(1, 2);
	known[1].emplace_back(4, 2);
	known[1].emplace_back(0, 5);
	known[2].emplace_back(7, 2);
	known[3].emplace_back(6, 0);
	known[5].emplace_back(5, 2);
	known[6].emplace_back(4, 0);
	known[7].emplace_back(3, 2);
	known[8].emplace_back(2, 5);
	
	multimap<int, vector<int>> mp;
	for(int i=0;i<10;i++) {
		if(i==0 || i==2 || i==5) continue;
		vector<int> digits;
		for(int j=0;j<10;j++)
			if(i!=j) digits.push_back(j);
		fill(digits, mp);
	}
	sol(mp);
    return 0;
}
