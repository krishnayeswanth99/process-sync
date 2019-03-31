#include <iostream>
#include <stdlib.h>
#include <pthread.h> 
using namespace std;


int mutex[] = {1};
int rt = 1;
int wt = 0;

int w[] = {5};
int r[] = { 0, 1, 2, 3, 4 }; 

void wait(){
  int a = rand();
  while(a--);
}
void wait(int* s){
  while(*s==0); 
  *s -= 1;
}

void wait(int* s1, int* s2){
  while(*s1==0 || *s2==0); 
  *s1 -= 1;
  *s2 -=1;
}

void signal(int* fork1){
  *fork1 += 1;
}

void* write(void* num) 
{
  int *ID = (int*)num;
  int i = *ID;
  
    while (1) {
      cout<<"writer ready to write"<<endl;
      wait(&rt);
      cout<<"writer writing"<<endl;
      
      wait();
      
      signal(&rt);
      cout<<"writer has completed writing"<<endl;
      wait();
    } 
} 

void* read(void* num) 
{
  int *ID = (int*)num;
  int i = *ID;
  
    while (1) {
      cout<<"reader "<<r[i]<<" waiting for reading"<<endl;
      wait(mutex);
      wt++;

      
      if (wt==1)
        wait(&rt);

      signal(mutex); 
      
      cout<<"reader "<<r[i]<<" is got reading"<<endl;
      wait();
      cout<<"reader "<<r[i]<<" has completed reading"<<endl;
      wait(mutex); 
      wt--;

      if(wt==0)
        signal(&rt); 

      signal(mutex); 

     wait();
    } 
} 

int main() {
    pthread_t thread_id[6];

    pthread_create(&thread_id[5], NULL, write, &w[0]); 

     for (int i = 0; i < 5; i++){ 
         
        pthread_create(&thread_id[i], NULL, read, &r[i]); 
     }

        for (int i = 0; i < 6; i++)   
          pthread_join(thread_id[i], NULL);
}
