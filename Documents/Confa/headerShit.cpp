#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>

void assert(bool rule, std::string message = "Not correct data.") {
	if (rule == 0) {
		std::cout << message;
		exit(226);
	}
}

void wrongAns(bool rule, int l, int r) {
	if (!rule)
	std::cout << "Test = [" << l << "," << "]\n";
	assert(rule, "Wrong answer!");
}

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

void Init(); // удалить весь мусор с прошлых тестов, приготовиться к этому
int answerQuery(int l, int r); // K(l, r) 
void pushBackQuery(IP& ip); // добавить IP в конец

double SolvePackage(std::string path, std::string answer_path) {
	clock_t start = clock();
	std::ifstream Input(path);
	std::ifstream Answers(answer_path);

	// Init();

	std::ios_base::sync_with_stdio(0);

	int n;
	Input >> n;

	assert(n);

	while (n--) {
		int type; // 0 - добавить, 1 - ответить
		Input >> type;

		assert(type == 0 || type == 1);

		if (type == 0) {
			std::string ipv4;
			Input >> ipv4;

			int cntDots = 0;
			for (int i = 0; i < ipv4.size(); i++)
				if (ipv4[i] == '.')
					cntDots++;
			assert(cntDots == 3);

			IP duty_ip = IP(ipv4);
			// pushBackQuery(duty_ip);
		} else {
			int l, r;
			int correct_answer;

			Input >> l >> r;
			Answers >> correct_answer;

			wrongAns(answerQuery(l, r) == correct_answer, l, r);
		}
	}

	return (double)(clock() - start) / CLOCKS_PER_SEC;
}

int main() {
	double used_time = SolvePackage("train.txt", "results.txt");
	std::cout << (int) used_time;
	return 0;
}