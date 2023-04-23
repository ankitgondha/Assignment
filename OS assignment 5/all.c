#include "stdio.h"
#include "stdlib.h"
#define N 100

struct process
{
   int process_id;
   int arrival_time;
   int burst_time;
   int waiting_time;
   int turn_around_time;
   int remain_time;
};

int queue[N];
int front = 0, rear = 0;
struct process proc[N];

void push(int process_id)
{
   queue[rear] = process_id;
   rear = (rear + 1) % N;
}

int pop()
{
   if (front == rear)
      return -1;

   int return_position = queue[front];
   front = (front + 1) % N;
   return return_position;
}

void FCFS()
{
   int n, i;
   printf("Number of processes: ");
   scanf("%d", &n);
   struct process proc[n];
   for (i = 0; i < n; i++)
   {
      printf("\n");
      printf("Arrival time for process%d: ", i + 1);
      scanf("%d", &proc[i].arrival_time);
      printf("Burst time for process%d: ", i + 1);
      scanf("%d", &proc[i].burst_time);
      proc[i].process_id = i + 1;
   }
   int service_time[n];
   service_time[0] = 0;
   proc[0].waiting_time = 0;

   for (i = 1; i < n; i++)
   {
      service_time[i] = service_time[i - 1] + proc[i - 1].burst_time;
      proc[i].waiting_time = service_time[i] - proc[i].arrival_time;

      if (proc[i].waiting_time < 0)
         proc[i].waiting_time = 0;
   }

   for (i = 0; i < n; i++)
   {
      proc[i].turn_around_time = proc[i].burst_time + proc[i].waiting_time;
   }
   printf("\n\n");
   printf("Process\tBurst Time\tArrival Time\tWaiting Time\tTurn-Around Time\tCompletion Time\n");
   int total_waiting_time = 0, total_turn_around_time = 0;
   for (i = 0; i < n; i++)
   {
      total_waiting_time += proc[i].waiting_time;
      total_turn_around_time += proc[i].turn_around_time;

      int completion_time = proc[i].turn_around_time + proc[i].arrival_time;

      printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].process_id, proc[i].burst_time, proc[i].arrival_time, proc[i].waiting_time, proc[i].turn_around_time, completion_time);
   }
   printf("Average waiting time: %f\n", (float)total_waiting_time / n);
   printf("Average turn around time: %f\n", (float)total_turn_around_time / n);
}

void SJF()
{
   int n, i, j;
   int bt = 0, k = 1, tat = 0, sum = 0, min;
   printf("Number of processes: ");
   scanf("%d", &n);
   struct process proc[n], temp;
   for (i = 0; i < n; i++)
   {
      printf("\n");
      printf("Arrival time for process%d: ", i + 1);
      scanf("%d", &proc[i].arrival_time);
      printf("Burst time for process%d: ", i + 1);
      scanf("%d", &proc[i].burst_time);
      proc[i].remain_time = proc[i].burst_time;
      proc[i].process_id = i + 1;
   }
   int quantum_time, flag = 0;
   printf("Time quantum: ");
   scanf("%d", &quantum_time);
   int processes_remaining = n;

   for (i = 0; i < n; i++)
   {
      for (j = 0; j < n; j++)
      {
         if (proc[i].arrival_time < proc[j].arrival_time)
         {
            temp = proc[j];
            proc[j] = proc[i];
            proc[i] = temp;
         }
      }
   }
   int wait_time_total = 0, totalExecutionTime = 0, turn_around_time_total = 0;
   i = 0;
   while (processes_remaining != 0)
   {
      if (proc[i].remain_time <= quantum_time && proc[i].remain_time > 0)
      {
         totalExecutionTime += proc[i].remain_time;
         proc[i].remain_time = 0;
         flag = 1;
      }
      else if (proc[i].remain_time > 0)
      {
         proc[i].remain_time -= quantum_time;
         totalExecutionTime += quantum_time;
      }
      if (flag == 1 && proc[i].remain_time == 0)
      {
         proc[i].waiting_time = totalExecutionTime - proc[i].arrival_time - proc[i].burst_time;
         wait_time_total += proc[i].waiting_time;

         proc[i].turn_around_time = totalExecutionTime - proc[i].arrival_time;
         turn_around_time_total += proc[i].turn_around_time;
         flag = 0;
         processes_remaining--;
      }

      if (i == n - 1)
      {
         i = 0;
      }
      else if (proc[i + 1].arrival_time <= totalExecutionTime)
         i++;
      else
         i = 0;
   }
   printf("Process\tBurst Time\tArrival Time\tWaiting Time\tTurn-Around Time\n");

   for (i = 0; i < n; i++)
   {

      printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].process_id, proc[i].burst_time, proc[i].arrival_time, proc[i].waiting_time, proc[i].turn_around_time);
   }
   printf("Average waiting time: %f\n", (float)wait_time_total / n);
   printf("Average turn around time: %f\n", (float)turn_around_time_total / n);
}

