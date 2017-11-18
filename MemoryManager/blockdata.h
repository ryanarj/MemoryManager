#ifndef _BLOCKDATA_
#define _BLOCKDATA_

#include <iostream>

using namespace std;

struct blockdata {
  friend ostream& operator << (ostream&, const blockdata &);
  int blocksize;
  bool free;
  unsigned char *blockptr;	    
  blockdata(unsigned int s = 0, unsigned char * p= nullptr, bool f = false);
};


#endif
