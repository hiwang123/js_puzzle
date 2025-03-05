//hi
#include<bits/stdc++.h>
using namespace std;
#define PB push_back
#define MP make_pair
#define F first
#define S second
// ulimit -s 262144
typedef long long int LL;
using Block = vector<vector<int>>;

/*
#define N 8  
#define B 13  
constexpr int block_id[N][N]={
	{1,1,8,8,8,8,8,8},
	{1,4,4,8,9,9,9,8},
	{1,4,5,7,12,9,9,8},
	{2,5,5,7,12,13,9,9},
	{2,6,6,7,12,13,13,13},
	{2,6,11,10,10,10,10,13},
	{2,11,11,3,10,3,13,13},
	{3,3,3,3,3,3,3,13}};
int M, X, Y;
int row_sum[N]={3,9,10,13,13,8,7,2};
int col_sum[N]={9,12,12,10,8,8,4,2};
int block_sum = 5;
*/


#define N 17
#define B 20
constexpr int block_id[N][N]={
	{ 1, 1, 5, 5, 7, 7, 7, 7, 7, 7,17,17,17,17,17,17,17},
	{ 1, 1, 1, 5, 5, 5, 5, 7, 7, 7,17,18,18,18,18,17,17},
	{ 1, 2, 2, 2, 5, 5, 5, 7, 6, 7,17,18,17,17,18,20,17},
	{ 1, 2, 2, 5, 5, 5, 5, 6, 6, 7,17,17,17,18,18,20,17},
	{ 1, 2, 4, 5, 6, 6, 6, 6, 8,16,16,17,17,18,20,20,17},
	{ 1, 2, 4, 4, 6, 4, 8, 8, 8, 9,16,17,17,18,18,20,20},
	{ 1, 2, 3, 4, 4, 4, 8, 8, 8, 9,16,17,17,19,18,20,20},
	{ 1, 2, 3, 3, 4, 8, 8, 9, 9, 9,16,17,16,19,20,20,20},
	{ 1, 2, 3, 3, 3, 8, 8, 9,16,16,16,16,16,19,19,20,20},
	{ 1, 2, 3, 3, 3, 3, 9, 9,13,13,16,19,16,19,20,20,20},
	{ 1, 2, 3, 3, 3, 9, 9,10,10,13,13,19,19,19,19,19,20},
	{ 1, 2, 3, 3, 9, 9,10,10,10,12,13,13,15,15,20,19,20},
	{ 1, 2, 3,10,10,10,10,10,12,12,12,13,13,15,20,20,20},
	{ 1, 2,10,10,10,10,10,10,12,14,12,15,15,15,15,20,20},
	{ 1, 2, 2,10, 1, 1,11,12,12,14,15,15,14,14,15,15,20},
	{ 1, 1, 2, 2, 1,11,11,14,14,14,14,14,14,14,20,20,20},
	{ 1, 1, 1, 1, 1, 1,11,11,11,11,11,11,11,14,20,20,20}};
int X, Y;
int row_sum[N]={14,24,24,39,43,INT_MAX,22,23,29,28,34,36,29,26,26,24,20};
int col_sum[N]={13,20,22,28,30,36,35,39,49,39,39,INT_MAX,23,32,23,17,13};
int block_sum;

vector<int> block_id_check(B+1);

