#ifndef ASTROFOCUS_COMMAND_LINE_ARGS_INC
#define ASTROFOCUS_COMMAND_LINE_ARGS_INC

static BOOL AfNextCommandLineArgument(LPCWSTR commandLine,int* cursor,LPWSTR output,int capacity){
    if(!commandLine||!cursor||!output||capacity<2||*cursor<0)return FALSE;
    int i=*cursor;while(commandLine[i]==L' '||commandLine[i]==L'\t')i++;
    if(!commandLine[i]){output[0]=0;*cursor=i;return FALSE;}
    BOOL quoted=FALSE;int count=0;
    while(commandLine[i]){
        wchar_t ch=commandLine[i];
        if(ch==L'"'){quoted=!quoted;i++;continue;}
        if(!quoted&&(ch==L' '||ch==L'\t'))break;
        if(count>=capacity-1){output[0]=0;*cursor=-1;return FALSE;}
        output[count++]=ch;i++;
    }
    if(quoted){output[0]=0;*cursor=-1;return FALSE;}
    output[count]=0;while(commandLine[i]==L' '||commandLine[i]==L'\t')i++;*cursor=i;return count>0;
}
static BOOL AfCommandLineArgumentEquals(LPCWSTR argument,LPCWSTR expected){
    if(!argument||!expected)return FALSE;int i=0;while(argument[i]&&expected[i]&&argument[i]==expected[i])i++;return !argument[i]&&!expected[i];
}
static int AfCommandLineArgumentCount(LPCWSTR commandLine,LPCWSTR expected){
    if(!commandLine||!expected||!expected[0])return 0;
    wchar_t argument[512];int cursor=0,count=0;
    while(AfNextCommandLineArgument(commandLine,&cursor,argument,512))if(AfCommandLineArgumentEquals(argument,expected))count++;
    return cursor<0?-1:count;
}
static BOOL AfCommandLineHasArgument(LPCWSTR commandLine,LPCWSTR expected){return AfCommandLineArgumentCount(commandLine,expected)==1;}
static BOOL AfGetCommandLineOption(LPCWSTR commandLine,LPCWSTR option,LPWSTR output,int capacity){
    if(!commandLine||!option||!option[0]||!output||capacity<2)return FALSE;
    output[0]=0;wchar_t argument[512],value[512];int cursor=0;BOOL found=FALSE;
    while(AfNextCommandLineArgument(commandLine,&cursor,argument,512)){
        if(!AfCommandLineArgumentEquals(argument,option))continue;
        if(found||!AfNextCommandLineArgument(commandLine,&cursor,value,512)||AfCommandLineArgumentEquals(value,option)){output[0]=0;return FALSE;}
        int n=0;while(value[n])n++;if(n>=capacity){output[0]=0;return FALSE;}
        for(int i=0;i<=n;i++)output[i]=value[i];found=TRUE;
    }
    if(cursor<0){output[0]=0;return FALSE;}
    return found;
}

#endif
