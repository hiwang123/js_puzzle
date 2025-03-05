// hi
#include <bits/stdc++.h>
using namespace std;
#define PB push_back
#define MP make_pair
#define F first
#define S second
typedef long long int LL;
typedef pair<int,int> pos;
vector<vector<int>> init_board={
	{9, 8, 10, 12, 11, 8, 10, 17},
	{7, 9, 11, 9, 10, 12, 14, 15},
	{4, 7, 5, 8, 8, 6, 13, 10},
	{4, 10, 7, 9, 6, 8, 7, 9},
	{2, 6, 4, 2, 5, 9, 8, 11},
	{0, 3, -2, 4, 2, 7, 10, 7},
	{-2, 2, 0, -2, 2, 5, 7, 6},
	{0, 2, 4, 3, 5, 6, 2, 4}
};
vector<vector<int>> vis_cnt;
vector<pair<int, pos>> steps;
pair<int, vector<vector<int>>> updateBoard(int h, pos now, vector<vector<int>> &board) {
	vector<vector<int>> ret = board;
	int cnt=0;
	if(h==0) return make_pair(cnt, ret);
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++){
			if(ret[i][j]==board[now.F][now.S]){
				cnt++;
				ret[i][j]-=h;
			}
		}
	ret[7-now.F][7-now.S] +=h;
	return make_pair(h * cnt, ret);
}
unordered_set<int> st;
unordered_map<int,bool> mp;
#define mod 10000019
int hashBoard(pos now, vector<vector<int>> &board, int sum) {
	LL ret=0;
	int base = 2;
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++) {
			ret += (LL(base) * board[i][j]) % mod; ret%=mod;
			base*=2; base%=mod;
		}
	ret += (LL(base) * now.F) % mod; ret%=mod;
	base*=2; base%=mod;
	ret += (LL(base) * now.S) % mod; ret%=mod;
	base*=2; base%=mod;
	ret += (LL(base) * sum) % mod; ret%=mod;
	base*=2; base%=mod;
	return ret;
}
bool ok;
struct Step{
	int val;
	int h;
	int s;
	pos p;
};
bool dfs(pos now, vector<vector<int>> &board, int dep, int sum){
	if(ok) return true;
	int hash = hashBoard(now, board, sum);
	if(mp.find(hash) != mp.end()) return mp[hash];
	if(board[now.F][now.S] < 2) return mp[hash] = false;
	if(dep >= 10 && sum < 10) return mp[hash] = false;
	if(dep >= 20 && sum < 100) return mp[hash] = false;
	if(dep >= 20 && board[now.F][now.S] < 5) return mp[hash] = false;
	if(dep >= 30 && sum < 150) return mp[hash] = false;
	//if(dep >= 30 && (board[now.F][now.S] <13 || sum < 140)) return;
	if(dep >=40) return mp[hash] = false;
	if(now == pos{0, 7}){
		int sum=0;
		for(auto [s, p] : steps){
			printf("%d, %d %d\n", s, p.F, p.S);
			sum+=s;
		}
		printf("total %d\n", sum);
		if(sum >=171)
			ok=true;
		return mp[hash] = ok;
	}
	st.insert(hash);
	vis_cnt[now.F][now.S]++;

	vector<Step> order;
	/*if( board[now.F][now.S] >10 && sum > 160) {
		printf("%d %d is %d,  dep: %d, tgt %d, sum %d\n", now.F, now.S, board[now.F][now.S], dep, board[0][7], sum);
		for(int i=0;i<8;i++){
			for(int j=0;j<8;j++)
				printf("%3d ", board[i][j]);
			printf("\n");
		}
		printf("--------------\n");
		for(auto [s, p] : steps)
			printf("%d, %d %d\n", s, p.F, p.S);
		printf("===============\n");
	}*/
	for(int h=0;h<=4;h++) {
		auto [s, tmp] = updateBoard(h, now, board);
		if(board[now.F][now.S] > 6  && h >=4) continue;
		if(board[now.F][now.S] > 10  && h >=3) continue;
		for(int i=-2;i<=2;i++)
			for(int j=-2;j<=2;j++) {
				if(abs(i)==abs(j)) continue;
				pos nxt = {now.F+i, now.S+j};
				if(nxt.F<0 || nxt.F >=8 || nxt.S<0 ||nxt.S >=8) continue;
				if(dep < 20 && nxt.F < 2) continue;
			//	if(dep < 20 && nxt.S > 5) continue;
				if(vis_cnt[nxt.F][nxt.S]==3) continue;
				int val_diff = 3-abs(i)-abs(j);
				if(abs(tmp[nxt.F][nxt.S] - tmp[now.F][now.S]) == val_diff) {
					int hash2 = hashBoard(nxt, tmp, sum+s);
					if(st.find(hash2) != st.end()) continue;
					order.PB(Step {
						.val = tmp[nxt.F][nxt.S],
						.h = h,
						.s = s,
						.p = nxt,
					});
				}
			}
	}
	sort(order.begin(), order.end(),[](Step &a, Step &b) {return a.val > b.val;});
	//sort(order.begin(), order.end(),[](Step &a, Step &b) {return a.s > b.s;});
	bool ret=false;
	for(auto od: order) {
		auto [s, tmp] = updateBoard(od.h, now, board);
		steps.PB(MP(s, od.p));
		ret |= dfs(od.p, tmp, dep+1, sum+s);
		steps.pop_back();
		if(ret) break;
	}
	st.erase(hash);
	vis_cnt[now.F][now.S]--;
	return mp[hash] = ret;
}
int main(void) {
	ok=false;
	/*for(int i=0;i<8;i++)
		for(int j=0;j<8;j++)
			scanf("%d",&init_board[i][j]);*/
	pos st={4, 0};
	vis_cnt.resize(8, vector<int>(8, 0));
	dfs(st, init_board, 0, 0);
    return 0;
}
