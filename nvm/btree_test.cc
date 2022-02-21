#include "btree.h"


class Data{
public:
    int a;
    ~Data(){
        printf("~Data \n");
    }
};


void func(){
   leveldb::silkstore::BTree<int,Data> btree;
   for(int i  = 0; i < 100; i ++){
       Data data;
       btree.insert(i,data);
   }
}

int main(){
    func();
    while(1);
}