
/*	MADE BY CODEHAT	- LICE2 TRANSLATER		*/


#include <stdbool.h>
#include <stdlib.h>

#include "../ADDS/ice2_date_sys.basicS.c"

//var conf
unsigned int ln=4; //longuitud de los numeros
unsigned int lfd=1; //longuitud de los tipos
unsigned int lc=4; //longuitud de los comandos
unsigned int lv=64; //longuitud de variables
unsigned int ls=64; //longuitud de script
unsigned int lj=16; //longuitud de jump
unsigned int ccv=64; //cantidad de CVAR
unsigned int lcv=16; //longuitud de los CVAR
unsigned int cd=4; //cantidad de Dwarfs o Enanos
unsigned int lr=16;//longuitut de los Rescue Saves
unsigned int cme=300;//cantidad maxima de errores antes de auto FATALITYERROR
unsigned int lf=1000; //longuitud de el file

//var save
unsigned int* pNff;//[ls][lc]

char* pAff;//[ls][lc]

char* pfile;

int main(){
 //conf_proces
 if(conf_proces()){
  return 0;
 } 
 //take the space for the save vars
 pNff=(unsigned int*)crea_memo(sizeof(unsigned int),ls*lc);
 if(pNff==NULL){serial_console("Error de memoria. NFF\n");return 0;}
 pAff=(char*)crea_memo(sizeof(char),ls*lc);
 if(pAff==NULL){serial_console("Error de memoria. AFF\n");return 0;}
 pfile=(char*)calloc(sizeof(char),lf);//lf
 if(pfile==NULL){serial_console("Error de memoria. PFILE\n");return 1;}
 //date_proces
 if(date_proces()){
  return 0;
 }
 
 unsigned int* Nfile = (unsigned int*)pfile;
 unsigned int lnf = lf/(sizeof(unsigned int)/sizeof(char));
 for(unsigned int a=0,c=0;(a<ls)&&(c<lnf);a++){
  for(unsigned int b=0;(b<lc)&&(c<lnf);b++){
   Nfile[c]=bAff(a,b);
   c++;
   if(c>=lnf){break;}
   Nfile[c]=bNff(a,b);
   c++;
  } 
 }
 
 char file_name[9999];
 printf(">>");
 scanf("%s",file_name);
 FILE* file=fopen(file_name,"wb"); 
 fwrite(pfile,sizeof(char),lf,file);
 fclose(file);
 

 return 0;
}