// (size 1 ~ 5) (8: rotate (0, 90, 180, 270), v-mirror + rotate)
Block block[6][8];
Block scale(const Block &block, int scale) {
	int n = block.size();
	int ns = n * scale;
	Block ret(ns, vector<int>(ns));
	for(int i=0;i<ns;i++)
		for(int j=0;j<ns;j++)
			ret[i][j]=block[i/scale][j/scale] ? scale : 0;
	return ret;
}
Block rotate90(const Block &block) {
	int n = block.size();
	Block ret(n, vector<int>(n));
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			ret[j][n-1-i]=block[i][j];
	return ret;
}
Block vMirror(const Block &block) {
	int n = block.size();
	Block ret(n, vector<int>(n));
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			ret[i][n-1-j]=block[i][j];
	return ret;
}
void init(int m) {
	block_sum = 23 + m ;
	/*row_sum[5]=block_sum * B;
	for(int i=0;i<N;i++) row_sum[5]-=i==5?0:row_sum[i];
	col_sum[11]=block_sum * B;
	for(int i=0;i<N;i++) col_sum[11]-=i==11?0:col_sum[i];
	printf("%d %d %d\n", block_sum, row_sum[5], col_sum[11]);*/
	
	block[1][0] = Block{
		{0,1,0},
		{1,1,1},
		{0,0,1}};
	for(int i=2;i<=5;i++)
		block[i][0] = scale(block[1][0], i);
	for(int i=1;i<=5;i++)
		block[i][1] = rotate90(block[i][0]);
	for(int i=1;i<=5;i++)
		block[i][2] = rotate90(block[i][1]);
	for(int i=1;i<=5;i++)
		block[i][3] = rotate90(block[i][2]);

	for(int i=1;i<=5;i++)
		block[i][4] = vMirror(block[i][0]);
	for(int i=1;i<=5;i++)
		block[i][5] = rotate90(block[i][4]);
	for(int i=1;i<=5;i++)
		block[i][6] = rotate90(block[i][5]);
	for(int i=1;i<=5;i++)
		block[i][7] = rotate90(block[i][6]);

	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++) {
			int b_id = block_id[i][j];
			block_id_check[b_id] = i+1;
		}
}
struct State {
	vector<int> rsum, csum, bsum;
	State() {
		rsum = vector<int>(N, 0);
		csum = vector<int>(N, 0);
		bsum = vector<int>(B+1, 0);
	}
};
// check overlap, row sum, col sum, block sum;
bool tryPut(int r, int c, int s, int t, Block &map, State &state) {
	int n = block[s][t].size();
	if(r+n > N || c+n > N) return false;
	// check
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++) {
			if(map[r+i][c+j]!=0 && block[s][t][i][j]!=0) return false;
		}
	State tmp_state = state;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++) {
			int val = block[s][t][i][j];
			int b_id = block_id[r+i][c+j];
			tmp_state.rsum[r+i]+=val;
			tmp_state.csum[c+j]+=val;
			tmp_state.bsum[b_id]+=val;
		}
	for(int i=0;i<N;i++) {
		if(tmp_state.rsum[i] > row_sum[i]) return false;
		if(tmp_state.csum[i] > col_sum[i]) return false;
	}
	for(int i=1;i<=B;i++) {
		if(tmp_state.bsum[i] > block_sum) return false;
	}
	
	// put
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++) {
			int val = block[s][t][i][j];
			if(val)
				map[r+i][c+j] = val;
		}
	state = tmp_state;
	return true;
}
void clear(int r, int c, int s, int t, Block &map, State &state) {
	int n = block[s][t].size();
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++) {
			int val = block[s][t][i][j];
			int b_id = block_id[r+i][c+j];
			if(val) {
				map[r+i][c+j] = 0;
				state.rsum[r+i]-=val;
				state.csum[c+j]-=val;
				state.bsum[b_id]-=val;
			}
		}
}
void print(const Block &map) {
	int n = map.size();
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}
	printf("----------------------------\n");
}
bool checkFinalState(const State &state) {
	for(int i=0;i<N;i++) {
		if(row_sum[i]==INT_MAX) continue;
		if(state.rsum[i] != row_sum[i]) return false;
	}
	for(int i=0;i<N;i++) {
		if(col_sum[i]==INT_MAX) continue;
		if(state.csum[i] != col_sum[i]) return false;
	}
	/*for(int i=1;i<=B;i++) {
		if(state.bsum[i] != block_sum) return false;
	}*/
	return true;
}
bool checkBlock(int r, const State &state) {
	for(int i=1;i<=B;i++)
		if(block_id_check[i] == r && state.bsum[i]!=block_sum)
			return false;
	return true;
}
bool checkRow(int r, const State &state) {
	if(r==-1) return true;
	if(row_sum[r]==INT_MAX) return true;
	return state.rsum[r] == row_sum[r];
}

