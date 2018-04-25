#include <bits/stdc++.h>

int main( ) {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);

	int tc;
	std::cin >> tc;

	while (tc--) {
		int n;
		std::string s;
		std::cin >> n >> s;

		int tabla[27] = { };
		for (int i = 0; i < s.size( ); ++i) {
			tabla[s[i] - 'A'] += 1;
		}

		char mid = ' ';
		std::string res = "";
		for (int i = 0; i < 27; ++i) {
			if ((tabla[i] & 1) && mid == ' ') {
				mid = (i + 'A');
			}
			for (int j = 2; j <= tabla[i]; j += 2) {
				res += char(i + 'A');
			}
		}
		std::cout << res;
		if (mid != ' ') {
			std::cout << mid;
		}
		std::reverse(res.begin( ), res.end( ));
		std::cout << res << "\n";
	}
}