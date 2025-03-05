// hi
#include <bits/stdc++.h>
using namespace std;
#define PB push_back
#define MP make_pair
#define F first
#define S second
#define N 11
using LL = int64_t;
enum Dir {U, L, R, D};
int dx[4] = {-1, 0, 0, 1};
int dy[4] = {0, -1, 1, 0};

/* ans
xx\xxx\xx\
xxxxxxxx\x
/xxx/xx/xx
xx/xxxxxx\
xxxxxx/xxx
x/xx\xx\xx
/x\xx/xx/x
xxx\xxxxxx
xxxx/x/x/x
/xxxx/xxxx
27 2025 3 27 112 12 48 12 225 24
3 12 112 56 48 3087 9 405 4 1
1 4 27 9 64 27 16 56 4 5
2025 225 24 12 64 5 16 405 4 3087
603185109176

 */

struct Hint {
	pair<int,int> pos;
	int val;
};
enum Grid{
	UNKNOWN,
	BLANK, 
	S1,  /*  \  */ 
	S2,  /*  /  */
};
vector<Hint> hints = {
	Hint{{11, 8}, 405},
	Hint{{0, 6}, 3087},
	Hint{{3, 11}, 27},
	Hint{{0, 7}, 9},
	Hint{{8, 0}, 12},
	Hint{{11, 4}, 12},
	Hint{{11, 6}, 5},
	Hint{{11, 1}, 2025},
	Hint{{2, 11}, 4},
	Hint{{7, 11}, 16},
	Hint{{9, 0}, 225},
	Hint{{0, 3}, 112},
	Hint{{11, 5}, 64},
	Hint{{0, 5}, 48},
	Hint{{4, 0}, 27},
};
vector<vector<int>> hints_map(N+1, vector<int>(N+1, 0));
void clearMods(vector<vector<Grid>>& grids, const vector<pair<int,int>>& mod_pos){
	for(const auto& [x, y]: mod_pos)
		grids[x][y] = UNKNOWN;
}
void printGrids(const vector<vector<Grid>>& grids) {
	for(int i=1;i<N;i++){
		for(int j=1;j<N;j++) {
			if(grids[i][j] == S1) printf("\\");
			else if(grids[i][j]==S2) printf("/");
			else if(grids[i][j] == BLANK) printf("x");
			else printf("?");
		}
		printf("\n");
	}
}
bool tryFill(const pair<int,int>& init_pos, const vector<int>& path, vector<vector<Grid>>& grids, vector<pair<int,int>>& mod_pos, int turn) {
	Dir dir;
	if(init_pos.first == 0) dir = D;
	else if(init_pos.first == N) dir = U;
	else if(init_pos.second == 0) dir = R;
	else if(init_pos.second == N) dir = L;
	pair<int,int> pos = init_pos;
	int l = path.size();
	//for(int i=0;i<l;i++) printf("%d ", path[i]); printf("\n");
	for(int i=0;i<l;i++) {
		//printf("old dir %d, old pos %d %d\n", dir, pos.first, pos.second);
		int val = path[i];
		pair<int,int> next_pos = {pos.first + dx[dir] * val, pos.second + dy[dir] * val};
		if(i< l-1 && (next_pos.first <=0 || next_pos.second <=0 || 
		              next_pos.first >=N || next_pos.second >=N)) {
			//printf("%d %d\n", val, 1);
			//printf("%d %d: %d %d -> %d %d\n", val, 4, pos.first, pos.second, next_pos.first, next_pos.second);
			//printGrids(grids);
			clearMods(grids, mod_pos);
			return false;
		}
		if(i== l-1 && !(next_pos.first ==0 || next_pos.second ==0 || 
		              next_pos.first ==N || next_pos.second ==N)) {
			//printf("%d %d\n", val, 2);
			clearMods(grids, mod_pos);
			return false;
		}
		for(int i=1;i<val;i++){
			Grid g = grids[pos.first + dx[dir] * i][pos.second + dy[dir] * i];
			if(g == S1 || g == S2){
				//printf("%d %d\n", val, 3);
				clearMods(grids, mod_pos);
				return false;
			}
		}
		if(i<l-1) {
			Grid g = grids[next_pos.first][next_pos.second];
			if (g == BLANK){
				clearMods(grids, mod_pos);
				return false;
			}
			Grid g2 = ((turn >> i) & 1) ? S1 : S2;
			if (grids[next_pos.first][next_pos.second] == UNKNOWN){
				grids[next_pos.first][next_pos.second] = g2;
				mod_pos.push_back(next_pos);
			}else if(grids[next_pos.first][next_pos.second] != g2){
				//printf("%d %d\n", val, 5);
				clearMods(grids, mod_pos);
				return false;
			}
		} else if(i == l-1) {
			if(hints_map[next_pos.first][next_pos.second] && 
				hints_map[init_pos.first][init_pos.second] != hints_map[next_pos.first][next_pos.second]) {
				//printf("%d %d\n", val, 6);
				clearMods(grids, mod_pos);
				return false;
			}
		}
		// ok
		for(int i=1;i<val;i++){
			if (grids[pos.first + dx[dir] * i][pos.second + dy[dir] * i] == UNKNOWN) {
				grids[pos.first + dx[dir] * i][pos.second + dy[dir] * i] = BLANK;
				mod_pos.push_back({pos.first + dx[dir] * i, pos.second + dy[dir] * i});
			}
		}
		pos = next_pos;
		if (i == l-1) break;
		if(grids[pos.first][pos.second] == S1){
			if(dir == L) dir = U;
			else if(dir == U) dir = L;
			else if(dir == R) dir = D;
			else if(dir == D) dir = R;
		}else if(grids[pos.first][pos.second] == S2) {
			if(dir == L) dir = D;
			else if(dir == U) dir = R;
			else if(dir == R) dir = U;
			else if(dir == D) dir = L;
		}else {
			assert(false);
		}
		//printf("new dir %d, new pos %d %d\n", dir, pos.first, pos.second);
	}
	return true;
}
vector<vector<int>> getFactors(int val){
	vector<vector<int>> ret;
	if(val < 10){
		ret.push_back({val});
		ret.push_back({1, val});
		ret.push_back({1, 1, val});
	}
	for(int i=2;i<val && i < 10;i++)
		if(val % i ==0) {
			auto fs = getFactors(val / i);
			for(const auto& f: fs){
				auto f2 = f;
				if(i >= f2.back()) {
					f2.push_back(i);
					ret.push_back(f2);
				}
			}
		}
	return ret;
}

