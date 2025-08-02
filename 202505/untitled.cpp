// hi
#include <bits/stdc++.h>
using namespace std;
using LL = long long int;
// ulimit -s 65536

// toggle
//#define SMALL

/*

---regions---
2 2 2 2 2 2 2 2 2 2 2
2 4 2 2 2 2 2 2 2 2 2
4 4 3 3 3 3 4 4 4 2 4
4 3 3 4 3 1 4 4 4 4 4
4 3 3 4 3 1 1 4 4 1 4
4 4 4 4 4 1 1 1 1 1 4
4 3 6 6 4 4 1 1 6 1 1
4 3 6 6 6 6 6 6 6 7 7
3 3 3 3 6 3 6 7 7 7 7
3 3 3 3 3 3 3 3 3 3 3
3 3 7 7 7 7 7 7 3 3 3

---displaces---
X 1 2 0 0 0 3 X 1 0 2
3 0 X 0 0 3 X 0 3 0 X
X 1 0 1 0 X 2 1 X 0 2
3 0 3 X 0 1 X 1 0 0 X
X 2 2 1 X 1 1 X 4 0 2
1 1 X 1 1 0 X 0 4 4 X
X 0 0 1 0 0 0 1 X 0 4
3 0 1 X 3 0 3 X 3 2 X
0 1 X 1 0 0 0 1 X 1 2
2 0 2 6 0 X 2 6 6 2 X
X 1 0 X 1 1 0 X 1 0 0

---total---
X 3 4 2 2 2 5 X 3 2 4
5 4 X 2 2 5 X 2 5 2 X
X 5 3 4 3 X 6 5 X 2 6
7 3 6 X 3 2 X 5 4 4 X
X 5 5 5 X 2 2 X 8 1 6
5 5 X 5 5 1 X 1 5 5 X
X 3 6 7 4 4 1 2 X 1 5
7 3 7 X 9 6 9 X 9 9 X
3 4 X 4 6 3 6 8 X 8 9
5 3 5 9 3 X 5 9 9 5 X
X 4 7 X 8 8 7 X 4 3 3


*/

#ifdef SMALL
#define N 5
#define R 3
int region[N][N]={
	{1,1,1,1,1},  // 0
	{2,1,1,1,1},  // 1
	{2,2,1,1,1},  // 2
	{0,2,2,1,1},  // 3
	{0,0,2,2,1}}; // 4
int highlight[N][N]={
	{1,1,0,0,0},  // 0
	{1,0,0,0,0},  // 1
	{0,0,0,0,0},  // 2
	{0,0,0,0,1},  // 3
	{0,0,0,1,1}}; // 4
#else
#define N 11
#define R 9
int region[N][N]={
	{1,1,1,1,1,1,1,1,1,1,1}, // 0
	{1,2,1,1,1,1,1,1,1,1,1}, // 1
	{2,2,3,3,3,3,4,4,4,1,4}, // 2
	{2,3,3,2,3,5,4,4,4,4,4}, // 3
	{2,3,3,2,3,5,5,4,4,5,4}, // 4
	{2,2,2,2,2,5,5,5,5,5,4}, // 5
	{2,6,7,7,2,2,5,5,7,5,5}, // 6
	{2,6,7,7,7,7,7,7,7,8,8}, // 7
	{6,6,6,6,7,6,7,8,8,8,8}, // 8
	{6,6,6,6,6,6,6,6,6,6,6}, // 9
	{6,6,0,0,0,0,0,0,6,6,6}};// 10
int highlight[N][N]={
	{0,0,0,0,0,0,0,0,0,0,0}, // 0
	{0,0,0,1,1,0,0,0,0,0,0}, // 1
	{0,0,0,0,1,0,0,0,0,1,0}, // 2
	{0,0,0,0,0,0,0,0,1,1,0}, // 3
	{0,0,0,0,0,0,0,0,0,0,0}, // 4
	{0,0,0,0,0,1,0,0,0,0,0}, // 5
	{0,1,1,0,0,1,1,0,0,0,0}, // 6
	{0,1,0,0,0,1,0,0,0,0,0}, // 7
	{0,0,0,0,1,1,0,0,0,0,0}, // 8
	{0,0,0,0,1,0,0,0,0,0,0}, // 9
	{0,0,0,0,0,0,0,0,0,0,0}};// 10
#endif

// LURD
int dx[4] = {0, -1, 0, 1};
int dy[4] = {-1, 0, 1, 0};

unordered_set<int> r_adj[R];
vector<int> masks; // bit 1 is tile, size: 54

