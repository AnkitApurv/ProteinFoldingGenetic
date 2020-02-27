#include "stdafx.h"

#include "node.h"

#pragma region nodeManagement
struct node* create_node(short int x, short int y, short int v)
{//allocate a node in the resultant sequence 

	struct node* newnode = (struct node*)malloc(sizeof(struct node));
	if (newnode == NULL)
	{
		printf_s("\nMemory was not allocated");
		return 0;
	}
	else
	{
		newnode->x = x;
		newnode->y = y;
		newnode->v = v;
		return newnode;
	}
}

void insert_node(short int x, short int y, short int v, node* newnode, node* first[], node* last[], short k)
{	//add a node
	newnode = create_node(x, y, v);
	if (first[k] == last[k] && last[k] == NULL)
	{
		first[k] = last[k] = newnode;
		first[k]->next = NULL;
		last[k]->next = NULL;
	}
	else
	{
		last[k]->next = newnode;
		last[k] = newnode;
		last[k]->next = NULL;
	}

}

void insert_nodefinal(short int x, short int y, short int v, node* newnode, node* tmpFirst[], node* tmpLast[], short l)
{	//keep the final best 2 nodes
	newnode = create_node(x, y, v);
	if (tmpFirst[l] == tmpLast[l] && tmpLast[l] == NULL)
	{
		tmpFirst[l] = tmpLast[l] = newnode;
		tmpFirst[l]->next = NULL;
		tmpLast[l]->next = NULL;
	}
	else
	{
		tmpLast[l]->next = newnode;
		tmpLast[l] = newnode;
		tmpLast[l]->next = NULL;
	}

}

struct EnergyVar* create_nodeE(short int x1, short int y1, short int x2, short int y2)
{//allocate a Energyvariation node in the resultant sequence 
	struct EnergyVar* newnodeE = (struct EnergyVar*)malloc(sizeof(struct EnergyVar));
	if (newnodeE == NULL)
	{
		printf_s("\nMemory was not allocated");
		return 0;
	}
	else
	{
		newnodeE->x1 = x1;
		newnodeE->y1 = y1;
		newnodeE->x2 = x2;
		newnodeE->y2 = y2;
		return newnodeE;
	}
}

void insert_nodeE(short int x1, short int y1, short int x2, short int y2, EnergyVar* newnodeE, EnergyVar* firstE[], EnergyVar* lastE[], short k)
{//
	newnodeE = create_nodeE(x1, y1, x2, y2);
	if (firstE[k] == lastE[k] && lastE[k] == NULL)
	{
		firstE[k] = lastE[k] = newnodeE;
		firstE[k]->next = NULL;
		lastE[k]->next = NULL;
	}
	else
	{
		lastE[k]->next = newnodeE;
		lastE[k] = newnodeE;
		lastE[k]->next = NULL;
	}

}

void insert_nodeEFinal(short int x1, short int y1, short int x2, short int y2, EnergyVar* newnodeE, EnergyVar* tmpFirstE[], EnergyVar* tmpLastE[], short l)
{
	newnodeE = create_nodeE(x1, y1, x2, y2);
	if (tmpFirstE[l] == tmpLastE[l] && tmpLastE[l] == NULL)
	{
		tmpFirstE[l] = tmpLastE[l] = newnodeE;
		tmpFirstE[l]->next = NULL;
		tmpLastE[l]->next = NULL;
	}
	else
	{
		tmpLastE[l]->next = newnodeE;
		tmpLastE[l] = newnodeE;
		tmpLastE[l]->next = NULL;
	}
}
#pragma endregion
