// inf.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>    // std::sort
#include <tuple>
#include <iomanip>		// std:setprecision
#include <limits>		// std::numeric_limits.
using namespace std;

std::tuple<double, int, int> CalcMedian(vector<double> &data)
{
	size_t size = data.size();
  
	if (size == 0)
	{
		return std::make_tuple(-1, 0, 0);		// error
	}
	else
	{
		sort(data.begin(), data.end());
		if (size % 1 == 0)
		{
			double median = (data[size / 2 - 1] + data[size / 2]) / 2.0;
			return std::make_tuple(median, (size / 2 - 1), (size / 2));
		}
		else 
		{
			double median = data[size / 2];
			return std::make_tuple(median, (size / 2 - 1), -1);
		}
	}
}

void process(string file)
{
	try 
	{
		string line;
		ifstream myfile (file);
		if (myfile.is_open())
		{
			while (getline(myfile, line) )
			{
				// Tokenizing with delimiter space ' ' 
				string t;
				stringstream check(line); 
				vector <double> tokens; 
				while(getline(check, t, ' ')) 
				{
					double value = stof(t);
					if((value < -70.0) || (value > 2080000000.0))
						throw "Value out of range!";
					tokens.push_back(value); 
				}

				auto median = CalcMedian(tokens);
				if(std::get<0>(median) < 0)
				{
					throw "No data found";
				}

				cout << "MEDIAN=" << setprecision (3) << std::get<0>(median) << endl;
		
				for(unsigned int i = 0; i < tokens.size(); i++) 
				{
					string used = ((i == std::get<1>(median)) || (i == std::get<2>(median)))? " *used* " : "";
					cout << tokens[i] << used << endl;
				}
			}
			myfile.close();
		}
		else
		{
			throw "Unable to open file"; 
		}
	} 
	catch (const char* msg) 
	{
		cerr << msg << endl;
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	if(argc < 2)
	{
		cout << "Provide input files!"<< endl;
		exit(0);
	}

	for(int i = 1; i < argc; i++)
	{
	    string f = argv[i]; 
		cout << "==============================\nProcessing file " << f << endl;
		process(f);
		
	}

	cout << "Finished."<< endl;

	return 0;
}