/*  helper */
inline bool inside(int x, int y) {
	return x>=0 && x<N && y>=0 && y<N;
}
inline bool hasTile(int v, int p) {
	return (v>>p)&1;
}
inline bool isSquare(LL v) {
	LL s = sqrt(v);
	return LL(s)*s == v;
}
inline bool productIs(LL v, int target) {
	int m=1;
	while(v) {
		m *= v%10;
		v/=10;
		if(m>target) return false;
	}
	return m==target;
}
inline bool multipleOf(LL v, int target) {
	return v%target==0;
}
inline bool divByDigits(LL v) {
	unordered_set<int> digits;
	LL x=v;
	while(x) {
		digits.insert(x%10);
		x/=10;
	}
	for(int d: digits)
		if(v%d!=0) return false;
	return true;
}
inline bool oddPalidrome(LL v) {
	if(v%2==0) return false;
	vector<int> digits;
	while(v) {
		digits.push_back(v%10);
		v/=10;
	}
	int n=digits.size();
	for(int i=0;i<n-1-i;i++)
		if(digits[i] != digits[n-1-i])
			return false;
	return true;
}
unordered_set<LL> fibs;
inline bool isFib(LL v) {
	return fibs.find(v) != fibs.end();
}
unordered_set<int> primes; // max: 1e6
inline bool isPrime(LL v) {
	if(v<=1'000'000)
		return primes.find(v) != primes.end();
	else{
		for(int prime: primes)
			if(v%prime==0) return false;
	}
	return true;
}
/*  helper */

vector<vector<int>> displaces(N, vector<int>(N, 0));
unordered_set<LL> nums_seen;

bool checkRules(int rule, LL num) {
#ifdef SMALL
    if (rule==0) return multipleOf(num, 11);
	else if(rule==1) return multipleOf(num, 14);
	else if(rule==2) return multipleOf(num, 28);
	else if(rule==3) return multipleOf(num, 101);
	else if(rule==4) return multipleOf(num, 2025);
#else
	if (rule==0) return isSquare(num);
	else if(rule==1) return productIs(num, 20);
	else if(rule==2) return multipleOf(num, 13);
	else if(rule==3) return multipleOf(num, 32);
	else if(rule==4) return divByDigits(num);
	else if(rule==5) return productIs(num, 25);
	else if(rule==6) return divByDigits(num);
	else if(rule==7) return oddPalidrome(num);
	else if(rule==8) return isFib(num);
	else if(rule==9) return productIs(num, 2025);
	else if(rule==10) return isPrime(num);
#endif
	return false;
}

bool ans;

void print(const vector<int>& region_clr, const vector<int>& tiles, int row) {
	printf("---regions---\n");
	for(int i=0;i<row;i++)
		for(int j=0;j<N;j++) {
			printf("%d", region_clr[region[i][j]]);
			printf("%c", j==N-1 ?'\n' : ' ');
		}
	printf("\n---displaces---\n");
	for(int i=0;i<row;i++)
		for(int j=0;j<N;j++) {
			if (hasTile(tiles[i], j)) printf("X");
			else printf("%d", displaces[i][j]);
			printf("%c", j==N-1 ?'\n' : ' ');
		}
	printf("\n---total---\n");
	for(int i=0;i<row;i++)
		for(int j=0;j<N;j++) {
			if (hasTile(tiles[i], j)) printf("X");
			else printf("%d", region_clr[region[i][j]] + displaces[i][j]);
			printf("%c", j==N-1 ?'\n' : ' ');
		}
	printf("============\n");
}

void fillTile(const vector<int>& region_clr, vector<int>& tiles, int n);

bool isRowValid(const vector<int>& region_clr, vector<int>& tiles, int row, vector<LL>& nums_added) {
	vector<LL> nums;
	LL cur=0;
	for(int i=0;i<N;i++) {
		if (hasTile(tiles[row], i)) {
			if (cur !=0) {
				if (!checkRules(row, cur)) return false;
				nums_added.push_back(cur);
			}
			cur=0;
		} else {
			cur = cur * 10 + displaces[row][i] + region_clr[region[row][i]];
		}
	}
	if (cur !=0) {
		if (!checkRules(row, cur)) return false;
		nums_added.push_back(cur);
	}
	return true;
}

void fillRow(const vector<int>& region_clr, vector<int>& tiles, int row, int col) { // displaces
	if(ans) return;
	while(col < N && !hasTile(tiles[row], col)) col++; 
	if(col==N) {
		// verify rules
		vector<LL> nums_added;
		if (row>0 && !isRowValid(region_clr, tiles, row-1, nums_added)) return;
		if (row==N-1 && !isRowValid(region_clr, tiles, row, nums_added)) return;
		
		unordered_set<LL> st;
		for(LL num: nums_added){
			if(st.find(num) != st.end()) return;
			if (nums_seen.find(num) != nums_seen.end()) return;
			st.insert(num);
		}
		
		for(LL num: nums_added){
			nums_seen.insert(num);
		}

		// all matched!
		if (row+2 <= N)
			fillTile(region_clr, tiles, row+2);
		else {
			// print ans
			print(region_clr, tiles, N);
			//ans = true;
		}
		
		for(LL num: nums_added){
			nums_seen.erase(num);
		}

	} else {
		// row, col is displaced
		int reg = region[row][col];
		int num = region_clr[reg]; // number to displace
		int ub[4] = {num, num, num, num};
		for(int d=0;d<4;d++) {
			int nx = row+dx[d], ny = col+dy[d];
			if (!inside(nx, ny) || highlight[nx][ny]) // can a cell be displaces twice???
				ub[d] = 0;
			else
				ub[d] = min(ub[d], 9-region_clr[region[nx][ny]]-displaces[nx][ny]); // can't exceed 9
		}
		for(int l=0; l<=ub[0]; l++) {
			for(int u=0;l+u<=num && u<=ub[1];u++)
				for(int r=0;l+u+r<=num && r<=ub[2];r++) {
					int d = num-l-u-r;
					if (d>ub[3]) continue;
					if (inside(row+dx[0], col+dy[0]) && l) displaces[row+dx[0]][col+dy[0]] += l;
					if (inside(row+dx[1], col+dy[1]) && u) displaces[row+dx[1]][col+dy[1]] += u;
					if (inside(row+dx[2], col+dy[2]) && r) displaces[row+dx[2]][col+dy[2]] += r;
					if (inside(row+dx[3], col+dy[3]) && d) displaces[row+dx[3]][col+dy[3]] += d;
					fillRow(region_clr, tiles, row, col+1);
					if (inside(row+dx[0], col+dy[0]) && l) displaces[row+dx[0]][col+dy[0]] -= l;
					if (inside(row+dx[1], col+dy[1]) && u) displaces[row+dx[1]][col+dy[1]] -= u;
					if (inside(row+dx[2], col+dy[2]) && r) displaces[row+dx[2]][col+dy[2]] -= r;
					if (inside(row+dx[3], col+dy[3]) && d) displaces[row+dx[3]][col+dy[3]] -= d;
				}
		}
	}
}

