//ħ�������ռ���(WarCraft IV)
//���հ� 2021��5��24��
//���ߣ�������  ѧ�ţ�2000013152
#include<iostream>
#include<iomanip>
#include<string>
#include<algorithm>
#include<vector>
#define MAX 10000
using namespace std;

//������ȫ�ֱ���----------------------------------------------------------
const int warriorNum = 5;//��ʿ��������
const int weaponNum = 3;//������������
int hour = 0;//Сʱ
int minute = 0;//����
const int RED = 0, BLUE = 1;//red-0,blue-1
int warriorAggressivity[warriorNum] = { 0 };
//0.sword;1.bomb;2.arrow
const string weaponName[weaponNum] = { "sword","bomb","arrow" };
int arrowAggressivity = 0;//arrow�Ĺ�����
const int workOrder[2][warriorNum] = { {2,3,4,1,0} ,{3,0,1,2,4} };//������ʿ��˳��
const string warriorName[warriorNum] = { "dragon","ninja","iceman","lion","wolf" };//0-dragon,1-ninja.2-iceman,3-lion,4-wolf
const string colorName[2] = { "red","blue" };//0-red,1-blue

//�������������----------------------------------------------------------
class Time;//ά��ʱ��
class Weapon;//ά������
class Headquarter;//ά��˾�
class City;//ά������
class Warrior;//ά����ʿ
class Dragon;//ά����
class Ninja;//ά��ninja
class Iceman;//ά��iceman
class Lion;//ά��ʨ��
class Wolf;//ά����
class World;//ά������ħ������

//��������ľ���ʵ��----------------------------------------------------------
class Weapon
{
private:
	int No;//���
	int aggressivity;//������
	int durability;//�;ö�
public:
	void setAggressivity(Warrior* pWorrior);
	void setDurability();
	int changeAggressivity();
	friend class Dragon;
	friend class Iceman;
	friend class Ninja;
	friend class Lion;
	friend class Wolf;
};

class Headquarter
{
private:
	int lifeNum;//˾�����ֵ
	int warriorQuantity[warriorNum];//ÿ��ʿ���ĸ�����¼
	int Number;//ʿ�����
	int stance;//���������췽������
	int sumWarriorNum;//�������ʿ������
	int totalWarriorNum;//�ִ�ʿ������
	int location;//˾�����λ��
	int reach;//����Է�˾�����ʿ������
	int nextProduce;//��һ����Ҫ�������ʿ������
	Warrior* points[MAX];//ʿ��ָ��
	int destination;//Ŀ�ĵ�
	string colorName;//��ɫ
public:
	Headquarter() :sumWarriorNum(0), reach(0), nextProduce(0), totalWarriorNum(0),
		location(0), destination(0), points{ NULL }{}//���캯��
	void set(int life, int st);//����˾�����ֵ������
	int getLifeNum() { return lifeNum; }
	int getLocation() { return location; }
	int getColor() { return stance; }
	string getColorName() { return colorName; }
	void warriorescape();//ʨ������
	friend class World;//����WorldΪ��Ԫ��
	void reportLifePoints();//�����������
	friend ostream& operator<<(ostream& o, Headquarter& hd);//�������
	friend class Weapon;
	friend class Warrior;
	friend class City;
	friend class Dragon;
	friend class Iceman;
	friend class Ninja;
	friend class Lion;
	friend class Wolf;
};

class Warrior
{
private:
	int No;//��ʿ���
	int kind;//��ʿ����
	int lifePoint;//��ʿ����ֵ
	int stance;//��ʿ�������������
	int aggressivity;//��ʿ������
	int temp;//��ʱ��¼���������ı���
	int position;//��ʿ����λ��
	int swordNum;//��ʿ��ӵ�еĽ����;�ֵ
	int arrowNum;//��ʿ��ӵ�еĹ���������
	int bombNum;//��ʿ��ӵ�е�ը��������
	bool isAlive;//�Ƿ񻹻���
	bool hasArrived;//�Ƿ��Ѿ��ִ�Է�˾�
	int loyalty;//�ҳ�
	vector<Weapon> weapon;//����
	int NumofWeapons;//��������
	int weaponKindNumber[3];//��������
	City* loc;//λ��
	Headquarter* st;//��Ӫ
	int pace;//����
	bool canWeaponUse[10];//�����ܷ�ʹ��
	static int birthData[warriorNum];//��ʼ����ֵ
	double morale;//ʱ��

public:
	Warrior(int n, Headquarter* p);//���캯��
	Warrior() :No(0), kind(0), lifePoint(0), stance(0), aggressivity(0), position(0), swordNum(0),
		arrowNum(0), bombNum(0), isAlive(1), hasArrived(0), loyalty(0), pace(0), morale(0) {};//���캯��
	friend ostream& operator<<(ostream& o, Warrior& w);//�������
	virtual void printState() {};//��ӡ��ʿ����
	void printNow(int n);
	void everyWeapons();//ͳ����������
	virtual int escape() { return 0; }//ʨ������
	void beFought(Warrior& w);//ֱ�����������˹���
	void beFoughtBack(Warrior& w);//ֱ�����������˷���
	virtual void looting(Warrior* opponent) {}//����������
	void match();//�о�ǰ��
	void clearWeapon(int);//��������
	void set(Time& t, int st, int id, int cityNum, int kd, int life, int agg, int loy);//���ø���ָ��
	void setWeapon(int s, int a, int b);//��������ָ��
	void loot(Warrior* opponent);//����������
	void yell(Time& t, int id);//������
	void showmarch();//����о�
	void reachDestination();//����ִ�
	void output();//����������
	//��������Ԫ�������
	friend class City;
	friend class Weapon;
	friend class Headquarter;
	friend class World;
	friend class Dragon;
	friend class Iceman;
	friend class Ninja;
	friend class Lion;
	friend class Wolf;
};

