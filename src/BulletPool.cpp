#include "BulletPool.h"
#include <iostream>
#include <vector>
using namespace std;

BulletPool::BulletPool(int size)
{
	for (int i = 0; i < size; i++)
	{
		Target* bullet = new Target();
		inactive.push_back(bullet);
		all.push_back(bullet);

	}

	cout << "Bullet Pool created with size " << size << endl;
}

Target* BulletPool::Spawn()
{
	Target* bullet = NULL;
	if (inactive.size() > 0)
	{
		bullet = inactive.back();
		bullet->Reset();
		bullet->active = true;
		inactive.pop_back();
		active.push_back(bullet);
		cout << "Spawned bullet!" << endl;
		cout << "Active count " << to_string(active.size()) << endl;
	}
	else
	{
		cout << "ERROR: Max Bullets Spawned." << endl;
	}
	return bullet;
}

void BulletPool::Despawn(Target* bullet)
{
	bullet->active = false;
	inactive.push_back(bullet);

	for (vector<Target*>::iterator myiter = active.begin(); myiter != active.end(); myiter++)
	{
		if (*myiter == bullet)

		{
			active.erase(myiter);
			return;
		}
	}
}