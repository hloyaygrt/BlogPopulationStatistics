#include <iostream>
#include <fstream>
#include <set>

void genTest(int n) {
	srand(time(0));

	std::ofstream inputFile("input.txt");
	std::ofstream outputFile("output.txt");

	inputFile << n << std::endl;
	int cnt = 0;

	for (int i = 0; i < n; i++) {
		int type = rand() % 2;
		if (!i)
			type = 0;

		inputFile << ( type != 0 )<< ' ';
		if (type == 0) {
			cnt++;
			for (int j = 0; j < 4; j++) {
				int x = rand() % 1000;
				inputFile << x;
				if (j != 3)
					inputFile << '.';
			}
			inputFile << std::endl;
		} else {
			int l = rand() % cnt, r = rand() % cnt;
			if (l > r)
				std::swap(l, r);
			// cerr << cnt << endl;
			while (r - l + 1 <= cnt / 2) {
				l = rand() % cnt, r = rand() % cnt;
				if (l > r)
					std::swap(l, r);
			}

			inputFile << l << ' ' << r << std::endl;
		}
	}
}