class Dragon :public Warrior
{
private:
	float morale;//ʿ��ֵ
public:
	Dragon(int n, Headquarter* p);//���캯��
	void printState();//��ӡ״̬
	int yell();//����
};

class Ninja :public Warrior
{
public:
	Ninja(int n, Headquarter* p);
	void printState();//״̬
};

class Iceman :public Warrior
{
private:
	int matchCount;//�Ƿ�ǰ��������
public:
	Iceman(int n, Headquarter* p);
	void printState();//��ӡ״̬
	virtual void match();//�о����ı䣩
};

class Lion :public Warrior
{
private:
	int loyalty;//��ʵ��
public:
	Lion(int n, Headquarter* p);
	void printState();//��ӡ״̬
	int escape();//���ܣ�1-escape;0-not escape
};

class Wolf :public Warrior
{
public:
	Wolf(int n, Headquarter* p);
	void printState();//��ӡ״̬
};

class Time
{
private:
	int hour;//ʱ
	int minute;//��
	int limit;//ʱ������
public:
	Time() :hour(0), minute(0), limit(0) {}//���캯��
	void setLimit(int time);//����ʱ������
	friend ostream& operator<<(ostream& o, Time& t);//�������
	int operator+=(int n);//��������ʱ��
};

class City
{
private:
	int flag;//����
	int firstAttack;//˭�ȹ���
	int lifeNum;//����Ԫ
	int No;//���
	int winner;//ʤ���ĳ���
	Warrior* warrior[2];//������ʿָ��
public:
	City() :flag(0), firstAttack(0), lifeNum(0), No(-1), winner(0), warrior{ NULL }{};//���캯��
	void set(int n);//�������
	void setWarrior(Warrior* p, int stance);//������ʿ
	void setFlag(int st, Time& t);//����
	int hasTwoWarriors();//�Ƿ���������ʿ
	void work(Time& t, int st);//�ֳ���ʤ�������øı�
	void change(Time& t, int k);//δ�ֳ�ʤ�������øı�
	void produceElements();//��������Ԫ
	int simulate(Time& t, int k);//ģ�⿪ս
	int fight(Time& t, int k);//˫��������ս��
	friend class World;
	friend class Headquarter;
};

class World
{
private:
	int startLifePoint;//��ʼ����ֵ
	int cityNum;//��������
	int arrowAttack;//�����Ĺ�����
	int loyaltyLost;//��ʵ���½�������
	int limitTime;//����ʱ��
	int startWarriorLifeNum[5];//��ʼ��ʿ������ֵ
	int startWarriorAggressivity[5];//��ʼ��ʿ�Ĺ�����
	Time time;//ʱ����
	Headquarter headquarter[2];//����˾�
	City* cities;//�������
	Warrior* warrior[2];//˫�������ʿ
	int end;
public:
	World(int caseNum);//���캯��
	void produceWarrior(int stance);//������ʿ
	void escape(int postion, int stance);//ʨ������
	void march();//�о�
	void work();//������Ϣ
	void earnLifePoint(int i);//�������ֵ
	void releaseArrow();//�ż���
	void releaseBomb();//��ը����
	void giveBonus(int stance, int position, int& bonus);//���轱��
	void output();
	void fight();//��ս��
	void operation();//����ʱ�������
	void myDelete();//��ֹ�ڴ�����
};

//��������ĳ�Ա����----------------------------------------------------------
//Weapon��
void Weapon::setAggressivity(Warrior* pWorrior)
{
	switch (No)
	{
	case 0:
		aggressivity = pWorrior->aggressivity * 2 / 10; break;
	case 1:
		aggressivity = MAX; break;
	case 2:
		aggressivity = arrowAggressivity; break;
	}
}
void Weapon::setDurability()
{
	switch (No)
	{
	case 0:
		durability = MAX; break;
	case 1:
		durability = 1; break;
	case 2:
		durability = 3; break;
	}
}
int Weapon::changeAggressivity()//0--����
{
	if (No == 0)
	{
		aggressivity = aggressivity * 8 / 10;
		if (aggressivity <= 0)
			return 0;
	}
	return 1;
}

