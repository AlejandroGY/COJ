#include <iostream>
#include <utility>
#include <vector>
#include <queue>
#include <list>
#include <algorithm>
#include <climits>
using namespace std;

int r, c, idx;
char mapa[52][52];
vector<pair<int, int>> islas[1252];

int lider[1252];
vector<pair<int, pair<int, int>>> v;

void init() {
	sort(v.begin(), v.end());
	for(int i = 0; i < idx; ++i) {
		lider[i] = i;
	}
}

void Union(int a, int b) {
	lider[b] = a;
}

int Find(int n) {
	if(n == lider[n]) return n;
	return (lider[n] = Find(lider[n]));
}

int Kruskal() {
	int a, b, sum = 0;
	init();
	for(int i = 0; i < v.size(); ++i) {
		a = Find(v[i].second.first);
		b = Find(v[i].second.second);
		if(a != b) {
			sum += (v[i].first);
			Union(a, b);
		}
	}
	return sum;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	int T; cin >> T;
	while(T--) {
		cin >> r >> c;
		for(int i = 0; i < r; ++i) {
			for(int j = 0; j < c; j++) {
				cin >> mapa[i][j];
			}
		}
		
		idx = 0;
		bool memo[52][52] = {};
		auto busqueda = [&](int x, int y) {
			memo[x][y] = true;
			islas[idx].push_back(make_pair( x, y ));
			vector<pair<int, int>> v = { {x, y} };
			do {
				auto actual = v.back();
				v.pop_back();
				pair<int, int> vecinos[] = {
					{actual.first-1, actual.second},
					{actual.first+1, actual.second},
					{actual.first, actual.second-1},
					{actual.first, actual.second+1}
				};
				for(auto current : vecinos) {
					if(0 <= current.first && current.first < r && 0 <= current.second && current.second < c && mapa[current.first][current.second] == 'X' && !memo[current.first][current.second]) {
						memo[current.first][current.second] = true;
						islas[idx].push_back(make_pair(current.first, current.second));
						v.push_back(current);
					}
				}
			}while(!v.empty());
		};
		
		for(int i = 1; i < r-1; ++i) {
			for(int j = 1; j < c-1; j++) {
				if(mapa[i][j] == 'X' && !memo[i][j]) {
					busqueda(i, j);
					++idx;
				}
			}
		}

		for(int i = 0; i < idx-1; ++i) {
			for(int j = i + 1; j < idx; ++j) {
				int costo_act = INT_MAX;
				for(auto it1 = islas[i].begin(); it1 != islas[i].end(); ++it1) {
					for(auto it2 = islas[j].begin(); it2 != islas[j].end(); ++it2) {
						auto x1 = (it1)->first, y1 = (it1)->second;
						auto x2 = (it2)->first, y2 = (it2)->second;
						costo_act = min(costo_act, abs(x2-x1) + abs(y2-y1));
					}
				}
				v.push_back(make_pair(costo_act-1, make_pair(i, j)));
			}
		}

		cout << Kruskal() << "\n";
		v.clear();
		for(int i = 0; i < idx; i++) islas[i].clear();
	}
}
