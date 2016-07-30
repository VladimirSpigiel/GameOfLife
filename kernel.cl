#include "Constants.h"

#define GRID_BEFORE(Y, X) gridBefore[(Y) * width + (X)]
#define GRID_AFTER(Y, X) gridAfter[(Y) * width + (X)]


__kernel void gameStep (__global int* gridBefore, __global int* gridAfter, const int width, const int height) {

	/* GET GLOBAL LOCATION */
	__private int x = get_global_id(0);
	__private int y = get_global_id(1);

	/* ARRAY CONTAINS CELLS AROUND US */
	__private Cell cellsAround[9];

	/* DEFAULT AFFECTION */
	__private Cell affect = DEAD_CELL;

	/* COUNTER TO DECIDE WHICH AFFECTION IS NEEDED WITH THE RULES */
	__private int aliveCounter = 0;

	
	
	/* RETRIEVE ALL CELLS AROUND THE ONE WE ARE */
	for (__private int j = -1; j <= 1; j++) {
		for (__private int i = -1; i <= 1; i++) {
			
			if ((y + j) >= height || (y + j) < 0 || (x + i) >= width || (x + i) < 0){
				affect = DEAD_CELL;
			}
			else
				affect = GRID_BEFORE(y + j, x + i);

			cellsAround[(j+1)*3 + (i + 1) ] = affect;
		
		}
	}
	
	/* COUNT HOW MANY CELLS ARE ALIVE AROUND US */
	for (__private int j = 0; j < 3; j++){
		for (__private int i = 0; i < 3; i++){

			if (j == 1 && i == 1) continue;

			if (cellsAround[j * 3 + i] == ALIVE_CELL){
				aliveCounter++;
			}
		}
	}
	
	/* RULES ARE :
		IF THERE ARE EXACTLY 3 CELLS ALIVE AND IF WE'RE DEAD : Make us alive
		IF THERE ARE LESS THAN 2 OR MORE THAN 3 CELLS ALIVE AROUND US AND IF WE'RE ALIVE : Make us dead
	*/

	GRID_AFTER(y, x) = cellsAround[4];

	if (cellsAround[4] == DEAD_CELL){
		if(aliveCounter == 3) 
			GRID_AFTER(y, x) = ALIVE_CELL;
	}
	else {
		if(aliveCounter != 2 && aliveCounter != 3) 
			GRID_AFTER(y, x) = DEAD_CELL;
	}
	

}