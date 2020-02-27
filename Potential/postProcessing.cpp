
#pragma region postProcessing
void result()
{	//Insert the resultant sequence
	//printf_s("%dth possibility\n",k+1);
	if (first[k] == NULL)
	{
		ISEMPTY;

	}
	else
	{
		tmpLast[l] = tmpFirst[l] = NULL;
		tmpLastE[l] = tmpFirstE[l] = NULL;
		for (ptr = first[k]; ptr != NULL; ptr = ptr->next)
		{
			//      printf_s("(%d,%d) %c\t", ptr->x,ptr->y,ptr->nxtMov);
			insert_nodefinal(ptr->x, ptr->y, ptr->v);
			tmpLast[l]->nxtMov = ptr->nxtMov;
			tmpLast[l]->index = last[k]->index;
		}
		for (ptrE = firstE[k]; ptrE != NULL; ptrE = ptrE->next)
		{
			insert_nodeEFinal(ptrE->x1, ptrE->y1, ptrE->x2, ptrE->y2);
		}
	}
	//printf_s("\n");
}

void calculateEnergy()
{// calculateenergy variation

	short int i, j, e;
	firstE[k] = NULL;
	lastE[k] = NULL;

	for (i = minRow; i <= maxRow; i++)
	{
		for (j = minCol; j <= maxCol; j++)
		{//Check whether there exists a direct connection between two points.
			// If no direct connection exists in the current direction increment theenergy variation value by 1

			if (cordinates[i][j] == 1)
			{
				//check for the horizontal connection
				if (moves == 6)
					e = 2;
				else
					e = 1;
				if (cordinates[i][j + e] == 0)
					if ((direction[i][j] != 'E' && direction[i][j + e] != 'W'))
					{
						Energy[k].HEV = Energy[k].HEV + 4;
						//insert_nodeE(i-MAX+1,j-(2*MAX)+2, i-MAX+1,j+e-(2*MAX)+2);
					}

				//check for vertical connection
				if (cordinates[i + e][j] == 0)
					if ((direction[i][j] != 'N' && direction[i + e][j] != 'S'))
					{
						Energy[k].HEV = Energy[k].HEV + 4;
						//insert_nodeE(i-MAX+1,j-(2*MAX)+2, i+e-MAX+1,j-(2*MAX)+2);
					}


				//check for diagonal (south west and north east) connection

				e = 1;
				if (cordinates[i + e][j + e] == 0)
					if ((direction[i][j] != 'y' && direction[i + e][j + e] != 'x'))
					{
						Energy[k].HEV = Energy[k].HEV + 4;
						//insert_nodeE(i-MAX+1,j-(2*MAX)+2, i+e-MAX+1,j+e-(2*MAX)+2);
					}


				//check for diagonal (north west and south east) connection
				if (cordinates[i + e][j - e] == 0)
					if ((direction[i][j] != 'a' && direction[i + 1][j - 1] != 'z'))
					{
						Energy[k].HEV = Energy[k].HEV + 4;
						//insert_nodeE(i-MAX+1,j-(2*MAX)+2, i+e-MAX+1,j-e-(2*MAX)+2);
					}
			}
			if (cordinates[i][j] == 1)
			{
				//check for the horizontal connection
				if (moves == 6)
					e = 2;
				else
					e = 1;
				if (cordinates[i][j + e] == 1)
					if ((direction[i][j] != 'E' && direction[i][j + e] != 'W'))
					{
						Energy[k].HEV = Energy[k].HEV + 2;

					}

				//check for vertical connection
				if (cordinates[i + e][j] == 1)
					if ((direction[i][j] != 'N' && direction[i + e][j] != 'S'))
					{
						Energy[k].HEV = Energy[k].HEV + 2;

					}


				//check for diagonal (south west and north east) connection

				e = 1;
				if (cordinates[i + e][j + e] == 1)
					if ((direction[i][j] != 'y' && direction[i + e][j + e] != 'x'))
					{
						Energy[k].HEV = Energy[k].HEV + 2;

					}


				//check for diagonal (north west and south east) connection
				if (cordinates[i + e][j - e] == 1)
					if ((direction[i][j] != 'a' && direction[i + 1][j - 1] != 'z'))
					{
						Energy[k].HEV = Energy[k].HEV + 2;

					}
			}
			if (cordinates[i][j] == 0)
			{
				//check for the horizontal connection
				if (moves == 6)
					e = 2;
				else
					e = 1;
				if (cordinates[i][j + e] == 0)
					if ((direction[i][j] != 'E' && direction[i][j + e] != 'W'))
					{
						Energy[k].HEV = Energy[k].HEV + 2;

					}

				//check for vertical connection
				if (cordinates[i + e][j] == 0)
					if ((direction[i][j] != 'N' && direction[i + e][j] != 'S'))
					{
						Energy[k].HEV = Energy[k].HEV + 2;

					}


				//check for diagonal (south west and north east) connection

				e = 1;
				if (cordinates[i + e][j + e] == 0)
					if ((direction[i][j] != 'y' && direction[i + e][j + e] != 'x'))
					{
						Energy[k].HEV = Energy[k].HEV + 2;

					}


				//check for diagonal (north west and south east) connection
				if (cordinates[i + e][j - e] == 0)
					if ((direction[i][j] != 'a' && direction[i + 1][j - 1] != 'z'))
					{
						Energy[k].HEV = Energy[k].HEV + 2;

					}
			}
			if (cordinates[i][j] == 2)
			{
				//check for the horizontal connection
				if (moves == 6)
					e = 2;
				else
					e = 1;
				if (cordinates[i][j + e] == 3)
					if ((direction[i][j] != 'E' && direction[i][j + e] != 'W'))
					{
						Energy[k].HEV = Energy[k].HEV + 1;

					}

				//check for vertical connection
				if (cordinates[i + e][j] == 3)
					if ((direction[i][j] != 'N' && direction[i + e][j] != 'S'))
					{
						Energy[k].HEV = Energy[k].HEV + 1;

					}


				//check for diagonal (south west and north east) connection

				e = 1;
				if (cordinates[i + e][j + e] == 3)
					if ((direction[i][j] != 'y' && direction[i + e][j + e] != 'x'))
					{
						Energy[k].HEV = Energy[k].HEV + 1;

					}


				//check for diagonal (north west and south east) connection
				if (cordinates[i + e][j - e] == 3)
					if ((direction[i][j] != 'a' && direction[i + 1][j - 1] != 'z'))
					{
						Energy[k].HEV = Energy[k].HEV + 1;

					}
			}
			if (cordinates[i][j] == 2)
			{
				//check for the horizontal connection
				if (moves == 6)
					e = 2;
				else
					e = 1;
				if (cordinates[i][j + e] == 2)
					if ((direction[i][j] != 'E' && direction[i][j + e] != 'W'))
					{
						Energy[k].HEV = Energy[k].HEV - 1;

					}

				//check for vertical connection
				if (cordinates[i + e][j] == 2)
					if ((direction[i][j] != 'N' && direction[i + e][j] != 'S'))
					{
						Energy[k].HEV = Energy[k].HEV - 1;

					}


				//check for diagonal (south west and north east) connection

				e = 1;
				if (cordinates[i + e][j + e] == 2)
					if ((direction[i][j] != 'y' && direction[i + e][j + e] != 'x'))
					{
						Energy[k].HEV = Energy[k].HEV - 1;

					}


				//check for diagonal (north west and south east) connection
				if (cordinates[i + e][j - e] == 2)
					if ((direction[i][j] != 'a' && direction[i + 1][j - 1] != 'z'))
					{
						Energy[k].HEV = Energy[k].HEV - 1;

					}
			}

		}
	}
}

