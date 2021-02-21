#include "Location.h"
#include "Util.h"
Location::Location(int location)
	:location(location)
{

}

bool Location::locationInfluence(Location nowLocation,int seed){
	return Util::getRisk(nowLocation.location, seed);
}
string Location::getDescription() {
	if (!(location >= 0 && location < 7)) return (string)"wrong weather...please check system.";
	switch (location) {
	case 0: {//Ͽ��
		return (string)"Here is a canyon, strange but a canyon.";
	}
	case 1: {//ƽ��
		return (string)"The flat terrain makes it a good place for racing";
	}
	case 2: {//��ɽ
		return (string)"There are volcanoes here. Who on earth decided to compete where there are volcanoes!";
	}
	case 3: {//����
		return (string)"There is a hill 50 meters high, which is not surprising.";
	}
	case 4: {//���Ӷ�
		return (string)"There are rabbit holes everywhere -- but no Alice";
	}
	case 5: {//ʨ��
		return (string)"There are prairies and lions -- shouldn't they be in zoos?";
	}
	case 6: {//��ˮ
		return (string)"There's some standing water -- is there any chance our men will drown?";
	}
	}
	return (string)"Sorry,something wrong.";
}