// hi
#include <bits/stdc++.h>
using namespace std;
using LL = long long int;
// ulimit -s 65536
#define N 9
pair<int,int> decode(int x){
	int y = x % 100;
	x/=100;
	return pair{x-2*N, y - N};
}
int encode(int x, int y) {
	return (x+2*N) * 100 + (y+N);
}
bool valid(int x, int y) {
	x = abs(x);
	y = abs(y);
	if ((x&1) != (y&1)) return false;
	if(x> 2*N) return false;
	if(y> N) return false;
	return x+y <= 2*N; 
}
int getRegion(int id) {
	auto [x, y] = decode(id);
	if(x==0 && y==0) return -1;
	if (y <=-1 && x>=1 && abs(x)>=abs(y)) return 1;
	if (y <=0 && x<=-2 && abs(x)>=abs(y)+2) return 5;
	if (y<=-1) return 0;
	if (y>0 && x<=-1 && abs(x) >= abs(y)) return 4;
	if (y>=0 && x>=1 && abs(x) >= abs(y)+2) return 2;
	return 3;
}
constexpr int dx[6] = {-2, -1, 1, 2, 1, -1};
constexpr int dy[6] = {0, 1, 1, 0, -1, -1};
/*vector<vector<int>> posts = {
	{-3, -1, 38}, 
	{-6, -6, 19}, 
	{15, -3, 11},
	{-10, 0, 6}, 
	{-10, -4, 6}, 
	{2, -2, 6}, 
	{0, -8, 6}, 
	{-2, 2, 8},
	{0, 8, 7},
	{10, 4, 6},
	{3, 1, 4},
	{10, 0, 3},
	{6, 6, 3},
	{-15, 3, 1},
};*/
vector<vector<int>> posts = {
	{-3, -1, 38}, 
	{-6, -6, 19}, 
	{15, -3, 11},
	{-10, 0, 6}, 
	{-10, -4, 6}, 
	//{2, -2, 6}, 
	{0, -8, 6},
	{-15, 3, 1},
};

/*vector<vector<int>> posts = {
	{-3, 3, 4}, 
	{0, 0, 4}, 
	{5, 1, 5},
	{-5, -1, 2}, 
	{3, -3, 2},  
};*/

