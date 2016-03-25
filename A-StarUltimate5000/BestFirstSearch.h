#pragma once
#include "Node.h"

namespace DHAlgos {

	class BestFirstSearch
	{
	public:
		BestFirstSearch(Node *start);
		~BestFirstSearch();

		Node *search();
		const std::vector<Node *> &getDebugData();

	private:
		std::vector<Node *> OPEN;
		std::vector<Node *> CLOSE;

		std::vector<Node *> debug;

		void findDoubleInClose(Node *in);
		void insertIntoOpen(Node *in);
	};

}

