#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
void main()
{

	float arival_time[3]={0.0,0.4,1.0};
	int burst_time[3]={8,4,1};
	float waiting_time[3];
	int option;
	float sum, avg_turnaround_time;
	int cpu[3]={1,2,3};
	float turnaround_time[3];
	int cpu_allocate[4];
	cpu_allocate[0]=0;
	sum=0;
	program:
	system("clear");
	printf("\n\n\n****************Question***************\n\n");
	printf("Process\tArrival Time\tBurst Time\n");
        for(int i=1; i<=3; i++)
        {
                printf("P%d\t%.1f\t\t%d\n",cpu[i-1],arival_time[i-1],burst_time[i-1]);
        }
	printf("****************Solution***************\n\n");
	printf("1. Calculate Average Turnaround Time With The FCFS Scheduling Algorithm.");
	printf("\n2. Calculate Average Turnaround Time With The SJF Scheduling Algorithm.");
	printf("\n3. Calculate Average Turnaround Time if CPU is Left Idle For The First 1 Unit, Using SJF Scheduling");


	printf("\n\nChoose Any Option:\n\t\t ");
	scanf("%d",&option);
	switch(option)
	{
		case 1:
		{
			//FCFS
		
			printf("\n\n\n****************Question***************\n\n");
		        printf("Process\tArrival Time\tBurst Time\n");

			for(int i=1; i<=3; i++)
			{
				printf("P%d\t%.1f\t\t%d\n",cpu[i-1],arival_time[i-1],burst_time[i-1]);
			}
			printf("****************Solution***************\n\n");


			for(int i=1; i<=3; i++)
			{
				cpu_allocate[i]=cpu_allocate[i-1]+burst_time[i-1];
				waiting_time[i-1]=cpu_allocate[i-1]-arival_time[i-1];
				turnaround_time[i-1]=waiting_time[i-1]+burst_time[i-1];
			}
			printf("Process\tArrival Time\tBrust Time\tWaiting Time\tTurnaround Time\n");

			for(int i=0; i<3; i++)
        		{
				printf("P%d\t%.1f\t\t%d\t\t%.1f\t\t%.1f\n",cpu[i],arival_time[i],burst_time[i],waiting_time[i],turnaround_time[i]);
        			sum=sum+turnaround_time[i];
			}
			printf("\n\n\t\tAverage Turnaround Time: %.2f\n\n\n",(sum/3));

			break;
		}
		case 2:
		{
			//SJF
			printf("\n\n\n****************Question***************\n\n");
                        printf("Process\tArrival Time\tBurst Time\n");

                        for(int i=1; i<=3; i++)
                        {
                                printf("P%d\t%.1f\t\t%d\n",cpu[i-1],arival_time[i-1],burst_time[i-1]);
                        }
                        printf("****************Solution***************\n\n");

			for(int i=0; i<3-1; i++)
			{

				if((burst_time[i]>burst_time[i+1]) && arival_time[i]!=0.0)
				{
					float temp=arival_time[i];
					arival_time[i]=arival_time[i+1];
					arival_time[i+1]=temp;


					float temp_burst=burst_time[i];
					burst_time[i]=burst_time[i+1];
					burst_time[i+1]=temp_burst;


					int temp_cpu=cpu[i];
					cpu[i]=cpu[i+1];
					cpu[i+1]=temp_cpu;
				}
			}

			for(int i=1; i<=3; i++)
        		{
                		cpu_allocate[i]=cpu_allocate[i-1]+burst_time[i-1];
                		waiting_time[i-1]=cpu_allocate[i-1]-arival_time[i-1];
                		turnaround_time[i-1]=waiting_time[i-1]+burst_time[i-1];
        		}
        		printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");

        		for(int i=0; i<3; i++)
        		{
                		printf("P%d\t%.1f\t\t%d\t\t%.1f\t\t%.1f\n",cpu[i],arival_time[i],burst_time[i],waiting_time[i],turnaround_time[i]);
    		    		sum=sum+turnaround_time[i];
                        }
                        printf("\n\n\t\tAverage Turnaround Time: %.2f\n\n\n",(sum/3));

			break;
		}
		case 3:
		{
			int idle_time=1;
			printf("\n\n\n****************Question***************\n\n");
                        printf("Process\tArrival Time\tBurst Time\n");

                        for(int i=1; i<=3; i++)
                        {
                                printf("P%d\t%.1f\t\t%d\n",cpu[i-1],arival_time[i-1],burst_time[i-1]);
                        }
                        printf("****************Solution***************\n\n");


			for(int j=0; j<=3-2; j++)
			{
				for(int i=0; i<3-1; i++)
        			{

                			if((burst_time[i]>burst_time[i+1]))
                			{
                       				float temp=arival_time[i];
                       				arival_time[i]=arival_time[i+1];
                       				arival_time[i+1]=temp;


	                        		float temp_burst=burst_time[i];
        	               			burst_time[i]=burst_time[i+1];
                	      	 		burst_time[i+1]=temp_burst;


		                	        int temp_cpu=cpu[i];
        		       		        cpu[i]=cpu[i+1];
						cpu[i+1]=temp_cpu;
               				}
        			}
			}

   			for(int i=1; i<=3; i++)
        		{
                		cpu_allocate[i]=cpu_allocate[i-1]+burst_time[i-1];
                		waiting_time[i-1]=cpu_allocate[i-1]-arival_time[i-1]+idle_time;
                		turnaround_time[i-1]=waiting_time[i-1]+burst_time[i-1];
        		}
        		printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");

        		for(int i=0; i<3; i++)
        		{
                		printf("P%d\t%.1f\t\t%d\t\t%.1f\t\t%.1f\n",cpu[i],arival_time[i],burst_time[i],waiting_time[i],turnaround_time[i]);
	        		sum=sum+turnaround_time[i];
                        }
                        printf("\n\n\t\tAverage Turnaround Time: %.2f\n\n\n",(sum/3));


			break;
		}
		default:
		{
			printf("Invalid Input!!");
		}
	}
	char dec[3];
	printf("Do You Want To Continue(Y/N))?");
	scanf("%s",dec);
	printf("%s",dec);
	if(dec[0]=='y' || dec[0]=='Y')
	{
		goto program;
	}
	printf("Thank You!!!");

}

