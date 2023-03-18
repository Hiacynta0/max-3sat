#pragma once

#ifndef MAX3SATPROBLEM_H
#define MAX3SATPROBLEM_H

#define VARIABLES_IN_CLAUSE_NUMBER 3
#define SPACE_BEFORE_VARIABLES 2
#define SPACE_BETWEEN_VARIABLES 2
#define SPACE_BEHIND_VARIABLES 3
#define SPACES_SEPARATING_VARIABLES "  "

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "Clause.h"

using std::vector;
using std::string;

class Individual;
class Max3SatProblem
{
public:
	~Max3SatProblem();
	void load(string filePath);
	int compute(Individual* newSolution);
	bool ready() { return clausesList.size() > 0; };
	int getVariablesNumber() { return variablesNumber; };
	int getClausesNumber() { return clausesList.size(); };
	Clause* getClause(int clauseIndex) { return clausesList.at(clauseIndex); };

private:
	vector<Clause*> clausesList;
	int variablesNumber;
};
#endif
