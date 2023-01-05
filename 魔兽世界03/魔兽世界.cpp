#include<iostream> 
#include<cstring> 
#include<string> 
#include<algorithm>
#include<vector>
#define MAX 10000
using namespace std;

//����Ϊ��ֵ����---------------------------------------------------------------
const int warriorNum = 5;
const int weaponNum = 3;
int hour = 0;//Сʱ
int minute = 0;//����
//0.dragon;1.ninja;2.iceman;3.lion;4.wolf
const string warriorName[warriorNum] = { "dragon","ninja","iceman","lion","wolf" };
const string colorname[2] = { "blue","red" };
int warriorAggressivity[warriorNum] = { 0 };
//0.sword;1.bomb;2.arrow
const string weaponName[weaponNum] = { "sword","bomb","arrow" };
//0.blue;1.red
const int workOrder[2][warriorNum] = { {3,0,1,2,4},{2,3,4,1,0} };
int cityNum, k;//����������ÿ��һ����lion���ҳ϶ȼ���k��

//����Ϊ�������----------------------------------------------------------------
class headquarter;
class weapon;
class warrior;
class dragon;
class ninja;
class iceman;
class lion;
class wolf;
class city;

//����Ϊ��ľ���ʵ��------------------------------------------------------------
class city
{
public:
	warrior* p1;//from red
	warrior* p2;//from blue
	int No;
	city(int n) :p1(NULL), p2(NULL), No(n) {};
	void setWarrior(warrior* p, int stance)
	{
		if (stance == 0) p2 = p;
		else p1 = p;
	}
	int fight();//0-ƽ�֣�1-��ʤ��2-��ʤ
	int hasTwoWarriors()
	{
		if (p1 && p2)
			return 1;
		return 0;
	}
};
class headquarter
{
private:
	int lifeNum;//˾�����ֵ
	int warriorQuantity[warriorNum];//ÿ��ʿ���ĸ�����¼
	int totalWarriorNum;//ʿ������
	int Number;//ʿ�����
	bool workOrNot;//˾��Ƿ��������ʿ��
	int preProductId;
	int location;//˾�����λ��
	int destination;//Ŀ�ĵ�
	warrior* points[MAX];//ʿ��ָ��
public:
	int color;//0--blue;1--red.
	string colorName;//��ɫ
	friend class warrior;
	friend class iceman;
	friend void combat();
	headquarter(int n, int type);//���캯��

