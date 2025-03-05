// hi
#include <bits/stdc++.h>
using namespace std;
#define PB push_back
#define MP make_pair
#define F first
#define S second
using LL = long long int;
#define N 11
constexpr int region[N][N]={
	{ 1, 1, 1, 3, 3, 3, 4, 4, 5, 5, 5},
	{ 1, 2, 2, 2, 3, 3, 4, 5, 5, 5, 6},
	{ 1, 2, 2, 3, 3, 3, 4, 5, 5, 5, 6},
	{ 1, 2, 2, 3, 3, 7, 7, 5, 6, 6, 6},
	{ 1, 2, 3, 3, 5, 5, 7, 5, 6,11, 6},
	{ 1, 5, 5, 5, 5, 5, 5, 5,11,11,12},
	{ 8, 5, 5, 5, 5,10,10, 5,11,11,11},
	{ 8, 8, 9, 5, 9,10,10, 5, 5,11, 5},
	{ 8, 8, 9, 9, 9,10,10, 5, 5, 5, 5},
	{ 8, 9, 9, 8, 8, 8,10, 5, 5, 5,13},
	{ 8, 8, 8, 8, 8,10,10,10, 5, 5,13}
};
void print(vector<int> &cur) {
	for(int i=0;i<N;i++)
		printf("%2d ", cur[i]);
	printf("\n");
}
void print2(vector<vector<int>> &cur) {
	for(int i=0;i<N;i++) {
		for(int j=0;j<N;j++)
			printf("%2d ", cur[i][j]);
		printf("\n");
	}
	printf("\n");
	LL sum=0;
	for(int i=0;i<N;i++){
		LL num=0;
		for(int j=0;j<N;j++) {
			if(cur[i][j]==-1) {
				sum += num;
				num=0;
			}else{
				num = num * 10 + cur[i][j];
			}
		}
		sum += num;
	}
	printf("%lld\n", sum);
}
void dfs(int r, int c, LL num, vector<int>&cur, vector<vector<int>>&all, const function<bool(LL)> &valid_num) {
	if(c==N) {
		if(cur[c-1]!=-1 && !(num >=10 && valid_num(num))) return;
		//print(cur);
		all.push_back(cur);
		return;
	}
	// try -1
	if(c==0 || cur[c-1]!=-1) { // no consecutive -1
		if(c==0 || (num >= 10 && valid_num(num))) {
			cur[c]=-1;
			dfs(r, c+1, 0, cur, all, valid_num);
		}
	}
	for(int i=0;i<10;i++) {
		if(num==0 && i==0) continue; // no leading 0
		if(c>0 && region[r][c-1]==region[r][c] && cur[c-1]!=-1 && cur[c-1]!=i) continue; // same region, same value
		if(c>0 && region[r][c-1]!=region[r][c] && cur[c-1]==i) continue; // different region, different value
		cur[c]=i;
		dfs(r, c+1, num * 10 + i, cur, all, valid_num);
	}
}
vector<vector<int>> genSquare(int r) {
	vector<vector<int>> all;
	vector<int> cur(N);
	auto is_square = [](LL num) {
		LL d = sqrt(num);
		return d*d == num || (d-1)*(d-1)==num || (d+1)*(d+1)==num;
	};
	dfs(r, 0, 0, cur, all, is_square);
	printf("%d: %d\n", r, all.size());
	return all;
}
vector<vector<int>> genPalindromeDelta(int r, int delta) {
	vector<vector<int>> all;
	vector<int> cur(N);
	auto is_palindrome_delta = [delta](LL num) {
		num-=delta;
		vector<int> digits;
		while(num) {
			digits.push_back(num%10);
			num/=10;
		}
		for(int i=0, j=int(digits.size())-1;i<j;i++, j--)
			if(digits[i]!=digits[j]) return false;
		return true;
	};
	dfs(r, 0, 0, cur, all, is_palindrome_delta);
	printf("%d: %d\n", r, all.size());
	return all;
}
vector<vector<int>> genPrimePP(int r) {
	vector<vector<int>> all;
	vector<int> cur(N);
	vector<int> primes;
	vector<int> is_prime(1000000, true);
	is_prime[1]=false;
	unordered_set<LL> large_prime_pp;
	unordered_set<int> pp;
	for(int i=2;i<1000000;i++){
		if(is_prime[i]) {
			if(i<1000) {
				primes.push_back(i);
				for(int j=i;j<=100;j*=i) pp.insert(j);
			}else if(i>=1000 && i<10000) {
				large_prime_pp.insert(i*i);
				large_prime_pp.insert(i*i*i);
			}else if(i>=10000) {
				large_prime_pp.insert(i*i);
			}
			for(int j=i+i;j<1000000;j+=i)
				is_prime[j]=false;
		}
	}
	auto is_primepp = [&primes, &large_prime_pp, &pp](LL num) {
		for(int i=0;i<primes.size() && primes[i] <= num;i++) {
			if(num%primes[i]==0) {
				int cnt=0;
				while(num%primes[i]==0) {
					cnt++;
					num/=primes[i];
				}
				if(num!=1) return false;
				return pp.find(cnt) !=pp.end();
			}
		}
		return large_prime_pp.find(num) != large_prime_pp.end();
	};
	dfs(r, 0, 0, cur, all, is_primepp);
	printf("%d: %d\n", r, all.size());
	return all;
}
vector<vector<int>> genDigitSum(int r, int sum) {
	vector<vector<int>> all;
	vector<int> cur(N);
	auto is_digit_sum = [sum](LL num) {
		int cur=0;
		while(num) {
			cur += num%10;
			num/=10;
			if(cur > sum) return false;
		}
		return cur==sum;
	};
	dfs(r, 0, 0, cur, all, is_digit_sum);
	printf("%d: %d\n", r, all.size());
	return all;
}
vector<vector<int>> genFibonacci(int r) {
	vector<vector<int>> all;
	vector<int> cur(N);
	LL f1=1, f2=2;
	constexpr LL limit = 1000000000000LL;
	vector<LL> fibs;
	while(f1 < limit) {
		fibs.push_back(f1);
		LL f3 = f1+f2;
		f1 = f2;
		f2 = f3;
	}
	auto is_fib = [&fibs](LL num) {
		return *lower_bound(fibs.begin(), fibs.end(), num) == num;
	};
	dfs(r, 0, 0, cur, all, is_fib);
	printf("%d: %d\n", r, all.size());
	return all;
}
vector<vector<int>> genMultiple(int r, int base) {
	vector<vector<int>> all;
	vector<int> cur(N);
	auto is_multiple = [base](LL num) {
		return num % base == 0;
	};
	dfs(r, 0, 0, cur, all, is_multiple);
	printf("%d: %d\n", r, all.size());
	return all;
}
vector<vector<int>> genPalindromeMultiple(int r, int base) {
	vector<vector<int>> all;
	vector<int> cur(N);
	auto is_palindrome_multiple = [base](LL num) {
		if(num%base!=0) return false;
		vector<int> digits;
		while(num) {
			digits.push_back(num%10);
			num/=10;
		}
		for(int i=0, j=int(digits.size())-1;i<j;i++, j--)
			if(digits[i]!=digits[j]) return false;
		return true;
	};
	dfs(r, 0, 0, cur, all, is_palindrome_multiple);
	printf("%d: %d\n", r, all.size());
	return all;
}
vector<vector<int>> genDigitsProd(int r, int val) {
	vector<vector<int>> all;
	vector<int> cur(N);
	auto is_digits_prod = [val](LL num) {
		int mul=1;
		while(num) {
			mul = (mul * (num%10))%10;
			num/=10;
		}
		return mul == 1;
	};
	dfs(r, 0, 0, cur, all, is_digits_prod);
	printf("%d: %d\n", r, all.size());
	return all;
}
bool isValidRow(int r, const vector<int>& row, const vector<int>& prev_row) {
	for(int i=0;i<N;i++) {
		if(row[i]==-1){
			if(prev_row[i]==-1) return false; // no consecutive -1
		}else{
			if(prev_row[i]==-1) continue;
			if(region[r][i] == region[r-1][i] && prev_row[i]!=row[i]) return false;
			if(region[r][i] != region[r-1][i] && prev_row[i]==row[i]) return false; 
		}
	}
	return true;
}
bool found;
LL sum;
void search(int r, vector<vector<int>> &cur, vector<vector<vector<int>>>&all) {
	//if(found) return;
	if(r==N) {
		print2(cur);
		found = true;
		return;
	}
	for(const auto& cur_row: all[r]) {
		if(r==0 || (r>0 && isValidRow(r, cur_row, cur[r-1]))) {
			cur[r] = cur_row;
			search(r+1, cur, all);
		}
	}
}
int main(void) {
	vector<vector<vector<int>>> all(N);
	all[0] = genSquare(0);
	all[1] = genPalindromeDelta(1, 1);
	all[2] = genPrimePP(2);
	all[3] = genDigitSum(3, 7);
	all[4] = genFibonacci(4); // slow
	all[5] = genSquare(5);
	all[6] = genMultiple(6, 37);
	all[7] = genPalindromeMultiple(7, 23);
	all[8] = genDigitsProd(8, 1);
	all[9] = genMultiple(9, 88);
	all[10] = genPalindromeDelta(10, -1);
	vector<vector<int>> cur(N, vector<int>(N));
	found = false;
	search(0, cur, all);
    return 0;
}