void SRTF()
{
   int n, i, j;
   int bt = 0, k = 1, tat = 0, sum = 0, min;
   printf("Enter number of processes: ");
   scanf("%d", &n);
   struct process proc[n], temp;
   for (i = 0; i < n; i++)
   {
      printf("\n");
      printf("Enter arrival time for process%d: ", i + 1);
      scanf("%d", &proc[i].arrival_time);
      printf("Enter burst time for process%d: ", i + 1);
      scanf("%d", &proc[i].burst_time);
      proc[i].process_id = i + 1;
   }

   for (i = 0; i < n; i++)
   {
      for (j = 0; j < n; j++)
      {
         if (proc[i].arrival_time < proc[j].arrival_time)
         {
            temp = proc[j];
            proc[j] = proc[i];
            proc[i] = temp;
         }
      }
   }

   for (i = 0; i < n; i++)
   {
      bt += proc[i].burst_time;
      min = proc[k].burst_time;
      for (j = k; j < n; j++)
      {
         if (bt >= proc[j].arrival_time && proc[j].burst_time < min)
         {
            temp = proc[k];
            proc[k] = proc[j];
            proc[j] = temp;
         }
      }
      k++;
   }
   proc[0].waiting_time = 0;
   int wait_time_total = 0;
   int turn_around_time_total = 0;
   for (i = 1; i < n; i++)
   {
      sum += proc[i - 1].burst_time;
      proc[i].waiting_time = sum - proc[i].arrival_time;
      wait_time_total += proc[i].waiting_time;
   }
   for (i = 0; i < n; i++)
   {
      tat += proc[i].burst_time;
      proc[i].turn_around_time = tat - proc[i].arrival_time;
      turn_around_time_total += proc[i].turn_around_time;
   }
   printf("Process\tBurst Time\tArrival Time\tWaiting Time\tTurn-Around Time\n");

   for (i = 0; i < n; i++)
   {

      printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].process_id, proc[i].burst_time, proc[i].arrival_time, proc[i].waiting_time, proc[i].turn_around_time);
   }
   printf("Average waiting time: %f\n", (float)wait_time_total / n);
   printf("Average turn around time: %f\n", (float)turn_around_time_total / n);
}

void Round_Robin()
{
   float wait_time_total = 0.0, tat = 0.0;
   int n, time_quantum;
   printf("Enter the number of processes: ");
   scanf("%d", &n);

   for (int i = 0; i < n; i++)
   {
      printf("Enter the arrival time for the process%d: ", i + 1);
      scanf("%d", &proc[i].arrival_time);
      printf("Enter the burst time for the process%d: ", i + 1);
      scanf("%d", &proc[i].burst_time);
      proc[i].process_id = i + 1;
      proc[i].remain_time = proc[i].burst_time;
   }
   printf("Enter time quantum: ");
   scanf("%d", &time_quantum);

   int time = 0;
   int processes_left = n;
   int position = -1;
   int local_time = 0;

   for (int j = 0; j < n; j++)
      if (proc[j].arrival_time == time)
         push(j);

   while (processes_left)
   {
      if (local_time == 0)
      {
         if (position != -1)
            push(position);

         position = pop();
      }

      for (int i = 0; i < n; i++)
      {
         if (proc[i].arrival_time > time)
            continue;
         if (i == position)
            continue;
         if (proc[i].remain_time == 0)
            continue;

         proc[i].waiting_time++;
         proc[i].turn_around_time++;
      }

      if (position != -1)
      {
         proc[position].remain_time--;
         proc[position].turn_around_time++;

         if (proc[position].remain_time == 0)
         {
            processes_left--;
            local_time = -1;
            position = -1;
         }
      }
      else
         local_time = -1;

      time++;
      local_time = (local_time + 1) % time_quantum;
      for (int j = 0; j < n; j++)
         if (proc[j].arrival_time == time)
            push(j);
   }

   printf("\n");

   printf("Process\t\tArrival Time\tBurst Time\tWaiting time\tTurn around time\n");
   for (int i = 0; i < n; i++)
   {
      printf("%d\t\t%d\t\t", proc[i].process_id, proc[i].arrival_time);
      printf("%d\t\t%d\t\t%d\n", proc[i].burst_time, proc[i].waiting_time, proc[i].turn_around_time);

      tat += proc[i].turn_around_time;
      wait_time_total += proc[i].waiting_time;
   }

   tat = tat / (1.0 * n);
   wait_time_total = wait_time_total / (1.0 * n);

   printf("\nAverage waiting time     : %f", wait_time_total);
   printf("\nAverage turn around time : %f\n", tat);
}



int main()
{
   int number;

   int flag = 1;

   while (flag == 1)
   {
      printf("******************************************************************************\n");
      printf("\n(1) FCFS  \n(2) SJF \n(3)SRTF  \n(4)Round Robin  \n(5) Priority \n(6)exit \n");
      printf("******************************************************************************\n");
      scanf("%d", &number);
      switch (number)
      {
      case 1:
         FCFS();
         break;

      case 2:
         SJF();
         break;

      case 3:
         SRTF();
         break;

      case 4:
         Round_Robin();
         break;

      case 6:
         flag = 0;
         break;
         
      default:
         break;
      }
   }
}