void fillTile(const vector<int>& region_clr, vector<int>& tiles, int n) { // row
	if(ans) return;
	if (n==N) {
		fillRow(region_clr, tiles, n-1, 0);
	}else{
		for(int m: masks) {
			bool ok = true;
			if (n>0 && (m & tiles[n-1])) ok = false; // has adj tiles with previous row
			for(int i=0;i<N && ok;i++)
				if(highlight[n][i] && hasTile(m, i)) { // can't have tiles on highlight
					ok=false;
				}
			if (!ok) continue;
			tiles[n] = m;
			if (n==0)
				fillTile(region_clr, tiles, n+1);
			else
				fillRow(region_clr, tiles, n-1, 0);
		}
	}
}

int cnt=0;
#ifdef SMALL
int print_base = 10;
#else
int print_base = 1000;
#endif

void fillRegion(vector<int>& region_clr, int n, int st, int ed) { // region
	if(ans) return;
	if (n==R) {
		// fill tile, size: 4e5
		vector<int> tiles(N);
		assert(nums_seen.empty());
		if (cnt >=st && cnt < ed) {
			if (cnt % print_base == 0)
				printf("%d\n", cnt);
			fillTile(region_clr, tiles, 0);
		}
		cnt++;
	}else {
		for(int c=1;c<=9;c++) {
			bool valid = !any_of(r_adj[n].begin(), r_adj[n].end(), [&](int reg) { return c==region_clr[reg]; });
#ifdef SMALL
#else
			// manual cuts
			if (n==1 && !(c==1 || c==2)) valid = false;
			if (n==2 && c>5) valid = false;
			if (n==4 && c==9) valid = false;
			if (n==5 && !(c==1 || c==5)) valid = false;
			if (n==6 && !(c==1 || c==3 || c==5 || c==9)) valid = false;
#endif
			if (valid){
				region_clr[n] = c;
				fillRegion(region_clr, n+1, st, ed);
			}
		}
	}
}
void calcAdj() {
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++) {
			int r = region[i][j];
			for(int d=0;d<4;d++) {
				if (inside(i+dx[d], j+dy[d])) {
					int r2 = region[i+dx[d]][j+dy[d]];
					if (r==r2) continue;
					r_adj[max(r, r2)].insert(min(r, r2));
				}
			}
		}
}
void initMask() {
	for(int i=0;i<(1<<N);i++) {
		bool ok=true;
		for(int j=0;j<N-1 && ok;j++)
			if(hasTile(i, j) && hasTile(i, j+1)) {
				ok=false;
			}
		for(int j=0;j<N-2 && ok;j++)
			if(hasTile(i, j) && hasTile(i, j+2)) {
				ok=false;
			}
		if (hasTile(i, 1) || hasTile(i, N-2)) ok = false;
		if(ok) masks.push_back(i);
	}
}
void initFib() {
	LL a=1, b=2;
	constexpr LL limit=100'000'000'000LL;
	fibs.insert(a);
	while(b<limit) {
		fibs.insert(b);
		a+=b;
		swap(a, b);
	}
}
void initPrime() {
	vector<int> is_prime(1'000'001, true);
	for(int i=2;i<=1'000'000;i++)
		if(is_prime[i]) {
			primes.insert(i);
			for(int j=i+i;j<=1'000'000;j+=i)
				is_prime[j]=false;
		}
}
int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("./binary st ed\n");
	}
	calcAdj();
	initMask();
	initFib();
	initPrime();
	// search
	vector<int> region_clr(N);
	ans = false;
	
	int st = stoi(argv[1]);
	int ed = stoi(argv[2]);
	fillRegion(region_clr, 0, st, ed);
	if(ans) printf(":)\n");
	return 0;
}
