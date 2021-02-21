#ifndef UTIL_H
#define UTIL_H
/*
* Description:�����࣬���������ʼ��
*
*/
#include "Team.h"

#include <vector>
class Util {
public:
	//�õ����α���֮��ļ��
	static int getInterval(int);
	static vector<Team*> getRandomTeam(int);
	static Athlete* getRandomAthlete(bool, int);
	static string getRandomManName(int);
	static string getRandomWomanName(int);
	static Psychologist* getRandomPsychologist(int);
	static Manager* getRandomManager(int);
	static Coach* getRandomCoach(int);
	static Therapist* getRandomTherapist(int);
	static bool getRandomGender(int);
	static int* getRandomCapacity(int);
	static int* getRandomPotential(int);
	static int getRandomCharacterstic(int);
	static int getRandomInt(int);
	static int getRandomWeather(int);
	static int getRandomLocation(int);
	static int getTrackScore(double A, double B, double C, double P);
	static int getFieldScore(double A, double B, double C, double P);
	static bool getRisk(int odds,int seed);
};

#endif // !UTIL_H