	int produceWarrior();
	int getLifeNum() { return lifeNum; }
	int getLocation() { return location; }
	int getColor() { return color; }
	void warriorescape();
	void warriorMatch();
	void warriorloot();
	void reportLifePoints();
	int win();
};
city cities[22] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21 };
class warrior
{
public:
	headquarter* stance;//��Ӫ
	city* loc;//λ��
	friend class headquarter;
	friend class city;
	int No;//���
	int kind;//���࣬0.dragon;1.ninja;2.iceman;3.lion;4.wolf
	int lifePoint;//����ֵ
	int aggressivity;//������
	int location;//����λ��
	int NumofWeapons;//��������
	int temp;//��ʱ��¼���������ı���
	bool canWeaponUse[10];
	vector<weapon> Weapon;
	int weaponKindNumber[3];
	static int birthData[warriorNum];//��ʼ����ֵ
	warrior(int n, headquarter* p);//���캯��
	static bool Mycompare1(weapon& p1, weapon& p2);//��һ��������Ҫ���ڵڶ�������ǰ��ʱ����true
	static bool Mycompare2(weapon& p1, weapon& p2);//��һ��������Ҫ���ڵڶ�������ǰ��ʱ����true
	virtual void printState() = 0;//��ӡ��ʿ����
	void printNow(int n)
	{
		cout << " " << stance->colorName << " " << warriorName[n] << " " << No << " born" << endl;
	}
	void everyWeapons();//ͳ����������
	virtual int escape() { return 0; }//ʨ������
	virtual void match()
	{
		if (stance->colorName == "red")
		{
			location++;
			loc = &cities[location];
			cities[location].setWarrior(this, stance->getColor());
		}
		else
		{
			location--;
			loc = &cities[location];
			cities[location].setWarrior(this, stance->getColor());
		}
	}//�о�
	virtual void loot(warrior* opponent) {}//����������
	void weaponSort()
	{
		sort(Weapon.begin(), (Weapon.begin() + NumofWeapons), Mycompare1);
	}//������������ս����ʼǰ��
	void weaponSort1()
	{
		sort(Weapon.begin(), (Weapon.begin() + NumofWeapons), Mycompare2);
	}//�����������ڽɻ�����ʱ)
	void seizeWeapon(warrior* opponent);//�ɻ�����
	int fight(warrior* opponent, int round);//round--�غ���//ս��
	virtual int yell() { return 0; }//����
	void clearWeapon();//��������
};
class weapon
{
private:
	int No;//���
	int aggressivity;//������
	int durability;//�;ö�
public:
	friend class warrior;
	friend class dragon;
	friend class ninja;
	friend class iceman;
	friend class wolf;
	friend class lion;
	void setAggressivity(warrior* pWorrior)
	{
		switch (No)
		{
		case 0:
			aggressivity = pWorrior->aggressivity * 2 / 10; break;
		case 1:
			aggressivity = pWorrior->aggressivity * 4 / 10; break;
		case 2:
			aggressivity = pWorrior->aggressivity * 3 / 10; break;
		}
	}
	void setDurability()
	{
		switch (No)
		{
		case 0:
			durability = MAX; break;
		case 1:
			durability = 1; break;
		case 2:
			durability = 2; break;
		}
	}
};
class dragon :public warrior
{
private:
	int morale;
public:
	dragon(int n, headquarter* p) :warrior(n, p)
	{
		Weapon[0].No = No % weaponNum;
		NumofWeapons = 1;
		temp = NumofWeapons;
		aggressivity = warriorAggressivity[0];
		Weapon[0].setAggressivity(this);
		Weapon[0].setDurability();
		kind = 0;
		lifePoint = birthData[0];
		morale = (p->getLifeNum()) / (double)birthData[0];
	}
	void printState()
	{
		warrior::printNow(0);
	}
	int yell()
	{
		printf("%03d:%02d", hour, minute % 60);
		cout << ' ' << colorname[stance->getColor()] << " dragon " << No << " yelled in city ";
		return 1;
	}
};
class ninja :public warrior
{
public:
	ninja(int n, headquarter* p) :warrior(n, p)
	{
		Weapon[0].No = No % weaponNum;
		Weapon[1].No = (No + 1) % weaponNum;
		NumofWeapons = 2;
		kind = 1;
		temp = NumofWeapons;
		aggressivity = warriorAggressivity[1];
		lifePoint = birthData[1];
		Weapon[0].setAggressivity(this);
		Weapon[1].setAggressivity(this);
		Weapon[0].setDurability();
		Weapon[1].setDurability();
	}
	void printState()
	{
		warrior::printNow(1);
	}
};
class iceman :public warrior
{
public:
	iceman(int n, headquarter* p) :warrior(n, p)
	{
		Weapon[0].No = No % weaponNum;
		NumofWeapons = 1;
		kind = 2;
		temp = NumofWeapons;
		aggressivity = warriorAggressivity[2];
		Weapon[0].setAggressivity(this);
		lifePoint = birthData[2];
		Weapon[0].setDurability();
	}
	void printState()
	{
		warrior::printNow(2);
	}
	virtual void match()
	{
		if (stance->colorName == "red")
		{
			location++;
			loc = &cities[location];
			cities[location].setWarrior(this, stance->getColor());
		}
		else
		{
			location--;
			loc = &cities[location];
			cities[location].setWarrior(this, stance->getColor());
		}
		lifePoint -= lifePoint * 1 / 10;
		if (lifePoint <= 0)
		{
			stance->totalWarriorNum--;
			stance->points[No - 1] = NULL;
		}
	}
};
class lion :public warrior
{
private:
	int loyalty;
public:
	lion(int n, headquarter* p) :warrior(n, p)
	{
		kind = 3;
		Weapon[0].No = No % weaponNum;
		NumofWeapons = 1;
		temp = NumofWeapons;
		lifePoint = birthData[3];
		aggressivity = warriorAggressivity[3];
		Weapon[0].setAggressivity(this);
		Weapon[0].setDurability();
		loyalty = p->getLifeNum();
	}
	void printState()
	{
		warrior::printNow(3);
		printf("Its loyalty is %d\n", loyalty);
	}
	int escape()//1-escape;0-not escape
	{
		if (loyalty <= 0 && location != stance->getLocation())
			return 1;
		return 0;
	}
	virtual void match()
	{
		if (stance->getColor() == 1)
		{
			location++;
			loc = &cities[location ];
			cities[location ].setWarrior(this, stance->getColor());
		}
		else
		{
			location--;
			loc = &cities[location ];
			cities[location ].setWarrior(this, stance->getColor());
		}
		loyalty -= k;
	}
};
class wolf :public warrior
{
public:
	wolf(int n, headquarter* p) :warrior(n, p) 
	{
		kind = 4;
		temp = NumofWeapons;
		aggressivity = warriorAggressivity[4];
		lifePoint = birthData[4];
	}
	void printState()
	{
		warrior::printNow(4);
	}
	void loot(warrior* opponent)
	{
		if (opponent->kind == 4)
			return;
		if (opponent->NumofWeapons == 0)
			return;
		opponent->weaponSort1();
		int temp = 0;//��ʱ��¼�ı���
		int took = -1;//0,sword;1,bomb;2,arrow
		int tt = NumofWeapons;
		for (int i = NumofWeapons; i < 10 && (i-tt) < opponent->NumofWeapons; i++)
		{
			if (i > tt && opponent->Weapon[i - tt].No != took)
				break;
			Weapon[i] = opponent->Weapon[temp];
			temp++;
			Weapon[i].setAggressivity(this);
			took = Weapon[i].No;
			NumofWeapons++;
			warrior::temp++;
		}
		if (took == -1)return;
		printf("%03d:%02d", hour, minute % 60);
		cout << ' ' << colorname[stance->getColor()] << " wolf " << No << " took " 
			<< temp << ' ' << weaponName[took] << " from " << colorname[opponent->stance->getColor()] 
			<< " " << warriorName[opponent->kind] << " " << opponent->No << " in city " << location << endl;
		opponent->Weapon.erase(opponent->Weapon.begin(), opponent->Weapon.begin() + temp);
		opponent->Weapon.resize(10);
		opponent->NumofWeapons -= temp;
		opponent->temp -= temp;
	}
};

