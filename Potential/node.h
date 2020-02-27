//structure for storing the resultant sequence
struct node {

	short int x;
	short int y;
	short int v;
	short int index;
	char nxtMov;
	struct node* next;

};
//struct node* newnode, * ptr, * temp;
//struct node* first[populationSize], * last[populationSize], * tmpFirst[4], * tmpLast[4];

//Structure holding theenergy variation coordinates value of each sequence formed, used in graphics for coordinates
struct EnergyVar
{

	short int x1, x2, y1, y2;
	struct EnergyVar* next;
};
//struct EnergyVar* newnodeE, * ptrE, * tempE;
//struct EnergyVar* firstE[populationSize], * lastE[populationSize], * tmpFirstE[4], * tmpLastE[4];

const int populationSize = 20;
//Structure holding the energy variation value of each sequence formed
struct Energy_
{
	int i;
	double HEV;
	//double FEV;
};
//struct Energy_ Energy[populationSize], tmp, Efinal[4];

//functions' signatures
struct node* create_node(short int x, short int y, short int v);

void insert_node(short int x, short int y, short int v, node* newnode, node* first[], node* last[], short k);

void insert_nodefinal(short int x, short int y, short int v, node* newnode, node* tmpFirst[], node* tmpLast[], short l);

struct EnergyVar* create_nodeE(short int x1, short int y1, short int x2, short int y2);

void insert_nodeE(short int x1, short int y1, short int x2, short int y2, EnergyVar* newnodeE, EnergyVar* firstE[], EnergyVar* lastE[], short k);

void insert_nodeEFinal(short int x1, short int y1, short int x2, short int y2, EnergyVar* newnodeE, EnergyVar* tmpFirstE[], EnergyVar* tmpLastE[], short l);
