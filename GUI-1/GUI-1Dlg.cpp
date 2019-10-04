
// GUI-1Dlg.cpp : implementation file

#pragma region headersMacroes

//project's headers
#include "stdafx.h"
#include "GUI-1.h"
#include "GUI-1Dlg.h"

//MFC header
#include "afxdialogex.h"

//standard library headers
#include<stdlib.h>
#include<math.h>
#include<windows.h>
#include<stdio.h>
#include<string.h>
#include<time.h>

//GLEW library header
#include <gl/glew.h>
//OpenGLUT library header
#include <openglut.h>



#ifdef _DEBUG
#define new DEBUG_NEW
#endif



//Macros section
#define pi 3.1415926
#define MAX 200
#define populationSize 20
#define ISEMPTY printf_s("\n Not a nice path\n");

#pragma endregion

#pragma region variables

double start=0.0, end=0.0, spent=0.0;

//Declaration Section
int moves=0;

int id1=0,choice=0;

//Variables used in graphics part for retrieving current height and width of the screen
int CurrentWidth=0,CurrentHeight=0,dif=0;

//fptrI: Input file pointer to read the string from the file "input.txt"
//fptrO: Output file pointer to read the string from the file "result.txt"

FILE *fptrO,*fptrOB,*fptrI;

//Current coordinates 
int row=0,col=0,x=0,y=0;

//str : input string
//res : printenergy variation on the screen

char res[MAX],val[4];

char str[MAX];

//other variables used in computation
short int k=0,l=0,maxRow=0,maxCol=0,minRow=0,minCol=0,cordinates[(2*MAX)][(4*MAX)];

char direction[(2*MAX)][(4*MAX)];


//structure for storing the resultant sequence
struct node {

	short int x;
	short int y;
	short int v;
	short int index;
	char nxtMov;
	struct node *next;

};
struct node *newnode, *ptr, *temp;
struct node *first[populationSize] , *last[populationSize], *tmpFirst[4], *tmpLast[4] ;


//Structure holding theenergy variation coordinates value of each sequence formed, used in graphics for coordinates
struct EnergyVar
{

	short int x1,x2,y1,y2;
	struct EnergyVar *next;
};
struct EnergyVar *newnodeE, *ptrE, *tempE;
struct EnergyVar *firstE[populationSize] , *lastE[populationSize],  *tmpFirstE[4], *tmpLastE[4];



//Structure holding theenergy variation value of each sequence formed
struct Energy_
{
	int i;
	double HEV;
	//double FEV;
}Energy[populationSize],tmp,Efinal[4];

#pragma endregion

#pragma region nodeManagement

struct node* create_node(short int x,short int y,short int v)
{//allocate a node in the resultant sequence 

