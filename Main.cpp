#include "Optimizer.h"

int main()
{
	Max3SatProblem problem1;
	problem1.load("D:/Studia/Semestr3/TEP/max3sat/50/m3s_50_0.txt");
	std::cout << "clauses number: " << problem1.getClausesNumber() << std::endl;
	std::cout << "variables: " << problem1.getVariablesNumber() << std::endl;
	Optimizer optimizer1(20, 0.5, 0.3, &problem1);
	for (int i = 0; i < 100; i++)
	{
		optimizer1.runIteration();
		std::cout << optimizer1.bestSolution() << std::endl;
	}
	std::cout << std::endl;

	Max3SatProblem problem2;
	problem2.load("D:/Studia/Semestr3/TEP/max3sat/50/m3s_50_1.txt");
	std::cout << "clauses number: " << problem2.getClausesNumber() << std::endl;
	std::cout << "variables: " << problem2.getVariablesNumber() << std::endl;;
	Optimizer optimizer2(100, 0.6, 0.2, &problem2);
	for (int j = 0; j < 20; j++)
	{
		optimizer2.runIteration();
		std::cout << optimizer2.bestSolution() << std::endl;
	}
}