vector<int> v[5000];
vector<int> all_pt;
bool traverse(int id, const vector<int> &mp, vector<bool> &vis) {
	queue<int> q;
	q.push(id);
	vis[id] = true;
	for(int r=0;r<6;r++) {
		queue<int> nxt_q;
		while(!q.empty()) {
			pair<int,int> pt = decode(q.front());
			q.pop();
			for(int d=0;d<6;d++){
				int nx = pt.first + dx[d];
				int ny = pt.second + dy[d];
				int nxt = encode(nx, ny);
				if (r == 5 && nxt == id)
					return true;
				if(valid(nx, ny) && !vis[nxt] && !mp[nxt]) {
					int r2 = getRegion(nxt);
					if(r2 == r) {
						vis[nxt] = true;
						q.push(nxt);
					}
					else if(r2 == (r+1) % 6){
						vis[nxt] = true;
						nxt_q.push(nxt);
					}
				}
			}
		}
		q = nxt_q;
	}
	return false;
}
bool connected(const vector<int> &mp) {
	for(int r = 0; r < 6; r++) {
		vector<bool> vis(mp.size(), false);
		for(int i: all_pt) {
			if(!mp[i] && getRegion(i) == 0 && !vis[i])
				if(traverse(i, mp, vis))
					return true;
		}
	}
	return false;
}
void dfs(int now, const vector<pair<int,int>>& target, vector<int> &mp) {
	if(!connected(mp)) return;
	if(now == posts.size()) {
		/*for(int i: all_pt) {
			if(mp[i]) {
				pair<int,int>  pt = decode(i);
				printf("(%d, %d), " ,pt.first, pt.second); 
			}
		}*/
		for(int j=N;j>=-N;j--) {
			for(int i=-2*N;i<=2*N;i++){				
				if(i==0 && j==0) printf("C");
				else if(!valid(i, j)) printf(" ");
				else if(mp[encode(i, j)]) printf("x");
				else printf("%d", getRegion(encode(i, j)));
			}
			printf("\n");
		}
		printf("\n");
	}
	pair<int,int> pt = decode(target[now].first);
	vector<int> max_len(6, 0);
	for(int d=0;d<6;d++){
		for(int l=1;;l++) {
			int nx = pt.first + dx[d] * l;
			int ny = pt.second + dy[d] * l;
			if(!valid(nx, ny)) break;
			if(mp[encode(nx, ny)]) break;
			max_len[d] = l;
		}
	}
	int cnt = target[now].second;
	for(int a=0;a<=max_len[0];a++) {
		if(a + max_len[1] + max_len[2] + max_len[3] + max_len[4] + max_len[5] < cnt) continue;
		if(a > cnt) break;
		for(int b=0;b<=max_len[1]; b++) {
			if(a + b + max_len[2] + max_len[3] + max_len[4] + max_len[5] < cnt) continue;
			if(a + b > cnt) break;
			for(int c=0;c<=max_len[2]; c++) {
				if(a + b + c + max_len[3] + max_len[4] + max_len[5] < cnt) continue;
				if(a + b + c > cnt) break;
				for(int d=0; d<=max_len[3]; d++) {
					if(a + b + c + d + max_len[4] + max_len[5] < cnt) continue;
					if(a + b + c + d > cnt) break;
					for(int e=0; e<=max_len[4]; e++) {
						if(a + b + c + d + e + max_len[5] < cnt) continue;
						if(a + b + c + d + e > cnt) break;
						for(int f=0; f<=max_len[5]; f++) {
							if(a + b + c + d + e + f != cnt) continue;
							
							//
							for(int i=1;i<=a;i++) mp[encode(pt.first + dx[0] * i, pt.second + dy[0] * i)] = true;
							for(int i=1;i<=b;i++) mp[encode(pt.first + dx[1] * i, pt.second + dy[1] * i)] = true;
							for(int i=1;i<=c;i++) mp[encode(pt.first + dx[2] * i, pt.second + dy[2] * i)] = true;
							for(int i=1;i<=d;i++) mp[encode(pt.first + dx[3] * i, pt.second + dy[3] * i)] = true;
							for(int i=1;i<=e;i++) mp[encode(pt.first + dx[4] * i, pt.second + dy[4] * i)] = true;
							for(int i=1;i<=f;i++) mp[encode(pt.first + dx[5] * i, pt.second + dy[5] * i)] = true;
							dfs(now+1, target, mp);
							for(int i=1;i<=a;i++) mp[encode(pt.first + dx[0] * i, pt.second + dy[0] * i)] = false;
							for(int i=1;i<=b;i++) mp[encode(pt.first + dx[1] * i, pt.second + dy[1] * i)] = false;
							for(int i=1;i<=c;i++) mp[encode(pt.first + dx[2] * i, pt.second + dy[2] * i)] = false;
							for(int i=1;i<=d;i++) mp[encode(pt.first + dx[3] * i, pt.second + dy[3] * i)] = false;
							for(int i=1;i<=e;i++) mp[encode(pt.first + dx[4] * i, pt.second + dy[4] * i)] = false;
							for(int i=1;i<=f;i++) mp[encode(pt.first + dx[5] * i, pt.second + dy[5] * i)] = false;
							//
						}
					}
				}
			}
		}
	}
	
}
int main(void) {
	vector<pair<int,int>> target;
	vector<int> mp(5000, false);
	for(int i=0;i<posts.size(); i++){
		int id = encode(posts[i][0], posts[i][1]);
		target.emplace_back(id, posts[i][2]);
		mp[id] = true;
	}
	for(int x = -N*2; x<=N*2; x++) {
		for(int y = -N; y<=N;y++) {
			if(!valid(x, y)) continue;
			int id = encode(x, y);
			all_pt.push_back(id);
			for(int d = 0;d<6;d++) {
				int nx = x+dx[d];
				int ny = y+dy[d];
				if(!valid(nx, ny)) continue;
				v[id].push_back(encode(nx, ny));
			}
		}
	}
	dfs(0, target, mp);
	return 0;
}
