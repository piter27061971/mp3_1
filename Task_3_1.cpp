#include <iostream>
#include <vector>
#include <random>
#include<future>
#include<algorithm>

void sortingByChoice(std::vector<int>& vec)
{
	
	auto n = vec.size();

	for (int i = 0; i < n - 1; i++)
	{
		int minElement = vec[i];

		for (int j = i + 1; j < n; j++)
		{
			if ((vec[j] < minElement) && (minElement != vec[j]))
			{
				minElement = vec[j];
				std::swap(vec[i], vec[j]);
			}
		}
	}
};

void printVec(const std::vector<int>& vec)
{
	for (const auto& i : vec)
	{
		std::cout << i << " ";
	}
	std::cout << "\n";
}

void findMinProm(const std::vector<int> vec, int i, const int vecSize, std::promise<int> prom)
{
		int minIndex = i;

		for (int j = i + 1; j < vecSize; j++)
		{
			if (vec[j] < vec[minIndex])
			{
				minIndex = j;
			}
		}
		prom.set_value(minIndex);
};


int main()
{
	std::vector<int> vec{ 6,2,3,5,9,4,1,8,7 };
	
	int vecSize = vec.size();
	
	std::cout << "Before sorting: ";
	printVec(std::ref(vec));

	for (int i = 0; i < vecSize - 1; i++)
	{
		std::promise<int> prom;
		std::future<int> future_res = prom.get_future();

		auto asyncFindMin = std::async(std::launch::async, findMinProm, vec, i, vecSize, std::move(prom));

		int minIndex = future_res.get();
		if (vec[i] != vec[minIndex])
		{
			std::swap(vec[i], vec[minIndex]);
		}
		
	}


	
	
	std::cout << "After sorting: ";
	printVec(std::ref(vec));
}