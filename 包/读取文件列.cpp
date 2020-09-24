//在 VS2017 下运行
#include <stdio.h>
#include <stdlib.h> 
#include <iostream>
using namespace std;

int main() {

	char line[129600], stra[129600], strb[129600];                                  //存每行,存第1列字符串的值
	//char str1[] = { "B1UM" }, str2[] = { "B2UM" }, str3[] = { "B3UM" }, str4[] = { "B4UM" }, str5[] = { "B5UM" }, str6[] = { "B6UM" }, str7[] = { "B7UM" }, str8[] = { "B8UM" }, str9[] = { "B9UM" };
	//float a;
	//float s1 = 0, av1, s2 = 0, av2, s3 = 0, av3, s4 = 0, av4, s5 = 0, av5, s6 = 0, av6, s7 = 0, av7, s8 = 0, av8, s9 = 0, av9;
	//float i1 = 0, i2 = 0, i3 = 0, i4 = 0, i5 = 0, i6 = 0, i7 = 0, i8 = 0, i9 = 0;

	FILE* file = fopen("1.txt", "r");
	//FILE *fpWrite = fopen("av.txt", "w");

	while (fgets(line, sizeof(line), file)) {																	//fgets逐行读取文件，到达文件尾终止while循环
		sscanf(line, "%s %s", stra, strb);							//sscanf解析每行数据，因为第*列不需要，在格式字符前加上*	
	    cout<<stra;
		//cout<< ' ';
		//sscanf(stra, "%f", &a);
		//if (strcmp(strb, str1) == 0) { s1 = s1 + a; i1++; }
		//if (strcmp(strb, str2) == 0) { s2 = s2 + a; i2++; }
		//if (strcmp(strb, str3) == 0) { s3 = s3 + a; i3++; }
		//if (strcmp(strb, str4) == 0) { s4 = s4 + a; i4++; }
		//if (strcmp(strb, str5) == 0) { s5 = s5 + a; i5++; }
		//if (strcmp(strb, str6) == 0) { s6 = s6 + a; i6++; }
		//if (strcmp(strb, str7) == 0) { s7 = s7 + a; i7++; }
		//if (strcmp(strb, str8) == 0) { s8 = s8 + a; i8++; }
		//if (strcmp(strb, str9) == 0) { s9 = s9 + a; i9++; }
	}
	//printf("%f %f %f %f %f %f %f %f %f\n", i1, i2, i3, i4, i5, i6, i7, i8, i9);
	//av1 = s1 / i1; av2 = s2 / i2; av3 = s3 / i3; av4 = s4 / i4; av5 = s5 / i5; av6 = s6 / i6; av7 = s7 / i7; av8 = s8 / i8; av9 = s9 / i9;
	//printf("%s %f\n%s %f\n%s %f\n%s %f\n%s %f\n%s %f\n%s %f\n%s %f\n%s %f\n", str1, av1, str2, av2, str3, av3, str4, av4, str5, av5, str6, av6, str7, av7, str8, av8, str9, av9);
	//fprintf(fpWrite, "%s %f\n%s %f\n%s %f\n%s %f\n%s %f\n%s %f\n%s %f\n%s %f\n%s %f\n", str1, av1, str2, av2, str3, av3, str4, av4, str5, av5, str6, av6, str7, av7, str8, av8, str9, av9);

	//fclose(fpWrite);
	fclose(file);
	//return -1;
}
