#include <cassert>
#include <iostream>
#include "MemoryManager.h"

MemoryManager::MemoryManager(unsigned int memtotal)
{
  memsize = memtotal;
  baseptr = new unsigned char[memsize];
  blockdata originalBlock(memsize, baseptr, true);  
  blocklist.insertAfter(blocklist.header, originalBlock);
  assert(!blocklist.empty());
}

void MemoryManager::showBlockList() 
{
  //cout << "\n-------------BlockList start------------------\n\n";
  blocklist.print("->");
  cout << endl;
  //cout << "\n-------------BlockList end------------------\n\n";
}

void MemoryManager::splitBlock(dlNode<blockdata> *p, unsigned int chunksize)
{
    int remain = p->info.blocksize - chunksize;
    unsigned char* bp1 = new unsigned char[chunksize-3];
    unsigned char* bp2 = new unsigned char[chunksize];
    blockdata newNode1(chunksize, bp1, false);
    blockdata newNode2(remain, bp2, true);
    blocklist.insertBefore(p, newNode1);
    blocklist.insertBefore(p, newNode2);
    blocklist.deleteNode(p);
}


unsigned char * MemoryManager::malloc(unsigned int request)
{
   // Fill in the missing code and delete this comment
    
    // split the blo
    static unsigned char *ptr2block = nullptr;
    dlNode<blockdata> *N = blocklist.header->next;
    while (N->next != nullptr) {
        if(N->info.free == true && N->info.blocksize >= request){
            if(N->info.blocksize > request){
                splitBlock(N, request);
                break;
            }
            
        } else if (N == blocklist.trailer){
            return ptr2block;
        }
        N = N->next;
    }
    N->info.free = false;
    
    // Find the block pointer
    dlNode<blockdata> *N2 = blocklist.header->next;
    while (N2->next != nullptr) {
        if(N2->info.free == false && N2->info.blocksize == request){
            ptr2block = N2->info.blockptr;
        }
        N2 = N2->next;
    }
    return ptr2block;
    
}


void MemoryManager::mergeForward(dlNode<blockdata> *p)
{
    int mergeAmt = p->info.blocksize + p->next->info.blocksize;
    p->info.blocksize = mergeAmt;
    blocklist.deleteNode(p->next);

}

void MemoryManager::mergeBackward(dlNode<blockdata> *p)
{ 
    int mergeAmt = p->info.blocksize + p->prev->info.blocksize;
    p->info.blocksize = mergeAmt;
    blocklist.deleteNode(p->prev);

}

void MemoryManager::free(unsigned char *ptr2block)
{
   dlNode<blockdata> *N = blocklist.header->next;

   while (N->next != nullptr) {
       unsigned char *NN = N->info.blockptr;
       unsigned char *NB = ptr2block;
    if(N->info.blockptr == ptr2block || N == blocklist.header){
        
        if(N == blocklist.trailer)
            throw "fatal error: attempting to free an unallocated block";
        
        if(N->info.free == false)
            N->info.free = true;
    
        if (N->next->info.free == true && N->prev->info.free == true){
            mergeBackward(N);
            mergeForward(N);
        } else if (N->next->info.free == true){
            mergeForward(N);
        } else if (N->prev->info.free == true){
            mergeBackward(N);
        }
        
     }
     N = N->next;
   }
    
}


