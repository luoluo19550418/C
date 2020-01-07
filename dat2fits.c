// gcc dat2fits.c -o dat2fits
#define minL 0.0
#define maxL 229.75
#define minB -5.25 
#define maxB 5.25
#define lnum 13786 //(maxl-minl)*60+1
#define bnum 631  //(maxB-minB)*60+1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

float data[lnum-1][bnum-1];
int data1[8698965]; //lnum*bnum-1
main(int argc, char *argv[]){ 
  char outname[20];
  float L,B,peak,area;
  int x,y,i,j,anum;
  FILE *infp,*fitsfp; 
  char tmpchar[100],char1[5],char2[5];
  if(argc!=2 ){
    system("echo -e '\007'");
    printf("Usage:such as 'dat2fits all.txt \n");
  }
  if((infp=fopen(argv[1],"r"))==NULL){
    printf("Can't Open File %s,try again !\n",argv[1]);
    exit(0);
  }

 ///////////////////////////////////////////////////////////
  while(!feof(infp)){
    fgets(tmpchar,100,infp);
    sscanf(tmpchar,"%f %f %s %s\n",&L,&B,char1,char2);
    if(!strstr(char1,"NaN")){
      sscanf(tmpchar,"%f %f %f %f\n",&L,&B,&peak,&area);
      if(L>=minL && L<=maxL){ 
	x=(int)(lnum-(L-minL)*60.0-1+0.5);
	if(B>=minB && B<=maxB){ 
	  y=(int)((B-minB)*60.0-1+0.5);
	}
      }
      printf("%d %d %f %f %f\n",x,y,L,B,lnum-(L-minL)*60.0-1);
      data[x][y]=peak;
    }
  }

////////////////////////////////////////////////////////////
  for(i=0;i<bnum;i++){
    for(j=0;j<lnum;j++){
      data1[i*lnum+j]=htonl((int)(data[j][i]*1000));
    }
  }

  strcpy(outname,"mwisp.fits");

  // Write Fits 
  if((fitsfp=fopen(outname,"wb"))==NULL){
      printf("Can't Open File %s,try again !\n",outname);
      exit(0);
  }

  //--------------save header---------------------------------
  fprintf(fitsfp,"SIMPLE  =                    T /%48s"," ");
  fprintf(fitsfp,"BITPIX  =                   32 /%48s"," ");
  fprintf(fitsfp,"NAXIS   =                    2 /%48s"," ");     
  fprintf(fitsfp,"NAXIS1  =               %05d  /%48s",lnum," ");     
  fprintf(fitsfp,"NAXIS2  =                 %03d  /%48s",bnum," "); 
  fprintf(fitsfp,"BSCALE  = %+1.13e /%48s",0.001," ");   
  fprintf(fitsfp,"EXTEND  =                    T /%48s"," ");   
  fprintf(fitsfp,"DATE    =   '2019-10-23'       /%48s"," ");  
  fprintf(fitsfp,"CTYPE1  = 'GLON-GLS'           /%48s"," ");  
  fprintf(fitsfp,"CRVAL1  = %+1.13e /%48s", 120.0," ");
  fprintf(fitsfp,"CDELT1  = %+1.13e /%48s",-1.0/60.0," ");
  fprintf(fitsfp,"CRPIX1  = %+1.13e /%48s",6226.0," ");
  fprintf(fitsfp,"CROTA1  =                    0 /%48s"," ");
  fprintf(fitsfp,"CTYPE2  = 'GLAT-GLS'           /%48s"," ");  
  fprintf(fitsfp,"CRVAL2  = %+1.13e /%48s",0.0," ");    
  fprintf(fitsfp,"CDELT2  = %+1.13e /%48s",1.0/60.0," ");
  fprintf(fitsfp,"CRPIX2  = %+1.13e /%48s",319.0," ");
  fprintf(fitsfp,"CROTA2  =                    0 /%48s"," ");
  fprintf(fitsfp,"OBJECT  = 'MWISP'              /%48s"," ");
  fprintf(fitsfp,"END                             %48s"," ");
  for(i=0;i<16;i++){
    fprintf(fitsfp,"%80s"," "); 
  }
  
  //______________header end and  savedata start___________
  fwrite(&data1,sizeof(int),lnum*bnum,fitsfp);

/////////////////////////////////////////////////////////////////
  anum=ceil(lnum*bnum/2880.0)*2880-lnum*bnum;
  for(i = 0;i < anum; i++){ 
    fprintf(fitsfp,"%c",' ');
  }
  fclose(fitsfp);
}
