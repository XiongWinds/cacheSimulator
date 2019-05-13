#include "base.h"
#include "HelperTools.h"
#include <unistd.h>

void LogDebug(char * ss)
{   
#ifdef DEBUG	
   printf("%s\n",ss);
#endif
}

void LogNormalInfo(char * ss)
{   
   printf(ss);     
}
void InterFace(CacheInfo *cacheinfo)
{
	unsigned long cacheSize;
	unsigned long cacheLineSize;
	printf("                                                              \n");
    printf("                                                              \n");
    printf("                                                              \n");
    printf("                ##############################################\n");
    printf("                ### ��������ԭ��Cache������ģ������ҵ  ###\n");
    printf("                ###      ѧԺ���������ѧ�빤��ѧԺ        ###\n");
    printf("                ###         ѧ��:201671010107              ###\n");
    printf("                ###           ��������С��                 ###\n");
    printf("                ##############################################\n");
    printf("                                                              \n");
    printf("                                                              \n");
    
    puts("                 ������cache�Ĵ�С(��λ:KB)");
    scanf("%ld",&cacheSize);
    puts("                 ������cache���д�С(��λ:B)");
    scanf("%ld",&cacheLineSize);
    
    puts("                 ���������ӳ�䷽ʽ��ֱ�ӹ���");
    puts("                 ����������滻���ԣ�ֱ���滻");

    
    struct blockInfo bInf; 
    unsigned long temp = cacheLineSize; 
    unsigned long bit_block = 0;

    while(temp)
    {
        temp >>= 1;
        bit_block++;
    }
    bit_block--; 
    
    bInf.bitBlock = bit_block;
    bInf.numLine = (cacheSize<<10)/cacheLineSize;
    unsigned long tempNumLine = bInf.numLine;
    unsigned long bit_line = 0;
    while(tempNumLine)
    {
        tempNumLine >>= 1;
        bit_line++;
    }
    bit_line--;
    bInf.bitLine = bit_line;
    bInf.bitTag = 32ul - bit_block - bit_line;
    
    cacheinfo->icacheSize = cacheSize;
    cacheinfo->icacheLineSize = cacheLineSize;
    cacheinfo->blkInf = bInf;
    cacheinfo->hitNum = 0;
    cacheinfo->hitReadNum = 0;
    cacheinfo->hitWriteNum = 0;
    cacheinfo->totalNum = 0;
    
    char tempSS[256];
    memset(tempSS,0,sizeof(tempSS));
    sprintf(tempSS,"cacheinfo->icacheSize ==%ld",cacheSize);
    LogDebug(tempSS);
    memset(tempSS,0,sizeof(tempSS));
    sprintf(tempSS,"cacheinfo->cacheLineSize ==%ld",cacheLineSize);
    LogDebug(tempSS);
    
    return;
}


void OutputResult(CacheInfo *cacheinfo)
{
#ifdef DEBUG	
	printf("cacheinfo->hitNum==%ld\n",cacheinfo->hitNum);
	printf("cacheinfo->hitReadNum==%ld\n",cacheinfo->hitReadNum);
	printf("cacheinfo->hitWriteNum==%ld\n",cacheinfo->hitWriteNum);
	printf("cacheinfo->totalNum==%ld\n",cacheinfo->totalNum);
	printf("cacheinfo->ReadNum==%ld\n",cacheinfo->ReadNum);
	printf("cacheinfo->WriteNum==%ld\n",cacheinfo->WriteNum);
	printf("cacheinfo->unknownNum==%ld\n",cacheinfo->unknownNum);
#endif	  
    
    printf("\n");
	printf("                 ################################################\n");
	printf("                 ###            cache���ò���˵��             ###\n");
	printf("                 ###            cache������: %06ld KB        ###\n",(long)cacheinfo->icacheSize);
	printf("                 ###            cache������: %06ld B         ###\n",(long)cacheinfo->icacheLineSize);
	printf("                 ###            cache����: %06ld             ###\n",cacheinfo->blkInf.numLine);
	printf("                 ###            cache���ж�����: %06ld       ###\n",cacheinfo->hitReadNum);
	printf("                 ###            cache����д����: %06ld       ###\n",cacheinfo->hitWriteNum);
	printf("                 ###            cache����������: %06ld       ###\n",cacheinfo->hitNum);
	printf("                 ###            ���Գ����ַ������: %06ld    ###\n",cacheinfo->totalNum);
	printf("                 ################################################\n");
    printf("\n");
    printf("\n");
    

    printf("                 �������������У����Ե�...\n");
    sleep(3);                
    printf("                 �������������У����Ե�...\n");
    sleep(3);                
	printf("                 ����������ɣ����ս��������ʾ��\n");
	printf("                 \n");
	printf("                 \n");
	sleep(1);                
	printf("                 ################################################\n");
    sleep(1); 
    printf("                 ###   ƽ��������Ϊ��       %02.4f  %%        ###\n",(float)(cacheinfo->hitNum)*100/cacheinfo->totalNum);
    sleep(1); 
    printf("                 ###   ������������Ϊ��     %02.4f  %%        ###\n",(float)(cacheinfo->hitReadNum)*100/cacheinfo->ReadNum);
    sleep(1); 
    printf("                 ###   д����������Ϊ��     %02.4f  %%        ###\n",(float)(cacheinfo->hitWriteNum)*100/cacheinfo->WriteNum); 
    printf("                 ################################################\n");

	  
}
