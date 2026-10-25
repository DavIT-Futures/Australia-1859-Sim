//---------------------------------------------------------------------------

#ifndef LisH
#define LisH
//---------------------------------------------------------------------------
#include "zwierze.h"
#include "PlodL.h"
class Lis :public Zwierze, public PlodL
{
 //status:
  // 0 - kreciola  
  // 1 - glodny
  // 2 - sex
  public:
   int pojemnoscZ;
   //int kes;
   float vl;
   float metabolizm;

   PlodL *plod;
};
#endif
