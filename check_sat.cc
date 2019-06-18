#include <ostream>
#include <cmath>
#include <vector>
#include <numeric>
#include <chrono>

#include "dreal/dreal.h"

namespace dreal {
	namespace {
		
		using std::cout;
		using std::endl;
		using namespace std::chrono;
		
		double minimize_main() {
			const double delta = 0.001;
			const Variable x{"x"};
			const Variable y{"y"};
			const Expression f = pow(sin(3 * 3.141592 * x),2) +
			(pow(x - 1,2)) * (1 + pow(sin(3 * 3.141592 * y),2)) +
			(pow(y - 1,2)) * (1 + pow(sin(2 * 3.141592 * y),2));
			const Formula c = (-10 <= x) && (x <= 10) && (-10 <= y) && (y <= 10) && (f <= 10);
			
			using namespace std::chrono;
			high_resolution_clock::time_point t1 = high_resolution_clock::now();
			optional<Box> result = Minimize(f, c, delta);
			high_resolution_clock::time_point t2 = high_resolution_clock::now();
			std::chrono::duration<double, std::milli> execTime = t2 - t1;
			
			if (result) {
				cout << f << "\nMinimum Point:\n" << *result << endl;
				cout << "\nThis took : " << execTime.count() << " ms to find min." << endl;
			} else {
				cout << f << "what??" << endl;
			}
			return (execTime.count());
		}
	}  // namespace
}  // namespace dreal

int main() {
	std::vector<double> execTimes;
	for(int i = 0; i < 1000; i++) {
//		dreal::sat_checker_main();
		execTimes.push_back(dreal::minimize_main());
//		dreal::sat_checker_2();
	}
	double ave = std::accumulate(execTimes.begin(), execTimes.end(), 0.0) / execTimes.size();
	std::cout << "\n\nOn average, it took " << ave << " ms" << std::endl;
}
