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
	{7, 9, 11, 9, 10, 12, 14, 12},
	{4, 7, 5, 8, 8, 6, 13, 10},
	{4, 10, 7, 9, 6, 8, 7, 9},
	{2, 6, 4, 2, 5, 9, 8, 11},
	{0, 3, 1, 4, 2, 7, 10, 7},
	{1, 2, 0, 1, 2, 5, 7, 6},
	{0, 2, 4, 3, 5, 6, 2, 4}
};
struct Move {
	pos src, dst;
	int h;
	int cnt;
	vector<vector<int>> original;
};
class Game {
  public:
    Game() {}
    Game(vector<vector<int>> b, pos c): board(b), cur(c) { n = board.size(); }
    // cur height -h and move to next_pos
	bool waitAndMove (int h, pos next_pos) {
		int c=0;
		vector<vector<int>> tmp = board;
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				if(tmp[i][j] == board[cur.F][cur.S]) {
					tmp[i][j]-=h;
					c++;
				}
		tmp[7-cur.F][7-cur.S]+=h;
		vector<int> jump;
		jump.PB(abs(next_pos.F - cur.F));
		jump.PB(abs(next_pos.S - cur.S));
		jump.PB(abs(tmp[next_pos.F][next_pos.S]-tmp[cur.F][cur.S]));
		sort(jump.begin(), jump.end());
		if(jump[0]!=0 || jump[1]!=1 || jump[2]!=2) return false;
		moves.PB(Move{
			.src = cur,
			.dst = next_pos,
			.h = h,
			.cnt = c,
			.original = board,
		});
		board = tmp;
		cur = next_pos;
		return true;
	}
	void undo() {
		auto lst = moves.back();
		moves.pop_back();
		board = lst.original;
		cur = lst.src;
	}
	void printInfo() {
		printf("===board===\n");
		for(int i=0;i<n;i++){
			printf("%d | ", i);
			for(int j=0;j<n;j++)
				printf("%3d ", board[i][j]);
			printf("\n");
		}
		printf("-------------------------------------\n    ");
		for(int i=0;i<n;i++) printf("%3d ", i);
		printf("\n");
		printf("cur pos: (%d %d)\n", cur.F, cur.S);
		printf("steps: \n");
		for(auto &m: moves) {
			printf("%d*%d  %d,%d\n", m.h, m.cnt, m.dst.F, m.dst.S);
		}
		printf("==========\n");
	}
	pos getCur() {return cur;}
  private:
	int n;
	vector<Move> moves;
    vector<vector<int>> board;
    pos cur;
};
int main(void) {
	pos p = {7, 0};
	Game g(init_board, p);
	int sum=0;
	while(p != pos{0, 7}) {
		int h, c, x, y;
		char a1, a2;
		scanf("%d%c%d %d%c%d",&h,&a1,&c,&x,&a2,&y);
		if(!g.waitAndMove(h, pos{x, y})) {
			assert(false);
		}
		printf("(%d, %c%d)\n",h*c, char('a'+y), 8-x);
		sum+=h*c;
		p = g.getCur();
	}
	printf("%d\n", sum);
    return 0;
}
