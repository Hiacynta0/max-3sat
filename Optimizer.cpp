#include "Optimizer.h"

Optimizer::Optimizer(int population, double crossing, double mutation, Max3SatProblem* max3SatProblem)
{
	populationSize = population;
	crossingPossibility = crossing;
	mutationPossibility = mutation;
	problem = max3SatProblem;
	initialize();
}

Optimizer::~Optimizer()
{
	for (int i = 0; i < currentPopulation.size(); i++)
		if (currentPopulation.at(i) != bestFoundSolution)
			delete currentPopulation.at(i);
	if (bestFoundSolution != NULL)
		delete bestFoundSolution;
}

void Optimizer::initialize()
{
	if (problem->ready())
	{
		for (int i = currentPopulation.size(); i < populationSize; i++)
			currentPopulation.push_back(new Individual(problem->getVariablesNumber()));
		bestFoundSolution = currentPopulation.at(0);
	}
}

void Optimizer::runIteration()
{
	if (problem->ready())
	{
		vector<Individual*> newPopulation;
		while (newPopulation.size() < currentPopulation.size())
		{
			Individual* parent1 = chooseParent();
			Individual* parent2 = chooseParent();
			Individual* child1;
			Individual* child2;
			if (((rand() % (HUNDRED + 1)) / HUNDRED) <= crossingPossibility)
			{
				child1 = parent1->crossover(parent2);
				child2 = parent1->crossover(parent2);
			}
			else
			{
				child1 = new Individual(*parent1);
				child2 = new Individual(*parent2);
			}
			child1->mutation(mutationPossibility);
			child2->mutation(mutationPossibility);
			newPopulation.push_back(child1);
			newPopulation.push_back(child2);
			if (child1->fitness(problem) > bestFoundSolution->fitness(problem) || child2->fitness(problem) > bestFoundSolution->fitness(problem))
				if (std::find(newPopulation.begin(), newPopulation.end(), bestFoundSolution) == newPopulation.end())
					if (std::find(currentPopulation.begin(), currentPopulation.end(), bestFoundSolution) == currentPopulation.end())
					{ 
						delete bestFoundSolution;
						if (child1->fitness(problem) > child2->fitness(problem)) bestFoundSolution = child1;
						else bestFoundSolution = child2;
					}
		}
		//modyfikacja
		for (int j = 0; j < newPopulation.size(); j++)
		{
			int clauseIndex = rand() % (problem->getClausesNumber());
			if (!problem->getClause(clauseIndex)->isTrue(newPopulation.at(j)))
				for (int k = 0; k < VARIABLES_IN_CLAUSE_NUMBER; k++)
				{
					int value = problem->getClause(clauseIndex)->getValues().at(k);
					if (newPopulation.at(j)->getSolution().at(abs(value)))
					{
						if (value > 0) newPopulation.at(j)->getSolution().at(abs(value)) = false;
						else newPopulation.at(j)->getSolution().at(abs(value)) = true;
					}
					else
					{
						if (value > 0) newPopulation.at(j)->getSolution().at(abs(value)) = true;
						else newPopulation.at(j)->getSolution().at(abs(value)) = false;
					}
				}	
		}//koniec modyfikacji
		for (int i = 0; i < currentPopulation.size(); i++)
			if (std::find(newPopulation.begin(), newPopulation.end(), currentPopulation.at(i)) == newPopulation.end())
				if (currentPopulation.at(i) != bestFoundSolution)
					delete currentPopulation.at(i);
		currentPopulation = newPopulation;
	}
}

Individual* Optimizer::chooseParent()
{
	Individual* potentialParent1 = currentPopulation.at(rand() % populationSize);
	Individual* potentialParent2 = currentPopulation.at(rand() % populationSize);
	if (potentialParent1->fitness(problem) < potentialParent2->fitness(problem)) return potentialParent2;
	return potentialParent1;
}