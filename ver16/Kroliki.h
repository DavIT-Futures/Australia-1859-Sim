//---------------------------------------------------------------------------

#ifndef KrolikiH
#define KrolikiH
//---------------------------------------------------------------------------
#include "krolik.h"
#include "lis.h"
#include <system.hpp>
class Kroliki :public PlodK
{
private:

  int **pole;
  int szer,wys;

  //Lisy *lis;

  void rusz(int);
  void stat (int);
  void dodaj(float,float,int,int);
  void def_par(int,int,int,int);
  void evolve(int);

public:

   DynamicArray <Lis> *Ltab;
   DynamicArray <Krolik> *Ktab;

   Kroliki(int**,int,int,DynamicArray <Krolik> *, DynamicArray <Lis> *);

   float evol;
   long z1,z2;
//POCZATKOWE:
   int pole_widz;
   int dl_ciazy;
   int dl_zycia;
   int wiek_dojrz;

   float pojemnoscZ;
   float kes;
   float vk;
   float metabolizm;

   void czysc();
   void generuj(int,int,int);
   void rusz();
   void kill(int);
};
#endif
