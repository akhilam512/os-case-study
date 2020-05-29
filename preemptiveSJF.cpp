#include <bits/stdc++.h>
#include <limits.h>
using namespace std;

struct Process {    
    int pid;
    int burstT;
    int arrivalT;    
};

void calcWaitingTime(Process[], int, int[]);
void calcTurnAroundTime(Process[], int, int[], int[]);
void calcAverageTime(Process[], int n);

int main() 
{
    int n;
    cout << " ================= INPUT DATA =================== \n ";
    cout << " Enter number of processes (n) : ";
    cin >> n;
    cout << "\n ======================== \n ";

    Process proc[n];
    for(int i = 0; i < n; i++) {
        proc[i].pid = i+1;
        cout << "   Enter Details for Process ID: " << proc[i].pid << endl;
        cout << "Enter Burst Time: ";
        cin >> proc[i].burstT;
        cout << "Enter Arrival Time: ";
        cin >> proc[i].arrivalT;
        cout << "\n ======================== \n ";
    }

    calcAverageTime(proc, n);
    return 0;
} 

void calcWaitingTime(Process proc[], int n, int wt[]) 
{
    int count = 0, t = 0, min = INT_MAX, shortest = 0, finishTime, rt[n];
    bool flag = false;

    for (int i = 0; i < n; i++)
        rt[i] = proc[i].burstT;

    while (count != n) {
        for (int j = 0; j < n; j++) {
            if ((proc[j].arrivalT <= t) && (rt[j] < min) && rt[j] > 0) {
                flag = true;
                min = rt[j];
                shortest = j;
            }
        }

        if (!flag) {
            t++;
            continue;
        }

        rt[shortest]--;
        min = rt[shortest];

        if (min == 0)
            min = INT_MAX;

        if (rt[shortest] == 0) {
            count++;
            flag = false;
            finishTime = t + 1;
            wt[shortest] = finishTime - proc[shortest].burstT - proc[shortest].arrivalT;

            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }

        t++; 
    } 
} 
  
void calcTurnAroundTime(Process proc[], int n, int wt[], int tat[]) 
{ 
    for (int i = 0; i < n; i++)
        tat[i] = proc[i].burstT + wt[i];
} 

void calcAverageTime(Process proc[], int n) 
{ 
    int wt[n], tat[n], total_wt = 0, total_tat = 0;
    calcWaitingTime(proc, n, wt);
    calcTurnAroundTime(proc, n, wt, tat);
    cout << " \n =================  OUTPUT  =================== \n ";
    cout << "-------------------------------------------------------------\n";
    cout << "PID"
        << "\t|  Burst Time"
        << "\t|  Waiting Time"
        << "\t|  Turn Around Time |\n";
  
    cout << "-------------------------------------------------------------\n";
    for (int i = 0; i < n; i++) {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        cout << " " << proc[i].pid << "\t|\t"
            << proc[i].burstT << "\t|\t " << wt[i]   
            << "\t|\t " << tat[i] << "\t    |" << endl;
    }
    cout << "-------------------------------------------------------------\n";
    cout << "\n \t \t Average Waiting Time = " << (float)total_wt / (float)n << endl;
    cout << "-------------------------------------------------------------\n";
    cout << "\n \t \tAverage Turn Around Time = " << (float)total_tat / (float)n << endl;
    cout << "-------------------------------------------------------------\n" << endl;
} 
