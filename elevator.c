#include <stdio.h>
#include <mpi.h>
#include <unistd.h>
#include <stdbool.h>

int main(int argc, char** argv) {
	int rank, tag, dest, source;
	t1 = MPI_Wtime();
	int elevator[2] = {0,0};
	
	//For loop for elevator so it goes up and down
	bool goUp = true;
	int cnt = 0;
	
	MPI_Status Stat;
	
	//
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	//The elevator
	//elevator[0] = current floor, elevator[1] = how many people inside
	
	if(rank == 0) {
		//This for loop can be changed with while(true) potentially to make the elevator just go on.. forever
		//MPI_Gather to get all the data from everyone
		//Ping to everyone which floor the elevator is on
		//Data from people :: Which rank they are, where they are, where they are going
		for(int i = 0; i<12; i++) {
			if(goUP) {
				cnt++;
				MPI_Bcast(cnt,1, MPI_INT, 0, MPI_COMM_WORLD);
			}
			else {
				cnt--;
				MPI_Bcast(cnt,1, MPI_INT, 0, MPI_COMM_WORLD);
			}
			printf("The elevator is on this floor: %d\n")
			if(cnt == 3) {goUp = false;}
			if(cnt == 0) {goUp = true;}
		}
		
		
		
		for(;;){
			//Get data from everyone and put it into an array, go down the array or find people on floor it stops on?
			MPI_Recv(&people[i][0],3,MPI_INT,source,tag,MPI_COMM_WORLD);
			
			
			
			//Send out the guy out after searching the people array
			MPI_Send(,MPI_COMM_WORLD);
		}
	}

	//The people going into the elevator
	//people[0] = Floor they are on, people[1] = Floor they are goign to, people[2] = if they are inside elevator
	if (rank > 0) {
		int people[3] = {0,0,0};
		int data[2];
		source = 0;
		tag = rank;
		
		//People sending their data to the elevator
		MPI_Send(&people,3,MPI_INT,0, tag,MPI_COMM_WORLD);
		
		//While they are not in the elevator
		while(people[2] == 0) {
			//Listen for the elevator updates
			MPI_Recv(&data[0], 2, MPI_INT, source,MPI_COMM_WORLD);
			//If elevator is on same floor and less than 2 people onboard
		 	if(people[0] == data[0] && data[1] < 2) {
				people[2] = 1;
			}
		} 
		
		//While they are inside the elevator
		while(people[2] == 1) {
			//Listen for the elevator updates
			MPI_Recv();
			//Get out of the elevator if they have reached their floor
			if(people[0] == people[1]) {
				//Sleep command here or when the elevator sends the update?
				//Exit the elevator
				elevator[1]--;
			}
		}
	}
	MPI_Finalize();
	return 0;
}
	
	
	
	
	
	
	
	
	
	
	
	
}