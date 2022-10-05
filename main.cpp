#include"snail.h"
#include<algorithm>
#include<math.h>
const int N = 1000000;
bool cmp_x(const snail& snail1, const snail& snail2) { //comparator for x
	return snail1.x < snail2.x || snail1.x == snail2.x && snail1.y < snail2.y;
}
bool cmp_y(const snail& snail1, const snail& snail2) { //comparator for y
	return snail1.y < snail2.y;
}
double calculat_dist(const snail& snail1, const snail& snail2) {//auxiliary function that calculates distance between the snails
	return sqrt((snail1.x - snail2.x) * (snail1.x - snail2.x) + (snail1.y - snail2.y) * (snail1.y - snail2.y));
}
double corner(const snail& snail1, const snail& snail2) {
	return (snail1.x * snail2.x + snail1.y * snail2.y) /()
}
double mindist;
void upd_ans(const snail& snail1, const snail& snail2) {//auxiliary function that calculates minimal distance between the snails
	double dist = sqrt((snail1.x - snail2.x) * (snail1.x - snail2.x) + (snail1.y - snail2.y) * (snail1.y - snail2.y));
	if (dist < mindist)
		mindist = dist;
}
snail quad[N];
void rec(int l, int r) {
	if (r - l <= 3) {
		for (int i = l; i <= r; ++i)
			for (int j = i + 1; j <= r; ++j)
				upd_ans(quad[i], quad[j]);
		sort(quad + l, quad + r + 1, &cmp_y);
		return;
	}

	int m = (l + r) >> 1;
	int m_x = quad[m].x;
	rec(l, m), rec(m + 1, r);
	static snail t[N];
	merge(quad + l, quad + m + 1, quad + m + 1, quad + r + 1, t, &cmp_y);
	copy(t, t + r - l + 1, quad + l);

	int tsz = 0;
	for (int i = l; i <= r; ++i)
		if (abs(quad[i].x - m_x) < mindist) {
			for (int j = tsz - 1; j >= 0 && quad[i].y - t[j].y < mindist; --j)
				upd_ans(quad[i], t[j]);
			t[tsz++] = quad[i];
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
	for (int i = 1; i < number - 1; i++) {

	}
	mindist = 1E20;
	rec(0, number - 1);
	cout << "the minimum time is equal to " << mindist << '\n';
	return 0;
}
