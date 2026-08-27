#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define Flong(a) (unsigned int)(sizeof(a)/sizeof(*a))

bool exist(char* fname){//true/false existe el fichero con el nombre dado
 FILE* file;
 if(file = fopen(fname, "r")){
  fclose(file);
  return true;
 }
 return false;
}

char* fusC(char* txtA,char* txtB){//fusiona dos textos txtA+txtB -> txtA
 for(unsigned int a=0,b=0;true;a++){
  if(txtA[a]=='.'){
   txtA[a]=txtB[b];
   b++;
  }
  if(txtA[a]==';'){
   txtA[a]=0;
   break;
  }
 }
 return txtA;
}

void pum(char* txtA,char chrA){//fusiona dos textos txtA+txtB -> txtA
 for(unsigned int a=0;true;a++){
  if(txtA[a]==0){
   txtA[a]=chrA;
   return;
  }
 }
}

void rpum(char* txtA,char chrA){//fusiona dos textos txtA+txtB -> txtA
 for(unsigned int a=0;true;a++){
  if(txtA[a]==0){
   txtA[a-1]=chrA;
   return;
  }
 }
}

char* Zfus(char* txtA,char* txtB,unsigned int numA){//fusiona dos textos txtA+txtB -> txtA
 bool add=false;
 for(unsigned int a=0,b=0;b<numA;a++){
  if((txtA[a]==0)&&(!(add))){
   add=true;
  }
  if(add){
   txtA[a]=txtB[b];
   b++;
  }
 }
 return txtA;
}

char* fus(char* txtA,char* txtB){//fusiona dos textos txtA+txtB -> txtA
 bool add=false;
 for(unsigned int a=0,b=0;txtB[b]!=0;a++){
  if((txtA[a]==0)&&(!(add))){
   add=true;
  }
  if(add){
   txtA[a]=txtB[b];
   b++;
  }
 }
 return txtA;
}

char* Dfus(char* txtA,char* txtB,char div){//fusiona dos textos txtA+txtB -> txtA
 bool add=false;
 for(unsigned int a=0,b=0;(txtB[b]!=0)&&(txtB[b]!=div);a++){
  if((txtA[a]==0)&&(!(add))){
   add=true;
  }
  if(add){
   txtA[a]=txtB[b];
   b++;
  }
 }
 return txtA;
}

char* replace(char* txtA,char chrA,char chrB){//remplaza un caracter en otro de un texto
 for(unsigned int a=0;txtA[a]!=0;a++){
  if(txtA[a]==chrA){
   txtA[a]=chrB;
  }
 }
 return txtA;
}

char* Creplace(char* txtA,char chrA,char chrB,unsigned int numA){//remplaza un caracter en otro de un texto, con un limite de remplazos
 for(unsigned int a=0,b=0;txtA[a]!=0;a++){
  if(txtA[a]==chrA){
   txtA[a]=chrB;
   b++;
  }
  if(b>=numA){break;}
 }
 return txtA;
}

unsigned int cut(char* txtA,char chrA){//corta por un sitio para poder printar no del todo un string, paso 1
 for(unsigned int a=0;txtA[a]!=0;a++){
  if(txtA[a]==chrA){
   txtA[a]=0;
   return a;
  }
 }
}

unsigned int Mcut(char* txtA,char* chrA){//corta por un sitio para poder printar no del todo un string, paso 1
 for(unsigned int a=0;txtA[a]!=0;a++){
  for(unsigned int b=0;chrA[a]!=0;b++){
   if(txtA[a]==chrA[b]){
    txtA[a]=0;
    return a;
   }
  }
 }
}

char* cut1(char* txtA,char chrA,unsigned int* numA){//corta por un sitio para poder printar no del todo un string, paso 1
 for(unsigned int a=0;txtA[a]!=0;a++){
  if(txtA[a]==chrA){
   txtA[a]=0;
   *numA=a;
   break;
  }
 }
 return txtA;
}

