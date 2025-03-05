// hi
#include <bits/stdc++.h>
using namespace std;
#define PB push_back
#define MP make_pair
#define F first
#define S second
using LL = int64_t;
using pt = pair<double, double>;
bool check(const pt& a, const pt& b) {
	pt mid = {(a.first + b.first)/2 , (a.second + b.second)/2};
	double slope = (b.second - a.second) / (b.first - a.first);
	double c = mid.second + mid.first / slope;
	double x = a.first;
	double y = a.second;
	if(x<=y && x<=1.0-x && x <=1.0 -y) { // x=0 
		double yy = c;
		return yy>=0 && yy<=1.0;
	}
	if(y<=x && y<=1.0-x && y <=1.0-y) {  // y=0
		double xx = (0.0+c) * slope;
		return xx>=0 && xx <=1.0;
	}
	if(1.0-x <=x && 1.0-x <=y && 1.0-x <=1.0-y) { // x=1
		double yy = -1.0 / slope + c;
		return yy>=0 && yy<=1.0;
	}
	if(1.0-y <=x && 1.0-y <=y && 1.0-y <=1.0-x) { // y=1
		double xx = (-1.0 + c) * slope;
		return xx>=0 && xx <=1.0;
	}
	assert(false);
	return false;
}
int main(void) {
	std::mt19937 generator(std::random_device{}());
	std::uniform_real_distribution<double> distribution(0.0, 1.0);
	//double random_number = distribution(generator);
	int cnt = 0;
	for(int i=0, base=0;i<1000'000'000;i++, base++) {
		pt blue = {distribution(generator), distribution(generator)};
		pt red = {distribution(generator), distribution(generator)};
		if(check(blue, red)) cnt++;
		if(base % 10000000 == 0)
			printf("%lf\n", double(cnt) / base);
	}
    return 0;
}
