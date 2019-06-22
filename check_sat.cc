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
#include "HolderTable.hpp"
#include "HolderTable.cpp"
#include "Trefethen.hpp"
#include "Trefethen.cpp"
#include "MishraBird.hpp"
#include "MishraBird.cpp"

#include "Optimizer.hpp"
#include "Optimizer.cpp"
#include "Evolutionary.hpp"
#include "Evolutionary.cpp"
#include "Annealing.hpp"
#include "Annealing.cpp"

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
			
			const TestFunction& tf = Trefethen();
			const Expression f = tf.getFunction(x,y);
			const Formula c = tf.getConstraint(x,y,-3);
			
			optional<Box> result;
			high_resolution_clock::time_point t1 = high_resolution_clock::now();
			result = Minimize(f, c, delta);
			high_resolution_clock::time_point t2 = high_resolution_clock::now();
			std::chrono::duration<double, std::milli> execTime = t2 - t1;
			
			cout << "Region:" << c << endl;
			if (result) {
				cout << "Optimize: "<< tf << "\nMinimum Point:\n" << *result << endl;
				cout << "\nThis took : " << execTime.count() << " ms to find min." << endl << endl;
			} else {
				cout << "No minimum found: what??\n" << f << endl;
			}
			
			return 0;
		}
		
		void test_random(int numRandomIter, TestFunction tf, const Optimizer& opt){
			high_resolution_clock::time_point t1;
			high_resolution_clock::time_point t2;
			std::chrono::duration<double, std::milli> execTime;
			
			t1 = high_resolution_clock::now();
			double approx_min = opt.optimize(tf, numRandomIter);
			t2 = high_resolution_clock::now();
			execTime = t2 - t1;
			
			cout << "Test Function: " << tf << endl;
			cout << "Using: " << opt << ", " << numRandomIter << " rounds." << endl;
			cout << "Random approx of min:" << approx_min << endl;
			cout << "Time it took: " << execTime.count() << " (ms)" << endl << endl << endl;
		}
		
		void proof_repeat(int numTests, int numRandomIter,const TestFunction& tf, const Optimizer& opt){
			high_resolution_clock::time_point t1;
			high_resolution_clock::time_point t2;
			std::chrono::duration<double, std::milli> time;
			
			double approx_min;
			double average = 0;
			double average2 = 0;
			const double delta = 0.001;
			for(int i = 0; i < numTests; i++) {
				const Variable x{"x"};
				const Variable y{"y"};
				const Expression f = tf.getFunction(x,y);
				
				const Formula cstr = tf.getConstraint(x,y);
				optional<Box> result2;
				t1 = high_resolution_clock::now();
				result2 = Minimize(f, cstr, delta);
				t2 = high_resolution_clock::now();
				time = t2 - t1;
				average2 = (average2*(((double) i)/((double) i + 1)) + (time.count()/((double) i + 1)));
				
				Formula c;
				optional<Box> result;
				
				t1 = high_resolution_clock::now();
				while(true) {
					approx_min = opt.optimize(tf, numRandomIter);
					c = (tf.getConstraint(x,y) && (f < (approx_min-(delta)))); //strengthen
					result = CheckSatisfiability(c, delta);
					if(result) {
						
					} else {
						break;
					}
				}
				t2 = high_resolution_clock::now();
				time = t2 - t1;
				
				average = (average*(((double) i)/((double) i + 1)) + (time.count()/((double) i + 1)));
			}
			
			cout << "Test Function: " << tf << ", " << numTests << " experiments." << endl;
			cout << "Direct Solve: " << average2 << " (ms)." << endl;
			cout << "Estimation Method: " << opt << endl;
			cout << "Random search & Prove: " << average << " (ms)" << endl;
			cout << "Speedup: " << (average2 / (average)) << endl;
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl<< endl<< endl;
			
			
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
				
				const Formula cReduced = tf.getConstraint(x,y,(estimateMin + (delta)));
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
			cout << "Estimation Method: " << opt << ", " << numRandomIter << " rounds." << endl;
			cout << "Time to Estimate Min: " << aveOpt << " (ms)." << endl;
			cout << "Estimate-Assisted Solve: " << aveRed << " (ms)." << endl;
			cout << "Total Assisted Solve: " << (aveRed + aveOpt) << " (ms)." << endl;
			cout << "Speedup: " << (ave / (aveRed + aveOpt)) << endl;
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl<< endl<< endl;
		}
	}  // namespace
}  // namespace dreal

int main() {
	std::cout << "Running Experiments..." << std::endl << std::endl << std::endl;
	srand (time(NULL));
	
	std::cout << "Technique: approximation-assisted minimization" << std::endl;
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	dreal::compare_on_model(100, 4000, dreal::LeviN13(), dreal::Annealing());
	dreal::compare_on_model(100, 4000, dreal::Booth(), dreal::Annealing());
	dreal::compare_on_model(3, 4000, dreal::HolderTable(), dreal::Annealing()); //this takes 30 sec.
	dreal::compare_on_model(30, 4000, dreal::Trefethen(), dreal::Annealing());
	dreal::compare_on_model(30, 4000, dreal::MishraBird(), dreal::Annealing());
	
	std::cout << "Technique: keep estimating until it can be proven to be minimum." << std::endl;
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	dreal::proof_repeat(30,4000, dreal::Trefethen(),dreal::Annealing());
	dreal::proof_repeat(30,4000, dreal::MishraBird(),dreal::Annealing());
	dreal::proof_repeat(3,4000, dreal::HolderTable(),dreal::Annealing());
	return 0;
}
