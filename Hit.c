#include "base.h"
#include "Hit.h"
#include <fstream>
#include <bitset>

using namespace std;

#define MAX_CACHE_LINE 65536 
bitset<32> cache_simulator[MAX_CACHE_LINE];

unsigned long int curSor = 0;

void CalclateRatio(CacheInfo *cacheInfo,HitRatio *hitRatio)
{
	  
    for(unsigned long i=0; i<(cacheInfo->blkInf).numLine; i++)
    {
        cache_simulator[i][31] = true;
    }
    char filepath[100];
    memset(filepath,0,sizeof(filepath));
    ifstream in_file;
    char address[13];
    memset(address,0,sizeof(address));
    int traceTag = 0;
    printf("                请输入你想测试的内置文件：\n");
    printf("                 ------\n");
    printf("                 |-->1：gcc内置测试程序\n");
    printf("                 |-->2：gzip内置测试程序\n");
    printf("                 |-->3：自行输入其他测试程序\n");
    printf("                 ------\n");
    
    scanf("%d",&traceTag);
    switch(traceTag){
        case 1:
        	  strcpy(filepath,".\\gcc.c");
            break;
        case 2:
            strcpy(filepath,".\\gzip.c");
            break;
        case 3:
        	  printf("         请输入你想测试的文件路径：\n");
            scanf("%s",filepath);
            break;
        default:
        	  printf("输入错误,程序退出!\n");
        	  exit(0);	
    }
    
    char tempSS[256];
    memset(tempSS,0,sizeof(tempSS));
    sprintf(tempSS,"filepath ==%s\n",filepath);
#ifdef DEBUG    
    printf(tempSS);
#endif    
    in_file.open(filepath,ios::in);

    while(in_file.fail())
    {
        printf("文件读取错误，程序即将退出!\n");
        in_file.close();
        exit(0);
    }
    
    while(!in_file.eof())
    {
        in_file.getline(address,13);
        bool __attribute__((unused)) is_success = GetHitNum(cacheInfo,address); 
        cacheInfo->totalNum++;
        
        memset(tempSS,0,sizeof(tempSS));
        sprintf(tempSS,"address ==%s\n",address);
#ifdef DEBUG        
        printf(tempSS);
#endif        
    }

    in_file.close();
	
}


bool GetHitNum(CacheInfo *cacheInfo,char *address)
{
    bool is_store = false;
    bool is_load = false;
    //bool is_space = false;
    bool hit = false;

    switch(address[0])
    {
        case 's':
            is_store = true;
            break;
        
        case 'l':
            is_load = true;
            break;
        
        case '\0':
            break; //In case of space lines
        
        default:
            return false;
    }
    unsigned long int temp = 0;
    temp = strtoul(address+2,NULL,16);
    bitset<32> flags(temp); // flags if the binary of address
    hit = IsHit(cacheInfo,flags);

    if( hit && is_load ) // 命中，读操作
    {
        cacheInfo->hitNum++;
        cacheInfo->hitReadNum++;
        cacheInfo->ReadNum++;
    }
    else if(hit && is_store) // 命中，写操作
    {
        cacheInfo->hitNum++;
        cacheInfo->hitWriteNum++;
        cacheInfo->WriteNum++;
        cache_simulator[curSor][29] = true; //设置dirty为true
    }
    else if((!hit) && is_load) // 没命中，读操作
    {
        cacheInfo->ReadNum++;

        GetRead(cacheInfo,flags); // read data from memory
    }
    else if((!hit) && is_store) // 没命中，写操作
    {
        cacheInfo->WriteNum++;
        GetRead(cacheInfo,flags); // read data from memory
        cache_simulator[curSor][29] = true; //设置dirty为true
    }
    else
    {
    	  cacheInfo->unknownNum++;
        //printf("Something ERROR\n");
        return false;
    }
    return true;
}

bool IsHit(CacheInfo *cacheInfo,bitset<32> flags)
{
    bool ret = false;

    bitset<32> flags_line; // a temp variable
    int j = 0;
    int i = 0;

    for(j=0,i=((cacheInfo->blkInf).bitBlock); i<(cacheInfo->blkInf.bitBlock+cacheInfo->blkInf.bitLine); j++,i++) //判断在cache多少行
    {
        flags_line[j] = flags[i];
    }

    curSor = flags_line.to_ulong();

    if(cache_simulator[curSor][30]==true) //判断hit位是否为真
    {
        ret = true;
        
        int i = 0;
        int j = 0;    
        for( i=31, j=28; i>(31ul-(cacheInfo->blkInf).bitTag); i--,j--) //判断标记是否相同,i:address,j:cache
        {
            if( flags[i] != cache_simulator[curSor][j] )
            {
                ret = false;
                break;
            }
        }
    }    
    return ret;
}

void GetRead(CacheInfo *cacheInfo,bitset<32> flags)
{
    if(cache_simulator[curSor][30] == false) //hit is false
    {
    	  int i = 0;
    	  int j = 28;
        for(i=31,j=28; i>(31ul-cacheInfo->blkInf.bitTag); i--,j--) //设置标记
        {
            cache_simulator[curSor][j] = flags[i];
        }
        cache_simulator[curSor][30] = true; //设置hit位为true
    }
    else
    {
        GetReplace(cacheInfo,flags);
    }
}

void GetReplace(CacheInfo *cacheInfo,bitset<32> flags)
{
    if(cache_simulator[curSor][29] == true) //dirty位必须为1才写入
    {
        GetWrite(); //写入内存
    }
    
    int i = 0;
    int j = 0;
    for( i=31, j=28; i>(31ul-cacheInfo->blkInf.bitTag); i--,j--) //设置标记
    {
        cache_simulator[curSor][j] = flags[i];
    }

    cache_simulator[curSor][30] = true; //设置hit位为true
}

void GetWrite() //写入内存
{
    cache_simulator[curSor][29] = false; //设置dirty为false
    cache_simulator[curSor][30] = false; //设置hit为false
}


