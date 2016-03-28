#include "BestFirstSearch.h"
#include <algorithm>
#include <functional>

using namespace DHAlgos;
typedef unsigned int uint32;

BestFirstSearch::BestFirstSearch(Node *start)
{
	OPEN.push_back(start);
}


BestFirstSearch::~BestFirstSearch()
{
}

Node *BestFirstSearch::search()
{
	while (!OPEN.empty()) {
		Node *working = OPEN.front();
		OPEN.erase(OPEN.begin());

		if (working->isIt()) {
			return working;
		}

		debug.push_back(working);

		findDoubleInClose(working);
		
		working->generateKids();
		for (uint32 i = 0; i < working->kids.size(); ++i) {
			if (working->kids[i]->isDead()) {
				continue;
			}

			insertIntoOpen(working->kids[i]);
		}

		std::sort(OPEN.begin(), OPEN.end(), DHAlgos::Helper::comparator);
	}

	return nullptr;
}

const std::vector<Node *> &BestFirstSearch::getDebugData()
{
	return debug;
}

void BestFirstSearch::findDoubleInClose(Node *in)
{
	in->kill();
	for (uint32 i = 0; i < CLOSE.size(); ++i) {
		if (Helper::same(in, CLOSE[i])) {
			if (in->getNodePrice() < CLOSE[i]->getNodePrice()) {
				CLOSE[i] = in;
			}
			return;
		}
	}

	CLOSE.push_back(in);
}

void BestFirstSearch::insertIntoOpen(Node *in) {
	for (uint32 i = 0; i < OPEN.size(); ++i) {
		if (Helper::same(in, OPEN[i])) {
			if (in->getNodePrice() < OPEN[i]->getNodePrice()) {
				OPEN[i] = in;
			}
			return;
		}
	}

	OPEN.push_back(in);
}
