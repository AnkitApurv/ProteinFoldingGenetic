#include "stdafx.h"

class Node {
private:
	Node() {}
public:
	//functionality of 'create_node' and 'create_nodeE' functions
	Node(short int x, short int y, short int v, short int x1, short int x2, short int y1, short int y2) {
		struct coordinates Coordinates;
		struct energy Energy;

		Coordinates.x = x;
		Coordinates.y = y;
		Coordinates.v = v;

		Energy.x1 = x1;
		Energy.x2 = x2;
		Energy.y1 = y1;
		Energy.y2 = y2;
	}
	~Node() {}

protected:
	struct coordinates {
		short int x, y, v, index;
		char nxtMov;
		struct node* next;
	};
	struct energy {
		short int x1, x2, y1, y2;
		struct EnergyVar* next;
	};
};