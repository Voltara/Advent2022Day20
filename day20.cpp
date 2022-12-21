#include <algorithm>
#include <cstdio>
#include <fstream>
#include <numeric>
#include <sys/time.h>
#include <vector>

int64_t solve(const std::vector<short> &input, int rounds, int64_t key);
double now();

int main() {
	char path[64];
	for (int i = 0; i < 100; i++) {
		std::vector<short> input;

		sprintf(path, "inputs/%02d", i);

		std::ifstream f(path);
		int value;
		while ((f >> value)) {
			input.push_back(value);
		}

		auto t0 = now();
		int64_t part1 = solve(input, 1, 1);
		int64_t part2 = solve(input, 10, 811589153);
		auto elapsed = now() - t0;
		printf("%.6f (%ld %ld)\n", elapsed, part1, part2);
	}

	return 0;
}

int64_t solve(const std::vector<short> &input, int rounds, int64_t key) {
	int len = input.size(), mod = len - 1;

	std::vector<short> indices(len);
	std::iota(indices.begin(), indices.end(), 0);

	std::vector<short> offsets;
	offsets.reserve(len);
	for (auto n : input) {
		int offset = n * key % mod;
		if (offset < 0) offset += mod;
		offsets.push_back(offset);
	}

	for (int round = 0; round < rounds; round++) {
		for (int i = 0; i < len; i++) {
			auto it = std::find(indices.begin(), indices.end(), i);
			indices.erase(it, it + 1);
			int pos = (it + offsets[i] - indices.begin()) % mod;
			indices.insert(indices.begin() + pos, i);
		}
	}

	int zeroidx = std::find(input.begin(), input.end(), 0) - input.begin();
	int base = std::find(indices.begin(), indices.end(), zeroidx) - indices.begin();

	int64_t answer = 0;
	for (int i : { 1000, 2000, 3000 }) {
		answer += input[indices[(base + i) % len]];
	}
	answer *= key;

	return answer;
}

double now() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec + tv.tv_usec * 1e-6;
}