//Headquarter��
void Headquarter::set(int life, int st)
{
	lifeNum = life;
	stance = st;
}
void Headquarter::warriorescape()
{
	int te = 0;//���ڴ����Ѿ���������ʿ
	for (int i = 0; i < totalWarriorNum + te; i++)
	{
		if (points[i] == NULL)//��ʿ�Ѿ�����
		{
			te++;
			continue;
		}
		if (points[i]->escape())//ʨ�������ˣ�
		{
			printf("%03d:%02d", hour, minute % 60);
			cout << ' ' << colorName << ' ' << warriorName[points[i]->kind]
				<< ' ' << points[i]->No << " ran away" << endl;//�����Ϣ
			if (stance == 0)
				points[i]->loc->warrior[0] = NULL;
			else
				points[i]->loc->warrior[1] = NULL;
			points[i] = NULL;
			totalWarriorNum--;//����ʿ����һ
		}
	}
}
void Headquarter::reportLifePoints()
{
	printf("%03d:%02d ", hour, minute % 60);
	cout << lifeNum << " elements in " << colorName << " headquarter" << endl;
}
ostream& operator<<(ostream& o, Headquarter& hd)
{
	o << hd.lifeNum << " elements in " << colorName[hd.stance] << " headquarter" << endl;
	return o;
}

//Warrior��
int Warrior::birthData[warriorNum];
Warrior::Warrior(int n, Headquarter* p): No(n), st(p), weapon(10)
{
	for (int i = 0; i < 10; i++)
		canWeaponUse[i] = true;
}
void Warrior::printNow(int n)
{
	cout << " " << st->colorName << " " << warriorName[n] << " " << No << " born" << endl;
}
ostream& operator<<(ostream& o, Warrior& w)
{
	o << colorName[w.stance] << " " << warriorName[w.kind] << " " << w.No;
	return o;
}
void Warrior::beFought(Warrior& w)
{
	//ÿ��ս��ֻ��һ��������������һ�Ρ�
	//������������ֵ���ȥ�����ߵĹ�����ֵ�ͽ���������sword�Ĺ�����ֵ
	lifePoint = lifePoint - (w.aggressivity + w.swordNum);
	w.swordNum *= 0.8;
}
void Warrior::everyWeapons()
{
	//����һ�飬��һ���Լ�����������
	weaponKindNumber[0] = weaponKindNumber[1] = weaponKindNumber[2] = 0;
	for (int i = 0; i < NumofWeapons; i++)
		weaponKindNumber[No]++;
}
void Warrior::reachDestination()
{
	cout << (*this) << " reached " << colorName[!stance] << " headquarter with "
		<< lifePoint << " elements and force " << aggressivity << endl;
	isAlive = 0;
	hasArrived = 1;
}
void Warrior::beFoughtBack(Warrior& w)
{
	//����������û�����ͻᷢ�𷴻�.
	//�������ߵ�����ֵҪ��ȥ�����߹�����ֵ��һ��(ȥβȡ��)�ͷ���������sword�Ĺ�����ֵ
	lifePoint = lifePoint - (w.aggressivity / 2 + w.swordNum);
	w.swordNum *= 0.8;
}
void Warrior::match()
{
	pace++;
	position = (stance) ? position - 1 : position + 1;
	if (kind == 2 && !(pace % 2))//iceman ÿǰ���������ڵ�2����ɵ�ʱ������ֵ�����9��������������20
	{
		aggressivity += 20;
		lifePoint -= 9;
		if (lifePoint <= 0)//����������ֵ��9���С�ڵ���0��������ֵ����9,���Ǳ�Ϊ1����iceman�������߶��˶���
			lifePoint = 1;
	}
}
void Warrior::showmarch()
{
	cout << (*this) << " marched to city " << position << " with "
		<< lifePoint << " elements and force " << aggressivity << endl;
}
void Warrior::set(Time& t, int st, int id, int cityNum, int kd, int life, int agg, int loy)
{
	isAlive = 1;
	hasArrived = 0;
	No = id;
	stance = st;
	pace = 0;
	kind = kd;
	lifePoint = life;
	aggressivity = agg;
	position = (st == 1) ? cityNum + 1 : 0;
	setWeapon(0, 0, 0);
	cout << t << *this << " born" << endl;
	if (kind == 1)//ninja����ӵ���������������Ϊn��ninja����ʱ����ñ��Ϊ n%3 �� (n+1)%3������
	{
		if (id % 3 == 0)
			setWeapon(aggressivity * 2 / 10, 0, 1);
		else if (id % 3 == 1)
			setWeapon(0, 3, 1);
		else
			setWeapon(aggressivity * 2 / 10, 3, 0);
	}
	else if (kind == 3)//lion �С��ҳ϶ȡ�������ԣ����ʼֵ����������֮����˾�ʣ������Ԫ����Ŀ
	{
		loyalty = loy;
		cout << "Its loyalty is " << loy << endl;
	}
	else if (kind == 0)//dragon����ӵ��һ�����������Ϊn��dragon����ʱ����ñ��Ϊ n%3 ������
	{
		morale = double(loy) / lifePoint;
		printf("Its morale is %.2lf\n", morale);
		if (id % 3 == 0)
			setWeapon(aggressivity * 2 / 10, 0, 0);
		else if (id % 3 == 1)
			setWeapon(0, 0, 1);
		else
			setWeapon(0, 3, 0);
	}
	else if (kind == 2)//iceman����ӵ��һ�����������Ϊn��iceman����ʱ����ñ��Ϊ n%3 ������
	{
		if (id % 3 == 0)
			setWeapon(aggressivity * 2 / 10, 0, 0);
		else if (id % 3 == 1)
			setWeapon(0, 0, 1);
		else
			setWeapon(0, 3, 0);
	}
}
void Warrior::setWeapon(int s, int a, int b)
{
	swordNum = s, arrowNum = a, bombNum = b;
}
void Warrior::loot(Warrior* opponent)
{
	if (!swordNum)
	{
		swordNum = opponent->swordNum;
	}
	if (!bombNum)
	{
		bombNum = opponent->bombNum;
	}
	if (!arrowNum)
	{
		arrowNum = opponent->arrowNum;
	}
}
void Warrior::clearWeapon(int temp)//�����;ö���0������
{
	NumofWeapons = temp;
	for (int i = 0; i < 10; i++)
		if (canWeaponUse[i] == false)//��������
		{
			weapon.erase(weapon.begin() + i, weapon.begin() + (i + 1));
			weapon.resize(10);
			canWeaponUse[i] = true;
		}
}
void Warrior::yell(Time& t, int id)
{
	cout << t << (*this) << " yelled in city " << id << endl;
}
void Warrior::output()
{
	cout << (*this) << " has ";
	int check = 0;
	//���������������
	if (arrowNum)
	{
		cout << "arrow(" << arrowNum << ")";
		check = 1;
	}
	if (bombNum)
	{
		if (check)
			putchar(',');
		cout << "bomb";
		check = 1;
	}
	if (swordNum)
	{
		if (check)putchar(',');
		cout << "sword(" << swordNum << ")";
		check = 1;
	}
	if (!check)
		cout << "no weapon" << endl;
	else
		cout << endl;
}

