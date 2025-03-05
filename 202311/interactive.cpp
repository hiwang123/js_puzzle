// hi
#include <bits/stdc++.h>
using namespace std;
#define PB push_back
#define MP make_pair
#define F first
#define S second
typedef long long int LL;
typedef pair<int,int> pos;
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
  private:
	int n;
	vector<Move> moves;
    vector<vector<int>> board;
    pos cur;
};
int main(void) {
	int n = 8;
	vector<vector<int>> input(n, vector<int>(n));
	printf("Input init board:\n");
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			scanf("%d",&input[i][j]);
	printf("Input init pos:\n");
	pos p;
	scanf("%d%d", &p.F, &p.S);
	Game g(input, p);
	while(true) {
		g.printInfo();
		printf("Input h and next_pos (input -1 to undo): ");
		int h;
		scanf("%d",&h);
		if(h>=0) {
			int x, y;
			scanf("%d%d",&x,&y);
			if(!g.waitAndMove(h, pos{x, y})) {
				printf("Invalid move.. continue\n");
				continue;
			}
		}else {
			g.undo();
		}
	}
    return 0;
}
