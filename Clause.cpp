#include "Clause.h"
#include "Individual.h"

bool Clause::isTrue(Individual* newSolution)
{
	for (unsigned int i = 0; i < values.size(); i++)
	{
		if((newSolution->getSolution())[abs(values.at(i))] && values.at(i) >= 0) return true;
		if(!((newSolution->getSolution())[abs(values.at(i))]) && values.at(i) < 0) return true;
	}
	return false;
};

void Clause::print()
{
	for (unsigned int i = 0; i < values.size(); i++)
		std::cout << values.at(i) << " ";
}