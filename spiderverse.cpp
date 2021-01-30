#include <iostream>
#include <string.h>
#include <time.h>
#include <cstdlib>
#include <unistd.h>
#include <string>

using namespace std;

const int chance_to_block = 40;

struct signature_ability
{
	int health_boost;
	int attack_boost;
	signature_ability()
	{
		health_boost = 0;
		attack_boost = 0;
	}
	signature_ability(int HEALTH_BOOST, int ATTACK_BOOST)
	{
		health_boost = HEALTH_BOOST;
		attack_boost = ATTACK_BOOST;
	}
};

class character
{
	char* name;
	int health;
	int attack;
	int chance_to_awade;
	int crit_chance;
public:
	character()
	{
		name = NULL;
		health = 0;
		attack = 0;
		chance_to_awade = 0;
		crit_chance = 0;
	}
	character(char* NAME, int HEALTH, int ATTACK, int CTA, int CC)
	{
		name = new char[strlen(NAME) + 1];
		strcpy(name, NAME);
		health = HEALTH;
		attack = ATTACK;
		chance_to_awade = CTA;
		crit_chance = CC;
	}
	void boost(int b)
	{
		health += b;	
	}
	char* getname()
	{
		return name;
	}
	void reducehealth(int hit)
	{
		health -= hit;
	}
	int gethealth()
	{
		return health;
	}
	int getattack()
	{
		return attack;
	}
	int getcta()
	{
		return chance_to_awade;
	}
	int getcc()
	{
		return crit_chance;
	}
	void addattack(int a)
	{
		attack += a;
	}
	void addhealth(int h)
	{
		health += h;
	}
	void addcta(int c)
	{
		chance_to_awade += c;
	}
	void addcc(int cc)
	{
		crit_chance += cc;
	}
	virtual void death(char* name1, char* name2){}
	void landhit(int CC, int ATTACK){}
	void landhit(int CC, int ATTACK, int ATTACKBOOST){}
	void gethit(int CTA, int BLOCK){}
	virtual ~character()
	{
		if (name != NULL)
			delete[] name;
	}
};

class hero: character, signature_ability
{	
public:
	hero():character(), signature_ability(){}
	hero(char* NAME, int HEALTH, int ATTACK, int CTA, int CC, int HEALTH_BOOST, int ATTACK_BOOST ):
	character(NAME, HEALTH, ATTACK, CTA, CC), signature_ability(HEALTH_BOOST, ATTACK_BOOST){}
	void boost(int HEALTH_BOOST)
	{
		character::boost(HEALTH_BOOST);
	}
	char* getname()
	{
		return character::getname();
	}
	int gethealth()
	{
		return character::gethealth();
	}
	void reducehealth(int hit)
	{
		character::reducehealth(hit);
	}
	int getattack()
	{
		return character::getattack();
	}
	int getcta()
	{
		return character::getcta();
	}
	int getcc()
	{
		return character::getcc();
	}
	int gethealthboost()
	{
		return health_boost;
	}
	int getattackboost()
	{
		return attack_boost;
	}
	void killhr()
	{
		this-> ~hero();
	}
	void death(char* name1, char* name2);
	friend ostream & operator << (ostream & out, const hero & obj);
	int landhit(int CC, int ATTACK, int ATTACKBOOST);
	void gethit(int HIT, int CTA, int BLOCK, char* name);
};

class villian: character
{	
public:
	villian():character(){}
	villian(char* NAME, int HEALTH, int ATTACK, int CTA, int CC):
	character(NAME, HEALTH, ATTACK, CTA, CC){}
	char* getname()
	{
		return character::getname();
	}
	int gethealth()
	{
		return character::gethealth();
	}
	void reducehealth(int hit)
	{
		character::reducehealth(hit);
	}
	int getattack()
	{
		return character::getattack();
	}
	int getcta()
	{
		return character::getcta();
	}
	int getcc()
	{
		return character::getcc();
	}
	void killvl()
	{
		this-> ~villian();
	}
	void addattack(int a)
	{
		character::addattack(a);
	}
	void addhealth(int h)
	{
		character::addhealth(h);
	}
	void addcta(int c)
	{
		character::addcta(c);
	}
	void addcc(int cc)
	{
		character::addhealth(cc);
	}
	villian operator +=(villian &vl)
	{
		addhealth(vl.gethealth());
		addattack(vl.getattack());
		addcta(vl.getcta());
		addcc(vl.getcc());
		return *this;
	}
	void death(char* name1, char* name2);
	friend ostream & operator << (ostream & out, const villian & obj);
	int landhit(int CC, int ATTACK);
	void gethit(int HIT, int CTA, int BLOCK, char* name1);
	void gethit(){};
};

