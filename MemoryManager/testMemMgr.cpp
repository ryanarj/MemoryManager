#include <iostream>
#include "MemoryManager.h"
using namespace std;

int main()
{
   MemoryManager heaper(50);
   cout << "After initializing" << endl;
   heaper.showBlockList();
    
   unsigned char *p1 = heaper.malloc(10);

   cout << "After the first malloc\n";
   heaper.showBlockList();

   unsigned char *p2 = heaper.malloc(20);
   cout << "After the second malloc\n";
   heaper.showBlockList();

   cout << "Asking for an un-allocatable block\n";
   unsigned char *p8 = heaper.malloc(30);
   if (p8 == 0)
      cout << "Good. The call to malloc returned NULL\n\n";
   else
      cout << "Uh-oh.  Call to malloc did not return NULL as it should have\n\n";

   cout << "Free the second block\n";
   heaper.free(p1);
   heaper.showBlockList();
    
   cout << "Allocate a block too big for the initial open block\n";
   p1 = heaper.malloc(15);
   // cout << "malloc done\n";
   heaper.showBlockList();

   cout << "Free the most recently allocated pointer\n";
   heaper.free(p1);
   heaper.showBlockList();

   cout << "Free the middle block\n";
   heaper.free(p2);
   heaper.showBlockList();


   return 0;
}
