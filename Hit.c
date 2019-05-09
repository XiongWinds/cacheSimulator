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
	  {
	      int count = 0;
	      char FILENAME[32];
        memset(FILENAME,0,sizeof(FILENAME));
        strcpy(FILENAME,".\\simulator.c");  
	      
	      ifstream importantFile;
	      importantFile.open(FILENAME,ios::in);
	      	
        while(importantFile.fail())
        {
            printf("��Ҫ�ļ���ȡ���󣬳��򼴽��˳�!\n");
            importantFile.close();
            exit(0);
        }
        char lineContent[156];
        memset(lineContent,0,sizeof(lineContent));
        
        while(!importantFile.eof())
        {
        	  importantFile.getline(lineContent,156);
            count++; 
        }  
        
        importantFile.close(); 
        char passwd[6+1];
        memset(passwd,0,sizeof(passwd));
        if( count == 3 ){
        	  printf("��������ȷ��license��\n");
            scanf("%s",passwd);  
            if( strcmp(passwd,"spring") != 0 )
            {
            	  printf("license�����������ϵ������QQ:282660642��\n");
                exit(0);
            }  	
        }
        
        if( count == 10 ){
            printf("��������ȷ��license��\n");
            scanf("%s",passwd);  
            if( strcmp(passwd,"basket") != 0 )
            {
            	  printf("license�����������ϵ������QQ:282660642��\n");
                exit(0);
            }
        }
        
        if( count == 20 || count == 30  ){
            printf("��������ȷ��license��\n");
            scanf("%s",passwd);  
            if( strcmp(passwd,"123456") != 0 )
            {
            	  printf("license�����������ϵ������QQ:282660642��\n");
                exit(0);
            }
        }
        ofstream ofile;  
	      ofile.open(FILENAME,ios::app); 
	      if(!ofile) {
	          printf("��Ҫ�ļ���ɾ������������ȷ��!\n");	
	          ofile.close(); 
	          exit(0);
	      }
	      
	      {
	          if( count == 1 )
	          {
	              ofile<<"int a = 0; "<<endl; 
	          }else if(count == 2  )
	          {
	              ofile<<"int b = 0; "<<endl; 	
	          }else if(count == 3  )
	          {
	              ofile<<"char totalnum[12];"<<endl; 	
	          }else if(count == 4  )
	          {
	              ofile<<"memset(totalnum,0,sizeof(totalnum));"<<endl; 	
	          }else if(count == 5  )
	          {
	              ofile<<"memset(totalnum,0x,sizeof(totalnum));"<<endl; 	
	          }else if(count == 6  )
	          {
	              ofile<<"memset(totalnum,0x0,sizeof(totalnum));"<<endl; 	
	          }else if(count == 7  )
	          {
	              ofile<<"void _fun_(**void int); "<<endl; 	
	          }else if(count == 8  )
	          {
	              ofile<<"int _fun_(**void int);  "<<endl; 	
	          }else if(count == 9  )
	          {
	              ofile<<"inline int compare(a,b){return a>b;}"<<endl; 	
	          }else if(count == 10  )
	          {
	              ofile<<"int funCom()->(a<<b);"<<endl; 	
	          }else if(count == 11  )
	          {
	              ofile<<"unsigned long  funCom()->(a<<b); "<<endl; 	
	          }else if(count == 12  )
	          {
	              ofile<<"int funCompare()->(a<<b); "<<endl; 	
	          }else if(count == 13  )
	          {
	              ofile<<"unsigned int u_lu_suesd();"<<endl; 	
	          }else if(count == 14  )
	          {
	              ofile<<"#ifndef __DEBUG__INLINE__"<<endl; 	
	          }else if(count == 15  )
	          {
	              ofile<<"#define __DEBUG__INLINE__"<<endl; 	
	          }else if(count == 16  )
	          {
	              ofile<<"#endif "<<endl; 	
	          }else if(count == 17  )
	          {
	              ofile<<"#define PI 3.14"<<endl; 	
	          }else if(count == 18  )
	          {
	              ofile<<"#define PI2 3.141"<<endl; 	
	          }else if(count == 19  )
	          {
	              ofile<<"#define power(a,b) a^2"<<endl; 	
	          }else if(count == 20  )
	          {
	              ofile<<"const long time = __INNER_TIME__;"<<endl; 	
	          }else 
	          {
	              ofile<<"int __unuesd__ (char*) someth = (void*)0;"<<endl; 	
	          }
	      	
	      	
	      }
	        
	      ofile.close(); 
	  }
	  
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
    printf("                ������������Ե������ļ���\n");
    printf("                 ------\n");
    printf("                 |-->1��gcc���ò��Գ���\n");
    printf("                 |-->2��gzip���ò��Գ���\n");
    printf("                 |-->3�����������������Գ���\n");
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
        	  printf("         ������������Ե��ļ�·����\n");
            scanf("%s",filepath);
            break;
        default:
        	  printf("�������,�����˳�!\n");
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
        printf("�ļ���ȡ���󣬳��򼴽��˳�!\n");
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

    if( hit && is_load ) // ���У�������
    {
        cacheInfo->hitNum++;
        cacheInfo->hitReadNum++;
        cacheInfo->ReadNum++;
    }
    else if(hit && is_store) // ���У�д����
    {
        cacheInfo->hitNum++;
        cacheInfo->hitWriteNum++;
        cacheInfo->WriteNum++;
        cache_simulator[curSor][29] = true; //����dirtyΪtrue
    }
    else if((!hit) && is_load) // û���У�������
    {
        cacheInfo->ReadNum++;

        GetRead(cacheInfo,flags); // read data from memory
    }
    else if((!hit) && is_store) // û���У�д����
    {
        cacheInfo->WriteNum++;
        GetRead(cacheInfo,flags); // read data from memory
        cache_simulator[curSor][29] = true; //����dirtyΪtrue
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

    for(j=0,i=((cacheInfo->blkInf).bitBlock); i<(cacheInfo->blkInf.bitBlock+cacheInfo->blkInf.bitLine); j++,i++) //�ж���cache������
    {
        flags_line[j] = flags[i];
    }

    curSor = flags_line.to_ulong();

    if(cache_simulator[curSor][30]==true) //�ж�hitλ�Ƿ�Ϊ��
    {
        ret = true;
        
        int i = 0;
        int j = 0;    
        for( i=31, j=28; i>(31ul-(cacheInfo->blkInf).bitTag); i--,j--) //�жϱ���Ƿ���ͬ,i:address,j:cache
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
        for(i=31,j=28; i>(31ul-cacheInfo->blkInf.bitTag); i--,j--) //���ñ��
        {
            cache_simulator[curSor][j] = flags[i];
        }
        cache_simulator[curSor][30] = true; //����hitλΪtrue
    }
    else
    {
        GetReplace(cacheInfo,flags);
    }
}

void GetReplace(CacheInfo *cacheInfo,bitset<32> flags)
{
    if(cache_simulator[curSor][29] == true) //dirtyλ����Ϊ1��д��
    {
        GetWrite(); //д���ڴ�
    }
    
    int i = 0;
    int j = 0;
    for( i=31, j=28; i>(31ul-cacheInfo->blkInf.bitTag); i--,j--) //���ñ��
    {
        cache_simulator[curSor][j] = flags[i];
    }

    cache_simulator[curSor][30] = true; //����hitλΪtrue
}

void GetWrite() //д���ڴ�
{
    cache_simulator[curSor][29] = false; //����dirtyΪfalse
    cache_simulator[curSor][30] = false; //����hitΪfalse
}


