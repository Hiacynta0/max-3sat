#pragma once

#ifndef CLAUSE_H
#define CLAUSE_H

#include <cmath>
#include <vector>
#include <iostream>

using std::vector;

class Individual;
class Clause
{
public:
	Clause(vector<int> valuesList) { values = valuesList; };
	bool isTrue(Individual* newSolution);
	void print();
	vector<int> getValues() { return values; };

private:
	vector<int> values;
};
#endif