//����Ϊ�����ľ���ʵ��----------------------------------------------------------
headquarter::headquarter(int n, int type) :color(type), lifeNum(n), totalWarriorNum(0),
workOrNot(true), preProductId(4), Number(0)//���캯��
{
	for (int i = 0; i < MAX; i++)
		points[i] = NULL;
	memset(warriorQuantity, 0, sizeof(warriorQuantity));
	if (type == 0) { colorName = "blue"; location = cityNum + 1; destination = 0; }
	else { colorName = "red"; location = 0; destination = cityNum + 1; }
}
int headquarter::produceWarrior()
{
	int searchingNum = 0;
	bool check = false;
	int temp = 1;
	if (!workOrNot)
		return 0;
	while (searchingNum < 1)
	{
		if (lifeNum >= warrior::birthData[workOrder[color][(preProductId + temp) % 5]])
		{
			lifeNum -= warrior::birthData[workOrder[color][(preProductId + temp) % 5]];
			warriorQuantity[workOrder[color][(preProductId + temp) % 5]]++;
			switch (workOrder[color][(preProductId + temp) % 5])
			{
			case 0:
				points[Number] = new dragon(Number + 1, this);
				break;
			case 1:
				points[Number] = new ninja(Number + 1, this);
				break;
			case 2:
				points[Number] = new iceman(Number + 1, this);
				break;
			case 3:
				points[Number] = new lion(Number + 1, this);
				break;
			case 4:
				points[Number] = new wolf(Number + 1, this);
				break;
			}
			printf("%03d:%02d", hour, minute % 60);
			points[Number]->printState();
			totalWarriorNum++;
			Number++;
			check = true;
			preProductId += temp;
			break;
		}
		searchingNum++;
		temp++;
	}
	if (check == false)
	{
		workOrNot = false;
		return 0;
	}
	return 1;
}
void headquarter::warriorescape()
{
	int te = 0;
	for (int i = 0; i < totalWarriorNum+te; i++)
	{
		if (points[i] == NULL)
		{
			te++;
			continue;
		}
		int x = points[i]->escape();
		if (x == 1)
		{
			printf("%03d:%02d", hour, minute % 60);
			cout << ' ' << colorName << ' ' << warriorName[points[i]->kind] 
				<< ' ' << points[i]->No << " ran away" << endl;
			if (color == 0)
				points[i]->loc->p2 = NULL;
			else
				points[i]->loc->p1 = NULL;
			points[i] = NULL;
			totalWarriorNum--;
		}
	}
}
void headquarter::warriorMatch()
{
	int te = 0;
	for (int i = 0; i < totalWarriorNum + te; i++)
	{
		if (points[i] == NULL)
		{
			te++;
			continue;
		}
		points[i]->match();
	}
}
warrior::warrior(int n, headquarter* p) : No(n), stance(p), Weapon(10)//���캯��
{
	if (stance->color == 1)
	{
		location = 0;
		loc = &cities[0];
	}
	else
	{
		location = cityNum + 1;
		loc = &cities[cityNum + 1];
	}
	for (int i = 0; i < 10; i++)
		canWeaponUse[i] = true;
}
bool warrior::Mycompare1(weapon& p1, weapon& p2)//��һ��������Ҫ���ڵڶ�������ǰ��ʱ����true
{
	if (p1.No < p2.No)
		return true;
	else if (p1.No > p2.No)
		return false;
	else if (p1.No == 2 && p2.No == 2)
	{
		if (p1.durability < p2.durability)
			return true;
		else return false;
	}
	else return false;
}
bool warrior::Mycompare2(weapon& p1, weapon& p2)//��һ��������Ҫ���ڵڶ�������ǰ��ʱ����true
{
	if (p1.No < p2.No)
		return true;
	else if (p1.No > p2.No)
		return false;
	else if (p1.No == 2 && p2.No == 2)
	{
		if (p1.durability > p2.durability)
			return true;
		else return false;
	}
	else return false;
}
void warrior::seizeWeapon(warrior* opponent)
{
	opponent->weaponSort1();
	int temp = 0;
	for (int i = NumofWeapons; i < 10 && temp < opponent->NumofWeapons; i++)
	{
		Weapon[i] = opponent->Weapon[temp++];
		Weapon[i].setAggressivity(this);
		NumofWeapons++;
	}
	warrior::temp = NumofWeapons;
	opponent->Weapon.erase(opponent->Weapon.begin(), opponent->Weapon.begin() + temp);
	opponent->NumofWeapons -= temp;
}
int warrior::fight(warrior* opponent, int round)//round--�غ���
{
	
	int weaponStateChange = false;
	if (NumofWeapons == 0)return false;
	if ((round - 1) % NumofWeapons == 0)//�����;ö���0������
	{
		NumofWeapons = temp;
		for (int i = 0; i < 10; i++)
			if (canWeaponUse[i] == false)
			{
				Weapon.erase(Weapon.begin() + i, Weapon.begin() + (i + 1));
				Weapon.resize(10);
				canWeaponUse[i] = true;
			}
	}
	if (temp == 0)return false;
	if (opponent->lifePoint <= 0)return false;
	opponent->lifePoint -= Weapon[(round - 1) % NumofWeapons].aggressivity;
	if (Weapon[(round - 1) % NumofWeapons].No == 1 && this->kind != 1)
		this->lifePoint -= Weapon[(round - 1) % NumofWeapons].aggressivity * 1 / 2;
	Weapon[(round - 1) % NumofWeapons].durability -= 1;
	if (Weapon[(round - 1) % NumofWeapons].durability <= 0)
	{
		canWeaponUse[(round - 1) % NumofWeapons] = false;
		temp = NumofWeapons - 1;
		weaponStateChange = true;
	}
	return weaponStateChange;
}
void warrior::everyWeapons()
{
	weaponKindNumber[0] = weaponKindNumber[1] = weaponKindNumber[2] = 0;
	for (int i = 0; i < NumofWeapons; i++)
		weaponKindNumber[Weapon[i].No]++;
}
int city::fight()//0-�����ˣ�1-��ʤ��2-��ʤ,-1-������
{
	if (p1 && p2)
	{
		int cc = 0;
		p1->weaponSort();
		p2->weaponSort();
		if (No % 2)//����ʿ�ȹ���
		{
			int round = 1;
			while (1)
			{
				int life1 = p1->lifePoint, life2 = p2->lifePoint;
				int a = p1->fight(p2, round);
				if (p1->lifePoint <= 0 && p2->lifePoint <= 0)
					return -1;
				if (p2->lifePoint <= 0)
					return 1;
				int b = p2->fight(p1, round);
				if (p1->lifePoint <= 0 && p2->lifePoint <= 0)
					return -1;
				int judge1 = life1 - p1->lifePoint, judge2 = life2 - p2->lifePoint;
				if (cc == 2)
					return 0;
				if (!a && !b && !judge1 && !judge2)
					cc += 1;
				if (p1->lifePoint <= 0)
					return 2;
				round++;
			}
		}
		else//����ʿ�ȹ���
		{
			int round = 1;
			while (1)
			{
				int life1 = p1->lifePoint, life2 = p2->lifePoint;
				int b = p2->fight(p1, round);
				if (p1->lifePoint <= 0 && p2->lifePoint <= 0)
					return -1;
				if (p1->lifePoint <= 0)
					return 2;
				int a = p1->fight(p2, round);
				if (p1->lifePoint <= 0 && p2->lifePoint <= 0)
					return -1;
				int judge1 = life1 - p1->lifePoint, judge2 = life2 - p2->lifePoint;
				if (p2->lifePoint <= 0)
					return 1;
				if (cc == 2)
					return 0;
				if (!a && !b && !judge1 && !judge2)
					cc += 1;
				round++;
			}
		}
	}
}
void warrior::clearWeapon()//�����;ö���0������
{
	NumofWeapons = temp;
	for (int i = 0; i < 10; i++)
		if (canWeaponUse[i] == false)
		{
			Weapon.erase(Weapon.begin() + i, Weapon.begin() + (i + 1));
			Weapon.resize(10);
			canWeaponUse[i] = true;
		}
}
void headquarter::reportLifePoints()
{
	printf("%03d:%02d ", hour, minute % 60);
	cout << lifeNum << " elements in " << colorName << " headquarter" << endl;
}
int headquarter::win()
{
	int te = 0;
	for (int i = 0; i < totalWarriorNum + te; i++)
	{
		if (points[i] == NULL)
		{
			te++;
			continue;
		}
		if (points[i]->location == destination)
		{
			int opponent = (color == 0) ? 1 : 0;
			printf("%03d:%02d ", hour, minute % 60);
			cout << colorName << " " << warriorName[points[i]->kind] << " " << 
				points[i]->No << " reached " << colorname[opponent] << " headquarter with " 
				<< points[i]->lifePoint << " elements and force " << points[i]->aggressivity << endl;
			printf("%03d:%02d ", hour, minute % 60);
			cout << colorname[opponent] << " headquarter was taken" << endl;
			return 1;
		}
	}
	return 0;
}
int warrior::birthData[warriorNum];
void warriorloot()
{
	for (int i = 1; i <= cityNum; i++)
		if (cities[i].hasTwoWarriors())
		{
			if (cities[i].p1->location != i || cities[i].p2->location != i)continue;
				cities[i].p1->loot(cities[i].p2);
				cities[i].p2->loot(cities[i].p1);
		}
}
void match()
{
	for (int i = 1; i <= cityNum; i++)
	{
		if (cities[i].p1 != NULL && cities[i].p1->location == i)
		{
			printf("%03d:%02d", hour, minute % 60);
			cout << " " << "red" << ' ' << warriorName[cities[i].p1->kind] <<
				' ' << cities[i].p1->No << " marched to city " << cities[i].p1->location
				<< " with " << cities[i].p1->lifePoint << " elements and force " <<
				cities[i].p1->aggressivity << endl;
		}
		if (cities[i].p2 != NULL && cities[i].p2->location == i)
		{
			printf("%03d:%02d", hour, minute % 60);
			cout << " " << "blue" << ' ' << warriorName[cities[i].p2->kind] <<
				' ' << cities[i].p2->No << " marched to city " << cities[i].p2->location
				<< " with " << cities[i].p2->lifePoint << " elements and force " <<
				cities[i].p2->aggressivity << endl;
		}
	}
}
void combat()
{
	for (int i = 1; i <= cityNum; i++)
	{
		if (cities[i].hasTwoWarriors())
		{
			if (cities[i].p1->location != i || cities[i].p2->location != i)continue;
			printf("%03d:%02d", hour, minute % 60);
			int result = cities[i].fight();
			cities[i].p1->clearWeapon();
			cities[i].p2->clearWeapon();
			if (result == 1)//��ʤ
			{
				cities[i].p2->stance->points[cities[i].p2->No - 1] = NULL;
				cities[i].p2->stance->totalWarriorNum--;
				cout << " red " << warriorName[cities[i].p1->kind] << " " << cities[i].p1->No <<
					" killed blue " << warriorName[cities[i].p2->kind] << " "
					<< cities[i].p2->No << " in city " << i << " remaining " << cities[i].p1->lifePoint
					<< " elements" << endl;
				cities[i].p1->seizeWeapon(cities[i].p2);
				if (cities[i].p1->yell())
					cout << i << endl;
				cities[i].p2 = NULL;
			}
			else if (result == 2)//��ʤ
			{
				cities[i].p1->stance->points[cities[i].p1->No - 1] = NULL;
				cities[i].p1->stance->totalWarriorNum--;
				cout << " blue " << warriorName[cities[i].p2->kind] << " " << cities[i].p2->No <<
					" killed red " << warriorName[cities[i].p1->kind] << " "
					<< cities[i].p1->No << " in city " << i << " remaining " << cities[i].p2->lifePoint
					<< " elements" << endl;
				cities[i].p2->seizeWeapon(cities[i].p1);
				if (cities[i].p2->yell())
					cout << i << endl;
				cities[i].p1 = NULL;
			}
			else if (result == 0)//������
			{
				cout << " both red " << warriorName[cities[i].p1->kind] <<
					" " << cities[i].p1->No << " and blue " << warriorName[cities[i].p2->kind] << ' '
					<< cities[i].p2->No << " were alive in city " << i << endl;
				if (cities[i].p1->yell())
					cout << i << endl;
				if (cities[i].p2->yell())
					cout << i << endl;
			}
			else//������
			{
				cities[i].p1->stance->points[cities[i].p1->No - 1] = NULL;
				cities[i].p1->stance->totalWarriorNum--;
				cities[i].p2->stance->points[cities[i].p2->No - 1] = NULL;
				cities[i].p2->stance->totalWarriorNum--;
				cout << " both red " << warriorName[cities[i].p1->kind] <<
					" " << cities[i].p1->No << " and blue " << warriorName[cities[i].p2->kind] << ' '
					<< cities[i].p2->No << " died in city " << i << endl;
				cities[i].p1 = NULL;
				cities[i].p2 = NULL;
			}

		}
	}
}
void reportWeapon()
{
	for (int i = 1; i <= cityNum; i++)
	{
		if (cities[i].p1 != NULL && cities[i].p1->location == i)
		{
			cities[i].p1->everyWeapons();
			printf("%03d:%02d", hour, minute % 60);
			cout << ' ' << "red" << " " << warriorName[cities[i].p1->kind]
				<< " " << cities[i].p1->No << " has " << cities[i].p1->weaponKindNumber[0]
				<< " sword " << cities[i].p1->weaponKindNumber[1] << " bomb " <<
				cities[i].p1->weaponKindNumber[2] << " arrow"
				<< " and " << cities[i].p1->lifePoint << " elements" << endl;
		}
		if (cities[i].p2 != NULL && cities[i].p2->location == i)
		{
			cities[i].p2->everyWeapons();
			printf("%03d:%02d", hour, minute % 60);
			cout << ' ' << "blue" << " " << warriorName[cities[i].p2->kind]
				<< " " << cities[i].p2->No << " has " << cities[i].p2->weaponKindNumber[0]
				<< " sword " << cities[i].p2->weaponKindNumber[1] << " bomb " <<
				cities[i].p2->weaponKindNumber[2] << " arrow"
				<< " and " << cities[i].p2->lifePoint << " elements" << endl;
		}
	}
}

