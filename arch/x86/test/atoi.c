int atoi(const char *str)
{
	int num=0;
	int sign=0;
	if(str!=NULL){
//step the space
		for(;*str==' '||*str=='\t';str++);
//judge the first num is 1 or -1
		if(*str=='-'){
			sign=1;
			str++;
		}
		if(*str=='+'){
			str++;
		}
//change
		while(*str!='\0'){
			if(*str>='0'&&*str<='9'){
				num=num*10+(*str-'0');
				str++;
			}
			else{
				num=num+0;
				break;
			}	
		}			
	}
	if(sign)
		num=0-num;
	return 0;

}











