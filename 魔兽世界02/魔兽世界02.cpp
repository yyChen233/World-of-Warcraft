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
	int sumLife;//�ܹ����е�����Ԫ
public:
	void getSumLife()//���������ֵ
	{
		cin >> sumLife;
		return;
	}
	friend class soldiers;//������soldiersΪ��Ԫ
	void copy(life& life_)//���ƺ���
	{
		sumLife = life_.sumLife;
	}
};
class soldiers
{
private:
	int quantity[5];//��¼����soldiers������
	int order[5];//��¼˳��
	int mode;//0Ϊred��1Ϊblue
	int preProduct;//��¼ǰһ�����������
	bool printOrNot;//�Ƿ��Լ�����ӡ
	int tempsoldier;//��ʱ��¼�ı���
	static int birthData[5];//����������Ϣ
	void chooseSoldierType(life& nlife)//ѡ����һ��ʿ��������
	{
		int temp = 1;
		bool check = false;//bool�ͱ����������ж��Ƿ��޷�����
		while (1)
		{
			if (temp > 5)
				break;
			if (nlife.sumLife >= birthData[order[(preProduct + temp) % 5]])//ģ5Ϊ˳��
			{
				nlife.sumLife -= birthData[order[(preProduct + temp) % 5]];
				check = true;//�ɹ�����
				tempsoldier = order[(preProduct + temp) % 5];
				quantity[tempsoldier]++;
				preProduct += temp;
				break;
			}
			temp++;
		}
		if (check == false)
		{
			state = false;//����״̬
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
	int ntime;//��ǰʱ��
	bool state;//�Ƿ��Լ�������
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
	static void dataInput()//�����ʼ����ֵ
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