void fillVal(const pair<int,int>& init_pos, const vector<vector<Grid>>& grids) {
	Dir dir;
	if(init_pos.first == 0) dir = D;
	else if(init_pos.first == N) dir = U;
	else if(init_pos.second == 0) dir = R;
	else if(init_pos.second == N) dir = L;
	pair<int,int> pos = init_pos;
	int mult = 1;
	int l = 0;
	for(;;) {
		pos.first += dx[dir];
		pos.second += dy[dir];
		l++;
		if (pos.first == 0 || pos.first== N || pos.second == 0 || pos.second == N) {
			mult *= l;
			break;
		}
		if(grids[pos.first][pos.second] == S1){
			if(dir == L) dir = U;
			else if(dir == U) dir = L;
			else if(dir == R) dir = D;
			else if(dir == D) dir = R;
			mult *= l;
			l=0;
		}else if(grids[pos.first][pos.second] == S2) {
			if(dir == L) dir = D;
			else if(dir == U) dir = R;
			else if(dir == R) dir = U;
			else if(dir == D) dir = L;
			mult *= l;
			l=0;
		}
	}
	hints_map[init_pos.first][init_pos.second] = mult;
	if (hints_map[pos.first][pos.second] == 0)
		hints_map[pos.first][pos.second] = mult;
}

bool found;
void dfs(vector<vector<Grid>>& grids, int now) {
	if(found) return;
	if(now == hints.size()) {
		printGrids(grids);
		long long int ans = 1;
		long long int sum[4] = {0,0,0,0};
		for(int i=1;i<N;i++){
			if(hints_map[i][0] == 0)
				fillVal({i, 0}, grids);
			if(hints_map[0][i] == 0)
				fillVal({0, i}, grids);
			if(hints_map[i][N] == 0)
				fillVal({i, N}, grids);
			if(hints_map[N][i] == 0)
				fillVal({N, i}, grids);
		}
		
		for(int i=1;i<N;i++){
			sum[0] += hints_map[i][0];
			sum[1] += hints_map[0][i];
			sum[2] += hints_map[i][N];
			sum[3] += hints_map[N][i];
		}
		
		for(const auto& hint: hints) {
			if (hint.pos.second == 0) sum[0] -= hint.val;
			else if (hint.pos.first == 0) sum[1] -= hint.val;
			else if (hint.pos.second == N) sum[2] -= hint.val;
			else if (hint.pos.first == N) sum[3] -= hint.val;
			else assert(false);
		}
		
		for(int i=1;i<N;i++)
			printf("%d%c", hints_map[i][0], i==N-1?'\n':' ');
		for(int i=1;i<N;i++)
			printf("%d%c", hints_map[0][i], i==N-1?'\n':' ');
		for(int i=1;i<N;i++)
			printf("%d%c", hints_map[i][N], i==N-1?'\n':' ');
		for(int i=1;i<N;i++)
			printf("%d%c", hints_map[N][i], i==N-1?'\n':' ');
		ans = sum[0] * sum[1] * sum[2] * sum[3];
		printf("%lld\n", ans);
		found = true;
		return;
	}
	vector<vector<int>> factors = getFactors(hints[now].val);
	
	for(const auto& factor: factors) {
		auto f = factor;
		sort(f.begin(), f.end());
		if(f.size() == 1) continue;
		do {
			int f_len = f.size();
			f_len--;
			for(int i=0;i<(1<<f_len); i++) {
				vector<pair<int,int>> mod_pos;
				if(tryFill(hints[now].pos, f, grids, mod_pos, i)) {
					//printf("%d:\n", now);
					//printGrids(grids);
					dfs(grids, now+1);
					clearMods(grids, mod_pos);
				}
			}
		} while(next_permutation(f.begin(), f.end()));
	}
}
int main(void) {
	for(const auto& hint: hints)
		hints_map[hint.pos.first][hint.pos.second] = hint.val;
	vector<vector<Grid>> grids(N+1,  vector<Grid>(N+1, UNKNOWN));
	grids[1][10] = S1;
	found = false;
	dfs(grids, 0);
    return 0;
}
