#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>
#include <chrono>

#include "dreal/dreal.h"

#include "TestFunction.hpp"
#include "TestFunction.cpp"
#include "LeviN13.hpp"
#include "LeviN13.cpp"

namespace dreal {
	namespace {
		
		using std::cout;
		using std::endl;
		using namespace std::chrono;
		using std::vector;
		
		double minimize_main() {
			const double delta = 0.001;
			const Variable x{"x"};
			const Variable y{"y"};
			
			const TestFunction& tf = LeviN13();
			const Expression f = tf.getFunction(x,y);
			const Formula c = tf.getConstraint(x,y,10);
			
			high_resolution_clock::time_point t1 = high_resolution_clock::now();
			optional<Box> result = Minimize(f, c, delta);
			high_resolution_clock::time_point t2 = high_resolution_clock::now();
			std::chrono::duration<double, std::milli> execTime = t2 - t1;
			
			if (result) {
				
				cout << "Optimize: "<< f << "\nMinimum Point:\n" << *result << endl;
//				cout << "Domain: " << c << endl;
				cout << "\nThis took : " << execTime.count() << " ms to find min." << endl;
			} else {
				cout << f << "what??" << endl;
			}
			
			return 0;
		}
		
		void minimize_model(int numTests, int numRandomIter,const TestFunction& tf) {
			vector<double> execTimes1;
			const double delta = 0.001;
			const Variable x{"x"};
			const Variable y{"y"};
			
			const Expression f = tf.getFunction(x,y);
			const Formula c = tf.getConstraint(x,y);
			
			high_resolution_clock::time_point t1;
			high_resolution_clock::time_point t2;
			std::chrono::duration<double, std::milli> execTime;
			std::chrono::duration<double, std::milli> randomTime;
			std::chrono::duration<double, std::milli> solveTime;
			for(int i = 0; i < numTests; i++) {
				t1 = high_resolution_clock::now();
				optional<Box> result = Minimize(f, c, delta);
				t2 = high_resolution_clock::now();
				execTime = t2 - t1;
				execTimes1.push_back(execTime.count());
				
			}
			double ave1 = std::accumulate(execTimes1.begin(), execTimes1.end(), 0.0) / execTimes1.size();
		}
	}  // namespace
}  // namespace dreal

int main() {
	dreal::minimize_main();
}
