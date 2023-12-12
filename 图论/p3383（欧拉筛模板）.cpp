#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e8 + 10;
bitset<maxn> pri;
int primes[maxn], pp = 0;

void eulerSieve(int n) {
	for (int i = 2; i <= n; ++i) {
		if (!pri[i])
			primes[++pp] = i;
		for (int j = 1; primes[j] * i <= n; ++j) {
			pri[primes[j] * i] = 1;
			if (i % primes[j] == 0)
				break;
		}
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	int n, q, k;
	cin >> n >> q;
	eulerSieve(n);
	while (q--) {
		cin >> k;
		cout << primes[k] << endl;
	}
}