#pragma once
#include <vector>

namespace DHAlgos {

	class Node
	{
	public:
		Node(Node *parent);
		virtual ~Node();
		virtual void deleteKids();

		virtual float getHeuristic() = 0;
		virtual float getNodePrice() = 0;
		virtual float getTotalPrice() = 0;

		bool isDead() const;
		void kill();

		virtual bool isIt() const = 0;

		/* 
		* Attention Please!!
		* Make sure to properly delete output vector to avoid memory leaks.
		*/
		std::vector<Node *> *getPathToStart() const;

		std::vector<Node *> kids;
		virtual void generateKids() = 0;

	protected:
		Node *parent;

	private:
		bool dead;
	};

	class Helper {
	public:
		static bool comparator(Node *a, Node *b);
		static bool same(const Node *a, const Node *b);
	};
}
