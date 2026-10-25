//---------------------------------------------------------------------------

#ifndef LisyH
#define LisyH
//---------------------------------------------------------------------------
#include "lis.h"
#include "krolik.h"
#include <system.hpp>
class Lisy
{
private:

  int **pole;
  int szer,wys;

  int timer;

  void rusz(int);
  void stat(int);
  void dodaj(float,float,int);  

public:

   int zoladek;
   int dl_zycia;
   int wiek_dojrz;
   int glod;
   int kes;
   float vl;
   int dl_ciazy;
   int metabolizm;

   DynamicArray <Lis> *Ltab;
   DynamicArray <Krolik> *Ktab;

   Lisy(int**,int,int, DynamicArray <Krolik> *, DynamicArray <Lis> *);
   void czysc();
   void generuj(int,int,int);
   void rusz();
};

#endif
