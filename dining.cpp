#include <iostream>
#include <stdlib.h>
#include <pthread.h> 
using namespace std;


bool fork[] = {1,1,1,1,1};

int pid[] = { 0, 1, 2, 3, 4 }; 

void wait(){
  int a = rand();
  while(a--);
}
void wait(bool* fork1, bool* fork2){

  while(!*fork1 || !*fork2); 
  *fork1 = false;
  *fork2 = false;
}

void signal(bool* fork1, bool* fork2){
  *fork1 = true;
  *fork2 = true;
}
void* phil(void* id) 
{
  int i = *(int*)id;
    while (1) {
        cout<<"Philosopher "<<i<<" is Hungry"<<endl;
        wait(fork+i, fork+((i-1)%5));
        cout<<"Philosopher "<<i<<" is Eating"<<endl;
        
        wait();        

        signal(fork + i,fork+((i-1)%5));
        cout<<"Philosopher "<<i<<" has completed Eating"<<endl;
        cout<<"Forks "<<i<<" & "<<(i-1)%5<<" can again used"<<endl;
        
        cout<<"Philosopher "<<i<<" is Thinking"<<endl;
        double waiter = rand() % 200000000 + 200000000;
        wait(); 
        
    } 
} 

int main() {
    pthread_t thread_id[5];
     for (int i = 0; i < 5; i++){ 
        pthread_create(&thread_id[i], NULL, phil, &pid[i]); 
     }
        for (int i = 0; i < 5; i++)   
        pthread_join(thread_id[i], NULL);
}