#pragma once

#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#define HUNDRED 100

#include <map>
#include "Max3SatProblem.h"

class Individual
{
public:
	Individual(int solutionSize);
	Individual(const Individual& other);
	Individual* crossover(Individual* otherParent);
	void mutation(double mutationPossibility);
	int fitness(Max3SatProblem* problem);
	std::map<int, bool> getSolution() { return solution; };
	int* getResultAsTable();

private:
	std::map<int, bool> solution;
};
#endif