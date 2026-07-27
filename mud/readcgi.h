const int NO_REQUEST_METHOD=0;
const int GET_REQUEST_METHOD=1;
const int POST_REQUEST_METHOD=2;
const int OTHER_REQUEST_METHOD=-1;

struct YVarValPair {
    char *Var;
    char *Val;
};

//iGetRequestMethod--取得请求方法类型
int iGetRequestMethod(void);
//SwapChar--将字符串pOriginal中所有的字符cBad换为cGood
void SwapChar(char *pOriginal, char cBad, char cGood);
//IntFromHex--返回字符串前两个字符所代表的16进制数
int IntFromHex(char *pChars);
//URLDecode--对输入字符串pEncoded进行解码,'+'号换为空格,%xx格式的恢复
void URLDecode(char *pEncoded);
//GetPOSTData--读PSOT方式的数据
void GetPOSTData(void);
//PrintVars--打印所有的环境变量(可用于测试)
void PrintVars(void);
//PrintPOSTData--打印所有POST数据Var=Value对(可用于测试)
void PrintPOSTData(void);
//LoadVarValPair--将Var=Value对装入AllVarValPairs中
void LoadVarValPair(char *VarVal);
//LoadPOSTData--将输入缓冲区中POST数据装入AllVarValPairs中
void LoadPOSTData(void);
//FindPOSTValue--读取变量名对应的值
char* FindPOSTValue(char *sVarName);
//GetPOSTMultipartData--读POST multipart/form-data方式的数据
void GetPOSTMultipartData(void);
//LoadPOSTMultipartData--将BinBuffer缓冲区中POST数据装入AllVarValPairs中
void LoadPOSTMultipartData(void);
//addVarValPair--将一对Var=Value添加到AllVarValPairs中
void addVarValPair(char *sVar,char *sValue);
//strtrim--删除字符串末尾的空白符,字符串将被改变
char* strtrim(char *s);
namespace yelin {
//strupr--将字符串中的所有字母转换为大写
char* strupr(char *s);
//strupr--将字符串中的所有字母转换为小写
char* strlwr(char *s);
}//namespace yelin
