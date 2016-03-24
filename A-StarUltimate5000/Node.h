#pragma once
#include <vector>

namespace DHAlgos {

	class Node
	{
	public:
		Node(Node *parent);
		virtual ~Node();

		virtual float getHeuristic() = 0;
		virtual float getNodePrice() = 0;
		virtual float getTotalPrice() = 0;
		virtual bool operator==(const Node &other) const = 0;

		bool isDead() const;
		void kill();

		/* 
		* Attention Please!!
		* Please properly delete output vector to avoid memory leaks.
		*/
		std::vector<Node *> *getPathToStart() const;

	protected:
		Node *parent;
		std::vector<Node *> kids;

	private:
		bool dead;

		virtual void generateKids() = 0;
	};

}
