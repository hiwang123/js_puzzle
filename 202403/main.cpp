// hi
#include <bits/stdc++.h>
using namespace std;
#define PB push_back
#define MP make_pair
#define F first
#define S second
using LL = int64_t;

int sz;
vector<vector<int>> target;
int dx[4]={1, 1, 0, 0};
int dy[4]={0, 1, 0, 1};
int dfx[4]={-1, 0, 1, 0};
int dfy[4]={0, -1, 0, 1};
vector<vector<int>> grids(9, vector<int>(9, -1));
vector<bool> filled(10, false);
inline bool inside(int x, int y) {
	return x>=0 && x<sz && y>=0 && y<sz;
}
bool has2by2Full(const pair<int,int> &pos) {
	pair<int,int> corner[4];
	corner[0] = pos;
	corner[1] = pair{pos.first - 1,  pos.second - 1};
	corner[2] = pair{pos.first,  pos.second - 1};
	corner[3] = pair{pos.first - 1,  pos.second};
	for(int i=0;i<4;i++) {
		int tot=0;
		int zeros=0;
		for(int j=0;j<2;j++)
			for(int k=0;k<2;k++) {
				int x = corner[i].first + j;
				int y = corner[i].second + k;
				if(inside(x, y)) {
					tot++;
					if(grids[x][y]==0 || grids[x][y]==-1) zeros++;
				}
			}
		if(tot==4 && zeros==0) return true;
	}
	return false;
}
void printGrid() {
	for(int i=0;i<sz;i++) {
		for(int j=0;j<sz;j++)
			printf("%2d ", grids[i][j]);
		printf("\n");
	}
	printf("\n");
}
bool onTarget(const pair<int,int> &pos) {
	return target[pos.first][pos.second]!=-1;
}
bool isIsolated(const pair<int,int> &pos) {
	for(int d=0;d<4;d++) {
		int x = pos.first + dfx[d];
		int y = pos.second +dfy[d];
		if(inside(x, y) && target[x][y]!=0) return false;
	}
	return true;
}
bool isNumMatch(const pair<int,int> &pos) {
	for(int d=0;d<4;d++) {
		int x = pos.first + dfx[d];
		int y = pos.second +dfy[d];
		if(inside(x, y) && target[x][y]!=-1) {
			int cnt=0;
			int unknown = 0;
			for(int i=0;i<4;i++) {
				int x2= x + dfx[i];
				int y2= y + dfy[i];
				if(inside(x2, y2)) {
					if(grids[x2][y2]==-1)
						unknown++;
					else
						cnt += grids[x2][y2];
				}
				if(cnt > target[x][y]) return false;
			}
			if(target[x][y]-cnt > 9 * unknown) return false;
		}
	}
	return true;
}
bool found;
template<bool is_zero>
int getCC(int x, int y,  vector<vector<bool>> &vis) {
	vis[x][y]=true;
	int ret=1;
	for(int i=0;i<4;i++) {
		int nx = x + dfx[i];
		int ny = y + dfy[i];
		if(inside(nx, ny) && !vis[nx][ny] && !(is_zero ^ grids[nx][ny]==0))
			ret += getCC<is_zero>(nx, ny, vis);
	}
	return ret;
}
void fill(int n, int off_x, int off_y) {
	if(found) return;
	if(n==0) {
		vector<vector<bool>> vis(9, vector<bool>(9, false));
		printGrid();
		for(int i=0;i<sz;i++)
			for(int j=0;j<sz;j++)
				if(grids[i][j]!=0 && !vis[i][j]) {
					if(getCC<false>(i, j, vis)!= ((1+sz) * sz)/2) return;
				}
		vis = vector<vector<bool>> (9, vector<bool>(9, false));
		long long int ans=1;
		for(int i=0;i<sz;i++)
			for(int j=0;j<sz;j++)
				if(grids[i][j]==0 && !vis[i][j]) {
					ans *= getCC<true>(i, j, vis);
				}
		printf("%lld\n", ans);
		found = true;
		return;
	}
	//if(n == 7) printGrid();
	for(int num=sz; num>0; num--) {
		if(n>=8) printf("%d %d\n", n, num);
		if (filled[num] || num > 2*n -1) continue;
		filled[num] = true;
		for(int d=0; d<4; d++) {
			int x = off_x + (n-1) * dx[d];
			int y = off_y + (n-1) * dy[d];
			vector<pair<int,int>> l_pos;
			for(int i=0;i<n;i++)
				l_pos.emplace_back(off_x+i, y);
			for(int i=0;i<n;i++) {
				if((d==0 || d==2) && i == 0) continue;
				if((d==1 || d==3) && i == n-1) continue;
				l_pos.emplace_back(x, off_y+i);
			}
			vector<int> place(2*n-1, 0);
			for(int i=0;i<num;i++) place[i]=1;
			reverse(place.begin(), place.end());
			do {
				bool ok=true;
				for(int i=0;i<2*n-1;i++) {
					if(place[i]) {
						grids[l_pos[i].first][l_pos[i].second] = num;
						if(onTarget(l_pos[i]) || has2by2Full(l_pos[i]) || isIsolated(l_pos[i])) {
							ok=false; break;
						}
					} else {
						grids[l_pos[i].first][l_pos[i].second] = 0;
					}
					if (!isNumMatch(l_pos[i])) {
						ok=false; break;
					} 
				}
				if(ok) {
					fill(n-1, off_x + (1-dx[d]), off_y + (1-dy[d]));
				}
				for(int i=0;i<2*n-1;i++)
					grids[l_pos[i].first][l_pos[i].second] = -1;
			}while(next_permutation(place.begin(), place.end()));
		}
		filled[num] = false;
	}
}
int main(int argc, char *argv[]) {
	if(argc != 2) {
		printf("./main testcase\n");
		return 0;
	} 
	int c = atoi(argv[1]);
	if(c==0) {
		sz = 5;
		target = vector<vector<int>> ({
			{ 0,-1,-1,-1,-1},
			{-1,-1, 9,-1, 7},
			{ 8,-1,-1,-1,-1},
			{-1,-1,15,-1,12},
			{10,-1,-1,-1,-1}});
	}else{
		sz = 9;
		target = vector<vector<int>> ({
			{-1,18,-1,-1,-1,-1, 7,-1,-1},
			{-1,-1,-1,-1,12,-1,-1,-1,-1},
			{-1,-1, 9,-1,-1,-1,-1,31,-1},
			{-1,-1,-1,-1,-1,-1,-1,-1,-1},
			{-1, 5,-1,11,-1,22,-1,22,-1},
			{-1,-1,-1,-1,-1,-1,-1,-1,-1},
			{-1, 9,-1,-1,-1,-1,19,-1,-1},
			{-1,-1,-1,-1,14,-1,-1,-1,-1},
			{-1,-1,22,-1,-1,-1,-1,15,-1}});
	}
	
	found = false;
	fill(sz, 0, 0);
    return 0;
}