char* cut2(char* txtA,char chrA,unsigned int* numA){//corta por un sitio para poder printar no del todo un string, paso 2
 txtA[*numA]=chrA;
 return txtA;
}

char* dinar(char* base,char div,unsigned int num){//DINAmic ARray
 for(unsigned int a=0,b=0;base[a]!=0;a++){
  if(b==num){
   return &base[a];
  }
  if(base[a]==div){
   b++;
  }
 }
 return base;
}

char* Mdinar(char* base,char* div,unsigned int num){//DINAmic ARray
 for(unsigned int a=0,b=0;base[a]!=0;a++){
  if(b==num){
   return &base[a];
  }
  for(unsigned int c=0;div[c]!=0;c++){
   if(base[a]==div[c]){
    b++;
    break;
   }
  }
 }
 return base;
}

unsigned int Dlong(char* base,char div){
 unsigned int res=0;
 for(unsigned int a=0;(base[a]!=0)&&(base[a]!=div);a++){
  res++;
 } 
 return res;
}

unsigned int Clong(char* base,unsigned int numA){
 unsigned int res=0;
 for(unsigned int a=0;(base[a]!=0)&&(a<numA);a++){
  res++;
 } 
 return res;
}

void Dupchr(char* txtA,char div){
 for(unsigned int a=0;(txtA[a]!=0)&&(txtA[a]!=div);a++){
  if((txtA[a]>='a')&&(txtA[a]<='z')){
   txtA[a]=txtA[a]+('A'-'a');
  }
 }
 return;
}

bool equal(char* txtA,char* txtB){//compara dos strings y informa si son iguales
 if((txtA[0]==0)!=(txtB[0]==0)){
  return false;
 }
 if((txtA[0]==0)&&(txtB[0]==0)){
  return true;
 }
 for(unsigned int a=0;(txtA[a]!=0)&&(txtB[a]!=0);a++){
  if(txtA[a]!=txtB[a]){
   return false;
  }
 }
 return true;
}

bool Dequal(char* txtA,char* txtB,char div){//compara dos strings y informa si son iguales
 if((txtA[0]==0)!=(txtB[0]==0)){
  return false;
 }
 if((txtA[0]==0)&&(txtB[0]==0)){
  return true;
 }
 if((txtA[0]==div)!=(txtB[0]==div)){
  return false;
 }
 if((txtA[0]==div)&&(txtB[0]==div)){
  return true;
 }
 for(unsigned int a=0;((txtA[a]!=0)&&(txtB[a]!=0))&&((txtA[a]!=0)&&(txtB[a]!=0));a++){
  if(txtA[a]!=txtB[a]){
   return false;
  }
 }
 return true;
}

bool FULLequal(char* txtA,char* txtB,char div){//compara dos strings y informa si son iguales
 if(Dlong(txtA,div)!=Dlong(txtB,div)){
  return false;
 }
 return Dequal(txtA,txtB,div);
}

bool MFULLequal(char* txtA,char* txtB,char* div){//compara dos strings y informa si son iguales
 for(unsigned int a=0;div[a]!=0;a++){
  if(Dlong(txtA,div[a])!=Dlong(txtB,div[a])){
   continue;
  }
  if(Dequal(txtA,txtB,div[a])){
   return true;
  }
 }
 return false;
}

unsigned int count(char* txtA,char chrA){
 unsigned int res=0;
 for(unsigned int a=0;txtA[a]!=0;a++){
  if(txtA[a]==chrA){
   res++;
  }
 }
 return res;
}

unsigned int Dcount(char* txtA,char chrA,char div){
 unsigned int res=0;
 for(unsigned int a=0;(txtA[a]!=0)&&(txtA[a]!=div);a++){
  if(txtA[a]==chrA){
   res++;
  }
 }
 return res;
}

void upchr(char* txtA){
 for(unsigned int a=0;txtA[a]!=0;a++){
  if((txtA[a]>='a')&&(txtA[a]<='z')){
   txtA[a]=txtA[a]+('A'-'a');
  }
 }
 return;
}

