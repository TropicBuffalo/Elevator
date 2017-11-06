#include <stdio.h>
#include <mpi.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char** argv) {
	int rank;
	int root = 0;
	//Variables for elevator movement
	bool goUp = true;
	int cnt = 0;
	int floorNr;
	
	//Variables for Gathering info about the people from the processors to the elevator
	int people[4] = {0};
	int allPeople[36] = {0};
	int finalPeople[8][4] = {0};
	
	t1 = MPI_Wtime();
	
	MPI_Status Stat;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	//The people going into the elevator
	//people[0] = What their rank is,      people[1] = Floor they are on, 
	//people[2] = Floor they are going to, people[3] = If they are inside the elevator? Maybe not needed
	if(rank > 0){
		int people[4] = {rank,0,0,0};
		
		//For loop to mirror the loop in the elevator
		for(int i = 0; i<12; i++) {
			//Receive which floor the elevator is on
			MPI_Bcast(&floorNr, 1, MPI_INT, root, MPI_COMM_WORLD);
			//While they are not in the elevator
			while(people[1] != people[2]) {
				//If elevator is on same floor and less than 2 people onboard
				if(people[0] == data[0] && data[1] < 2) {
					people[2] = 1;
				}
			} 
			//While they are inside the elevator
			while(people[1] == people[2]) {
				//Get out of the elevator if they have reached their floor
				if(people[0] == people[1]) {
					//Sleep command here or when the elevator sends the update?
					//Exit the elevator
					elevator[1]--;
					//Change floors when people reach their destination
					if (people[1] > 1) people[1]--;
					else {
						people[1]++;
					}
				}
			}
		}
	}
	
	//Gather the people array from all the processors into allPeople
	MPI_Gather(&people[0], 4, MPI_INT, allPeople, 4, MPI_INT, 0, MPI_COMM_WORLD);
    
	if(rank == 0) {
		//Copy the 1D allPeople into the 2D finalPeople to make things "easier", need to ignore the first row
		memcpy(finalPeople, allPeople, 36* sizeof(int));
		
		/* For loop to test if memcpy works
		for(int i=0; i<8;i++) {
			for(int j=0;j<4;j++) {
				printf("finalPeople[%d][%d] = %d\n",i,j,finalPeople[i][j]);
			}
		}
		*/
		for(int i =0;i < 12;i++) {
			if(goUp) {
				cnt++;
				sleep(2);
			}
			else{
				cnt--;
				sleep(2);
			}
			printf("The elevator is on this floor: %d\n", cnt);
			MPI_Bcast(&cnt,1,MPI_INT, root, MPI_COMM_WORLD);
			if(cnt==3) {goUp =false;}
			if(cnt==0) {goUp = true;}
		}
    }
	
	MPI_Finalize();
	return 0;
}