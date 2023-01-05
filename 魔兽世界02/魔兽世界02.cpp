#include<iostream>
#include<cstring>
#include<cstdio>
#include<string>
using namespace std;
const string name[5] = { "iceman","lion","wolf","ninja","dragon" };
const string weapon[3] = { "sword","bomb","arrow" };

class life
{
private:
	int sumLife;//总共所有的生命元
public:
	void getSumLife()//获得总生命值
	{
		cin >> sumLife;
		return;
	}
	friend class soldiers;//声明类soldiers为友元
	void copy(life& life_)//复制函数
	{
		sumLife = life_.sumLife;
	}
};
class soldiers
{
private:
	int quantity[5];//记录五类soldiers的数量
	int order[5];//记录顺序
	int mode;//0为red，1为blue
	int preProduct;//记录前一个制造的类型
	bool printOrNot;//是否仍继续打印
	int tempsoldier;//临时记录的变量
	static int birthData[5];//出生数据信息
	void chooseSoldierType(life& nlife)//选择下一个士兵的类型
	{
		int temp = 1;
		bool check = false;//bool型变量，用于判断是否无法制造
		while (1)
		{
			if (temp > 5)
				break;
			if (nlife.sumLife >= birthData[order[(preProduct + temp) % 5]])//模5为顺序
			{
				nlife.sumLife -= birthData[order[(preProduct + temp) % 5]];
				check = true;//成功制造
				tempsoldier = order[(preProduct + temp) % 5];
				quantity[tempsoldier]++;
				preProduct += temp;
				break;
			}
			temp++;
		}
		if (check == false)
		{
			state = false;//更新状态
		}
		return;
	}
	void equipment(life& nlife)
	{
		if (state == false)return;
		switch (tempsoldier)
		{
		case 0:
		{
			cout << "It has a " << weapon[(ntime + 1) % 3] << endl;
			break;
		}
		case 1:
		{
			cout << "It's loyalty is " << nlife.sumLife << endl;
			break;
		}
		case 3:
		{
			cout << "It has a " << weapon[(ntime + 1) % 3] << " and a " << weapon[(ntime + 2) % 3] << endl;
			break;
		}
		case 4:
		{
			cout << "It has a " << weapon[(ntime + 1) % 3] << ",and it's morale is " ;
			printf("%.2lf\n", (float)nlife.sumLife / birthData[4]);
			break;
		}
		}

	}
	void printNow()
	{
		if (printOrNot == 0)return;
		printf("%03d ", ntime);
		if (mode == 0)
			printf("red ");
		else
			printf("blue ");
		if (state == 0)
		{
			printf("headquarter stops making warriors\n");
			printOrNot = 0;
		}
		else
		{
			cout << name[tempsoldier] << ' ' << ntime + 1 << " born with strength " << birthData[tempsoldier] << "," << quantity[tempsoldier] << " " << name[tempsoldier] << " in ";
			if (mode == 0)
				printf("red ");
			else
				printf("blue ");
			cout << "headquarter" << endl;
		}
		return;
	}

public:
	int ntime;//当前时间
	bool state;//是否仍继续制造
	soldiers(int mod) :state(1), printOrNot(1), mode(mod), preProduct(4)
	{
		memset(quantity, 0, sizeof(quantity));
		if (mod == 0)
		{
			order[0] = 0; order[1] = 1; order[2] = 2; order[3] = 3; order[4] = 4;
		}
		else
		{
			order[0] = 1; order[1] = 4; order[2] = 3; order[3] = 0; order[4] = 2;
		}
	}
	static void dataInput()//输入初始生命值
	{
		cin >> birthData[4] >> birthData[3] >> birthData[0] >> birthData[1] >> birthData[2];
		return;
	}
	void work(life& life_)
	{
		chooseSoldierType(life_);
		printNow();
		equipment(life_);
		ntime++;
		return;
	}
};
int soldiers::birthData[5] = { 0 };

int main()
{
	int caseNum;
	cin >> caseNum;
	int index = caseNum;
	while (index > 0)
	{
		soldiers R(0), B(1);
		life Rlife, Blife;
		Rlife.getSumLife();
		Blife.copy(Rlife);
		soldiers::dataInput();
		R.ntime = B.ntime = 0;
		cout << "Case:" << caseNum - index + 1 << endl;
		while (1)
		{
			if (R.state == 0 && B.state == 0)
				break;
			R.work(Rlife);
			B.work(Blife);
		}
		index--;
	}
	return 0;
}