void hero::death(char* name1, char* name2)
{
	cout << name1 <<" defeated " << name2 << endl;
	sleep(1);
}

void villian::death(char* name1, char* name2)
{
	cout << name1 <<" defeated " << name2 << endl;
	sleep(1);
}

ostream & operator << (ostream & out, hero & obj)
{
	cout << "You have chosen: " << obj.getname() << endl;
	cout << "Basic parametrs: "<< endl; 
	cout << "Health: "<< obj.gethealth() << endl; 
	cout << "Attack: "<< obj.getattack() << endl; 
	cout << "Chance to awaid: "<< obj.getcta()<<'%' << endl;
	cout << "Crit chance: "<< obj.getcc() <<'%'<< endl; 
	cout << "Signature ability health boost: "<< obj.gethealthboost() << endl; 
	cout << "Signature ability attack boost: "<< obj.getattackboost() << endl;
	return out; 
}

ostream & operator << (ostream & out, villian & obj)
{
	cout << "You have chosen: " << obj.getname() << endl;
	cout << "Basic parametrs: "<< endl; 
	cout << "Health: "<< obj.gethealth() << endl; 
	cout << "Attack: "<< obj.getattack() << endl; 
	cout << "Chance to awaid: "<< obj.getcta()<<'%' << endl;
	cout << "Crit chance: "<< obj.getcc() <<'%'<< endl; 
	return out;
}

int hero::landhit(int CC, int ATTACK, int ATTACKBOOST)
{
	if (CC >= rand()%100)
	{
		cout << this->getname()<<" lands A CRITICAL HIT!!!" << endl;
		sleep(1);
		return 2*(ATTACK + ATTACKBOOST);
	}
	else
	{
		cout << this->getname()<<" lands a hit" << endl;
		sleep(1);
		return ATTACK + ATTACKBOOST;
	}
}

int villian::landhit(int CC, int ATTACK)
{
	if (CC >= rand()%100)
	{
		cout << this->getname()<<" lands A CRITICAL HIT!!!" << endl;
		sleep(1);
		return 2*ATTACK;
	}
	else
	{
		cout << this->getname()<<" lands a hit" << endl;
		sleep(1);
		return ATTACK;
	}
}

void hero::gethit(int HIT, int CTA, int BLOCK, char* name1) 
{
	if (CTA >= rand()%100)
	{
		cout << this->getname() << " EVADED!!!" << endl;
		sleep(2);
	}
	else if (BLOCK >= rand()%100)
	{
		cout << this-> getname() <<" BLOCKED the hit!!!"<< endl;
		sleep(2);
		if (this->gethealth() <= HIT/2)
		{
			this->reducehealth(this->gethealth());
			hero::death(name1, this->getname());
		}
		else
			this->reducehealth(HIT/2);
	}
	else
	{
		if (this->gethealth() <= HIT)
		{
				this->reducehealth(this->gethealth());
				hero::death(name1, this->getname());
		}
			else
				this->reducehealth(HIT);
	}
	cout << "Current health of "<< this->getname() <<": "<<this->gethealth()<<endl;
}

void villian::gethit(int HIT, int CTA, int BLOCK, char* name1) 
{
	if (CTA >= rand()%100)
	{
		cout << this->getname() << " EVADED!!!" << endl;
		sleep(2);
	}
	else if (BLOCK >= rand()%100)
	{
		cout << this-> getname() <<" BLOCKED the hit!!!"<< endl;
		if (this->gethealth() <= HIT/2)
		{
			this->reducehealth(this->gethealth());
			villian::death(name1, this->getname());
		}
		else
			this->reducehealth(HIT/2);
	}
	else
	{
		if (this->gethealth() <= HIT)
		{
				this->reducehealth(this->gethealth());
				villian::death(name1, this->getname());
		}
			else
				this->reducehealth(HIT);
	}
	cout << "Current health of "<< this->getname() <<": "<<this->gethealth()<<endl;
}