constexpr int dx[4]={-1,0,0,1};
constexpr int dy[4]={0, -1, 1, 0};
void searchCC(int r, int c, const Block &map, vector<vector<bool>> &vis, int &sz) {
	vis[r][c]=true;
	sz++;
	for(int d=0;d<4;d++) {
		int nr = r+dx[d];
		int nc = c+dy[d];
		if(nr >=0 && nr < N && nc >= 0 && nc < N && map[nr][nc]==0 && !vis[nr][nc])
			searchCC(nr, nc, map, vis, sz);
	}
}
int countCC(const Block &map) {
	vector<vector<bool>> vis(N, vector<bool>(N, false));
	int mul=1;
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
			if(map[i][j]==0 && !vis[i][j]) {
				int sz=0;
				searchCC(i, j, map, vis, sz);
				mul *= sz;
				printf("%d\n", sz);
			}
	return mul;
}

void dfs(int r, int c, Block &map, State &state, bool &found) {
	if(found) return;
	// ending
	if(r==N) {
		if(checkFinalState(state)) {
			found = true;
			for(int i=0;i<N;i++) printf("row %d: %d == %d\n", i, state.rsum[i], row_sum[i]);
			for(int i=0;i<N;i++) printf("col %d: %d == %d\n", i, state.csum[i], col_sum[i]);
			for(int i=1;i<=B;i++) printf("block %d (bd %d): %d\n", i, block_id_check[i], state.bsum[i]);
			print(map);
			int ans = countCC(map);
			printf("%d\n", ans);
		}
		return;
	}
	
	if(c==0) {
		if(!checkRow(r-1, state) || !checkBlock(r-1, state))
			return;
	}
	/*if(r>=4) { // debug
		printf("%d %d: \n", r, c);
		for(int i=0;i<N;i++) printf("row %d: %d\n", i, state.rsum[i]);
		for(int i=0;i<N;i++) printf("col %d: %d\n", i, state.csum[i]);
		for(int i=1;i<=B;i++) printf("block %d (bd %d): %d\n", i, block_id_check[i], state.bsum[i]);
		print(map);
	}*/
	
	// next (r, c)
	int nxt_r = r, nxt_c = c+1;
	if(nxt_c == N) {
		nxt_r = r+1;
		nxt_c =0;
	}

	// try put blocks @(r, c) or empty, then dfs to next
	for(int i=3;i>0;i--) {
		for(int j=0;j<8;j++) {
			if(tryPut(r, c, i, j, map, state)) {
				dfs(nxt_r, nxt_c, map, state, found);
				clear(r, c, i, j, map, state);
			}
		}
	}
	// put blocks[1] & blocks[3]
	for(int j1=0;j1<8;j1++)
		for(int j2=0;j2<8;j2++)
			if(tryPut(r, c, 1, j1, map, state)) {
				if(tryPut(r, c, 3, j2, map, state)) {
					dfs(nxt_r, nxt_c, map, state, found);
					clear(r, c, 3, j2, map, state);
				}
				clear(r, c, 1, j1, map, state);
			}
	
	// dont put
	dfs(nxt_r, nxt_c, map, state, found);
}
int main(void){
	int m=1;
	//cin>>m;
	init(m);
	Block map(N, vector<int>(N, 0));
	bool found = false;
	State state;
	state.rsum = vector<int>(N, 0);
	state.csum = vector<int>(N, 0);
	state.bsum = vector<int>(B+1, 0);
	dfs(0, 0, map, state, found);
	return 0;
}
