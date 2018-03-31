#include <iostream>
#include <thread>
using namespace std;
void runit(){
    cout<<"itis"<<endl;
}
int main(){
    thread run(runit);
    run.~thread();
    return 0;
} 