//Dragon��
Dragon::Dragon(int n, Headquarter* p) :Warrior(n, p)
{
	weapon[0].No = No % weaponNum;
	NumofWeapons = 1;
	temp = NumofWeapons;
	aggressivity = warriorAggressivity[0];
	weapon[0].setAggressivity(this);
	weapon[0].setDurability();
	kind = 0;
	lifePoint = birthData[0];
	morale = (p->getLifeNum()) / (double)birthData[0];
}
void Dragon::printState()
{
	Warrior::printNow(0);
	printf("Its morale is %.2lf", morale);
}
int Dragon::yell()
{
	if (morale <= 0.8)
		return 0;
	printf("%03d:%02d", hour, minute % 60);
	cout << ' ' << colorName[1] << " dragon " << No << " yelled in city ";
	return 1;
}

//Ninja��
void Ninja::printState()
{
		Warrior::printNow(1);
}
Ninja::Ninja(int n, Headquarter* p) :Warrior(n, p)
{
	weapon[0].No = No % weaponNum;
	weapon[1].No = (No + 1) % weaponNum;
	NumofWeapons = 2;
	kind = 1;
	temp = NumofWeapons;
	aggressivity = warriorAggressivity[1];
	lifePoint = birthData[1];
	weapon[0].setAggressivity(this);
	weapon[1].setAggressivity(this);
	weapon[0].setDurability();
	weapon[1].setDurability();
}

//Iceman��
Iceman::Iceman(int n, Headquarter* p) :Warrior(n, p)
{
	weapon[0].No = No % weaponNum;
	NumofWeapons = 1;
	kind = 2;
	temp = NumofWeapons;
	aggressivity = warriorAggressivity[2];
	weapon[0].setAggressivity(this);
	lifePoint = birthData[2];
	weapon[0].setDurability();
}
void Iceman::printState()
{
	Warrior::printNow(2);
}
void Iceman::match()
{
	matchCount++;
	if (matchCount == 2)
	{
		matchCount = 0;
		lifePoint -= 9;
		aggressivity += 20;
		if (lifePoint <= 0)
			lifePoint = 1;
	}
}

//Lion��
Lion::Lion(int n, Headquarter* p) :Warrior(n, p)
{
	kind = 3;
	NumofWeapons = 0;
	temp = NumofWeapons;
	lifePoint = birthData[3];
	aggressivity = warriorAggressivity[3];
	loyalty = p->getLifeNum();
}
void Lion::printState()
{
	Warrior::printNow(3);
	printf("Its loyalty is %d\n", loyalty);
}
int Lion::escape()//1-escape;0-not escape
{
	if (loyalty <= 0 && position != st->destination)
		return 1;
	return 0;
}

//Wolf��
void Wolf::printState()
{
	Warrior::printNow(4);
}
Wolf::Wolf(int n, Headquarter* p) :Warrior(n, p)
{
	kind = 4;
	NumofWeapons = 0;
	temp = NumofWeapons;
	aggressivity = warriorAggressivity[4];
	lifePoint = birthData[4];
}

//Time��
void Time::setLimit(int time)
{
	limit = time;
}
ostream& operator<<(ostream& o, Time& t)
{
	printf("%03d:%02d ", t.hour, t.minute % 60);
	hour = t.hour;
	minute = t.minute;
	return o;
}
int Time::operator+=(int n)
{
	this->minute += n;
	this->hour = minute / 60;
	return minute <= limit;
}

