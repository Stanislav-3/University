extern "C" __declspec(dllexport) int __cdecl Multiplication(int a, int b, int mod) {
	a %= mod;
	b %= mod;
	return (a * b) % mod;
}

extern "C" __declspec(dllexport) int __stdcall BinPow(int a, int n, int mod) {
	long long int result = 1;
	while (n) {
		if (1 & n) {
			result *= a % mod;
		}
		a *= a % mod;
		n >>= 1;
	}
	return result;
}
