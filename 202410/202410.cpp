#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define N 6
#define SUM 2024
#define INF 10000
typedef long long int LL;
typedef pair<int,int> pii;
enum Alpha{
	A, B, C,
};
const vector<vector<Alpha>> mp = {
	{A, B, B, C, C, C},
	{A, B, B, C, C, C},
	{A, A, B, B, C, C},
	{A, A, B, B, C, C},
	{A, A, A, B, B, C},
	{A, A, A, B, B, C},
};
pii s1 = {N-1, 0}, e1 = {0, N-1}, s2 = {0, 0}, e2 = {N-1, N-1};
int dx[8] = {-1, -2, -2, -1,  1,  2, 2, 1};
int dy[8] = {-2, -1,  1,  2, -2, -1, 1, 2};
vector<int> pow_[60];
struct Num {
	int p[3];
	bool operator<(const Num &n)const {
		if(p[A] != n.p[A]) return p[A] < n.p[A];
		if(p[B] != n.p[B]) return p[B] < n.p[B];
		return p[C] < n.p[C]; 
	}
};
void mul(vector<Num> &nums, Num mu) {
	for(auto &num: nums) {
		num.p[A]+=mu.p[A];
		num.p[B]+=mu.p[B];
		num.p[C]+=mu.p[C];
	}
}
void add(vector<Num> &nums, Num num) {
	nums.push_back(num);
}
inline bool valid(const pii& pos) {
	return pos.first >=0 && pos.first < N && pos.second >=0 && pos.second < N;
}
inline int m_pow(int a, int b) {
	if(b==0) return 1;
	if(a==1) return 1;
	if(b>=pow_[a].size()) return INF;
	return pow_[a][b];
}
inline Num toNum(Alpha alp) {
	Num num;
	num.p[A]=0;
	num.p[B]=0;
	num.p[C]=0;
	num.p[alp] = 1;
	return num;
}
inline bool validNum(const vector<Num> &nums) {
	for(const auto& num: nums) {
		if(num.p[A] > 10 && num.p[B] > 10) return false;
		if(num.p[B] > 10 && num.p[C] > 10) return false;
		if(num.p[A] > 10 && num.p[C] > 10) return false;
	}
	return true;
}

inline int calculateSum(const vector<Num> &nums, int a, int b, int c) {
	int sum=0;
	for(const auto& num: nums) {
		int mul=1;
		mul *= m_pow(a, num.p[A]);
		if(mul > SUM) return INF;
		mul *= m_pow(b, num.p[B]);
		if(mul > SUM) return INF;
		mul *= m_pow(c, num.p[C]);
		if(mul > SUM) return INF;
		sum += mul;
		if(sum > SUM) return INF;
	}
	return sum;
}

int pA, pB, pC;

bool sumPossible(const vector<Num> &nums) {
	for(int a=1;a<=5;a++)
		for(int b=1;b<=5;b++) {
			if(a==b || a+b >= 50) continue;
			for(int c=1;c<=5;c++) {
				if(a==c || b==c || a+b+c > 50) continue;
				if(calculateSum(nums, a, b, c) == SUM) {
					printf("A=%d B=%d C=%d\n",  a, b, c);
					pA = a;
					pB = b;
					pC = c;
					return true; 
				}
			}
		}
	return false;
}
bool ok = false;
set<vector<Num>> seen;

template<int pass>
void dfs(pii cur, pii dst, vector<vector<bool>> &vis, vector<Num> nums, vector<pii> &path) {
	if(ok) return;
	if(pass ==2 && calculateSum(nums, pA, pB, pC) > SUM) return;
	if (cur == dst) {
		if (pass == 1 && !sumPossible(nums)) return;
		if (pass == 2 && calculateSum(nums, pA, pB, pC) != SUM) return;
		sort(nums.begin(), nums.end());
		if (seen.find(nums) == seen.end()) {
			seen.insert(nums);
			for(const auto& num: nums) {
				printf("a%d b%d c%d + ", num.p[A], num.p[B], num.p[C]);
			}
			printf("\n");
			for(const auto& p: path)
				printf("%c%d,", 'a'+p.second, 6-p.first);
			printf("\n");
			ok = true;
		}
		return;
	}
	vis[cur.first][cur.second] = true;
	path.push_back(cur);
	for(int d = 0; d < 8; d++) {
		pii nxt = {cur.first + dx[d], cur.second + dy[d]};
		if(!valid(nxt)) continue;
		if(vis[nxt.first][nxt.second]) continue;
		auto tmp = nums;
		auto nxt_num = toNum(mp[nxt.first][nxt.second]);
		if(mp[cur.first][cur.second] == mp[nxt.first][nxt.second])
			add(tmp, nxt_num);
		else
			mul(tmp, nxt_num);
		if (!validNum(tmp)) continue;
		dfs<pass>(nxt, dst, vis, tmp, path);
	}
	vis[cur.first][cur.second] = false;
	path.pop_back();
}
int main(void) {
	for(int i=2;i<50;i++) {
		pow_[i].push_back(1);
		for(int j=1;j<15;j++){
			pow_[i].push_back(pow_[i].back() * i);
			if(pow_[i].back()>SUM) break;
		}
	}
	{
		vector<pii> path;
		vector<Num> nums;
		vector<vector<bool>> vis(N, vector<bool>(N, false));
		add(nums, toNum(mp[s1.first][s1.second]));
		dfs<1>(s1, e1, vis, nums, path);
	}
	
	ok = false;
	seen.clear();
	{
		vector<pii> path;
		vector<Num> nums;
		vector<vector<bool>> vis(N, vector<bool>(N, false));
		add(nums, toNum(mp[s2.first][s2.second]));
		dfs<2>(s2, e2, vis, nums, path);
	}
    return 0;
}

/*

A=3 B=1 C=2
a0 b0 c1 + a0 b1 c1 + a0 b2 c2 + a0 b3 c4 + a0 b4 c4 + a0 b4 c5 + a0 b5 c5 + a1 b6 c6 + a2 b7 c6 + a2 b7 c6 + a2 b7 c6 + 
a1,b3,a5,c6,b4,a6,c5,e6,d4,b5,d6,e4,c3,d1,e3,f1,d2,f3,e1,d3,e5,c4,b6,d5,f6
a0 b3 c3 + a2 b5 c5 + a3 b6 c5 + a3 b6 c5 + 
a6,b4,c6,a5,b3,c5,e6,d4,c2,e3,c4,b6,d5,c3,e4,d2,f1

3,1,2,a1,b3,a5,c6,b4,a6,c5,e6,d4,b5,d6,e4,c3,d1,e3,f1,d2,f3,e1,d3,e5,c4,b6,d5,f6,a6,b4,c6,a5,b3,c5,e6,d4,c2,e3,c4,b6,d5,c3,e4,d2,f1
*/
