#include "BestFirstSearch.h"
#include <algorithm>

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

		findDoubleInClose(working);
		
		working->generateKids();
		for (uint32 i = 0; i < working->kids.size(); ++i) {
			insertIntoOpen(working->kids[i]);
		}

		std::sort(OPEN.begin(), OPEN.end(), Node::compare);
	}

	return nullptr;
}

const std::vector<Node *> &BestFirstSearch::getDebugData()
{
	return CLOSE;
}

void BestFirstSearch::findDoubleInClose(Node *in)
{
	in->kill();
	for (uint32 i = 0; i < CLOSE.size(); ++i) {
		if (in == CLOSE[i]) {
			if (in->getTotalPrice() < CLOSE[i]->getTotalPrice()) {
				CLOSE[i] = in;
				return;
			}
		}
	}

	CLOSE.push_back(in);
}

void BestFirstSearch::insertIntoOpen(Node *in) {
	for (uint32 i = 0; i < OPEN.size(); ++i) {
		if (in == OPEN[i]) {
			if (in->getTotalPrice() < OPEN[i]->getTotalPrice()) {
				OPEN[i] = in;
				return;
			}
		}
	}

	OPEN.push_back(in);
}
