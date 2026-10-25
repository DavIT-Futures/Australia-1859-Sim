//---------------------------------------------------------------------------

#ifndef krolikH
#define krolikH
//---------------------------------------------------------------------------
#include "zwierze.h"
#include "PlodK.h"

class Krolik :public Zwierze, public PlodK
{
  //status:
  // 0 - starving
  // 1 - ucieczka
  // 2 - glodny
  // 3 - sex
  public:
  int pamiec_trawy[2]; //x,y ostatnio widzianej trawy

   float pojemnoscZ;
   float vk;
   float kes;
   float metabolizm;

   PlodK *plod;
};
#endif
