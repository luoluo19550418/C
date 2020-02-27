//共2880字节为一块，fits头为一块
//二进制数据存储也是2880字节为一块，块数=总数据数(字符)*2/2880；1个数据16位，也就是2个字节（等于1个数据字符）
//读取fits时，需要头文件的中心坐标，数据长度等参数

// gcc dat2fits.c -o dat2fits
// 20200121 ip12 有改动
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

float data[lnum][bnum];   //如果定义太短，数组会有溢出
int data1[8698965]; //lnum*bnum-1
main(int argc, char *argv[]){            //argc(argument count) argv(argument vector)
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
//---------------------------------------------------//
  for(i=0;i<lnum;i++){
    for(j=0;j<bnum;j++){
      data[i][j]=0
    }
  } 
 //----------------------------------------------------------------
  while(!feof(infp)){
    fgets(tmpchar,100,infp);
    sscanf(tmpchar,"%f %f %s %s\n",&L,&B,char1,char2);
    if(!strstr(char1,"NaN")){
      sscanf(tmpchar,"%f %f %f %f\n",&L,&B,&peak,&area);
      if(L>=minL && L<=maxL){ 
	x=(int)(lnum-(L-minL)*60.0-0.5);
	if(B>=minB && B<=maxB){ 
	  y=(int)((B-minB)*60.0+0.5);
	}
      }
      //printf("%d %d %f %f %f\n",x,y,L,B,lnum-(L-minL)*60.0-1);
      data[x][y]=peak;
    }
  }

//-------------------------------------------------------------------
  for(i=0;i<bnum;i++){
    for(j=0;j<lnum;j++){
      data1[i*lnum+j]=htonl((int)(data[j][i]*1000));  //htonl将一个无符号短整形数从网络字节顺序转换为主机字节顺序；ntohl
    }
  }

  strcpy(outname,"mwisp.fits");

  // Write Fits 
  if((fitsfp=fopen(outname,"wb"))==NULL){
      printf("Can't Open File %s,try again !\n",outname);
      exit(0);
  }

  //--------------save header---------------------------------
  fprintf(fitsfp,"SIMPLE  =                    T /%48s"," ");   //指明文件是否符合FITS标准，%48表示48个空字符数
  fprintf(fitsfp,"BITPIX  =                   16 /%48s"," ");   //每一个像元值的存储位数
  fprintf(fitsfp,"NAXIS   =                    2 /%48s"," ");   //指明图像里的坐标轴数     
  fprintf(fitsfp,"NAXIS1  =               %05d  /%48s",lnum," ");   //X(RA)方向像元数     
  fprintf(fitsfp,"NAXIS2  =                 %03d  /%48s",bnum," ");   //Y(Dec)方向像元数，输出一个数值变量，不足3位在前面补0
  fprintf(fitsfp,"BSCALE  = %+1.13e /%48s",0.001," ");   //用于将像元值转换为真实值的参数：真实值=(磁带值×BSCALE)＋BZERO 
  fprintf(fitsfp,"EXTEND  =                    T /%48s"," ");   
  fprintf(fitsfp,"DATE    =   '2019-10-23'       /%48s"," ");  
  fprintf(fitsfp,"CTYPE1  = 'GLON-GLS'           /%48s"," ");   //RA=CRVAL1+(i-CRPIX1)*CDELT1/COS(Dec)
  fprintf(fitsfp,"CRVAL1  = %+1.13e /%48s", 120.0," ");   //X轴参考位置
  fprintf(fitsfp,"CDELT1  = %+1.13e /%48s",-1.0/60.0," ");   //X轴坐标增量
  fprintf(fitsfp,"CRPIX1  = %+1.13e /%48s",6226.0," ");   //X轴像素位置
  fprintf(fitsfp,"CROTA1  =                    0 /%48s"," ");   //
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
  fwrite(&data1,sizeof(short int),lnum*bnum,fitsfp);   //短整型，16位

//-----------------------------------------------------------------------
  anum=ceil(lnum*bnum/2880.0)*2880-lnum*bnum;
  for(i = 0;i < anum; i++){     //在最后一块未满2880字节添加空格符。
    fprintf(fitsfp,"%c",' ');
  }
  fclose(fitsfp);
}