//City��
void City::set(int n)
{
	winner = 0, lifeNum = 0, flag = 0;
	No = n;
	warrior[RED] = warrior[BLUE] = NULL;
	firstAttack = (n + 1) % 2;
}
void City::setFlag(int st, Time& t)
{
	if (st && winner <= 0)//���������
	{
		winner = 1;
		return;
	}
	if (!st && winner >= 0)//���Ϲ����
	{
		winner = -1;
		return;
	}
	if (st&&winner==1)//st==1��ʾ���������ʤ��
	{
		winner = 2;
		if (!flag)
		{
			flag = 1, firstAttack = 1;//�����죬����ʿ�Ƚ���
			cout << t << "blue flag raised in city " << No << endl;
		}
		else if (!firstAttack)
		{
			flag = 1, firstAttack = 1;//�����죬����ʿ�Ƚ���
			cout << t << "blue flag raised in city " << No << endl;
		}
	}
	else if(winner==-1)//�췽ʤ
	{
		winner = -2;
		if (!flag )
		{
			flag = 1;
			firstAttack = 0;//����죬�췽�Ƚ���
			cout << t << "red flag raised in city " << No << endl;
		}
		else if (firstAttack)
		{
			flag = 1;
			firstAttack = 0;//����죬�췽�Ƚ���
			cout << t << "red flag raised in city " << No << endl;
		}
	}
	
}
int City::hasTwoWarriors()
{
	auto p1 = warrior[0];
	auto p2 = warrior[1];
	if (p1 && p2)//˫������
	{
		if (p1->position == No && p2->position == No)
			return 1;
	}
	return 0;
}
void City::work(Time& t, int st)
{
	
	if (warrior[st]->kind == 4)//wolf����ʱû��������������ս���������ʤ��ɱ�����ˣ����ͻ�ɻ���˵����������Լ����е������Ͳ��ɻ���
	{
		warrior[st]->loot(warrior[!st]);
	}
	else if (warrior[st]->kind == 0)//dragon ��һ����������������ս�������������û��ս��������ʿ��ֵ����0.8���ͻỶ��
	{
		warrior[st]->morale += 0.2;
		if (st == firstAttack && warrior[st]->morale > 0.8)
			warrior[st]->yell(t, No);
	}
	cout << t << (*warrior[st]) << " earned " << lifeNum << " elements for his headquarter" << endl;
	setFlag(st, t);//������
}
void City::setWarrior(Warrior* p, int stance)
{
	if (stance == 0) warrior[1] = p;
	else warrior[0] = p;
}
void City::change(Time& t, int k)
{
	winner = 0;//���˻�ʤ
	for (int i = 0; i < 2; i++)
	{
		if (warrior[i]->kind == 3)
			warrior[i]->loyalty -= k;
		else if (warrior[i]->kind == 0)
			warrior[i]->morale -= 0.2;
	}
	if (warrior[firstAttack]->kind == 0 && warrior[firstAttack]->morale > 0.8)//��û��
	{
		cout << t << (*warrior[firstAttack]) << " yelled in city " << No << endl;
	}
}
void City::produceElements()
{
	lifeNum += 10;
}
int City::fight(Time& t, int k)
{
	int tempLifeNum[2] = { warrior[0]->lifePoint,warrior[1]->lifePoint };//��ʱ��¼����ֵ
	int loser;//ʧ����
	warrior[!firstAttack]->beFought(*warrior[firstAttack]);
	cout << t << (*warrior[firstAttack]) << " attacked "
		<< (*warrior[!firstAttack]) << " in city " << No << " with "
		<< warrior[firstAttack]->lifePoint << " elements and force "
		<< warrior[firstAttack]->aggressivity << endl;//�����Ϣ
	if (warrior[!firstAttack]->lifePoint <= 0)//�з����ˣ�
	{
		loser = !firstAttack;
		cout << t << (*warrior[!firstAttack]) << " was killed in city " << No << endl;
		work(t, firstAttack);
		if (warrior[loser]->kind == 3)//lion���������ȡ�Է�����Ԫ
		{
			warrior[!loser]->lifePoint += tempLifeNum[loser];
		}
		return loser;
	}
	else if (warrior[!firstAttack]->kind != 1)//�з�û�����Ҳ���ninja����Ҫ������
	{
		cout << t << (*warrior[!firstAttack]) << " fought back against "
			<< (*warrior[firstAttack]) << " in city " << No << endl;
		warrior[firstAttack]->beFoughtBack(*warrior[!firstAttack]);//���������Ϣ
		if (warrior[firstAttack]->lifePoint <= 0)//����ʹ�������ˣ�
		{
			loser = firstAttack;
			cout << t << (*warrior[loser]) << " was killed in city " << No << endl;
			work(t, !loser);
			if (warrior[loser]->kind == 3)//lion���������ȡlion������Ԫ
			{
				warrior[!loser]->lifePoint += tempLifeNum[loser];
			}
			return loser;
		}
	}
	change(t, k);//��û����ִ��˫�������ŵ�һЩ�仯
	return -1;
}
int City::simulate(Time& t, int k)
{
	//��fight�������������ڽ���ģ�⣬������ʵ�ʸı�
	int tempLifeNum[2] = { warrior[0]->lifePoint,warrior[1]->lifePoint };
	int loser;
	warrior[!firstAttack]->beFought(*warrior[firstAttack]);
	if (warrior[!firstAttack]->lifePoint <= 0)
	{
		loser = !firstAttack;
		return loser;
	}
	else if (warrior[!firstAttack]->kind != 1)//����ninja
	{
		warrior[firstAttack]->beFoughtBack(*warrior[!firstAttack]);
		if (warrior[firstAttack]->lifePoint <= 0)
		{
			loser = firstAttack;
			return loser;
		}
	}
	return -1;
}

