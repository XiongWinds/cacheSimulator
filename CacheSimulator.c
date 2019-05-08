#include "base.h"
#include "CacheSimulator.h"

int main()
{
	  CacheInfo *cacheinfo = (CacheInfo*)malloc(sizeof(CacheInfo));
	  memset(cacheinfo,0,sizeof(CacheInfo));
	  HitRatio *hitRatio = (HitRatio*)malloc(sizeof(HitRatio));
	  memset(hitRatio,0,sizeof(HitRatio));
	  
    InterFace(cacheinfo);
    CalclateRatio(cacheinfo,hitRatio);
    OutputResult(cacheinfo);
    
    return 0;	
}