int main()
{
	srand(time(0));
	string retry;
	int hr_number;
	int vl_number;
	hero *hr;
	villian *vl;
	int hit;
	
HereWeGoAgain:	
	cout << "Let's have fun!!!" << endl;
	sleep(2);
	cout << "Choose your fighter"<< endl;
	sleep(1);
	cout << "1 - Spiderman"<< endl;
	sleep(1);
	cout << "2 - Spider Gwen"<< endl;
	sleep(1);
	cout << "3 - Spider Woman"<< endl;
	sleep(1);
	cout << "4 - Myles Moralez"<< endl;
	sleep(1);
	cout << "Input a number of your hero: ";
	cin >> hr_number;
	try
	{
		switch (hr_number)
		{
			case 1: 
				hr = new hero((char*)"Spiderman\0", 1100, 100, 15, 35, 0, 10);
				break;	
			case 2: 
				hr = new hero((char*)"Spider Gwen\0", 900, 100, 35, 40, 0, 20);
				break;	
			case 3: 
				hr = new hero((char*)"Spider Woman\0", 1050, 100, 15, 25, 150, 10);
				break;	
			case 4: 
				hr = new hero((char*)"Myles Moralez\0", 1000, 90, 10, 20, 50, 25);
				break;
			default:
				throw -1;
				break;
		}
    }
    catch (int a)
    {
		if (a == -1)
		{
			cout << "incorrect number, spiderman was chosen by default" << endl;
			hr = new hero((char*)"Spiderman", 1100, 100, 15, 35, 0, 10);
		}
	}
    cout << *hr;
	cout << "Perfect choice!"<< endl;
	sleep(2);
	cout << "And now choose your opponent"<< endl;
	sleep(1);
	cout << "1 - Venom"<< endl;
	sleep(1);
	cout << "2 - Doctor Octopus"<< endl;
	sleep(1);
	cout << "3 - Electro" << endl;
	sleep(1);
	cout << "4 - Green Goblin" << endl;
	sleep(1);
	cout << "5 - Vulture" << endl;
	sleep(1);
	cout << "6 - Rhino" << endl;
	sleep(1);
	cout << "Input a number of the villian: ";
	cin >> vl_number;
	switch(vl_number)
	{
		case 1:
			vl = new villian((char*)"Venom\0", 1000, 130, 5, 40);
			break;
		case 2:
			vl = new villian((char*)"Doctor Octopus\0", 1100, 120, 0, 30);
			break;
		case 3:
			vl = new villian((char*)"Electro\0", 900, 150, 0, 25);
			break;
		case 4:
			vl = new villian((char*)"Green Goblin\0", 1200, 95, 3, 28);
			break;
		case 5:
			vl = new villian((char*)"Vulture\0", 1000, 100, 0, 33);
			break;
		case 6:
			vl = new villian((char*)"Rhino\0", 1300, 90, 0, 18);
			break;
		default:
			cout << "incorrect number, venom was chosen by default" << endl;
			vl = new villian((char*)"Venom\0", 1000, 130, 0, 40);
			break;		
	}
	sleep(1);
	cout << *vl;
	sleep(1);
	hr->boost(hr->gethealthboost());
	cout << "Begin" << endl;
	sleep(1);
	cout << "First hit will land: ";
	if(50 < rand())
	{
		cout << vl->getname() << endl;
		while (hr->gethealth() && vl->gethealth())
		{
			hit = vl->landhit(vl->getcc(), vl->getattack());
			hr->gethit(hit, hr->getcta(),chance_to_block, vl->getname());
			sleep(2);
			if(hr->gethealth())
			{
				hit = hr->landhit(hr->getcc(), hr->getattack(),hr->getattackboost());
				vl->gethit(hit, vl->getcta(),chance_to_block, hr->getname());
				sleep(2);
			}
		}
	}
	else
	{
		cout << hr->getname() << endl;
		while (hr->gethealth() && vl->gethealth())
		{
			hit = hr->landhit(hr->getcc(), hr->getattack(),hr->getattackboost());
			vl->gethit(hit, vl->getcta(),chance_to_block, hr->getname());
			sleep(2);
			if(hr->gethealth())
			{
				hit = vl->landhit(vl->getcc(), vl->getattack());
				hr->gethit(hit, hr->getcta(),chance_to_block, vl->getname());
				sleep(2);
			}
		}
	}		
	cout << "GAMEOVER" << endl;
	sleep(2);
	cout << "Retry? (yes/no)" << endl;
	cin >> retry;
	if(retry == "yes")
		goto HereWeGoAgain;
	hr->killhr();
	delete hr;	
	vl->killvl();
	delete vl;
	return 0;
}
