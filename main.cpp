#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h> 
#include <math.h> 
#include <stdio.h>

using namespace std;

class Wyzarzanie
{
 public: int *s,*sp,*sb,d,l,dlugosc,licznikZatrzymania,**tab,licznikPodniesieniaTemperatury;	
 public: double t,r,x,podniesTemp;

 /*
rozwiazanie poczatkowe s
 temperatura poczatkowa t
 sb -najlepsze
s - biezace rozwiazanie,
N(S) - zbiór sasiednich rozwiazan dla rozwiazania s,
d - róznica kosztów rozwiazan: nowego i poprzedniego,
f (s) - funkcja oceny rozwiazania (funkcja kosztu),
t - aktualna temperatura,
a(t) - funkcja zmiany temperatury,
l - d³ugosc epoki (liczba wewnetrznych iteracji).
 */
 
 Wyzarzanie( int **tab2, int d){
 	licznikPodniesieniaTemperatury=0;
 dlugosc = d;
 tab=tab2;
  licznikZatrzymania=0;
  l=100;	
  t=100;
  podniesTemp=0.01;
  s = new int[dlugosc];
  sp = new int[dlugosc];
  	
  sb = new int[dlugosc];
r=0.95;  


 }
 bool nieMozeIstiec(int d, int x){
 	for(int i=0;i<d;i++)
 	{
 		if(s[i]==x)return true;
		 	
	}
	return false;
 }
 void ustawPozycjeStartowa(){
int x;

for (int i=0 ; i<dlugosc; i++)
	{
		do{	
	x = rand() % dlugosc+1;
	}
	while(nieMozeIstiec(i,x));
	s[i]=x;

}
wypiszDrogeS();
	  for(int i=0 ; i<dlugosc;i++)	{
		sb[i]=s[i];
		sp[i]=s[i];
}
 	
 }
 int f(int s[]){
 	int koszt = 0;
	  	koszt+=tab[s[dlugosc-1]-1][s[0]-1];
	for (int i= 0 ; i<dlugosc-1 ; i++)
 	koszt+=tab[s[i]-1][s[i+1]-1];
 	return koszt;
 }
 double a(double t){
 return t*r;
 }
 
  bool waruekZatrzymaia ()
 {
 	licznikZatrzymania++;
 if(licznikZatrzymania<100)
 return true;
 else 
 return false;
 }
 
void losoweSasiednieRozwiazanie(int *s,int *sp){
	int x,y,*st;
	do{
	x = rand() % dlugosc;
    y = rand() % dlugosc;
	}
	while(x==y);
    st =new int [dlugosc];
    podstaw(st,s);

	int zamiana = st[x];
	st[x]=st[y];
	st[y]=zamiana;
    podstaw(sp,st);
   }
   void podstaw(int *s,int *sp)
   {
   for(int i = 0 ;i<dlugosc;i++)
   s[i]=sp[i];
   }
   double losujX()
   {
	x = rand() % 98;
	x++;
	x =x/100;
   return x;
   }
   
   bool bolt(double x,int d, double t){
   	double y = ((-d)/t);  	
    if (x < exp(y)) return true;
   	return false;
   }
   
   void podniesTemperature(){
   	if(licznikPodniesieniaTemperatury>50)
	  t+=podniesTemp;  
   }
void wykonaj(){
ustawPozycjeStartowa();
do{
	for(int i = 0;i<l;i++){
		losoweSasiednieRozwiazanie(s,sp);
	if(f(sp)<f(sb)){
	
		licznikPodniesieniaTemperatury=0;
		podstaw(sb,sp);
	}
	else
	licznikPodniesieniaTemperatury++;
     podniesTemperature();
    
	d=f(sp)-f(s);
	if(d<0)podstaw(s,sp);	
    else
	if(bolt(losujX(),d,t))podstaw(s,sp);
	}
	t=a(t);
}
while (waruekZatrzymaia());
//wypiszDrogeMin();
 wypiszRozwiazanieMin();
}
 void wypiszRozwiazanieMin(){
 	cout<<"\n"<<f(sb)<<"\n";
 }
 void wypiszDrogeMin(){
 		cout<<"\n";
 	for(int i=0;i<dlugosc;i++)cout<<sb[i]<<" ";
 		cout<<"\n";
 }
 void wypiszRozwiazanieKosztS(){
 	cout<<"\n"<<f(s)<<"\n";
 }
 void wypiszDrogeS(){
 	cout<<"\n";
 	for(int i=0;i<dlugosc;i++)cout<<s[i]<<" ";
 }
 void wypiszRozwiazanieKosztSp(){
 	cout<<"\n"<<f(sp)<<"\n";
 }
 void wypiszDrogeSp(){
 	cout<<"\n";
 	for(int i=0;i<dlugosc;i++)cout<<sp[i]<<" ";
 }
 
void wypiszTab(){

	for ( int i = 0; i < dlugosc; ++i, cout<<endl )
    	for ( int j = 0; j < dlugosc; ++j)
 			cout<<tab[i][j]<<'\t';
}

 
 void zwolnijPamiec(){
 
 	for ( int i(0); i < dlugosc; ++i )
 		delete [] tab[i]; 
		delete [] tab;
 		tab = NULL;
 }
};

class OdczytZPliku
{
 public: int a;	
 
 int w,k;
 int **tab2;


int **zwrucTablice(){
	return tab2;
}
 void utwurzTablice(int i,int j){
	
	w=i;
	k=j;

	tab2 = new int *[w];
	 
	for ( int i = 0; i < w; ++i )
 		tab2[i] = new int [k];
 }
 
 
 void zwolnijPamiec(){
 
 	for ( int i(0); i < w; ++i )
 		delete [] tab2[i]; 
		delete [] tab2;
 		tab2 = NULL;
 }
 
 void wczytajPlik(string nazwaPliku){
 	
    std::ifstream plik;
    plik.open( nazwaPliku.c_str() );
        int j=0;
        int i=0;
		int a=0;
		
    while( true ){
        if( plik.good() ){
		    plik >> a;  
		 
     	    if(j>=w){ j=0; i++; }
     	    if(i>=k)break;
 			tab2[i][j]=a;
        	j++;
    	}
		else
          	break;        
    } 
      plik.close();
}

void wypiszTab(){

	for ( int i = 0; i < w; ++i, cout<<endl )
    	for ( int j = 0; j < k; ++j)
 			cout<<tab2[i][j]<<'\t';
}
void uzupelnijZeramiTab(){
	for ( int i = 0; i < w; ++i )
    	for ( int j = 0; j < k; ++j)
 			tab2[i][j]=0;
}


void wykonaj(){
	
  utwurzTablice(29,29);
 uzupelnijZeramiTab();
  wczytajPlik("dane.txt");
  //wypiszTab();
}

};



int main(int argc, char** argv) {
	
	//Wyzarzanie w;
//	OdczytZPliku h;	
//	h.wykonaj();



	OdczytZPliku o;
	o.wykonaj();
	
   srand (time(NULL));	
	for (int i= 0 ;i <50;i++)
	{
	Wyzarzanie w(o.zwrucTablice(),29);	
	w.wykonaj();
    }    
	

	

	//w.a=36;
	//cout<<w.a;

	getchar();
	return 0;
}