char* stasi(char* txtA,char* txtB){//static asignacion
 unsigned int a=0;
 for(a=0;txtB[a]!=0;a++){
  txtA[a]=txtB[a];
 }
 for(;txtA[a]!=0;a++){
  txtA[a]=0;
 }
 return txtA;
}

char* Dstasi(char* txtA,char* txtB,char div){//static asignacion
 unsigned int a=0;
 for(a=0;(txtB[a]!=0)&&(txtB[a]!=div);a++){
  txtA[a]=txtB[a];
 }
 for(;txtA[a]!=0;a++){
  txtA[a]=0;
 }
 return txtA;
}

char* MDstasi(char* txtA,char* txtB,char* div){//static asignacion
 unsigned int a=0;
 for(a=0;txtB[a]!=0;a++){
  for(unsigned int b=0;div[b]!=0;b++){if(txtB[a]==div[b]){goto exit;}}
  txtA[a]=txtB[a];
 }
 exit:
 for(;txtA[a]!=0;a++){
  txtA[a]=0;
 }
 return txtA;
}

unsigned int lvr(unsigned int numb,unsigned int nume){
 int long res=1;
 for(int long a=0;a<nume;a++){
  res*=numb;
 }
 return res;
}

unsigned int ces(unsigned int numb,unsigned int cnc,char* numd){
 unsigned int numc=0;
 for(unsigned int a=cnc,b=0;a>0;a--){
  if((numd[a-1]>=0)&&(numd[a-1]<numb)){
   numc+=lvr(numb,cnc-1-a+1-b)*numd[a-1];
  }else{
   b+=1;
  }
 }
 return numc;
}

unsigned int charces(unsigned int numb,unsigned int cnc,char* numd,char rest){
 unsigned int numc=0;
 for(unsigned int a=cnc,b=0;a>0;a--){
  if((numd[a-1]-rest>=0)&&(numd[a-1]-rest<numb)){
   numc+=lvr(numb,cnc-1-a+1-b)*(numd[a-1]-rest);
  }else{
   b+=1;
  }
 }
 return numc;
}

unsigned int ces2(unsigned int numb,unsigned int cnc,unsigned int* numd){
 unsigned int numc=0;
 for(long unsigned int a=cnc-1,b=0;a>=0;a--){
  if(numd[a]>=0&&(numd[a]<numb)){
   numc+=lvr(numb,cnc-1-a-b)*numd[a];
  }else{
   b+=1;
  }
 }
 return numc;
}

unsigned int charint(char* txtA){
 unsigned int len=0;
 for(unsigned int a=0;(txtA[a]!=0)&&((txtA[a]>='0')&&(txtA[a]<='9'));a++){
  len++;
 }
 return charces(10,len,txtA,'0');
}

unsigned int charint_count(char* txtA,unsigned int* count){
 unsigned int len=0;
 for(unsigned int a=0;(txtA[a]!=0)&&((txtA[a]>='0')&&(txtA[a]<='9'));a++){
  len++;
 }
 *count+=len;
 return charces(10,len,txtA,'0');
}

unsigned int charint_count_bin(char* txtA,unsigned int* count){
 unsigned int len=0;
 for(unsigned int a=0;(txtA[a]!=0)&&((txtA[a]>='0')&&(txtA[a]<='1'));a++){
  len++;
 }
 *count+=len;
 return charces(2,len,txtA,'0');
}

char* intchar(unsigned int num,unsigned int base,unsigned int lout,char* out,char inichr,char finchr,char jmpchr){
 out[lout]=0;
 for(unsigned int a=lout-1,b=num;(a>=0)&&(a<lout);a--){
  out[a]=b%base+inichr;
  if(out[a]>finchr){
   out[a]+=(jmpchr-finchr);
  }
  b=b/base;
 }	
 return out;
}
