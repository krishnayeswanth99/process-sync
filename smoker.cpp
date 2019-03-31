#include <iostream>
#include <stdlib.h>
#include <pthread.h> 
using namespace std;

string sem[] = {"P and T", "M and P", "M and T"};
int s[] = {0,0,0}; 
int done[] = {1}; 
int a[] = {3};
int smokers[] = {0, 1, 2}; 
string resource[] = {"M","T","P"};

void wait() {
  int len=rand();
  while(len--);
}

void wait(int* semaphore){
  while(*semaphore==0); 
  *semaphore -= 1;
}

void wait(int* semaphore, string p){
  while(*semaphore==0);
  cout<<p<<endl;
  *semaphore -= 1;
}

void signal(int* semaphore){
  *semaphore += 1;
}

void* agent(void* num) 
{
    while (1) {
      
      wait(done);
      int r = rand() % 3;
      cout<<"Agent puts "<<sem[r]<<" on table"<<endl;
      signal(s+r);
    } 
} 

void* smoker(void* num) 
{
  int *ID = (int*)num;
  int i = *ID;
  
    while (1) {
        cout<<"Smoker with "+resource[i]+" wants to smoke"<<endl;
        wait(s + i,"Smoker with "+resource[i]+" is smoking");

       
        wait(); 

        cout<<"Smoker with "<<resource[i]<<" is done smoking"<<endl;
       
        signal(done);
        
        
    } 
} 

int main() {
    pthread_t thread_id[4];

     pthread_create(&thread_id[3], NULL, agent, &a[0]); 
     wait();

     for (int i = 0; i < 3; i++){ 
        
        pthread_create(&thread_id[i], NULL, smoker, &smokers[i]); 
     } 
       
        for (int i = 0; i < 3; i++)   
         pthread_join(thread_id[i], NULL);
}