#ifndef __HIT__H__
#define __HIT__H__

#include "HelperTools.h"
#include <bitset>
using namespace std;

void CalclateRatio(CacheInfo *cacheInfo,HitRatio *hitRatio);
bool GetHitNum(CacheInfo *cacheInfo,char *address);
bool IsHit(CacheInfo *cacheInfo,bitset<32> flags);
void GetRead(CacheInfo *cacheInfo,bitset<32> flags);
void GetReplace(CacheInfo *cacheInfo,bitset<32> flags);
void GetWrite();

#endif