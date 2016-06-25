#ifndef UTIL_H
#define UTIL_H

#include <random>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <functional>

using namespace std;

namespace Util
{	
	void read_file(string filename, function<void(string)> callback)
	{
		ifstream reader (filename.c_str());
		if(!reader.is_open())
		{
			//lancar exception
			cout << "Arquivo não encontrado." << endl;
			return;
		}

		while(!reader.eof())
		{
			string line;
			//reader >> line; // get word by word
			getline(reader, line); //get line			
			callback(line);
		}

		reader.close();
	}
	
	int random(const int min, const int max) //min[included] max[included]
	{
		random_device rd;     // only used once to initialise (seed) engine
		mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
		uniform_int_distribution<int> uni(min, max); // guaranteed unbiased
	
		return uni(rng);
	}
	
	int prime(int v)
	{
		return 33809;
	}
	
	int ctoi(char c)
	{
		return c - '0';
	}
	
	string clean_up(string str)
	{
		string result = "";
		for(auto c : str)
		{
			if(c >= 'a' && c <= 'z')
				result += c;
			else if(c >= 'A' && c <= 'Z')
				result += (c + 'a' - 'A');
		}
		return result;
	}
	
	vector<string> split_on_separators(string str, string separators)
	{
		vector<string> divided;
		int i = 0, count = 0;
		for(auto c : str)
		{
			if(separators.find(c) != string::npos)
			{
				if(count > 0)
					divided.push_back(str.substr(i, count));
				
				i += count + 1;
				count = 0;
			}	
			else ++count;
		}
		
		if(i < str.size())
			divided.push_back(str.substr(i, count));
		
		return divided;
	}
}

#endif