int findMaxVariation(int size, struct Energy_ Energy[])
{//Find the maximumenergy variation and index among the resultant sequences


	short int i;
	int maxVar = 0;
	for (i = 1; i < size; i++)
	{
		if (Energy[maxVar].HEV < Energy[i].HEV)
			maxVar = i;
		Energy[i].i = i;
	}

	return maxVar;

}

void sortEnergySt()
{//Sort the HEV structure based on theenergy variation found. 
	//Function is executed so that the top 10 sequences are choosen and written into the output file


	int i, j;
	for (i = 0; i < populationSize; i++)
		for (j = i + 1; j < populationSize; j++)
		{//Sort the structure
			if (Energy[j + 1].HEV < Energy[j].HEV)
			{
				tmp.i = Energy[j + 1].i;
				tmp.HEV = Energy[j + 1].HEV;
				//tmp.FEV=Energy[j+1].FEV;
				Energy[j + 1].i = Energy[j].i;
				Energy[j + 1].HEV = Energy[j].HEV;
				//Energy[j+1].FEV=Energy[j].FEV;
				Energy[j].HEV = tmp.HEV;
				//Energy[j].FEV=tmp.FEV;
				Energy[j].i = tmp.i;
			}
		}


	//Write the top 10 sequences to output file result.txt
	for (i = 0; i < populationSize / 4; i++)
	{
		if (Energy[i].HEV != -1) {
			for (ptr = first[Energy[i].i]; ptr != NULL; ptr = ptr->next)
			{
				//need to replace file i/o with another data sharing strategy
				//list of nodes, in the order it is being appended to the file?
				fprintf_s(fptrO, "(%d,%d) %c\t~", ptr->x, ptr->y, ptr->nxtMov);
			}
			fprintf_s(fptrO, "%f %s", Energy[i].HEV, "||\n");
		}

	}

}
#pragma endregion
