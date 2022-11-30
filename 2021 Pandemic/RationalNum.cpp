#include <iostream>
#include <bits/stdc++.h>
using namespace std;

bool read_rational(int& num, int& den) {
    int d = __gcd(num, den);
    num = num / d;
    den = den / d;
    return true;
}

int main() {
	int num, den;
	while (read_rational(num, den)) cout << num << ' ' << den << endl;
}