
//  main.cpp
//  RoundRobin
//
//  Created by Catalina Diaz on 11/9/19.
//  Copyright © 2019 class. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <queue>
using namespace std;


//checks if it pushes into the queue
void check_next(vector<pair<double,double> > proc, queue<int> &wait_list, double total_time, vector<bool> serviced)
{

  for(int i =0; i < proc.size(); i++)
  {
    //checks if its in range of total time and if it still has burst time
    if(proc[i].first <= total_time)
    {
      if(proc[i].second >0 )
      {
          wait_list.push(i);
        // cout << "input: " << proc[i].second << "total time: " << total_time <<endl;
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////

void find_average(vector<double> w, vector<double> ta)
{
  double total = 0;

  for(int i= 0; i < w.size(); i++)
  {
    total += w[i];
  }

  double seconds = (total/w.size());

cout << "size wait time: " << w.size() <<endl;
  //convert to mili seconds
  cout << seconds <<endl;

  total = 0;
    for(int i= 0; i < w.size(); i++)
  {
    total += ta[i];
  }
  cout <<endl;
 cout <<"size of tat vector: " << ta.size() <<endl;
  seconds = (total/ta.size()) ;
  cout << "Turnaround time: " <<  seconds <<endl;
}

////////////////////////////////////////////////////////////////////////////////

void schedule(vector<pair<double,double> > proc, double qt,double oh)
{
  //variables
  queue<int> wait_list; //contains indexes of all the processes
  vector<double> w; //wait time
  vector<double> ta; //turnaround
  double total_time = 0;
  vector<bool> serviced;
  vector<bool> in_loop;
    int count = 0;
  int total_services = 0;

  int temp = 0; //this keeps track of indexes

  //do serviced;
  for(int i =0; i < proc.size(); i++)
  {
    serviced.push_back(false);
    in_loop.push_back(false);
  }

  //push the first one
  wait_list.push(0);


  //process
  while(total_services < proc.size())
  {
     
    //insert into the queue the remaining
   check_next(proc, wait_list, total_time, serviced);

   //get the next one from the queue
    if(wait_list.empty())
    {
      for(int i = 0; i < serviced.size(); i++)
      {
        if(serviced[i] == false)
        {
          temp = i;
          break;
        }
         
         
      }

      double add_difference= proc[temp].first - total_time;

      total_time += add_difference;
    
    }
    else{
      temp = wait_list.front();

      wait_list.pop();
    }
   //check how much burst time remaining if > qt then subtract qt otherwise subtract remaining
  if(proc[temp].second >= qt)
  {
      
    //track down the wait time and turn around
    if(in_loop[temp] == false)
    {
        w.push_back(total_time - proc[temp].second);
        in_loop[temp] = true;
    }
  
    
    //edit proc
      cout << proc[temp].second << " ";
    proc[temp].second = proc[temp].second - qt;
      cout << proc[temp].second << endl;
    //increase total time including the OH time
    total_time +=qt + oh;

    if(proc[temp].second == 0)
    {
      serviced[temp] = true;
        total_services++;
    }
  }
  else if (serviced[temp] == false){
    if(in_loop[temp] == false)
    {
      w.push_back(total_time - proc[temp].second);
      in_loop[temp] = true;
    }
      cout << proc[temp].second << " " ;
    total_time +=proc[temp].second +oh;
    proc[temp].second = proc[temp].second - proc[temp].second;
    serviced[temp] = true;
    //calculate turnaround
           cout << proc[temp].second << endl;
   // cout << total_time << " - " << proc[temp].first << "= " << total_time - proc[temp].first << endl;
    ta.push_back(total_time - proc[temp].first);
      //cout << temp << " " << proc[temp].first <<endl;
    total_services++;
      
    
  }

 // cout << total_time << " " << proc[temp].second <<endl;

  }

  //calculate the averages
  find_average(w,ta);
}


int main() {
    
//variables
    vector<pair<double,double> > processes;
  
    ifstream inputFile;
    inputFile.open("times.txt");
    
    double arrival, service;
//reading in from file
    if(inputFile.is_open())
    {
        while(!inputFile.eof())
        {
            inputFile >> arrival;
            inputFile >> service;

           processes.push_back(make_pair(arrival,service));
        }

        schedule(processes, 50, 0);
         schedule(processes, 50, 5);
         schedule(processes, 50, 10);
         schedule(processes, 50, 15);
         schedule(processes, 50, 20);
         schedule(processes, 50, 25);
        
        
        schedule(processes, 100, 0);
         schedule(processes, 100, 5);
         schedule(processes, 100, 10);
         schedule(processes, 100, 15);
         schedule(processes, 100, 20);
         schedule(processes, 100, 25);
        
        schedule(processes, 250, 0);
         schedule(processes, 250, 5);
         schedule(processes, 250, 10);
         schedule(processes, 250, 15);
         schedule(processes, 250, 20);
         schedule(processes, 250, 25);
        
        schedule(processes, 500, 0);
         schedule(processes, 500, 5);
         schedule(processes, 500, 10);
         schedule(processes, 500, 15);
         schedule(processes, 500, 20);
         schedule(processes, 500, 25);
    }
    else
    {
        cout << "could not acess file" <<endl;
    }



    
    return 0;
}
