#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>
#include <chrono>
#include <stdlib.h>

#include "dreal/dreal.h"

#include "TestFunction.hpp"
#include "TestFunction.cpp"
#include "LeviN13.hpp"
#include "LeviN13.cpp"
#include "Booth.hpp"
#include "Booth.cpp"

#include "Optimizer.hpp"
#include "Optimizer.cpp"

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
			const Formula c = tf.getConstraint(x,y,0.286);
			
			high_resolution_clock::time_point t1 = high_resolution_clock::now();
			optional<Box> result = Minimize(f, c, delta);
			high_resolution_clock::time_point t2 = high_resolution_clock::now();
			std::chrono::duration<double, std::milli> execTime = t2 - t1;
			
			if (result) {
				
				cout << "Optimize: "<< tf << "\nMinimum Point:\n" << *result << endl;
//				cout << "Domain: " << c << endl;
				cout << "\nThis took : " << execTime.count() << " ms to find min." << endl << endl;
			} else {
				cout << f << "what??" << endl;
			}
			
			return 0;
		}
		
		void test_random(int numRandomIter,const TestFunction& tf, const Optimizer& opt){
			high_resolution_clock::time_point t1;
			high_resolution_clock::time_point t2;
			std::chrono::duration<double, std::milli> execTime;
			
			t1 = high_resolution_clock::now();
			double approx_min = opt.optimize(tf, numRandomIter);
			t2 = high_resolution_clock::now();
			execTime = t2 - t1;
			
			cout << "Using: " << opt << endl;
			cout << "Random approx of min:" << approx_min << endl;
			cout << "Time it took: " << execTime.count() << endl << endl << endl;
		}
		
		void compare_on_model(int numTests, int numRandomIter,const TestFunction& tf, const Optimizer& opt) {
			vector<double> execTimes;
			vector<double> optTimes;
			vector<double> reducedTimes;
			high_resolution_clock::time_point t1;
			high_resolution_clock::time_point t2;
			high_resolution_clock::time_point o1;
			high_resolution_clock::time_point o2;
			high_resolution_clock::time_point r1;
			high_resolution_clock::time_point r2;
			std::chrono::duration<double, std::milli> execTime;
			std::chrono::duration<double, std::milli> optTime;
			std::chrono::duration<double, std::milli> reducedTime;
			
			const double delta = 0.001;
			optional<Box> result1;
			optional<Box> result2;
			double estimateMin;
			for(int i = 0; i < numTests; i++) {
				const Variable x{"x"};
				const Variable y{"y"};
				const Expression f = tf.getFunction(x,y);
				const Formula c = tf.getConstraint(x,y);
				t1 = high_resolution_clock::now();
				result1 = Minimize(f, c, delta);
				t2 = high_resolution_clock::now();
				
				o1 = high_resolution_clock::now();
				estimateMin = opt.optimize(tf, numRandomIter);
				o2 = high_resolution_clock::now();
				
				const Formula cReduced = tf.getConstraint(x,y,estimateMin);
				r1 = high_resolution_clock::now();
				result2 = Minimize(f, cReduced, delta);
				r2 = high_resolution_clock::now();
				
				execTime = t2 - t1;
				optTime = o2 - o1;
				reducedTime = r2 - r1;
				execTimes.push_back(execTime.count());
				optTimes.push_back(optTime.count());
				reducedTimes.push_back(reducedTime.count());
				
				if (result1) {
					;
				}else {
					cout << "Initial Opt failed. Test function: " << tf << ", Optimizer: " << opt << endl;
					cout << "Test Round: " << i <<endl;
					std::exit(1);
					break;
				}
				if (result2) {
					;
				} else {
					cout << "Second Opt failed. Test function: " << tf << ", Optimizer: " << opt << endl;
					cout << "Test Round: " << i << " with random value" << estimateMin <<endl;
					std::exit(1);
					break;
				}
			}
			double ave = std::accumulate(execTimes.begin(), execTimes.end(), 0.0) / execTimes.size();
			double aveOpt = std::accumulate(optTimes.begin(), optTimes.end(), 0.0) / optTimes.size();
			double aveRed = std::accumulate(reducedTimes.begin(), reducedTimes.end(), 0.0) / reducedTimes.size();
			
			cout << "Test Function: " << tf << ", " << numTests << " experiments." << endl;
			cout << "Direct Solve: " << ave << " (ms)." << endl;
			cout << "Estimation Method: " << opt << endl;
			cout << "Time to Estimate Min: " << aveOpt << " (ms)." << endl;
			cout << "Estimate-Assisted Solve: " << aveRed << " (ms)." << endl;
			cout << "Total Assisted Solve: " << (aveRed + aveOpt) << " (ms)." << endl;
			cout << "Speedup: " << (ave / (aveRed + aveOpt)) << endl;
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		}
	}  // namespace
}  // namespace dreal

int main() {
	std::cout << "Running Experiments..." << std::endl << std::endl << std::endl;
	srand (time(NULL));
//	dreal::minimize_main();
//	dreal::test_random(100000, dreal::Booth(), dreal::Optimizer());
	
//	dreal::compare_on_model(300, 1000, dreal::LeviN13(), dreal::Optimizer());
	dreal::compare_on_model(100, 100000, dreal::Booth(), dreal::Optimizer());
	
	return 0;
}