//����Ϊmain����------------------------------------------------------------------
int main()
{
	int u = 0;
	cin >> u;
	int caseNo = 1;
	while (u--)
	{
		cout << "Case " << caseNo++ << ":" << endl;
		//����-----------------------------------
		int life, t;//Ҫ�������0ʱ0�ֿ�ʼ����ʱ��tΪֹ(����t) �������¼�,t�Է���Ϊ��λ.
		cin >> life >> cityNum >> k >> t;
		headquarter Blue(life, 0), Red(life, 1);//0--blue,1--red
		for (int i = 0; i < warriorNum; i++)
			cin >> warrior::birthData[i];
		for (int i = 0; i < warriorNum; i++)
			cin >> warriorAggressivity[i];
		hour = 0; minute = 0;
		for (int i = 0; i < 21; i++)
		{
			cities[i].p1 = NULL;
			cities[i].p2 = NULL;
		}
		//----------------------------------------
		while (minute <= t)
		{
			//��ÿ�����㣬��ÿ��Сʱ�ĵ�0�֣� ˫����˾��и���һ����ʿ������
			Red.produceWarrior();
			Blue.produceWarrior();
			minute += 5;
			if (minute > t)break;
			//��ÿ��Сʱ�ĵ�5�֣������ܵ�lion������һʱ�������ˡ�
			Red.warriorescape();
			Blue.warriorescape();
			minute += 5;
			if (minute > t)break;
			//��ÿ��Сʱ�ĵ�10�֣����е���ʿ������˾�����ǰ��һ����
			//���Ӽ���˾��ߵ����ڳ��У����һ�������ߵ���һ�����С���Ӻ͵о�˾����ڵĳ��е���о�˾���
			Red.warriorMatch();
			Blue.warriorMatch();
			int b = Blue.win(); 
			match();
			int a = Red.win();if (b == 1)break;
			if (a == 1)break;
			minute += 25;
			if (minute > t)break;
			//��ÿ��Сʱ�ĵ�35�֣�����wolf������˵ĳ��У�wolfҪ����Է���������
			warriorloot();
			minute += 5;
			if (minute > t)break;
			//��ÿ��Сʱ�ĵ�40�֣�����������ʿ�ĳ��У��ᷢ��ս����
			combat();
			minute += 10;
			if (minute > t)break;
			//��ÿ��Сʱ�ĵ�50�֣�˾�������ӵ�е�����Ԫ������
			Red.reportLifePoints();
			Blue.reportLifePoints();
			minute += 5;
			if (minute > t)break;
			//��ÿ��Сʱ�ĵ�55�֣�ÿ����ʿ������ӵ�е����������
			reportWeapon();
			minute += 5;
			hour += 1;
		}
	}
	return 0;
}