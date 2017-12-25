#pragma once

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <list>
#include <stdint.h>
using namespace std;

//Vehicle parameters
#define FRONTWHEELANGLELIMIT 25.0
#define MAXSTEERINGANGLE 600
#define WHEELBASE 2.65
#define MAX_VECTOR_SIZE 2000
const double kVehicleWidth = 1.8;
const double kVehicleLength = 4;

//lcm message lost
#define MESSAGELOST_COUNTER 10
#define MESSAGELOST_RATIO 0.3

template<typename T>
vector<T> Filter(list<T> source_data, T threshold)
{
	int i = 0, j = 0;
	int array_number = 0, current_number = 0;
	int max_no = 0, max_array = 0;
	float last_float = 0;
	list<T>::iterator ifloat;
	vector<T> return_data;
	return_data.clear();

	if (source_data.empty())
	{
		return return_data;
	}
	else if (source_data.size() < 2)
	{
		for (ifloat = source_data.begin(); ifloat != source_data.end(); ++ifloat)
		{
			return_data.push_back(*ifloat);
		}
		return return_data;
	}

	int iL = source_data.size() + 1;
	vector<vector<T> > vector_array(iL);
	ifloat = source_data.begin();
	last_float = *ifloat;
	source_data.pop_front();
	vector_array[current_number].push_back(last_float);
	array_number++;

	for (ifloat = source_data.begin(); ifloat != source_data.end(); ++ifloat)
	{
		if (fabs(*ifloat - last_float) > threshold)
		{
			for (j = 0; j < array_number; j++)
			{
				if (fabs(*ifloat - vector_array[j].back()) <= threshold)
				{
					vector_array[j].push_back(*ifloat);
					current_number = j;
					break;
				}
			}
			if (j == array_number)
			{
				array_number++;
				current_number = array_number - 1;
				vector_array[current_number].push_back(*ifloat);
			}
		}
		else
		{
			vector_array[current_number].push_back(*ifloat);
		}
		last_float = *ifloat;
	}

	for (i = 0; i < array_number; i++)
	{
		if (vector_array[i].size() > max_no)
		{
			max_no = vector_array[i].size();
			max_array = i;
		}
	}
	return_data = vector_array[max_array];
	return return_data;
}

template<typename T>
vector<T> Filter(vector<T> source_data, T threshold)
{
	if (source_data.empty())
	{
		return source_data;
	}
	else if (source_data.size() < 2)
	{
		return source_data;
	}

	int i = 0, j = 0;
	int array_number = 0, current_number = 0;
	vector<T> return_data;
	vector<T> vector_array[source_data.size() + 1];
	//vector<T> vector_array[100];
	array_number++;
	vector_array[current_number].push_back(source_data.at(0));

	//  Allocate the source data
	for (i = 1; i < source_data.size(); i++)
	{
		if (fabs(source_data.at(i) - source_data.at(i - 1)) > threshold)
		{
			for (j = 0; j < array_number; j++)
			{
				if (fabs(source_data.at(i) - vector_array[j].back()) <= threshold)
				{
					vector_array[j].push_back(source_data.at(i));
					current_number = j;
					break;
				}
			}
			if (j == array_number)
			{
				array_number++;
				current_number = array_number - 1;
				vector_array[current_number].push_back(source_data.at(i));
			}
		}
		else
		{
			vector_array[current_number].push_back(source_data.at(i));
		}
	}

	int max_no = 0, max_array = 0;
	for (i = 0; i < array_number; i++)
	{
		if (vector_array[i].size() > max_no)
		{
			max_no = vector_array[i].size();
			max_array = i;
		}
	}
	return_data = vector_array[max_array];
	return return_data;
}

template<typename T>
T GetMin(T x1, T x2)
{
	return x1 < x2 ? x1 : x2;
}

template<typename T>
T GetMax(T x1, T x2)
{
	return x1 > x2 ? x1 : x2;
}