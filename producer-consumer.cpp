#include<iostream>

using namespace std;

#define BUFFER_SIZE 2
int in = 0,out = 0,counter = 0, mutex = 1;

struct pid{
    int id;
};

pid buffer[BUFFER_SIZE];

int wait(int s){
    while(s<=0);
    s--;
    return s;
}
int signal(int s){
    s++;
    return s;
}

void prod(int id){
        mutex = wait(mutex);
        buffer[in].id = id;
        cout<<"Process with id: "<<buffer[in].id<<" has been produced"<<endl;
        in = (in+1)%BUFFER_SIZE;
        counter++;
        mutex = signal(mutex);
}
void cons(){
        mutex = wait(mutex);
        cout<<"Process with id: "<<buffer[out].id<<" has been consumed"<<endl;
        out = (out+1)%BUFFER_SIZE;
        counter--;
        mutex = signal(mutex);
}

int main(){
    int i=0,j=0;
    while(j<15){
        int a = rand()%2;
        if(a){
            if(counter != BUFFER_SIZE && mutex){
                prod(i);i++;
            }
            else{
                cout<<"Buffer full"<<endl;
            }
        }
        else{
            if(counter != 0 && mutex){
                cons();
            }
            else{
                cout<<"Buffer is empty"<<endl;
            }
        }
        j++;
    }
}