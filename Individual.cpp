#include "Individual.h"

Individual::Individual(int solutionSize)
{
	for (int i = 0; i < solutionSize; i++)
	{
		std::pair<int, bool> newPair(i, false);
		if (rand() % (1 + 1) == 1) newPair.second = true;
		solution.insert(newPair);
	}
}

Individual::Individual(const Individual& other)
{
	std::map<int, bool> solutionCopy(other.solution.begin(), other.solution.end());
	solution = solutionCopy;
}

Individual* Individual::crossover(Individual* otherParent)
{
	Individual* child = new Individual(*this);
	std::map<int, bool>::iterator i;
	for (i = solution.begin(); i != solution.end(); i++)
		if (rand() % (1 + 1) == 0) child->solution[i->first] = otherParent->solution[i->first];
	return child;
}

void Individual::mutation(double mutationPossibility)
{
	std::map<int, bool>::iterator i;
	for (i = solution.begin(); i != solution.end(); i++)
		if (((rand() % (HUNDRED + 1)) / HUNDRED) <= mutationPossibility)
		{
			if (solution[i->first]) solution[i->first] = false;
			else solution[i->first] = true;
		}
}

int Individual::fitness(Max3SatProblem* problem)
{
	return problem->compute(this);
}

int* Individual::getResultAsTable()
{
	int* solutionTable = new int[solution.size()];
	for (unsigned int i = 0; i < solution.size(); i++)
		solutionTable[i] = solution[i];
	return solutionTable;
}
