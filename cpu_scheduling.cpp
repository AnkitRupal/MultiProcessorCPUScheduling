#include "bits/stdc++.h"

using namespace std;

class pcb
{
public:
   int arrival, burst, id, turn_around, waiting, priority;
   int flag = 0;
   void execute()
   {
       burst = burst - 1;
   }
   int fincheck()
   {
       if (burst == 0)
       {
           return 1;
       }
       return -1;
   }
   int readycheck(int time)
   {
       if (time == arrival)
       {
           return 1;
       }
       return -1;
   }
};
class processor
{
public:
   vector<pcb> processor_history;
   vector<int> ids;
};

void IO(void){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(NULL);
}

int main()
{
   IO();
   pcb null;
   processor proc;
   null.id = -1;
   null.burst = 1;
   int algo_id, total_processors, total_processes, time;
   vector<pcb> processlist;
   vector<pcb> readyqueue;
   vector<pcb> running;
   vector<pcb> terminated;
   vector<processor> processchart;
   vector<int> waiting_list;
   vector<int> ta_list;
   int avg_tt = 0;
   int avg_wt = 0;
   float placeholder;

//    cout << "Give Number of processors: ";
   cin >> total_processors;

//    cout << "Give Number of processes: ";
   cin >> total_processes;

   int arrival_times[total_processes];
   int burst_times[total_processes];
   int priority_list[total_processes];

//    cout << "Give arrival times of the processes: ";
   for (int i = 0; i < total_processes; i++)
   {
       cin >> arrival_times[i];
   }

//    cout << "Give burst times of the processes: ";
   for (int i = 0; i < total_processes; i++)
   {
       cin >> burst_times[i];
   }

//    cout << "Give priorities of the processes(lower number means higher priority): ";
   for (int i = 0; i < total_processes; i++)
   {
       cin >> priority_list[i];
   }

//    cout << "Input number based on scheduling algorithm to be used:" << endl
//         << "0:First Come, First Serve" << endl
//         << "1:Round Robin" << endl
//         << "2:Shortest Job First" << endl
//         << "3:Priority" << endl;
   cin >> algo_id;

   /*----------------------------------------------------------------------------------------------------------------------------------*/
   for (int i = 0; i < total_processes; i++)
   {
       processlist.push_back(null);
       processlist[i].id = i;
       processlist[i].arrival = arrival_times[i];
       processlist[i].burst = burst_times[i];
       processlist[i].priority = priority_list[i];
       processlist[i].waiting = 0;
       processlist[i].turn_around = 0;
   }
   for (int i = 0; i < total_processors; i++)
   {
       processchart.push_back(proc);
   }
   time = -1;
   for (int i = 0; i < total_processors; i++)
   {
       running.push_back(null);
   }
   while (terminated.size() != processlist.size())
   {
       time++;
       if (algo_id == 3)
       {
           for (int i = 0; i < processlist.size(); i++)
           {
               if (processlist[i].readycheck(time) > 0)
               {

                   if (readyqueue.size() == 0)
                   {
                       readyqueue.push_back(processlist[i]);
                   }
                   else if (processlist[i].priority > readyqueue[readyqueue.size() - 1].priority)
                   {
                       readyqueue.push_back(processlist[i]);
                   }

                   else
                   {
                       for (int j = 0; j < readyqueue.size(); j++)
                       {
                           if (readyqueue[j].priority > processlist[i].priority)
                           {
                               readyqueue.insert(readyqueue.begin() + j, processlist[i]);
                               break;
                           }
                           else if (j == (readyqueue.size() - 1))
                           {
                               readyqueue.push_back(processlist[i]);
                           }
                       }
                   }
               }
           }
       }
       else if (algo_id == 2)
       {
           for (int i = 0; i < processlist.size(); i++)
           {
               if (processlist[i].readycheck(time) > 0)
               {
                   if (readyqueue.size() == 0)
                   {
                       readyqueue.push_back(processlist[i]);
                   }
                   else if (processlist[i].burst > readyqueue[readyqueue.size() - 1].burst)
                   {
                       readyqueue.push_back(processlist[i]);
                   }

                   else
                   {
                       for (int j = 0; j < readyqueue.size(); j++)
                       {

                           if (processlist[i].burst < readyqueue[j].burst)
                           {
                               readyqueue.insert(readyqueue.begin() + j, processlist[i]);
                               break;
                           }
                           else if (j == (readyqueue.size() - 1))
                           {
                               readyqueue.push_back(processlist[i]);
                           }
                       }
                   }
               }
           }
       }
       else if (algo_id <= 1)
       {
           for (int i = 0; i < processlist.size(); i++)
           {
               if (processlist[i].readycheck(time) > 0)
               {
                   readyqueue.push_back(processlist[i]);
               }
           }
       }
       if (algo_id == 0 || algo_id >= 2)
       {
           for (int i = 0; i < running.size(); i++)
           {
               if (running[i].fincheck() > 0)
               {
                   if (running[i].id != -1)
                   {
                       terminated.push_back(running[i]);
                   }
                   running[i] = null;
               }
           }
       }
       else if (algo_id == 1)
       {
           for (int i = 0; i < running.size(); i++)
           {
               if (running[i].fincheck() > 0)
               {
                   if (running[i].id != -1)
                   {
                       terminated.push_back(running[i]);
                   }
                   running[i] = null;
               }
               else
               {
                   readyqueue.push_back(running[i]);
                   running[i] = null;
               }
           }
       }

       if (algo_id == 0 || algo_id >= 2)
       {
           for (int i = 0; i < running.size(); i++)
           {
               if (readyqueue.size() == 0)
               {
                   if (running[i].id == -1)
                   {
                       (processchart[i].processor_history).push_back(null);
                   }
                   else
                   {
                       (processchart[i].processor_history).push_back(running[i]);
                   }
               }
               else
               {
                   if (running[i].id == -1)
                   {
                       running[i] = readyqueue[0];
                       (processchart[i].processor_history).push_back(running[i]);
                       readyqueue.erase(readyqueue.begin() + 0);
                   }
                   else
                   {
                       (processchart[i].processor_history).push_back(running[i]);
                   }
               }
           }
       }
       else if (algo_id == 1)
       {
           for (int i = 0; i < running.size(); i++)
           {
               if (readyqueue.size() != 0)
               {
                   readyqueue[0].flag = readyqueue[0].flag + 1;

                   running[i] = readyqueue[0];
                   (processchart[i].processor_history).push_back(running[i]);
                   readyqueue.erase(readyqueue.begin() + 0);
               }
               else
               {
                   (processchart[i].processor_history).push_back(null);
               }
           }
       }

       if (algo_id == 0 || algo_id >= 2)
       {
           for (int i = 0; i < readyqueue.size(); i++)
           {
               readyqueue[i].waiting = readyqueue[i].waiting + 1;
           }
       }
       else if (algo_id == 1)
       {
           for (int i = 0; i < readyqueue.size(); i++)
           {
               if (readyqueue[i].flag == 0)
               {
                   readyqueue[i].waiting = readyqueue[i].waiting + 1;
               }
               else
               {
                   readyqueue[i].turn_around = readyqueue[i].turn_around + 1;
               }
           }
       }
       for (int i = 0; i < running.size(); i++)
       {
           running[i].burst = running[i].burst - 1;
           running[i].turn_around = running[i].turn_around + 1;
       }
   }
   /*------------------------------------------------------------------------------------------------------------------------------------*/

//    cout << "Gantt Queue: " << endl;
   for (int i = 0; i < processchart.size(); i++)
   {
    //    cout << "For Processor " << i + 1 << ": ";
       for (int j = 0; j < (processchart[i].processor_history).size(); j++)
       {
           if ((processchart[i].processor_history)[j].id == -1)
           {
               cout << "-1 ";
           }
           else
           {
               cout << (processchart[i].processor_history)[j].id << " ";
           }
       }
       cout << "\n";
   }

   for (int i = 0; i < total_processes; i++)
   {
       for (int j = 0; j < total_processes; j++)
       {
           if (i == terminated[j].id)
           {
               avg_wt = (avg_wt + terminated[j].waiting);
               avg_tt = (avg_tt + terminated[j].waiting + terminated[j].turn_around);

               waiting_list.push_back(terminated[j].waiting);
               ta_list.push_back(terminated[j].waiting + terminated[j].turn_around);
           }
       }
   }
//    cout << "Waiting time of each process: ";
   for (int i = 0; i < total_processes; i++)
   {
       cout << waiting_list[i] << " ";
   }
   cout << endl;

   placeholder = ((float)avg_wt / (float)total_processes);
   cout << placeholder << endl;

//    cout << "Turn-Around time of each process: ";
   for (int i = 0; i < total_processes; i++)
   {
       cout << ta_list[i] << " ";
   }
   cout << endl;
   placeholder = ((float)avg_tt / (float)total_processes);
   cout << placeholder << endl;

   return 0;
}