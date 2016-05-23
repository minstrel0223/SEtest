#include<iostream>
#include<cmath>
#include<set>
#include<algorithm>
#include<vector>
#include<cstdio>
using namespace std;
#define PI acos(-1)
int dots[2010][2010];
vector<double> target;
struct point
{
	int x, y;
};
struct Circle
{
	point center;
	double radius;
	bool operator<(const Circle &b)const
	{
		return (this->radius < b.radius);
	};
};
double distance(point p1, point p2)
{
	return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}
set<Circle> cr;
void refresh(point p, double r)
{
	point temp;
	for (int i = 0; i <= 2000; i++)
	for (int j = 0; j <= 2000; j++)
	{
		temp.x = i; temp.y = j;
		if (distance(temp, p) <= r)
			dots[i][j] = 1;
	}
}
double calradius(point p)
{
	double minradius = min(min(min(p.x, p.y), 2000 - p.x), 2000 - p.y);

	for (set<Circle>::iterator it = cr.begin(); it != cr.end(); it++)
	{
		minradius = min(minradius, distance(p, it->center) - it->radius);
	}
	return minradius;
}
int main()
{
	int count = 2;
	int m;
	point a;
	point b;
	memset(dots, 0, sizeof(dots));
	//refresh(a, 1);
	double maxr = 0;
	double sum = 0;
	cin >> m;
	m--;
	a.x = 1000; a.y = 1000;
	target.push_back(1000);
	refresh(a, 1000);
	cout << "1th radius " << 1000 / 1000 << " x: " << 0 << " y: " << 0 << endl;
	cr.insert(Circle{ a, 1000 });
	while (m--)
	{

		maxr = 0;
		for (int i = 0; i <= 2000; i++)
		for (int j = 0; j <= 2000; j++)
		{
			if (!dots[i][j])
			{
				a.x = i; a.y = j;
				double temp = calradius(a);
				if (temp > maxr)
				{
					maxr = temp;
					b.x = i; b.y = j;
				}
				//cout << maxr << endl;

			}
		}
		dots[b.x][b.y] = 1;
		refresh(b, maxr);
		target.push_back(maxr);
		cout << count++ << "th radius " << maxr / 1000 << " x: " << (double)b.x / 1000 - 1 << " y: " << (double)b.y / 1000 - 1 << endl;
		cr.insert(Circle{ b, maxr });
	}
	for (vector<double>::iterator it = target.begin(); it != target.end(); it++)
		sum += (*it)*(*it);
	printf("%.4f\n", sum / 1000000);
	system("pause");
}