//---------------------------------------------------------------------------

#ifndef nicH
#define nicH
//---------------------------------------------------------------------------
#include "lis.h"
#include "krolik.h"
#include <system.hpp>
class nico
{
private:

  int **pole;
  int szer,wys;

  int timer;

  void rusz(int);
  void stat(int);
  void dodaj(float,float);  

public:

   DynamicArray <Lis> *Ltab;
   DynamicArray <Krolik> *Ktab;

   Lisy(int**,int,int, DynamicArray <Krolik> *, DynamicArray <Lis> *);
   void czysc();
   void generuj(int,int,int);
   void rusz();
};
#endif
