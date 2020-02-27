#include<stdio.h>
#include<math.h>
int main()
{
	while (1)
	{
		int n;
		double a[100], x1 = 0, v1[100] = { 0.0 }, standard = 0, b[100];
		printf("请输入你要输入数据得个数：");
		scanf_s("%d", &n);

		//算术平均值 
		printf("请输入数据：");
		for (int i = 0; i < n; i++)
		{
			scanf_s("%lf", &a[i]);
			x1 += a[i];
		}
		x1 = x1 / n;
		printf("算术平均值:%lf\n", x1);

		//残余误差 
		printf("残余误差等于：");
		for (int i = 0; i < n; i++)
		{
			v1[i] = a[i] - x1;
			printf("%lf  \t", a[i] - x1);
		}
		printf("\n");

		//标准偏差
		for (int i = 0; i < n; i++)
		{
			standard += pow(v1[i], 2);
		}
		standard = standard / (n - 1);
		standard = sqrt(standard);
		printf("标准偏差: %lf\n", standard);

		//删除较大偏差
		double upper = x1 + 3 * standard, down = x1 - 3 * standard;
		int count = 0;
		for (int i = 0; i < n; i++)
		{
			if (a[i] <= upper && a[i] >= down)
			{
				b[count++] = a[i];
			}
		}
		printf("3倍标准差原则后的剩下的数据：");
		for (int i = 0; i < count; i++)
		{
			printf("%lf  \t", b[i]);
		}
		printf("\n");

		double x2 = 0, v2[100] = { 0.0 }, standard1 = 0;
		//重新计算算术平均值
		for (int i = 0; i < count; i++)
		{
			x2 += b[i];
		}
		x2 = x2 / count;
		printf("重新计算的算术平均值:%lf\n", x2);

		//重新计算残余误差
		printf("重新计算的残余误差为: ");
		for (int i = 0; i < count; i++)
		{
			v2[i] = b[i] - x2;
			printf("%lf  \t", v2[i]);
		}
		printf("\n");


		//重新计算的标准差
		for (int i = 0; i < count; i++)
		{
			standard1 += pow(v2[i], 2);
		}
		standard1 = standard1 / (count - 1);
		standard1 = sqrt(standard1);
		printf("重新计算的标准差为：%lf\n", standard1);

		//标准偏差
		double standard2 = 0;
		standard2 = standard1 / (sqrt(count));
		printf("标准偏差:%lf\n", standard2);

		//测量结果
		double xupper, xdown;
		xupper = x2 + 3 * standard2;
		xdown = x2 - 3 * standard2;
		printf("测量结果:%lf--%lf\n", xdown, xupper);
	}
	return 0;
}
