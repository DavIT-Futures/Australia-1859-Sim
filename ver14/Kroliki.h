//---------------------------------------------------------------------------

#ifndef KrolikiH
#define KrolikiH
//---------------------------------------------------------------------------
#include "krolik.h"
#include "lis.h"
#include <system.hpp>
class Kroliki
{
private:

  int **pole;
  int szer,wys;

  //Lisy *lis;

  void rusz(int);
  void stat (int);
  void dodaj(float,float,int);
  void def_par(int,int,int,int);

public:

   DynamicArray <Lis> *Ltab;
   DynamicArray <Krolik> *Ktab;

   Kroliki(int**,int,int,DynamicArray <Krolik> *, DynamicArray <Lis> *);

   int zoladek;
   int dl_zycia;
   int wiek_dojrz;
   int glod;
   int starving;
   int pole_widz;
   int kes;
   float vk;
   int dl_ciazy;
   int metabolizm;

   void czysc();
   void generuj(int,int,int);
   void rusz();
   void kill(int);
};
#endif