//World��
World::World(int caseNum):end(0)
{
	cin >> startLifePoint >> cityNum >> arrowAttack >> loyaltyLost >> limitTime;
	for (int i = 0; i < 5; i++)
		cin >> startWarriorLifeNum[i];
	for (int i = 0; i < 5; i++)
		cin >> startWarriorAggressivity[i];
	cities = new City[cityNum + 2];
	for (int i = 0; i < cityNum + 2; i++)
		cities[i].set(i);//��������
	for (int i = 0; i < 2; i++)
		warrior[i] = new Warrior[limitTime / 60 + 5];
	time.setLimit(limitTime);
	cout << "Case " << caseNum << ":" << endl;
	headquarter[RED].set(startLifePoint, RED);
	headquarter[BLUE].set(startLifePoint, BLUE);
}
void World::produceWarrior(int stance)
{
	auto nowLife = headquarter[stance].lifeNum;//��ǰ˾�����Ԫ
	auto nextProduceLife = startWarriorLifeNum[workOrder[stance][headquarter[stance].nextProduce]];//������һ��Ҫ�������ʿ����������Ԫ
	int searchingNum = 0;
	bool check = false, lifeNum = 0;
	int temp = 1;
	if (lifeNum > Warrior::birthData[workOrder[stance][(nextProduceLife + temp) % 5]])//ѭ������
	{
		lifeNum -= Warrior::birthData[workOrder[stance][(nextProduceLife + temp) % 5]];
		int Number = 1;
		switch (workOrder[stance][(nextProduceLife + temp) % 5])
		{
		case 0:
			headquarter->points[Number] = new Dragon(Number + 1, this->headquarter);
			break;
		case 1:
			headquarter->points[Number] = new Ninja(Number + 1, this->headquarter);
			break;
		case 2:
			headquarter->points[Number] = new Iceman(Number + 1, this->headquarter);
			break;
		case 3:
			headquarter->points[Number] = new Lion(Number + 1, this->headquarter);
			break;
		case 4:
			headquarter->points[Number] = new Wolf(Number + 1, this->headquarter);
			break;
		}
	}
	if (nowLife >= nextProduceLife)//�������������Լ���������ʿ
	{
		auto tempNum = ++headquarter[stance].sumWarriorNum;
		auto tempLocation = (stance == 1) ? cityNum + 1 : 0;
		headquarter[stance].lifeNum -= nextProduceLife;
		warrior[stance][tempNum].set(time, stance, headquarter[stance].sumWarriorNum, cityNum, workOrder[stance][headquarter[stance].nextProduce]
			, nextProduceLife, startWarriorAggressivity[workOrder[stance][headquarter[stance].nextProduce]], headquarter[stance].lifeNum);
		cities[tempLocation].warrior[stance] = &warrior[stance][tempNum];//������ʿ��Ϣ

		headquarter[stance].nextProduce++;//��һ��Ҫ�������ʿ
		headquarter[stance].nextProduce %= 5;//��һ��Ҫ�������ʿ
	}
}
void World::march()
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 1; j <= headquarter[i].sumWarriorNum; j++)//ö��
		{
			if (warrior[i][j].isAlive)//������ʿ�Ͳ��ش�����
			{
				cities[warrior[i][j].position].warrior[i] = NULL;//ԭλ�����
				warrior[i][j].match();//�о�
				cities[warrior[i][j].position].warrior[i] = &warrior[i][j];//��λ��ռ��
			}
		}
	}
}
void World::work()
{
	for (int i = 0; i <= cityNum + 1; i++)//ö��
	{
		for (int j = 0; j < 2; j++)
		{
			if (cities[i].warrior[j])//����ʿ
			{
				cout << time;
				if (i == 0 || (i == cityNum + 1))//���λ����˾�
				{
					headquarter[j].reach++;
					cities[i].warrior[j]->reachDestination();//����Ŀ�ĵ�
					cities[i].warrior[j] = NULL;
					if ((headquarter[j].reach == 2))
					{
						cout << time << colorName[!j] << " headquarter was taken" << endl;
						end = 1;//һ��˾���ռ�ˣ���Ϸ������ע�����ﲻҪֱ��return 0����Ϊ���ܻ���ͬһʱ�̷������¼���Ҫ���
					}
				}
				else
					cities[i].warrior[j]->showmarch();//λ�ò���˾���ֻ����ͨ���о�����
			}
		}
	}
}
void World::earnLifePoint(int i)
{
	for (int k = 0; k < 2; k++)
	{
		if (!cities[i].warrior[k] && cities[i].warrior[!k])//������ֻ�����Լ�
		{
			headquarter[!k].lifeNum += cities[i].lifeNum;//�ջ�����Ԫ
			cout << time << *(cities[i].warrior[!k]) << " earned " << cities[i].lifeNum
				<< " elements for his headquarter" << endl;
			cities[i].lifeNum = 0;//��������Ԫ���ո�
		}
	}
}
void World::releaseArrow()
{
	for (int i = 1; i <= cityNum; i++)
	{
		int dx[] = { 1,-1 };
		for (int j = 0; j < 2; j++)
		{
			if (i + dx[j] >= 1 && i + dx[j] <= cityNum)//��һ���ط��ĳ���λ�úϷ�
			{
				if (cities[i].warrior[j] && cities[i + dx[j]].warrior[!j])//��һ���ط��ео�
				{
					if (cities[i].warrior[j]->arrowNum > 0)//�Լ������й���
					{
						cities[i + dx[j]].warrior[!j]->lifePoint -= arrowAttack;//�ż���ɱ
						cities[i].warrior[j]->arrowNum--;//���������
						if (cities[i + dx[j]].warrior[!j]->lifePoint <= 0)//ɱ���о�
							cout << time << *(cities[i].warrior[j]) << " shot and killed " << *(cities[i + dx[j]].warrior[!j]) << endl;
						else//ûɱ���о�
							cout << time << *(cities[i].warrior[j]) << " shot" << endl;
					}
				}
			}
		}
	}
}
void World::releaseBomb()
{
	for (int i = 1; i <= cityNum; i++)
	{
		if (cities[i].warrior[0] && cities[i].warrior[1])//��������ʿ
		{
			if (cities[i].warrior[0]->lifePoint > 0 && cities[i].warrior[1]->lifePoint > 0)//˫��������
			{
				auto temp1 = *cities[i].warrior[0];//��¼ģ��ǰ״̬
				auto temp2 = *cities[i].warrior[1];//��¼ģ��ǰ״̬
				int temp = cities[i].simulate(time, loyaltyLost); //ģ��һ��ս��!��
				*cities[i].warrior[0] = temp1;//�ָ�ģ��ǰԭ״̬
				*cities[i].warrior[1] = temp2;//�ָ�ģ��ǰԭ״̬
				if (temp == 0 && cities[i].warrior[0]->bombNum)//���ģ����������ʤ���췽��ʹ��ը��
				{
					cout << time << *(cities[i].warrior[0]) << " used a bomb and killed " << *(cities[i].warrior[1]) << endl;
					cities[i].warrior[0]->lifePoint = 0;//ͬ���ھ�
					cities[i].warrior[1]->lifePoint = 0;//ͬ���ھ�
				}
				if (temp == 1 && cities[i].warrior[1]->bombNum)//���ģ�����Ǻ췽ʤ��������ʹ��ը��
				{
					cout << time << *(cities[i].warrior[1]) << " used a bomb and killed " << *(cities[i].warrior[0]) << endl;
					cities[i].warrior[0]->lifePoint = 0;//ͬ���ھ�
					cities[i].warrior[1]->lifePoint = 0;//ͬ���ھ�
				}
			}
		}
	}
}
void World::giveBonus(int stance, int position, int& bonus)
{
	//��ý���
	bonus += cities[position].lifeNum;//�ջ��������Ԫ
	cities[position].warrior[!stance]->isAlive = 0;//�Է�����
	cities[position].warrior[!stance] = NULL;//�Է����ˣ����ָ��
	cities[position].lifeNum = 0;
	if (headquarter[stance].lifeNum - 8 > 0)//˾������Ը��轱��
	{
		headquarter[stance].lifeNum -= 8;
		cities[position].warrior[stance]->lifePoint += 8;
	}
}
void World::output()
{
	for (int i = headquarter[0].sumWarriorNum; i > 0; i--)
	{
		//��������Ż����Ѿ�����Է�˾����������
		if (warrior[0][i].isAlive)
		{
			cout << time;
			warrior[0][i].output();
		}
		else if (warrior[0][i].hasArrived)
		{
			cout << time;
			warrior[0][i].output();
		}
	}
	for (int i = 1; i <= headquarter[1].sumWarriorNum; i++)
	{
		//��������Ż����Ѿ�����Է�˾����������
		if (warrior[1][i].isAlive)
		{
			cout << time;
			warrior[1][i].output();
		}
		else if (warrior[1][i].hasArrived)
		{
			cout << time;
			warrior[1][i].output();
		}
	}
}
void World::fight()
{
	int A = 0, B = 0;
	for (int i = 1; i <= cityNum; i++)
	{
		if (cities[i].warrior[0] && cities[i].warrior[1])//�ó�����������ʿ
		{
			if (cities[i].warrior[0]->lifePoint <= 0 && cities[i].warrior[1]->lifePoint <= 0)//˫��������
			{
				cities[i].warrior[0]->isAlive = 0;
				cities[i].warrior[1]->isAlive = 0;
				cities[i].warrior[0] = cities[i].warrior[1] = NULL;
			}
			else if (cities[i].warrior[0]->lifePoint <= 0)//�췽����
			{
				cities[i].work(time, 1);
				giveBonus(1, i, B);//��B��ý���
			}
			else if (cities[i].warrior[1]->lifePoint <= 0)//��������
			{
				cities[i].work(time, 0);
				giveBonus(0, i, A);//��A��ý���
			}
			else
			{
				//˫�������ţ�׼����ս��
				int temp = cities[i].fight(time,loyaltyLost);
				if (temp == 0)//�췽���ˣ���B��ý���
				{
					giveBonus(1, i, B);
				}
				else if (temp == 1)//�������ˣ���A��ý���
				{
					giveBonus(0, i, A);
				}
			}
		}
		else if (cities[i].warrior[0] != NULL && cities[i].warrior[0]->lifePoint <= 0)//һ������ʿ
		{
			cities[i].warrior[0]->isAlive = 0;
			cities[i].warrior[0] = NULL;
		}
		else if (cities[i].warrior[1] != NULL && cities[i].warrior[1]->lifePoint <= 0)//һ������ʿ
		{
			cities[i].warrior[1]->isAlive = 0;
			cities[i].warrior[1] = NULL;
		}
	}
	headquarter[0].lifeNum += A;//˾���������Ԫ
	headquarter[1].lifeNum += B;
}
void World::escape(int position, int stance)
{
	if (cities[position].warrior[stance]->kind == 3)
	{
		if (cities[position].warrior[stance]->isAlive)
		{
			if (cities[position].warrior[stance]->loyalty <= 0)
			{
				//�ҳ϶Ƚ���0��0���£����lion����ս��,��Զ��ʧ�������Ѿ��������˾���lion�������ܡ�Lion�ڼ���˾��������ܡ�
				cout << time << colorName[stance] << " lion " << cities[position].warrior[stance]->No << " ran away" << endl;
				cities[position].warrior[stance]->isAlive = 0;
				cities[position].warrior[stance] = NULL;
			}
		}
	}
}
void World::operation()
{
	while (true)
	{
		//��ÿ�����㣬��ÿ��Сʱ�ĵ�0�֣� ˫����˾��и���һ����ʿ������
		produceWarrior(0), produceWarrior(1);
		//��ÿ��Сʱ�ĵ�5�֣������ܵ�lion������һʱ�������ˡ�
		if ((time += 5) == 0)
			break;
		for (int i = 0; i <= cityNum + 1; i++)
			for (int j = 0; j < 2; j++)
				if (cities[i].warrior[j])
					escape(i, j);
		//��ÿ��Сʱ�ĵ�10�֣����е���ʿ������˾�����ǰ��һ�������Ӽ���˾��ߵ����ڳ��У����һ�������ߵ���һ�����С�
		//��Ӻ͵о�˾����ڵĳ��е���о�˾���
		if ((time += 5) == 0)
			break;
		march();
		work();
		//��ÿ��Сʱ�ĵ�20�֣�ÿ�����в���10������Ԫ������Ԫ���ڳ��У�ֱ������ʿȡ�ߡ�
		if (end)
			break;
		if ((time += 10) == 0)
			break;
		for (int i = 1; i <= cityNum; i++)
			cities[i].produceElements();
		//��ÿ��Сʱ�ĵ�30�֣����ĳ��������ֻ��һ����ʿ����ô����ʿȡ�߸ó����е���������Ԫ��
		//����������Щ����Ԫ���͵���������˾���
		if ((time += 10) == false)
			break;
		for (int i = 1; i <= cityNum; i++)
			earnLifePoint(i);
		//��ÿ��Сʱ�ĵ�35�֣�ӵ��arrow����ʿ�ż����Ե�������˺����ż��¼�Ӧ�㷢���ڼ������ĳ��С�ע�⣬�ż�������ս����
		//��˷ż�����ʿ����õ��κκô�����ʿ��û�е��˵ĳ��б�������Ҳ��Ӱ�������ڳ��е����ĸ��������
		if ((time += 5) == false)
			break;
		releaseArrow();
		//��ÿ��Сʱ�ĵ�38�֣�ӵ��bomb����ʿ�����Ƿ�Ӧ��ʹ��bomb������ǣ�����bomb�͵���ͬ���ھ���
		if ((time += 3) == false)
			break;
		releaseBomb();
		//��ÿ��Сʱ�ĵ�40�֣�����������ʿ�ĳ��У��ᷢ��ս���� ���������5����ǰ�Ѿ���������arrow��������ô��Ȼ��Ϊ������һ��ս����
		//���Ҵ������Ϊ�����ս����ʤ����������²����С���ʿ����������������ʿ������������ʿս�������¼�������
		//��ս��ʤ����Ӧ�÷��������鶼�ᷢ������Wolfһ���ܽɻ�����������Ҳ���ܸ������ȵȡ�
		//�ڴ������,Dragonͬ����ͨ���ж��Ƿ�Ӧ���ֵ��Լ����������������Ƿ񻶺���
		if ((time += 2) == false)
			break;
		fight();
		//��ÿ��Сʱ�ĵ�50�֣�˾�������ӵ�е�����Ԫ������
		if ((time += 10) == false)
			break;
		for (int i = 0; i < 2; i++)
			cout << time << headquarter[i];
		//��ÿ��Сʱ�ĵ�55�֣�ÿ����ʿ������ӵ�е����������
		if ((time += 5) == false)
			break;
		output();
		//��ÿСʱ�ĵ�60�֣������㣬ѭ����
		if ((time += 5) == false)
			break;
	}
}
void World::myDelete()
{
	delete[] cities;
	delete[] warrior[0];
	delete[] warrior[1];
}

//������main����----------------------------------------------------------
int main()
{
	int num;
	cin >> num;//��������
	const int iterator = num;
	while (num--)
	{
		World world(iterator - num);//�ֱ���
		world.operation();//����ħ�����������
		world.myDelete();//ÿ�����ݲ���������ɾ���ڴ�����
	}
	return 0;
}