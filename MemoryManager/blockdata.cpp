#include "blockdata.h"
#include <iostream>
using namespace std;

blockdata::blockdata(unsigned int s, unsigned char *p, bool f)
{
  blocksize = s;
  blockptr = p;
  free = f;
}

ostream &operator << (ostream &out, const blockdata &B)
{
  out << "[" << B.blocksize << ",";
  if (B.free)
    out << "free";
  else
    out << "allocated";
  out << "]";
  return out;
}