	newnode = (struct node *)malloc(sizeof(struct node));
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


void insert_node(short int x,short int y,short int v)
{	//add a node
	newnode = create_node(x,y,v);
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


void insert_nodefinal(short int x,short int y,short int v)
{	//keep the final best 2 nodes
	newnode= create_node(x,y,v);
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



struct EnergyVar* create_nodeE(short int x1,short int y1,short int x2,short int y2)
{//allocate a Energyvariation node in the resultant sequence 
	newnodeE = (struct EnergyVar *)malloc(sizeof(struct EnergyVar));
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


void insert_nodeE(short int x1,short int y1,short int x2,short int y2)
{//
	newnodeE = create_nodeE(x1,y1,x2,y2);
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


void insert_nodeEFinal(short int x1,short int y1,short int x2,short int y2)
{
	newnodeE = create_nodeE(x1,y1,x2,y2);
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

#pragma region geneticAlgorithm

void result()
{	//Insert the resultant sequence
	//printf_s("%dth possibility\n",k+1);
	if (first[k] == NULL)
	{
		ISEMPTY;

	}
	else
	{	tmpLast[l]=tmpFirst[l]=NULL;
	tmpLastE[l]=tmpFirstE[l]=NULL;
	for (ptr = first[k];ptr != NULL;ptr = ptr->next)
	{    
		//      printf_s("(%d,%d) %c\t", ptr->x,ptr->y,ptr->nxtMov);
		insert_nodefinal(ptr->x,ptr->y,ptr->v);
		tmpLast[l]->nxtMov=ptr->nxtMov;
		tmpLast[l]->index=last[k]->index;
	}
	for (ptrE = firstE[k];ptrE != NULL;ptrE = ptrE->next)
	{    
		insert_nodeEFinal(ptrE->x1,ptrE->y1,ptrE->x2,ptrE->y2);
	}
	}
	//printf_s("\n");
}


void calculateEnergy()
{// calculateenergy variation

	short int i,j,e;
	firstE[k]=NULL;
	lastE[k]=NULL;

	for(i=minRow;i<=maxRow;i++)
	{
		for(j=minCol;j<=maxCol;j++)
		{//Check whether there exists a direct connection between two points.
			// If no direct connection exists in the current direction increment theenergy variation value by 1

			if(cordinates[i][j]==1)
			{
				//check for the horizontal connection
				if(moves==6)
					e=2;
				else
					e=1;
				if(cordinates[i][j+e]==0)
					if((direction[i][j]!='E' && direction[i][j+e]!='W')	)
					{
						Energy[k].HEV=Energy[k].HEV+4;
						//insert_nodeE(i-MAX+1,j-(2*MAX)+2, i-MAX+1,j+e-(2*MAX)+2);
					}

				//check for vertical connection
				if(cordinates[i+e][j]==0)
					if((direction[i][j]!='N' && direction[i+e][j]!='S')	)
					{
						Energy[k].HEV=Energy[k].HEV+4;
						//insert_nodeE(i-MAX+1,j-(2*MAX)+2, i+e-MAX+1,j-(2*MAX)+2);
					}


				//check for diagonal (south west and north east) connection

				e=1;
				if(cordinates[i+e][j+e]==0)
					if((direction[i][j]!='y' && direction[i+e][j+e]!='x')	)
					{
						Energy[k].HEV=Energy[k].HEV+4;
						//insert_nodeE(i-MAX+1,j-(2*MAX)+2, i+e-MAX+1,j+e-(2*MAX)+2);
					}


				//check for diagonal (north west and south east) connection
				if(cordinates[i+e][j-e]==0)
					if((direction[i][j]!='a' && direction[i+1][j-1]!='z')	)
					{
						Energy[k].HEV=Energy[k].HEV+4;
						//insert_nodeE(i-MAX+1,j-(2*MAX)+2, i+e-MAX+1,j-e-(2*MAX)+2);
					}
			}
			if(cordinates[i][j]==1)
			{
				//check for the horizontal connection
				if(moves==6)
					e=2;
				else
					e=1;
				if(cordinates[i][j+e]==1)
					if((direction[i][j]!='E' && direction[i][j+e]!='W')	)
					{
						Energy[k].HEV=Energy[k].HEV+2;
						
					}

				//check for vertical connection
				if(cordinates[i+e][j]==1)
					if((direction[i][j]!='N' && direction[i+e][j]!='S')	)
					{
						Energy[k].HEV=Energy[k].HEV+2;
						
					}


				//check for diagonal (south west and north east) connection

				e=1;
				if(cordinates[i+e][j+e]==1)
					if((direction[i][j]!='y' && direction[i+e][j+e]!='x')	)
					{
						Energy[k].HEV=Energy[k].HEV+2;
						
					}


				//check for diagonal (north west and south east) connection
				if(cordinates[i+e][j-e]==1)
					if((direction[i][j]!='a' && direction[i+1][j-1]!='z')	)
					{
						Energy[k].HEV=Energy[k].HEV+2;
						
					}
			}
			if(cordinates[i][j]==0)
			{
				//check for the horizontal connection
				if(moves==6)
					e=2;
				else
					e=1;
				if(cordinates[i][j+e]==0)
					if((direction[i][j]!='E' && direction[i][j+e]!='W')	)
					{
						Energy[k].HEV=Energy[k].HEV+2;
						
					}

				//check for vertical connection
				if(cordinates[i+e][j]==0)
					if((direction[i][j]!='N' && direction[i+e][j]!='S')	)
					{
						Energy[k].HEV=Energy[k].HEV+2;

					}


				//check for diagonal (south west and north east) connection

				e=1;
				if(cordinates[i+e][j+e]==0)
					if((direction[i][j]!='y' && direction[i+e][j+e]!='x')	)
					{
						Energy[k].HEV=Energy[k].HEV+2;

					}


				//check for diagonal (north west and south east) connection
				if(cordinates[i+e][j-e]==0)
					if((direction[i][j]!='a' && direction[i+1][j-1]!='z')	)
					{
						Energy[k].HEV=Energy[k].HEV+2;

					}
			}
			if(cordinates[i][j]==2)
			{
				//check for the horizontal connection
				if(moves==6)
					e=2;
				else
					e=1;
				if(cordinates[i][j+e]==3)
					if((direction[i][j]!='E' && direction[i][j+e]!='W')	)
					{
						Energy[k].HEV=Energy[k].HEV+1;

					}

				//check for vertical connection
				if(cordinates[i+e][j]==3)
					if((direction[i][j]!='N' && direction[i+e][j]!='S')	)
					{
						Energy[k].HEV=Energy[k].HEV+1;

					}


				//check for diagonal (south west and north east) connection

				e=1;
				if(cordinates[i+e][j+e]==3)
					if((direction[i][j]!='y' && direction[i+e][j+e]!='x')	)
					{
						Energy[k].HEV=Energy[k].HEV+1;

					}


				//check for diagonal (north west and south east) connection
				if(cordinates[i+e][j-e]==3)
					if((direction[i][j]!='a' && direction[i+1][j-1]!='z')	)
					{
						Energy[k].HEV=Energy[k].HEV+1;

					}
			}
			if(cordinates[i][j]==2)
			{
				//check for the horizontal connection
				if(moves==6)
					e=2;
				else
					e=1;
				if(cordinates[i][j+e]==2)
					if((direction[i][j]!='E' && direction[i][j+e]!='W')	)
					{
						Energy[k].HEV=Energy[k].HEV-1;

					}

				//check for vertical connection
				if(cordinates[i+e][j]==2)
					if((direction[i][j]!='N' && direction[i+e][j]!='S')	)
					{
						Energy[k].HEV=Energy[k].HEV-1;

					}


				//check for diagonal (south west and north east) connection

				e=1;
				if(cordinates[i+e][j+e]==2)
					if((direction[i][j]!='y' && direction[i+e][j+e]!='x')	)
					{
						Energy[k].HEV=Energy[k].HEV-1;

					}


				//check for diagonal (north west and south east) connection
				if(cordinates[i+e][j-e]==2)
					if((direction[i][j]!='a' && direction[i+1][j-1]!='z')	)
					{
						Energy[k].HEV=Energy[k].HEV-1;
						
					}
			}
			
		}
	}
}

int findMaxVariation(int size,struct Energy_ Energy[])
{//Find the maximumenergy variation and index among the resultant sequences


	short int i;
	int maxVar=0;
	for(i=1;i<size;i++)
		{
			if(Energy[maxVar].HEV<Energy[i].HEV)
				maxVar=i;
			Energy[i].i=i;
		}

	return maxVar;

}


void sortEnergySt()
{//Sort the HEV structure based on theenergy variation found. 
	//Function is executed so that the top 10 sequences are choosen and written into the output file


	int i,j;
		for(i=0;i<populationSize;i++)
			for(j=i+1;j<populationSize;j++)
			{//Sort the structure
				if(Energy[j+1].HEV<Energy[j].HEV)
				{
					tmp.i=Energy[j+1].i;
					tmp.HEV=Energy[j+1].HEV;
					//tmp.FEV=Energy[j+1].FEV;
					Energy[j+1].i=Energy[j].i;
					Energy[j+1].HEV=Energy[j].HEV;
					//Energy[j+1].FEV=Energy[j].FEV;
					Energy[j].HEV=tmp.HEV;
					//Energy[j].FEV=tmp.FEV;
					Energy[j].i=tmp.i;
				}
			}
	

	//Write the top 10 sequences to output file result.txt
	for(i=0;i<populationSize/4;i++)
	{
		if(Energy[i].HEV!=-1){
			for (ptr = first[Energy[i].i];ptr != NULL;ptr = ptr->next)
			{    


				fprintf_s(fptrO,"(%d,%d) %c\t~", ptr->x,ptr->y,ptr->nxtMov);

			}
			fprintf_s(fptrO,"%f %s",Energy[i].HEV,"||\n");
		}

	}

}

#pragma endregion

#pragma region procedures

void procedureTriangular()
{
	//Function for performing the fold


	short int i,j,row,col,trow,a,tcol,tx,ty,xIn,r,posMov[12],c;
	char nxtMov;
	short int cnt[12],flag[12];
	unsigned short int strIndex;
	k=0;
	while(k<populationSize)
	{
		first[k]=NULL;last[k]=NULL;


		//Initialization of coordinates and direction
		for(i=0;i<(2*MAX);i++)
			for(j=0;j<(4*MAX);j++)
			{
				cordinates[i][j]=-1;
				direction[i][j]='H';

			}



			//Initialization
			//startP oint = latticeCenter

			row=MAX-1;
			col=(2*MAX)-2;
			cordinates[row][col]=str[0]-'0';
			minCol=col;

			// PointsList:add(startPoint)
			insert_node(row-MAX+1,col-(2*MAX)+2,cordinates[row][col]);



			//secondP oint = eastNeighbour(startPoint)
			nxtMov='E';
			last[k]->nxtMov=nxtMov;
			last[k]->index=0;
			direction[row][col]=nxtMov;
			col=col+2;
			cordinates[row][col]=str[1]-'0';

			// PointsList:add(secondPoint)
			insert_node(row-MAX+1,col-(2*MAX)+2,cordinates[row][col]);
			last[k]->index=1;
			minRow=maxRow=row;
			maxCol=col;


			for(strIndex=2;strIndex  < strlen(str);strIndex++)
			{

				i=0;


				//Initialize the c value
				
					if(str[strIndex]=='1')
						c=1;
					if(str[strIndex]=='0')
						c=0;
					if(str[strIndex]=='2')
						c=2;
					if(str[strIndex]=='3')
						c=3;
					

				
				


				//For finding the possible moves from the current coordinates(row,col)
								
				
				for(i=0;i<moves;i++)
				{
					switch(i)
					{
					case 0://next move is to the east
						trow=row;
						tcol=col+2;	
						break;

					case 1://next move is to the west
						trow=row;
						tcol=col-2;		 	
						break;

					case 2: //next move is to the south west
						trow=row-1;//x
						tcol=col-1;
						break;

					case 3:	//next move is to the North east
						trow=row+1;//y
						tcol=col+1;
						break;

					case 4: //next move is to the South east
						trow=row-1;//z
						tcol=col+1;
						break;

					case 5:	//next move is to the North west
						trow=row+1;//a
						tcol=col-1;
						break;




					}


					cnt[i]=0;flag[i]=0;



					//find the suitable coordinate
					if(cordinates[trow][tcol]==-1 )
					{
						//If the coordinate is not occupied 
						for(tx=trow-1;tx<trow+2;tx++)		
							   {

								   if(tx!=trow)
									   for(ty=tcol-1;ty<tcol+2;ty++)
									   {
										   if(cordinates[tx][ty]==c)
											   cnt[i]++;
									   }


								   else
									   for(ty=tcol-2;ty<tcol+4;ty+=2)
									   {
										   if(cordinates[tx][ty]==c)
											   cnt[i]++;
									   }
							   }
						
						
					}
					else
					{
						//If the coordinate is already occupied then set the flag and do not count that moves
						flag[i]=1;

					}

				}	




				//find max cnt index

				xIn=0;
				while(flag[xIn]==1)
				{	
					if(xIn<moves)
						xIn++;
				}

				if(xIn<moves)
				{
					//Find the maximum count of c in the neighbourhood of the present coordinate
					for(i=0;i<moves;i++)
						if(cnt[i]>cnt[xIn] && flag[i]!=1) 
						{
							xIn=i;

						}

						j=0;
						for(i=xIn;i<moves;i++)
							if(cnt[i]==cnt[xIn] && flag[i]!=1)  
							{
								//Find the maximum count of c and the coordinates with equal maximum count in the neighbourhood of the present coordinate
								posMov[j++]=i;
							}
							else
								posMov[i]=-1;

						r=rand()%j;


						//Choose the possible move using random function
						switch(posMov[r])
						{

						case 0:	//next move is to the east
							col=col+2;
							nxtMov='E';
							break;

						case 1: //next move is to the west
							col=col-2;
							nxtMov='W';
							break;

						case 2: //next move is to the south west
							row=row-1;
							col=col-1;
							nxtMov='x';
							break;

						case 3: //next move is to the north east
							row=row+1;
							col=col+1;
							nxtMov='y';
							break;

						case 4: //next move is to the south east
							row=row-1;
							col=col+1;
							nxtMov='z';
							break;

						case 5: //next move is to the north west
							row=row+1;
							col=col-1;
							nxtMov='a';
							break;

						}
				
						//Set the coordinate value with c
						cordinates[row][col]=str[strIndex]-'0';

						//Set the direction value with next move choosen
						last[k]->nxtMov=nxtMov;
						direction[last[k]->x+MAX-1][last[k]->y+2*(MAX-1)]=nxtMov;

						// PointsList:add(ithPoint)
						insert_node(row-MAX+1,col-(2*MAX)+2,cordinates[row][col]);//,nxtMov);
						last[k]->index=strIndex;


						//Set the outline of the coordinates
						if(minRow>row)
							minRow=row;
						if(minCol>col)
							minCol=col;
						if(maxRow<row)
							maxRow=row;
						if(maxCol<col)
							maxCol=col;
						if(str[strIndex]=='1' && str[strIndex+1]!='1' && str[strIndex+2]=='1')
						{
							if(cordinates[row-1][col-1]==1 && cordinates[row-1][col+1]==-1 && cordinates[row-2][col]==-1  )
							{
								for(a=1;a<=2;a++)
								{
									if(a==1)
									{
										row=row-1;
										col=col+1;
										nxtMov='z';
									}
									else
									{
										row=row-1;
										col=col-1;
										nxtMov='x';

									}
								//Set the coordinate value with c
								cordinates[row][col]=str[strIndex+a]-'0';

								//Set the direction value with next move choosen
								last[k]->nxtMov=nxtMov;
								direction[last[k]->x+MAX-1][last[k]->y+2*(MAX-1)]=nxtMov;
	
								// PointsList:add(ithPoint)
								insert_node(row-MAX+1,col-(2*MAX)+2,cordinates[row][col]);//,nxtMov);
								last[k]->index=strIndex+a;
	

								//Set the outline of the coordinates
								if(minRow>row)
									minRow=row;
								if(minCol>col)
									minCol=col;
								if(maxRow<row)
									maxRow=row;
								if(maxCol<col)
									maxCol=col;
								}
								strIndex++;
							}
							else if(cordinates[row-1][col+1]==1 && cordinates[row+1][col+1]==-1 && cordinates[row][col+2]==-1  )
							{
								for(a=1;a<=2;a++)
								{
									if(a==1)
									{
										row=row+1;
										col=col+1;
										nxtMov='y';
									}
									else
									{
										row=row-1;
										col=col+1;
										nxtMov='z';

									}
								//Set the coordinate value with c
								cordinates[row][col]=str[strIndex+a]-'0';

								//Set the direction value with next move choosen
								last[k]->nxtMov=nxtMov;
								direction[last[k]->x+MAX-1][last[k]->y+2*(MAX-1)]=nxtMov;
	
								// PointsList:add(ithPoint)
								insert_node(row-MAX+1,col-(2*MAX)+2,cordinates[row][col]);//,nxtMov);
								last[k]->index=strIndex+a;
	

								//Set the outline of the coordinates
								if(minRow>row)
									minRow=row;
								if(minCol>col)
									minCol=col;
								if(maxRow<row)
									maxRow=row;
								if(maxCol<col)
									maxCol=col;
								}
								strIndex++;
							}
							
						}
				}
				else
				{
					//Not a favourable move. 
					//Further moves not possible
					first[k]=NULL;
					break;
				}
				

			}

			//Set the last node of the result sequence's direction value
			last[k]->nxtMov='H';
			direction[row][col]='H';



			if(strIndex<strlen(str))
			{	//Not a favourable move. 
				//Further moves not possible

				Energy[k].HEV=-1;
			//	Energy[k].FEV=-1;
			}
			else
			{
				//find theenergy variation value for a favourable move
				Energy[k].HEV=0;
			//	Energy[k].FEV=0;
				calculateEnergy();
				
			}

			k++;
	}

	//Find the index of the best sequence
	//k=findMaxVariation(populationSize,Energy);



	//	printf_s("\nk=%dth Energy Variation %f\n",k+1,Energy[k].HEV);

	//add the index of the best sequence to an structure


	//Sort the HEV structure so that the top 10 sequences based on theenergy variation value into a file
	sortEnergySt();

	k=0;

	//Display the best sequence
	result();

	Efinal[l].HEV=Energy[k].HEV;
	//Increment the index of the array storing the index  of the best sequence 
	l++;

}


void procedureSquare(int Case,int e)
{
	//Function for performing the fold


	short int i,j,row,col,trow,tcol,tx,ty,xIn,r,posMov[12],c;
	char nxtMov;
	short int cnt[12],flag[12];
	int strIndex;
	k=0;
	start=clock();
	while(k<populationSize)
	{
		first[k]=NULL;last[k]=NULL;


		//Initialization of coordinates and direction
		for(i=0;i<(2*MAX);i++)
			for(j=0;j<(4*MAX);j++)
			{
				cordinates[i][j]=-1;
				direction[i][j]='H';

			}



			//Initialization
			//startP oint = latticeCenter

			row=MAX-1;
			col=(2*MAX)-2;
			cordinates[row][col]=str[0]-'0';
			minCol=col;

			// PointsList:add(startPoint)
			insert_node(row-MAX+1,col-(2*MAX)+2,cordinates[row][col]);



			//secondP oint = eastNeighbour(startPoint)
			nxtMov='E';
			last[k]->nxtMov=nxtMov;
			last[k]->index=0;
			direction[row][col]=nxtMov;
			col=col+1;
			cordinates[row][col]=str[1]-'0';

			// PointsList:add(secondPoint)
			insert_node(row-MAX+1,col-(2*MAX)+2,cordinates[row][col]);
			last[k]->index=1;
			minRow=maxRow=row;
			maxCol=col;


			for(strIndex=2;strIndex<strlen(str);strIndex++)
			{

				i=0;


				//Initialize the c value
				switch(Case)
				{
				case 1:	//case for counted 0 and 1 value

					if(str[strIndex]=='1')
						c=1;
					if(str[strIndex]=='0')
						c=0;
					if(str[strIndex]=='2')
						c=2;
					if(str[strIndex]=='3')
						c=3;
					break;

				case 0://case for counted 1 and randomized 0 value

					if(str[strIndex]=='1')
						c=1;
					else 
						c=-2;
					break;
				}




				//For finding the possible moves from the current coordinates(row,col)

				for(i=0;i<moves;i++)
				{
					switch(i)
					{
					case 0://next move is to the east
						trow=row;
						tcol=col+1;	
						break;

					case 1://next move is to the west
						trow=row;
						tcol=col-1;		 	
						break;

					case 2: //next move is to the south west
						trow=row-1;//x
						tcol=col;
						break;

					case 3:	//next move is to the North east
						trow=row+1;//y
						tcol=col;
						break;
					}

					cnt[i]=0;flag[i]=0;


					//find the suitable coordinate
					if(cordinates[trow][tcol]==-1 )
					{
						//If the coordinate is not occupied 
						switch(e)
						{
						case 1:for(tx=trow-1;tx<trow+2;tx++)		
							   {

								   for(ty=tcol-1;ty<tcol+2;ty++)
								   {
									   if(cordinates[tx][ty]==c)
										   cnt[i]++;
								   }
							   }	
							   break;
						case 2:

							for(tx=trow-2;tx<=trow+2;tx++)
							{
								for(ty=tcol-1;ty<tcol+2;ty++)
								{
									if(cordinates[tx][ty]==c)
										cnt[i]++;
								}

							}	
							break;

						}
					}
					else
					{
						//If the coordinate is already occupied then set the flag and do not count that moves
						flag[i]=1;

					}

				}	




				//find max cnt index

				xIn=0;
				while(flag[xIn]==1)
				{	
					if(xIn<moves)
						xIn++;
				}

				if(xIn<moves)
				{
					//Find the maximum count of c in the neighbourhood of the present coordinate
					for(i=0;i<moves;i++)
						if(cnt[i]>cnt[xIn] && flag[i]!=1) 
						{
							xIn=i;

						}

						j=0;
						for(i=xIn;i<moves;i++)
							if(cnt[i]==cnt[xIn] && flag[i]!=1)  
							{
								//Find the maximum count of c and the coordinates with equal maximum count in the neighbourhood of the present coordinate
								posMov[j++]=i;
							}
							else
								posMov[i]=-1;

						r=rand()%j;


						//Choose the possible move using random function
						switch(posMov[r])
						{

						case 0:	//next move is to the east
							col=col+1;
							nxtMov='E';
							break;

						case 1: //next move is to the west
							col=col-1;
							nxtMov='W';
							break;

						case 2: //next move is to the south
							row=row-1;
							col=col;
							nxtMov='S';
							break;

						case 3: //next move is to the north
							row=row+1;
							col=col;
							nxtMov='N';
							break;



						}
						//Set the coordinate value with c
						cordinates[row][col]=str[strIndex]-'0';

						//Set the direction value with next move choosen
						last[k]->nxtMov=nxtMov;
						direction[last[k]->x+MAX-1][last[k]->y+2*MAX-2]=nxtMov;

						// PointsList:add(ithPoint)
						insert_node(row-MAX+1,col-(2*MAX)+2,cordinates[row][col]);//,nxtMov);
						last[k]->index=strIndex;


						//Set the outline of the coordinates
						if(minRow>row)
							minRow=row;
						if(minCol>col)
							minCol=col;
						if(maxRow<row)
							maxRow=row;
						if(maxCol<col)
							maxCol=col;
				}
				else
				{
					//Not a favourable move. 
					//Further moves not possible
					first[k]=NULL;
					break;
				}

			}

			//Set the last node of the result sequence's direction value
			last[k]->nxtMov='H';
			direction[row][col]='H';


			if(strIndex<strlen(str))
			{	//Not a favourable move. 
				//Further moves not possible

				Energy[k].HEV=-1;
				//Energy[k].FEV=-1;
			}
			else
			{
				//find theenergy variation value for a favourable move
				Energy[k].HEV=0;
				//Energy[k].FEV=0;
				calculateEnergy();
			}


			k++;
			end=clock();
			spent=(end-start)/CLOCKS_PER_SEC;
	}

		//Find the index of the best sequence
	//k=findMaxVariation(populationSize,Energy);
/*

	printf("\nThe maximumenergy variation Path\n");*/

	printf("\n time taken is %f  second", spent);

	//Sort the HEV structure so that the top 10 sequences based on theenergy variation value into a file
	sortEnergySt();
	k=0;
	result();

	//add the index of the best sequence to an structure

		Efinal[l].HEV=Energy[k].HEV;

	//Increment the index of the array storing the index  of the best sequence 
	l++;

}

#pragma endregion



#pragma region graphics
//Following section for drawing 


void lineh(int x,int y,int x2)
{	//Draw horizontal line

	glBegin(GL_LINES);
	glLineWidth(4.0);
	glVertex2i(x,y);
	glVertex2i(x2,y);
	glEnd();
}


void linev(int x,int y,int y2)
{	//Draw vertical line
	glBegin(GL_LINES);
	glLineWidth(1.0);
	glVertex2i(x,y);
	glVertex2i(x,y2);
	glEnd();
}


void line(int x1,int y1,int x2,int y2)
{	// Draw a line
	glBegin(GL_LINES);
	glLineWidth(1.0);
	glVertex2i(x1,y1);
	glVertex2i(x2,y2);
	glEnd();
}

void color(float red,float green,float blue)
{	//for choosing color
	glColor3f(red,green,blue);
}



void points(float x, float y)	
{	//to draw a point
	glBegin(GL_POINTS);
	glVertex2f(x,y);
	glEnd();
}

void DrawCircle(float x_pt, float y_pt, float radius, int num_segments) 
{	int ii;
float angle,x,y;
for( ii = 0; ii < num_segments; ii++) 
{	//formula used arc_length=radius*angle
	angle = 2.0 * pi * float(ii) / float(num_segments);//get the current angle 

	x = radius * cosf(angle);//calculate the x component 
	y = radius * sinf(angle);//calculate the y component 

	glVertex2f(x + x_pt, y + y_pt);//output vertex 

} 
glEnd();
}


void myInit(void)
{//Setting Background Color
	glClearColor(0.7,0.7,0.6,0);
	glLoadIdentity();
}



void Reshape(int width, int height) 
{  //othr pages 
	glutReshapeWindow( 800, 600);
	CurrentWidth = 800;
    CurrentHeight = 600;
	dif=0;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); 
	glViewport(0,0,CurrentWidth,CurrentHeight); 

	x=250;
	y=350;
	gluOrtho2D(0, width,0,height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}


void circle(int y,int x)
{	glBegin(GL_POLYGON);
DrawCircle(x,y,5,10);
}


void Graph_page(void)
{//for displaying front page and then creating a new window aftr few delay
	struct HWND__ *windowHandle = GetForegroundWindow();
	long int Style = GetWindowLong(windowHandle, GWL_STYLE);
	Style &= ~WS_MAXIMIZEBOX; //this makes it still work when WS_MAXIMIZEBOX is actually already toggled off
	SetWindowLong(windowHandle, GWL_STYLE, Style);

	int q=0;
	glClear(GL_COLOR_BUFFER_BIT);


	l=findMaxVariation(4,Efinal);

	//Display the start point
	glClearColor(1,1,1,1);
	glBegin(GL_POLYGON);
	color(0,1,0);
	DrawCircle(y,x,9,10);
	color(0,0,0);

	//Display the rest of the coorinates
	for (ptr = tmpFirst[l];ptr != NULL;ptr = ptr->next)
	{


		if(ptr==tmpFirst[l])
		{	//Display the start point with black outline
			glBegin(GL_POLYGON);
			color(0,0,0);
			DrawCircle(y+(ptr->y * 20),x+(ptr->x * 20),6,10);
		}

		if(ptr==tmpLast[l])
		{	//Display the end point with aqua background
			glBegin(GL_POLYGON);
			color(0,1,1);
			DrawCircle(y+(ptr->y * 20),x+(ptr->x * 20),7,10);
		}

		switch(ptr->v)
		{
			case 1:
			//Red color 
			color(1,0,0);break;
		
			case 0:
			//Blue color
			color(0,0,1);
			//peach color(1,0.5,0.5);
			break;
			case 2:
			//peech color
			color(1,0.5,0.5);break;
			case 3://light bluecolor
			color(0.5,0.5,1);break;
		}
		

		//Draw circle
		circle(x+(ptr->x * 20),y+(ptr->y * 20));

		//Draw the connection in black color
		color(0,0,0);
		glLineWidth(1.0);
		if(ptr->nxtMov=='E')
		{//East connection
			if(moves==6)
				q=35;
			else
				q=15;
			lineh(y+(ptr->y * 20)+5,x+(ptr->x * 20),y+(ptr->y * 20)+q);
		}

		else if(ptr->nxtMov=='W')
		{//West connection
			if(moves==6)
				q=35;
			else
				q=15;
			lineh(y+(ptr->y * 20)-5,x+(ptr->x * 20),y+(ptr->y * 20)-q);
		}

		else if(ptr->nxtMov=='x')
		{//next move is to the South west
			line(y+(ptr->y * 20)-20,x+(ptr->x * 20)-20,y+(ptr->y * 20),x+(ptr->x * 20));
		}

		else if(ptr->nxtMov=='y')
		{//next move is to the north east
			line(y+(ptr->y * 20)+20,x+(ptr->x * 20)+20,y+(ptr->y * 20),x+(ptr->x * 20));
		}

		else if(ptr->nxtMov=='z')
		{//next move is to the South east
			line(y+(ptr->y * 20)+20,x+(ptr->x * 20)-20,y+(ptr->y * 20),x+(ptr->x * 20));
		}

		else if(ptr->nxtMov=='a')
		{//next move is to the north west
			line(y+(ptr->y * 20)-20,x+(ptr->x * 20)+20,y+(ptr->y * 20),x+(ptr->x * 20));
		}
		else if(ptr->nxtMov=='N')
			linev(y+(ptr->y * 20),x+(ptr->x * 20)+5,x+(ptr->x * 20)+15);

		else if(ptr->nxtMov=='S')
			linev(y+(ptr->y * 20),x+(ptr->x * 20)-5,x+(ptr->x * 20)-15);
		//color(0,0,1);
	}


	//display theenergy variation between the coordinates
	color(0.8,0.9,0);
	glLineWidth(1.0);
	for (ptrE = tmpFirstE[l];ptrE != NULL;ptrE = ptrE->next)
	{    
		line(y+(ptrE->y1 * 20),x+(ptrE->x1 * 20),y+(ptrE->y2 * 20),x+(ptrE->x2 * 20));
	}


	glutPostRedisplay();
	glutSwapBuffers();
	glFlush();

}


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
	int argc=1;
	char * argv="OPENGL";
	glutInit(&argc,&argv);//initialize openGl glut library
	glutInitDisplayMode (GLUT_DOUBLE |GLUT_RGB);//2 buffers are used as it is animation and RGB color model is used

}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGUI1Dlg dialog



CGUI1Dlg::CGUI1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGUI1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CGUI1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGUI1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(txtInput2, &CGUI1Dlg::OnEnChangetxtinput2)
	ON_BN_CLICKED(btnSquareEV2D, &CGUI1Dlg::OnBnClickedbtnsquareev2d)
	ON_BN_CLICKED(btnTriangularEV2D, &CGUI1Dlg::OnBnClickedbtntriangularev2d)
	ON_EN_CHANGE(txtInput, &CGUI1Dlg::OnEnChangetxtinput)
	ON_EN_KILLFOCUS(txtInput, &CGUI1Dlg::OnEnKillfocustxtinput)
END_MESSAGE_MAP()


// CGUI1Dlg message handlers

BOOL CGUI1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here


	return TRUE;  // return TRUE  unless you set the focus to a control
}
void close()
{
	glutDestroyWindow(id1);

}
void CGUI1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGUI1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGUI1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CGUI1Dlg::OnBnClickedbtnsquareev2d()
{
	// TODO: Add your control notification handler code here
	if(strlen(str)>1)
	{
		fopen_s(&fptrO,"resultSquareHP.txt","w");
		if(fptrO==NULL)
			printf_s("Error in opening file");

		//Initialize the output pointer
		fopen_s(&fptrOB,"bestResultSquareHP.txt","w");
		if(fptrOB==NULL)
			printf_s("Error in opening file");

		moves=4;

		l=0;

		CWnd * btn = GetDlgItem( btnTriangularEV2D );
		btn->EnableWindow( FALSE );
		btn=GetDlgItem( btnSquareEV2D );
		btn->EnableWindow( FALSE );
		btn = GetDlgItem( btnTriangularV2D2 );
		btn->EnableWindow( FALSE );
		btn=GetDlgItem( btnSquareV2D2 );
		btn->EnableWindow( FALSE );


		
		//moves are based on counted 1's and 0's
		procedureSquare(1,1);

		//moves are based on counted 1's and randomized 0's
		procedureSquare(0,1);


		//moves are based on counted 1's and 0's
		procedureSquare(1,2);

		//moves are based on counted 1's and randomized 0's
		procedureSquare(0,2);

		fprintf_s(fptrO,"end\n");

		//Write the best sequence to the file
		l=findMaxVariation(4,Efinal);
		for (ptr = tmpFirst[l];ptr != NULL;ptr = ptr->next)
		{
			fprintf_s(fptrOB,"(\t%d\t~\t%d\t)\n",ptr->x,ptr->y);
		}
		//print theenergy variation
		sprintf_s(res,"-%f",Efinal[l].HEV );
		printf( "\n time is %f" , spent);

		CStatic* text=(CStatic*)GetDlgItem(IDC_RESULT);
		text->SetWindowText(CA2T(res));

		text=(CStatic*)GetDlgItem(IDC_RESULT);
		text->ShowWindow(SW_SHOW);

		text=(CStatic*)GetDlgItem(labelEnergy);
		text->ShowWindow(SW_SHOW);
		UpdateData(FALSE) ;

		//visualization



		glutInitWindowSize(800,600);//to set window size( width,height)
		glutInitWindowPosition(50,50);//to set window position
		id1=glutCreateWindow("Graph");//creates window
		glutDisplayFunc(Graph_page);//Register the call back function "myDisplay" Function
		//glutFullScreen(); 

		glutReshapeFunc(Reshape);

		glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE ,GLUT_ACTION_CONTINUE_EXECUTION);
		myInit();
		glutMainLoop();
		glutCloseFunc(close);
		text=(CStatic*)GetDlgItem(IDC_RESULT);
		text->ShowWindow(SW_HIDE);
		text=(CStatic*)GetDlgItem(IDC_RESULTEV);
		text->ShowWindow(SW_HIDE);
		text=(CStatic*)GetDlgItem(labelEnergy2);
		text->ShowWindow(SW_HIDE);
		text=(CStatic*)GetDlgItem(labelEnergy);
		text->ShowWindow(SW_HIDE);

		UpdateData(FALSE) ;

		btn = GetDlgItem( btnTriangularEV2D );
		btn->EnableWindow( TRUE );
		btn=GetDlgItem( btnSquareEV2D );
		btn->EnableWindow( TRUE );

		btn = GetDlgItem( btnTriangularV2D2 );
		btn->EnableWindow( TRUE );
		btn=GetDlgItem( btnSquareV2D2 );
		btn->EnableWindow( TRUE );

		CWnd * txt =GetDlgItem(txtInput);
		txt->EnableWindow(true);
		txt =GetDlgItem(txtInput2);
		txt->EnableWindow(true);
		fclose(fptrO);
		fclose(fptrOB);
	}
	else
	{
		CStatic *text=(CStatic*)GetDlgItem(labelEnergy);
		text->ShowWindow(SW_SHOW);
		char *error="Enter the sequence atleast of length 2 ";
		text->SetWindowText(CA2T(error));
		UpdateData(FALSE) ;
	}
}



void CGUI1Dlg::OnBnClickedbtntriangularev2d()
{
	// TODO: Add your control notification handler code here


	if(strlen(str)>1){
		fopen_s(&fptrO,"resultTriangularHP.txt","w");
		if(fptrO==NULL)
			printf_s("Error in opening file");

		//Initialize the output pointer
		fopen_s(&fptrOB,"bestResultTriangularHP.txt","w");
		if(fptrOB==NULL)
			printf_s("Error in opening file");

		moves=6;
		l=0;
		CWnd * btn = GetDlgItem( btnTriangularEV2D );
		btn->EnableWindow( FALSE );
		btn=GetDlgItem( btnSquareEV2D );
		btn->EnableWindow( FALSE );
		btn = GetDlgItem( btnTriangularV2D2 );
		btn->EnableWindow( FALSE );
		btn=GetDlgItem( btnSquareV2D2 );
		btn->EnableWindow( FALSE );

		
		//moves are based on counted 1's and 0's
		procedureTriangular();

		fprintf_s(fptrO,"end\n");

		//Write the best sequence to the file
		l=findMaxVariation(4,Efinal);
		for (ptr = tmpFirst[l];ptr != NULL;ptr = ptr->next)
		{
			fprintf_s(fptrOB,"(\t%d\t~\t%d\t)\n",ptr->x,ptr->y);
		}
		//print theenergy variation
		sprintf_s(res,"-%f",Efinal[l].HEV );

		CStatic* text=(CStatic*)GetDlgItem(IDC_RESULT);
		text->SetWindowText(CA2T(res));

		text=(CStatic*)GetDlgItem(IDC_RESULT);
		text->ShowWindow(SW_SHOW);

		text=(CStatic*)GetDlgItem(labelEnergy);
		text->ShowWindow(SW_SHOW);

		char *dis="Energy Variation";
		text->SetWindowText(CA2T(dis));
		UpdateData(FALSE) ;
		//visualization

		glutInitWindowSize(800,600);//to set window size( width,height)
		glutInitWindowPosition(50,50);//to set window position
		id1=glutCreateWindow("Graph");//creates window
		glutDisplayFunc(Graph_page);//Register the call back function "myDisplay" Function
		glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE ,GLUT_ACTION_CONTINUE_EXECUTION);

		glutReshapeFunc(Reshape);
		myInit();
		glutMainLoop();
		glutCloseFunc(close);

		text=(CStatic*)GetDlgItem(IDC_RESULT);
		text->ShowWindow(SW_HIDE);
		text=(CStatic*)GetDlgItem(IDC_RESULTEV);
		text->ShowWindow(SW_HIDE);

		text=(CStatic*)GetDlgItem(labelEnergy2);
		text->ShowWindow(SW_HIDE);


		text=(CStatic*)GetDlgItem(labelEnergy);
		text->ShowWindow(SW_HIDE);
		btn = GetDlgItem( btnTriangularEV2D );
		btn->EnableWindow( TRUE );
		btn=GetDlgItem( btnSquareEV2D );
		btn->EnableWindow( TRUE );

		btn = GetDlgItem( btnTriangularV2D2 );
		btn->EnableWindow( TRUE );
		btn=GetDlgItem( btnSquareV2D2 );
		btn->EnableWindow( TRUE );

		
		CWnd * txt =GetDlgItem(txtInput);
		txt->EnableWindow(true);
		txt =GetDlgItem(txtInput2);
		txt->EnableWindow(true);
		fclose(fptrO);
		fclose(fptrOB);
	}
	else
	{
		CStatic *text=(CStatic*)GetDlgItem(labelEnergy);
		text->ShowWindow(SW_SHOW);
		char *error="Enter the sequence atleast of length 2 ";
		text->SetWindowText(CA2T(error));
		UpdateData(FALSE) ;
	}


}

void CGUI1Dlg::OnEnChangetxtinput()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	CString s;

	//char len[15];//tmp[100];
	char len[MAX];
	CEdit *input2=(CEdit*) GetDlgItem(txtInput);
	input2->GetWindowText(s);
	//convert(s);
	CWnd * txt=(CWnd *) GetDlgItem(txtInput2);
	txt->EnableWindow( FALSE );
	sprintf_s(len,"%ld",strlen(str));
	CStatic*  text=(CStatic*)GetDlgItem(IDC_LENGTH);
	text->SetWindowText(CA2T(len));

}



void CGUI1Dlg::OnEnChangetxtinput2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	//char len[15];
	char len[MAX];
	CString s;
	CEdit * input1=(CEdit*) GetDlgItem(txtInput2);
	input1->GetWindowText(s);
	//sprintf_s( str, 100, "%s", CT2CA(s) );
	sprintf_s( str, MAX, "%s", CT2CA(s) );
	sprintf_s(len,"%ld",strlen(str));
	CStatic*  text=(CStatic*)GetDlgItem(IDC_LENGTH);
	text->SetWindowText(CA2T(len));
	CWnd * txt=(CWnd *) GetDlgItem(txtInput);
	txt->EnableWindow( FALSE );
}



void CGUI1Dlg::OnEnKillfocustxtinput()
{
	// TODO: Add your control notification handler code here
	CEdit * txt=(CEdit *) GetDlgItem(txtInput2);
	txt->SetWindowTextW(CA2T(str));
}


#pragma endregion