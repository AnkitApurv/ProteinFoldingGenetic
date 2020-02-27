
#pragma region procedures
void procedureTriangular()
{
	//Function for performing the fold


	short int i, j, row, col, trow, a, tcol, tx, ty, xIn, r, posMov[12], c;
	char nxtMov;
	short int cnt[12], flag[12];
	unsigned short int strIndex;
	k = 0;
	while (k < populationSize)
	{
		first[k] = NULL; last[k] = NULL;


		//Initialization of coordinates and direction
		for (i = 0; i < (2 * MAX); i++)
			for (j = 0; j < (4 * MAX); j++)
			{
				cordinates[i][j] = -1;
				direction[i][j] = 'H';

			}



		//Initialization
		//startP oint = latticeCenter

		row = MAX - 1;
		col = (2 * MAX) - 2;
		cordinates[row][col] = str[0] - '0';
		minCol = col;

		// PointsList:add(startPoint)
		insert_node(row - MAX + 1, col - (2 * MAX) + 2, cordinates[row][col]);



		//secondP oint = eastNeighbour(startPoint)
		nxtMov = 'E';
		last[k]->nxtMov = nxtMov;
		last[k]->index = 0;
		direction[row][col] = nxtMov;
		col = col + 2;
		cordinates[row][col] = str[1] - '0';

		// PointsList:add(secondPoint)
		insert_node(row - MAX + 1, col - (2 * MAX) + 2, cordinates[row][col]);
		last[k]->index = 1;
		minRow = maxRow = row;
		maxCol = col;


		for (strIndex = 2; strIndex < strlen(str); strIndex++)
		{

			i = 0;


			//Initialize the c value

			if (str[strIndex] == '1')
				c = 1;
			if (str[strIndex] == '0')
				c = 0;
			if (str[strIndex] == '2')
				c = 2;
			if (str[strIndex] == '3')
				c = 3;






			//For finding the possible moves from the current coordinates(row,col)


			for (i = 0; i < moves; i++)
			{
				switch (i)
				{
				case 0://next move is to the east
					trow = row;
					tcol = col + 2;
					break;

				case 1://next move is to the west
					trow = row;
					tcol = col - 2;
					break;

				case 2: //next move is to the south west
					trow = row - 1;//x
					tcol = col - 1;
					break;

				case 3:	//next move is to the North east
					trow = row + 1;//y
					tcol = col + 1;
					break;

				case 4: //next move is to the South east
					trow = row - 1;//z
					tcol = col + 1;
					break;

				case 5:	//next move is to the North west
					trow = row + 1;//a
					tcol = col - 1;
					break;




				}


				cnt[i] = 0; flag[i] = 0;



				//find the suitable coordinate
				if (cordinates[trow][tcol] == -1)
				{
					//If the coordinate is not occupied 
					for (tx = trow - 1; tx < trow + 2; tx++)
					{

						if (tx != trow)
							for (ty = tcol - 1; ty < tcol + 2; ty++)
							{
								if (cordinates[tx][ty] == c)
									cnt[i]++;
							}


						else
							for (ty = tcol - 2; ty < tcol + 4; ty += 2)
							{
								if (cordinates[tx][ty] == c)
									cnt[i]++;
							}
					}


				}
				else
				{
					//If the coordinate is already occupied then set the flag and do not count that moves
					flag[i] = 1;

				}

			}




			//find max cnt index

			xIn = 0;
			while (flag[xIn] == 1)
			{
				if (xIn < moves)
					xIn++;
			}

			if (xIn < moves)
			{
				//Find the maximum count of c in the neighbourhood of the present coordinate
				for (i = 0; i < moves; i++)
					if (cnt[i] > cnt[xIn] && flag[i] != 1)
					{
						xIn = i;

					}

				j = 0;
				for (i = xIn; i < moves; i++)
					if (cnt[i] == cnt[xIn] && flag[i] != 1)
					{
						//Find the maximum count of c and the coordinates with equal maximum count in the neighbourhood of the present coordinate
						posMov[j++] = i;
					}
					else
						posMov[i] = -1;

				r = rand() % j;


				//Choose the possible move using random function
				switch (posMov[r])
				{

				case 0:	//next move is to the east
					col = col + 2;
					nxtMov = 'E';
					break;

				case 1: //next move is to the west
					col = col - 2;
					nxtMov = 'W';
					break;

				case 2: //next move is to the south west
					row = row - 1;
					col = col - 1;
					nxtMov = 'x';
					break;

				case 3: //next move is to the north east
					row = row + 1;
					col = col + 1;
					nxtMov = 'y';
					break;

				case 4: //next move is to the south east
					row = row - 1;
					col = col + 1;
					nxtMov = 'z';
					break;

				case 5: //next move is to the north west
					row = row + 1;
					col = col - 1;
					nxtMov = 'a';
					break;

				}

				//Set the coordinate value with c
				cordinates[row][col] = str[strIndex] - '0';

				//Set the direction value with next move choosen
				last[k]->nxtMov = nxtMov;
				direction[last[k]->x + MAX - 1][last[k]->y + 2 * (MAX - 1)] = nxtMov;

				// PointsList:add(ithPoint)
				insert_node(row - MAX + 1, col - (2 * MAX) + 2, cordinates[row][col]);//,nxtMov);
				last[k]->index = strIndex;


				//Set the outline of the coordinates
				if (minRow > row)
					minRow = row;
				if (minCol > col)
					minCol = col;
				if (maxRow < row)
					maxRow = row;
				if (maxCol < col)
					maxCol = col;
				if (str[strIndex] == '1' && str[strIndex + 1] != '1' && str[strIndex + 2] == '1')
				{
					if (cordinates[row - 1][col - 1] == 1 && cordinates[row - 1][col + 1] == -1 && cordinates[row - 2][col] == -1)
					{
						for (a = 1; a <= 2; a++)
						{
							if (a == 1)
							{
								row = row - 1;
								col = col + 1;
								nxtMov = 'z';
							}
							else
							{
								row = row - 1;
								col = col - 1;
								nxtMov = 'x';

							}
							//Set the coordinate value with c
							cordinates[row][col] = str[strIndex + a] - '0';

							//Set the direction value with next move choosen
							last[k]->nxtMov = nxtMov;
							direction[last[k]->x + MAX - 1][last[k]->y + 2 * (MAX - 1)] = nxtMov;

							// PointsList:add(ithPoint)
							insert_node(row - MAX + 1, col - (2 * MAX) + 2, cordinates[row][col]);//,nxtMov);
							last[k]->index = strIndex + a;


							//Set the outline of the coordinates
							if (minRow > row)
								minRow = row;
							if (minCol > col)
								minCol = col;
							if (maxRow < row)
								maxRow = row;
							if (maxCol < col)
								maxCol = col;
						}
						strIndex++;
					}
					else if (cordinates[row - 1][col + 1] == 1 && cordinates[row + 1][col + 1] == -1 && cordinates[row][col + 2] == -1)
					{
						for (a = 1; a <= 2; a++)
						{
							if (a == 1)
							{
								row = row + 1;
								col = col + 1;
								nxtMov = 'y';
							}
							else
							{
								row = row - 1;
								col = col + 1;
								nxtMov = 'z';

							}
							//Set the coordinate value with c
							cordinates[row][col] = str[strIndex + a] - '0';

							//Set the direction value with next move choosen
							last[k]->nxtMov = nxtMov;
							direction[last[k]->x + MAX - 1][last[k]->y + 2 * (MAX - 1)] = nxtMov;

							// PointsList:add(ithPoint)
							insert_node(row - MAX + 1, col - (2 * MAX) + 2, cordinates[row][col]);//,nxtMov);
							last[k]->index = strIndex + a;


							//Set the outline of the coordinates
							if (minRow > row)
								minRow = row;
							if (minCol > col)
								minCol = col;
							if (maxRow < row)
								maxRow = row;
							if (maxCol < col)
								maxCol = col;
						}
						strIndex++;
					}

				}
			}
			else
			{
				//Not a favourable move. 
				//Further moves not possible
				first[k] = NULL;
				break;
			}


		}

		//Set the last node of the result sequence's direction value
		last[k]->nxtMov = 'H';
		direction[row][col] = 'H';



		if (strIndex < strlen(str))
		{	//Not a favourable move. 
			//Further moves not possible

			Energy[k].HEV = -1;
			//	Energy[k].FEV=-1;
		}
		else
		{
			//find theenergy variation value for a favourable move
			Energy[k].HEV = 0;
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

	k = 0;

	//Display the best sequence
	result();

	Efinal[l].HEV = Energy[k].HEV;
	//Increment the index of the array storing the index  of the best sequence 
	l++;

}

void procedureSquare(int Case, int e)
{
	//Function for performing the fold


	short int i, j, row, col, trow, tcol, tx, ty, xIn, r, posMov[12], c;
	char nxtMov;
	short int cnt[12], flag[12];
	int strIndex;
	k = 0;
	start = clock();
	while (k < populationSize)
	{
		first[k] = NULL; last[k] = NULL;


		//Initialization of coordinates and direction
		for (i = 0; i < (2 * MAX); i++)
			for (j = 0; j < (4 * MAX); j++)
			{
				cordinates[i][j] = -1;
				direction[i][j] = 'H';

			}



		//Initialization
		//startP oint = latticeCenter

		row = MAX - 1;
		col = (2 * MAX) - 2;
		cordinates[row][col] = str[0] - '0';
		minCol = col;

		// PointsList:add(startPoint)
		insert_node(row - MAX + 1, col - (2 * MAX) + 2, cordinates[row][col]);



		//secondP oint = eastNeighbour(startPoint)
		nxtMov = 'E';
		last[k]->nxtMov = nxtMov;
		last[k]->index = 0;
		direction[row][col] = nxtMov;
		col = col + 1;
		cordinates[row][col] = str[1] - '0';

		// PointsList:add(secondPoint)
		insert_node(row - MAX + 1, col - (2 * MAX) + 2, cordinates[row][col]);
		last[k]->index = 1;
		minRow = maxRow = row;
		maxCol = col;


		for (strIndex = 2; strIndex < strlen(str); strIndex++)
		{

			i = 0;


			//Initialize the c value
			switch (Case)
			{
			case 1:	//case for counted 0 and 1 value

				if (str[strIndex] == '1')
					c = 1;
				if (str[strIndex] == '0')
					c = 0;
				if (str[strIndex] == '2')
					c = 2;
				if (str[strIndex] == '3')
					c = 3;
				break;

			case 0://case for counted 1 and randomized 0 value

				if (str[strIndex] == '1')
					c = 1;
				else
					c = -2;
				break;
			}




			//For finding the possible moves from the current coordinates(row,col)

			for (i = 0; i < moves; i++)
			{
				switch (i)
				{
				case 0://next move is to the east
					trow = row;
					tcol = col + 1;
					break;

				case 1://next move is to the west
					trow = row;
					tcol = col - 1;
					break;

				case 2: //next move is to the south west
					trow = row - 1;//x
					tcol = col;
					break;

				case 3:	//next move is to the North east
					trow = row + 1;//y
					tcol = col;
					break;
				}

				cnt[i] = 0; flag[i] = 0;


				//find the suitable coordinate
				if (cordinates[trow][tcol] == -1)
				{
					//If the coordinate is not occupied 
					switch (e)
					{
					case 1:for (tx = trow - 1; tx < trow + 2; tx++)
					{

						for (ty = tcol - 1; ty < tcol + 2; ty++)
						{
							if (cordinates[tx][ty] == c)
								cnt[i]++;
						}
					}
						  break;
					case 2:

						for (tx = trow - 2; tx <= trow + 2; tx++)
						{
							for (ty = tcol - 1; ty < tcol + 2; ty++)
							{
								if (cordinates[tx][ty] == c)
									cnt[i]++;
							}

						}
						break;

					}
				}
				else
				{
					//If the coordinate is already occupied then set the flag and do not count that moves
					flag[i] = 1;

				}

			}




			//find max cnt index

			xIn = 0;
			while (flag[xIn] == 1)
			{
				if (xIn < moves)
					xIn++;
			}

			if (xIn < moves)
			{
				//Find the maximum count of c in the neighbourhood of the present coordinate
				for (i = 0; i < moves; i++)
					if (cnt[i] > cnt[xIn] && flag[i] != 1)
					{
						xIn = i;

					}

				j = 0;
				for (i = xIn; i < moves; i++)
					if (cnt[i] == cnt[xIn] && flag[i] != 1)
					{
						//Find the maximum count of c and the coordinates with equal maximum count in the neighbourhood of the present coordinate
						posMov[j++] = i;
					}
					else
						posMov[i] = -1;

				r = rand() % j;


				//Choose the possible move using random function
				switch (posMov[r])
				{

				case 0:	//next move is to the east
					col = col + 1;
					nxtMov = 'E';
					break;

				case 1: //next move is to the west
					col = col - 1;
					nxtMov = 'W';
					break;

				case 2: //next move is to the south
					row = row - 1;
					col = col;
					nxtMov = 'S';
					break;

				case 3: //next move is to the north
					row = row + 1;
					col = col;
					nxtMov = 'N';
					break;



				}
				//Set the coordinate value with c
				cordinates[row][col] = str[strIndex] - '0';

				//Set the direction value with next move choosen
				last[k]->nxtMov = nxtMov;
				direction[last[k]->x + MAX - 1][last[k]->y + 2 * MAX - 2] = nxtMov;

				// PointsList:add(ithPoint)
				insert_node(row - MAX + 1, col - (2 * MAX) + 2, cordinates[row][col]);//,nxtMov);
				last[k]->index = strIndex;


				//Set the outline of the coordinates
				if (minRow > row)
					minRow = row;
				if (minCol > col)
					minCol = col;
				if (maxRow < row)
					maxRow = row;
				if (maxCol < col)
					maxCol = col;
			}
			else
			{
				//Not a favourable move. 
				//Further moves not possible
				first[k] = NULL;
				break;
			}

		}

		//Set the last node of the result sequence's direction value
		last[k]->nxtMov = 'H';
		direction[row][col] = 'H';


		if (strIndex < strlen(str))
		{	//Not a favourable move. 
			//Further moves not possible

			Energy[k].HEV = -1;
			//Energy[k].FEV=-1;
		}
		else
		{
			//find theenergy variation value for a favourable move
			Energy[k].HEV = 0;
			//Energy[k].FEV=0;
			calculateEnergy();
		}


		k++;
		end = clock();
		spent = (end - start) / CLOCKS_PER_SEC;
	}

	//Find the index of the best sequence
//k=findMaxVariation(populationSize,Energy);
/*

	printf("\nThe maximumenergy variation Path\n");*/

	printf("\n time taken is %f  second", spent);

	//Sort the HEV structure so that the top 10 sequences based on theenergy variation value into a file
	sortEnergySt();
	k = 0;
	result();

	//add the index of the best sequence to an structure

	Efinal[l].HEV = Energy[k].HEV;

	//Increment the index of the array storing the index  of the best sequence 
	l++;

}
#pragma endregion
