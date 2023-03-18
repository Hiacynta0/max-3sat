#pragma once

#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#define HUNDRED 100

#include "Max3SatProblem.h"
#include "Clause.h"
#include "Individual.h"

using std::vector;
using std::string;

class Optimizer
{
public:
	Optimizer(int population, double crossing, double mutation, Max3SatProblem* problem);
	~Optimizer();
	void runIteration();
	double bestSolution() { return double(bestFoundSolution->fitness(problem)) / problem->getClausesNumber(); };

private:
	void initialize();
	Individual* chooseParent();

	vector<Individual*> currentPopulation;
	int populationSize;
	double crossingPossibility;
	double mutationPossibility;
	Max3SatProblem* problem;
	Individual* bestFoundSolution;
};
#endif