//main.cpp
#include"snail.h"
#include<algorithm>
#include<math.h>
#include<time.h>
const int N = 10000000;
bool cmp_x(const snail& snail1, const snail& snail2) { //comparator for x
	return snail1.x < snail2.x || snail1.x == snail2.x && snail1.y < snail2.y;
}
bool cmp_y(const snail& snail1, const snail& snail2) { //comparator for y
	return snail1.y < snail2.y;
}
double mindist;
int upd_ans(const snail& snail1, const snail& snail2) {//auxiliary function that calculates minimal distance between the snails
	double dist = sqrt((snail1.x - snail2.x) * (snail1.x - snail2.x) + (snail1.y - snail2.y) * (snail1.y - snail2.y));
	if (dist < mindist) {
		mindist = dist;
		return 2;
	}
	else
		if (dist == mindist) {
			return 1;
		}
		else
			return 0;
}
snail quad[N];
snail t[N];
int is_ans_is = 0;
int u = 0;
void find(int l, int r) {
	if (r - l <= 3) {
		for (int i = l; i <= r; ++i) {
			for (int j = i + 1; j <= r; ++j)
				if (upd_ans(quad[i], quad[j]) == 1)
					u++;
				else
					u = 1;
			if (u > 1)
				is_ans_is = 0;
			else
				is_ans_is = 1;
		}
		sort(quad + l, quad + r + 1, &cmp_y);
		return ;
	}

	int m = (l + r) >> 1;
	int m_x = quad[m].x;
	find(l, m);
	double h1 = mindist;
	find(m + 1, r);
	double h2 = mindist;
	double h = min(h1, h2);
	if (h < mindist)
		mindist = h;

	int tsz = 0;
	for (int i = l; i <= r; ++i) {
		u = 0;
		if (abs(quad[i].x - m_x) <= mindist) {
			for (int j = tsz - 1; j >= 0 && quad[i].y - t[j].y < mindist; --j)
				if (upd_ans(quad[i], t[j]) == 1)
					u++;
				else
					u = 1;
			t[tsz++] = quad[i];
		}
		if (u > 1)
			is_ans_is = 0;
		else
			is_ans_is = 1;
	}
}
int main() {
	cout << "enter the number of snails" << '\n';
	int number;
	cin >> number;
	cout << "enter the coordinates of the snails" << '\n'; 
	for (int i = 0; i < number; i++) {
		cin >> quad[i].x >> quad[i].y;
	}
	sort(quad, quad + number, &cmp_x);
	mindist = 1E20;
	find(0, number - 1);
	if (is_ans_is == 1) {
		cout << "\nthe minimum time is equal to " << mindist << '\n';
	}
	else
		cout << "\nno answer." << '\n';
	/*int number = 0;        //a fragment for empirical evaluation
	setlocale(LC_ALL, "RUS");
	while (number <= 10000) {
		for (int i = 0; i < number; i++) {
			quad[i].x = 0 + rand() % 10001;
			quad[i].y = 0 + rand() % 10001;
		}
		const clock_t start = clock();
		sort(quad, quad + number, &cmp_x);
		mindist = 1E20;
		rec(0, number - 1);
		const clock_t end = clock();
		const double time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;
		cout << '(' << number << ';' << time << ')';
		number += 100;
		if (is_ans_is == 1) {
		cout << "\nthe minimum time is equal to " << mindist << '\n';
	}
	else
		cout << "\nno answer." << '\n';

	}*/
	return 0;
}
