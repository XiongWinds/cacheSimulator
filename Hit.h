#ifndef __HIT__H__
#define __HIT__H__

#include "HelperTools.h"
#include <bitset>
using namespace std;

void CalclateRatio(CacheInfo *cacheInfo,HitRatio *hitRatio);
bool GetShotCount(CacheInfo *cacheInfo,char *address);
bool ifShot(CacheInfo *cacheInfo,bitset<32> flags);
void GetRead(CacheInfo *cacheInfo,bitset<32> flags);
void change(CacheInfo *cacheInfo,bitset<32> flags);

#endif