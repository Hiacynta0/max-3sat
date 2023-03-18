#include "Max3SatProblem.h"

Max3SatProblem::~Max3SatProblem()
{
	for (int i = 0; i < clausesList.size(); i++)
		delete clausesList.at(i);
}

void Max3SatProblem::load(string filePath)
{
	string text;
	std::ifstream readFile(filePath);
	if (readFile.is_open()) 
	{
		int highestVariable = 0;
		while (readFile)
		{
			std::getline(readFile, text);
			if(!text.empty())
			{ 
				text.erase(0, SPACE_BEFORE_VARIABLES);
				text.erase(text.size() - SPACE_BEHIND_VARIABLES, SPACE_BEHIND_VARIABLES);
				int start = 0, end, value;
				vector<int> values;
				while ((end = text.find(SPACES_SEPARATING_VARIABLES, start)) != string::npos)
				{
					value = stoi(text.substr(start, end - start));
					start = end + SPACE_BETWEEN_VARIABLES;
					values.push_back(value);
					if (abs(value) > highestVariable) highestVariable = abs(value);
				}
				values.push_back(stoi(text.substr(start)));
				if (abs(values.back()) > highestVariable) highestVariable = abs(values.back());
				if (values.size() == VARIABLES_IN_CLAUSE_NUMBER)
					clausesList.push_back(new Clause(values));
			}
		}
		variablesNumber = highestVariable + 1;
	}
	readFile.close(); 
}

int Max3SatProblem::compute(Individual* newSolution)
{
	int trueClauses = 0;
	for (unsigned int i = 0; i < clausesList.size(); i++)
	{
		if (clausesList.at(i)->isTrue(newSolution)) trueClauses++;
	}
	return trueClauses;
}