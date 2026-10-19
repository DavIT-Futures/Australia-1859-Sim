//---------------------------------------------------------------------------

#ifndef LisyH
#define LisyH
//---------------------------------------------------------------------------
#include "lis.h"
#include "krolik.h"
#include "plodL.h"
#include <system.hpp>
class Lisy: public PlodL
{
private:

  int **pole;
  int szer,wys;

  int timer;

  void rusz(int);
  void stat(int);
  void dodaj(float,float,int,int);
  void def_par(int,int,int,int);
  void evolve(int);

public:

   int z1,z2,z3;
   float evol;    

   float pojemnoscZ;
   float kes;
   float vl;
   float metabolizm;

   int dl_ciazy;
   int dl_zycia;
   int wiek_dojrz;

   DynamicArray <Lis> *Ltab;
   DynamicArray <Krolik> *Ktab;

   Lisy(int**,int,int, DynamicArray <Krolik> *, DynamicArray <Lis> *);
   void czysc();
   void generuj(int,int,int);
   void rusz();
};

#endif
