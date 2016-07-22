#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>

struct IP
{
	int data[4];
	IP() {
		for (int i = 0; i < 4; i++)
			data[i] = 0;
	}

	IP(std::string toParse) {
		toParse = "." + toParse;
		for (int i = 3; i >= 0; i--) {
			int res = 0, st = 1;
			while (toParse.back() != '.')
				res += (toParse.back() - '0') * st, 
					st *= 10, toParse.pop_back();
			toParse.pop_back();
			data[i] = res;
		}
	}
};
