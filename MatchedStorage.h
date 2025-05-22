#pragma once
#include "Matcher.h"
#include <vector>
class MatchedStorage : protected Matcher
{
protected:
	vector<Matcher> matchedList;
};

