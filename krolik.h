//---------------------------------------------------------------------------

#ifndef krolikH
#define krolikH
//---------------------------------------------------------------------------
#include "zwierze.h"

class Krolik :public Zwierze
{
  //status:
  // 0 - starving
  // 1 - ucieczka
  // 2 - glodny
  // 3 - sex

  int pamiec_trawy[2]; //x,y ostatnio widzianej trawy
};
#endif
