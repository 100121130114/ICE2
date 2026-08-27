#include <stdio.h>
#include <stdbool.h>

#include "../LIBS/libloc.h"

//var conf
 //basic
extern unsigned int ln; //longuitud de los numeros
extern unsigned int lfd;//longuitud de los tipos
extern unsigned int lc; //longuitud de los comandos
extern unsigned int lv; //longuitud de variables
extern unsigned int ls; //longuitud de script
extern unsigned int lj; //longuitud de jump
extern unsigned int ccv; //cantidad de CVAR
extern unsigned int lcv; //longuitud de los CVAR
extern unsigned int cd; //cantidad de Dwarfs
extern unsigned int lr; //Longuitud de Recover
extern unsigned int cme;//cantidad maxima de errores antes de auto FATALITYERROR
 //adds
char ic='0'; //caracter de inicio
char fc='9'; //caracter de final
extern unsigned int lf; //longuitud de el file
unsigned int lds=1000; //longuitud de el define save
unsigned int lfs=1000; //longuitud de el function save
//var save
 //basic
extern unsigned int* pNff;//[ls][lc]
#define bNff(a,b) pNff[(a)*lc+(b)]
extern char* pAff;//[ls][lc]
#define bAff(a,b) pAff[(a)*lc+(b)]

#define serial_console(a) printf("%s",a)
#define serial_console_num(a) printf("%u",a)
#define crea_memo(a,b) calloc(a,b)

bool conf_proces(){
 FILE* file;
 if(!(file=fopen("CONFIG/ice2.cnf","rb"))){
  serial_console("Error, no se puede abrir el archivo de configuracion ice2.cnf\n");
  return 1;
 }
 char* cfile=(char*)calloc(sizeof(char),9999);//[9999]
 if(cfile==NULL){serial_console("Error de memoria. CFILE\n");return 1;}
 fread(cfile,sizeof(char),9999,file);
 fclose(file);

 unsigned int conf[16]; 
 bool confc[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,};
 unsigned int a=0,b=0;
 while(b<16){
  unsigned int c=0;
  char Cff[5];
  bool coment=0;
  while((a<9999)&&(c<5)){
   if(cfile[a]==';'){
    coment=!(coment);
   }
   if(!(coment)){
    if(cfile[a]==':'){
     goto con;
    }
    if((cfile[a]>='0')&&(cfile[a]<='9')){
     Cff[c]=cfile[a]-'0';
     c++;
    }
   }
   a++;
  }
  conf[b]=ces(10,5,Cff);
  confc[b]=1;
  con:
  b++;
 }
 
//ln, lfd, lc, lv, ls, lj, ccv, lcv, cd, lr, ic, fc, lf, cme, lds, lfs
 if(confc[0]){ln=conf[0];}
 if(confc[1]){lfd=conf[1];}
 if(confc[2]){lc=conf[2];}
 if(confc[3]){lv=conf[3];}
 if(confc[4]){ls=conf[4];}
 if(confc[5]){lj=conf[5];}
 if(confc[6]){ccv=conf[6];}
 if(confc[7]){lcv=conf[7];}
 if(confc[8]){cd=conf[8];}
 if(confc[9]){lr=conf[9];}
 if(confc[10]){ic=conf[10];}
 if(confc[11]){fc=conf[11];}
 if(confc[12]){lf=conf[12];}
 if(confc[13]){cme=conf[13];}
 if(confc[14]){lds=conf[14];}
 if(confc[15]){lfs=conf[15];}
 return 0;
}

bool date_syntax_system(char* file_name,unsigned int* a){
 FILE* file;
 if(!(file=fopen(file_name,"rb"))){
  serial_console("Error, no se puede abrir el archivo ");serial_console(file_name);serial_console("\n");
  return 1;
 }
 char* pfile=(char*)calloc(sizeof(char),lf);//lf
 if(pfile==NULL){serial_console("Error de memoria. PFILE\n");return 1;}
 
 fread(pfile,sizeof(char),lf,file);
 fclose(file);
 //procesador de datos de entrada
 
 //? bNff(Comando,SecionDelComando) Datos ?
 //? bAff(Comando,SecionDelComando) Tipos ?
 
 unsigned int* Nfile = (unsigned int*)pfile;
 unsigned int lnf = lf/(sizeof(unsigned int)/sizeof(char));
 for(unsigned int a=0,c=0;(a<ls)&&(c<lnf);a++){
  for(unsigned int b=0;(b<lc)&&(c<lnf);b++){
   bAff(a,b)=Nfile[c];
   c++;
   if(c>=lnf){break;}
   bNff(a,b)=Nfile[c];
   c++;
  } 
 }
 
 free(pfile);
 return 0;
}

bool date_proces(){//funcion llamada para dar los datos requeridos
 char file_name[9999];
 printf(">");
 scanf("%s",file_name);
 //upchr(file_name);
 unsigned int a=0;
 return date_syntax_system(file_name,&a);
}
