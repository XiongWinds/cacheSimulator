#ifndef __BASE_H__
#define __BASE_H__

typedef struct HitRatio{
	double avgHitRatio;
	double readHitRatio;
	double WriteHitRatio;
}HitRatio;

typedef struct blockInfo{
	unsigned long bitBlock;
	unsigned long numLine;
	unsigned long bitLine;
	unsigned long bitTag;
}blockInfo;

typedef struct CacheInfo{
    unsigned int icacheSize;
    unsigned int icacheLineSize;
    struct blockInfo blkInf;
    unsigned long hitNum;
    unsigned long hitReadNum;
    unsigned long hitWriteNum;
    unsigned long ReadNum;
    unsigned long WriteNum;
    unsigned long totalNum;	
    unsigned long unknownNum;
}CacheInfo;



#endif