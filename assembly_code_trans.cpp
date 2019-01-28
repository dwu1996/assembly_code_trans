
// 
//     組合語言轉二進位檔程式 
//     design by N.C.Wu, NTHUHSS, Taiwan.
//     版權所有，轉載請註明出處 
//
//     ver 1.0 
//     2016/03/27 at 清大 
// 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void inttobin(int in,int bin[])    //十進位轉二進位 
{
	int i;
	for(i=0;i<32;i++){bin[i]=0;}   //淨空陣列 
	if(in>=0)      //正數 
	{
		for(i=0;i<32;i++)
		{
			bin[31-i]=in%2;
			in=in/2;
		}
	}
	else           //負數 
	{
		in=in*(-1);	in=in-1;
		for(i=0;i<32;i++)
		{
			bin[31-i]=in%2;
			in=in/2;
		}
		for(i=0;i<32;i++)
		{
			if(bin[i]==0) {bin[i]=1;}
			else          {bin[i]=0;}
		}
	}
	return;
}

void regtobin(char ch[],int bin[])    //轉換位址
{
	int i;
	for(i=0;i<32;i++){bin[i]=0;}   //淨空bin陣列 
	if(ch[1]=='z'){	}
	else if(ch[1]=='v')
	{
		if(ch[2]=='0'){bin[3]=1;}
		if(ch[2]=='1'){bin[3]=1;bin[4]=1;}
	}
	else if(ch[1]=='a')
	{
		if(ch[2]=='0'){bin[2]=1;}
		if(ch[2]=='1'){bin[2]=1;bin[4]=1;}
		if(ch[2]=='2'){bin[2]=1;bin[3]=1;}
		if(ch[2]=='3'){bin[2]=1;bin[3]=1;bin[4]=1;}
		if(ch[2]=='t'){bin[4]=1;}
	}
	else if(ch[1]=='t')
	{
		if(ch[2]=='0'){bin[1]=1;}
		if(ch[2]=='1'){bin[1]=1;bin[4]=1;}
		if(ch[2]=='2'){bin[1]=1;bin[3]=1;}
		if(ch[2]=='3'){bin[1]=1;bin[3]=1;bin[4]=1;}
		if(ch[2]=='4'){bin[1]=1;bin[2]=1;}
		if(ch[2]=='5'){bin[1]=1;bin[2]=1;bin[4]=1;}
		if(ch[2]=='6'){bin[1]=1;bin[2]=1;bin[3]=1;}
		if(ch[2]=='7'){bin[1]=1;bin[2]=1;bin[3]=1;bin[4]=1;}
		if(ch[2]=='8'){bin[0]=1;bin[1]=1;}
		if(ch[2]=='9'){bin[0]=1;bin[1]=1;bin[4]=1;}
	}
	else if(ch[1]=='s')
	{
		if(ch[2]=='0'){bin[0]=1;}
		if(ch[2]=='1'){bin[0]=1;bin[4]=1;}
		if(ch[2]=='2'){bin[0]=1;bin[3]=1;}
		if(ch[2]=='3'){bin[0]=1;bin[3]=1;bin[4]=1;}
		if(ch[2]=='4'){bin[0]=1;bin[2]=1;}
		if(ch[2]=='5'){bin[0]=1;bin[2]=1;bin[4]=1;}
		if(ch[2]=='6'){bin[0]=1;bin[2]=1;bin[3]=1;}
		if(ch[2]=='7'){bin[0]=1;bin[2]=1;bin[3]=1;bin[4]=1;}
		if(ch[2]=='p'){bin[0]=1;bin[1]=1;bin[2]=1;bin[4]=1;}
	}
	else if(ch[1]=='g')
	{
		bin[0]=1;bin[1]=1;bin[2]=1;
	}
	else if(ch[1]=='f')
	{
		bin[0]=1;bin[1]=1;bin[2]=1;bin[3]=1;
	}
	else if(ch[1]=='r')
	{
		bin[0]=1;bin[1]=1;bin[2]=1;bin[3]=1;bin[4]=1;
	}
	
	for(i=0;i<6;i++){ch[i]=0;}   //淨空ch陣列 
	return;
}

int main(void)
{
	//宣告:R、I、J、S各型別助憶詞
	char opr[][6]={{'a','d','d',' ',' ',' ',},{'a','d','d','u',' ',' ',},{'s','u','b',' ',' ',' ',},
	               {'a','n','d',' ',' ',' ',},{'o','r',' ',' ',' ',' ',},{'x','o','r',' ',' ',' ',},
				   {'n','o','r',' ',' ',' ',},{'n','a','n','d',' ',' ',},{'s','l','t',' ',' ',' ',},
				   {'s','l','l',' ',' ',' ',},{'s','r','l',' ',' ',' ',},{'s','r','a',' ',' ',' ',},
				   {'j','r',' ',' ',' ',' ',}};

	char opi[][6]={{'a','d','d','i',' ',' ',},{'a','d','d','i','u',' ',},{'l','w',' ',' ',' ',' ',},
	               {'l','h',' ',' ',' ',' ',},{'l','h','u',' ',' ',' ',},{'l','b',' ',' ',' ',' ',},
				   {'l','b','u',' ',' ',' ',},{'s','w',' ',' ',' ',' ',},{'s','h',' ',' ',' ',' ',},
				   {'s','b',' ',' ',' ',' ',},{'l','u','i',' ',' ',' ',},{'a','n','d','i',' ',' ',},
				   {'o','r','i',' ',' ',' ',},{'n','o','r','i',' ',' ',},{'s','l','t','i',' ',' ',},
				   {'b','e','q',' ',' ',' ',},{'b','n','e',' ',' ',' ',},{'b','g','t','z',' ',' ',}};

	char opj[][6]={{'j',' ',' ',' ',' ',' ',},{'j','a','l',' ',' ',' '}};

	char ops[][6]={{'h','a','l','t',' ',' '}};;

	//主程序
	FILE *in;
	in=fopen("assemcode.txt","r");
	if(in==NULL)  //若讀不到檔案
	{    printf("Error: File not found.\n ");   return 0;	}
	
	FILE *out;  //宣告輸出檔、輸出dim 
	out=fopen("iimage.bin","wb");
	unsigned char dim[4]= {0};
	int *bin=(int*)malloc(32*sizeof(int));    //十進位轉二進位用、轉換位址用 
	char *ch=(char*)malloc(6*sizeof(char));   //轉換位址用 
	
	int i,j,k;  //暫存及迴圈用值 
	
	printf("Please enter your initial PC value (suggest set 0) : ");  //設定初始PC值 
	scanf("%d",&k);
	inttobin(k,bin);
	for(i=0;i<4;i++)    //轉換成二進位檔 
	{
		dim[i]=bin[i*8];
		for(j=1;j<8;j++)
		{
			dim[i]=dim[i]*2;
			dim[i]=dim[i]+bin[i*8+j];
		}
	}
	fwrite(dim,sizeof(char),4,out);
	
	printf("Please enter how many lines needs to convert : ");  //設定ilines值
	scanf("%d",&k);
	inttobin(k,bin);
	for(i=0;i<4;i++)    //轉換成二進位檔 
	{
		dim[i]=bin[i*8];
		for(j=1;j<8;j++)
		{
			dim[i]=dim[i]*2;
			dim[i]=dim[i]+bin[i*8+j];
		}
	}
	fwrite(dim,sizeof(char),4,out);
	printf("\n") ;

	int end=0;
	while(end==0)
	{
		int reg[32]={};
		char inch[2048]={};
		
		char *rinch=fgets(inch,2048,in);
		if(rinch==NULL){end=1;}  //讀入檔案到底

		int strl=strlen(inch)-1;
		int check=0;  //紀錄值
		for(i=0;i<strl;i++)
		{
			if(inch[i]=='#'){check=1;}  //註解後全刪除
			if(check==1){inch[i]=0;}
		}
		strl=strlen(inch)-1;  //重新確認
		//printf("%s",rinch);
		//printf("%s\n",ops[0]);
		for(i=0;i<strl;i++){printf("%c",inch[i]);}
		printf("\n");

		int pos=0;    //讀取位置 
		char f[6]={};
		for(i=0;i<6;i++){f[i]=32;}
		for(i=0;i<6;i++)
		{
			if(inch[i]==32||inch[i]=='\n'||inch[i]=='\0')  {pos+=i;pos++;break;}
			f[i]=inch[i];
		}
		
		int op=0,opn;  //讀取最前段助憶詞並確認種類，op=主類型，opn=次類型 
		for(i=0;i<13;i++)
		{
			if(strncmp(f,opr[i],6)==0)  {op=1;opn=i;break;}
		}
		for(i=0;i<18;i++)
		{
			if(strncmp(f,opi[i],6)==0)  {op=2;opn=i;break;}
		}
		for(i=0;i<2;i++)
		{
			if(strncmp(f,opj[i],6)==0)  {op=3;opn=i;break;}
		}
		for(i=0;i<1;i++)
		{
			if(strncmp(f,ops[i],6)==0)  {op=4;opn=i;break;}
		}
		//printf("%d  %d\n",op,opn);
		
		if(op==4)    //type s
		{
			for(i=0;i<32;i++){reg[i]=1;}
		}
		else if(op==3)    //type j
		{
			if(opn==0)
			{
				reg[4]=1;
				printf("There is a [j] instruction, where do you want go to? ");
				int jp; scanf("%d",&jp);
				inttobin(jp,bin);
				for(i=0;i<26;i++){reg[31-i]=bin[31-i];}
			}
			else if(opn==1)
			{
				reg[4]=1;
				printf("There is a [jal] instruction, where do you want go to? ");
				int jp; scanf("%d",&jp);
				inttobin(jp,bin);
				for(i=0;i<26;i++){reg[31-i]=bin[31-i];}
			}
		}
		else if(op==2)    //type i
		{
			if(opn==0)		{reg[2]=1;}    //寫入opcode 
			if(opn==1)		{reg[2]=1;reg[5]=1;}
			if(opn==2)		{reg[0]=1;reg[4]=1;reg[5]=1;}
			if(opn==3)		{reg[0]=1;reg[5]=1;}
			if(opn==4)		{reg[0]=1;reg[3]=1;reg[5]=1;}
			if(opn==5)		{reg[0]=1;}
			if(opn==6)		{reg[0]=1;reg[3]=1;}
			if(opn==7)		{reg[0]=1;reg[2]=1;reg[4]=1;reg[5]=1;}
			if(opn==8)		{reg[0]=1;reg[2]=1;reg[5]=1;}
			if(opn==9)		{reg[0]=1;reg[2]=1;}
			if(opn==10)		{reg[2]=1;reg[3]=1;reg[4]=1;reg[5]=1;}
			if(opn==11)		{reg[2]=1;reg[3]=1;}
			if(opn==12)		{reg[2]=1;reg[3]=1;reg[5]=1;}
			if(opn==13)		{reg[2]=1;reg[3]=1;reg[4]=1;}
			if(opn==14)		{reg[2]=1;reg[4]=1;}
			if(opn==15)		{reg[3]=1;}
			if(opn==16)		{reg[3]=1;reg[5]=1;}
			if(opn==17)		{reg[3]=1;reg[4]=1;reg[5]=1;}
			
			for(i=0;i<6;i++){f[i]=32;}    //讀入rs 
			j=0;
			for(i=pos;i<(pos+6);i++)
	    	{
		    	if(inch[i]==32||inch[i]=='\n'||inch[i]=='\0')  {pos=i;pos++;break;}
		    	f[j]=inch[i];  j++;
    		}
    		
    		//printf("%c%c",f[0],f[1]);printf("\n");
    		
    		if(opn==10)    //lui例外，只輸入rt
    		{
    			for(i=0;i<6;i++){ch[i]=f[i];}
    			regtobin(ch,bin);
    			for(i=0;i<5;i++)
    			{
					reg[i+11]=bin[i];
				}
				
			}
			else
			{
				if(opn==17)    //bgtz例外，只輸入rs
				{
					for(i=0;i<6;i++){ch[i]=f[i];}
    			    regtobin(ch,bin);
    		    	for(i=0;i<5;i++)
    		    	{
    		    		reg[i+6]=bin[i];
			    	}
				}
				else
				{
					for(i=0;i<6;i++){ch[i]=f[i];} //輸入rs
    			    regtobin(ch,bin);
    		    	for(i=0;i<5;i++)
    		    	{
    		    		reg[i+11]=bin[i];
			    	}
			    	
			    	if(opn>=2&&opn<=9)    //處理常數在rt前的指令 
			    	{
			    		if(inch[pos]=='0'&&inch[pos+1]=='x') {pos=pos+2;}  //處理0x開頭
			    		k=0;
						for(i=0;i<4;i++)    //加總常數 
						{
							if(inch[pos]=='$'){break;}    //考慮完全沒有常數 
							if(inch[pos]=='(')    //處理括號並去除 
							{
								if(inch[pos+4]==')') {inch[pos+4]=32;}
								if(inch[pos+6]==')') {inch[pos+4]=32;}
								pos++; break; 
							}
							k=k*16;
							if(inch[pos]>='0'&&inch[pos]<='9')  //處理16進位 
							{
								k=k+(inch[pos]-48);pos++;
							}
							if(inch[pos]>='A'&&inch[pos]<='F')  //考慮大寫 
							{
								k=k+(inch[pos]-65)+10;pos++;
							}
							if(inch[pos]>='a'&&inch[pos]<='f')  //考慮小寫 
							{
								k=k+(inch[pos]-97)+10;pos++;
							}
						}
						inttobin(k,bin);
						for(i=0;i<16;i++)  {reg[31-i]=bin[31-i];}
					}
					
				 	for(i=0;i<6;i++){f[i]=32;}    //讀入rt 
			       	j=0;
    				for(i=pos;i<(pos+6);i++)
    		    	{
    			    	if(inch[i]==32||inch[i]=='\n'||inch[i]=='\0')  {pos=i;pos++;break;}
   				    	f[j]=inch[i];  j++;
   	    	  		}
	      	    	for(i=0;i<6;i++){ch[i]=f[i];}
    			    regtobin(ch,bin);
    		    	for(i=0;i<5;i++)
    		    	{
    	    			reg[i+6]=bin[i];
		    		}
			    	
				}
			}
			
    		if(opn>=2&&opn<=9){	}    //前面處理過 
    		else
    		{
				if(inch[pos]==32){}    //讀入常數 
    			else if(inch[pos]=='-')
    			{
    				j=0;  pos++;
    				while(inch[pos]>='0'&&inch[pos]<='9')
					{
						j=j*10;  j=j+(inch[pos]-48);
						pos++;
					}
					j=j*(-1);
				}
				else if(inch[pos]>='0'&&inch[pos]<='9')
				{
					j=(inch[pos]-48); pos++;
					while(inch[pos]>='0'&&inch[pos]<='9')
					{
						j=j*10;  j=j+(inch[pos]-48);
						pos++;
					}
				}
				inttobin(j,bin);
				for(i=0;i<16;i++)  {reg[31-i]=bin[31-i];}
			}
		}
		else if(op==1)    //type r
		{
			if(opn==0)		{reg[26]=1;}    //寫入function code 
			if(opn==1)		{reg[26]=1;reg[31]=1;}
			if(opn==2)		{reg[26]=1;reg[30]=1;}
			if(opn==3)		{reg[26]=1;reg[29]=1;}
			if(opn==4)		{reg[26]=1;reg[29]=1;reg[31]=1;}
			if(opn==5)		{reg[26]=1;reg[29]=1;reg[30]=1;}
			if(opn==6)		{reg[26]=1;reg[29]=1;reg[30]=1;reg[31]=1;}
			if(opn==7)		{reg[26]=1;reg[28]=1;}
			if(opn==8)		{reg[26]=1;reg[28]=1;reg[30]=1;}
			if(opn==9)		{}
			if(opn==10)		{reg[30]=1;}
			if(opn==11)		{reg[30]=1;reg[31]=1;}
			if(opn==12)		{reg[28]=1;}
			
			if(opn==13)	{	}    //jr例外
			else
			{
				for(i=0;i<6;i++){f[i]=32;}    //讀入rd 
		    	j=0;
				for(i=pos;i<(pos+6);i++)
		    	{
			    	if(inch[i]==32||inch[i]=='\n'||inch[i]=='\0')  {pos=i;pos++;break;}
			    	f[j]=inch[i];  j++;
	    		}
	    		for(i=0;i<6;i++){ch[i]=f[i];}
    			regtobin(ch,bin);
    			for(i=0;i<5;i++)
    			{
    				reg[i+16]=bin[i];
				}
			}
			if(opn==9||opn==10||opn==11)    {	}     //sll、srl、sra例外 
			else
			{
				for(i=0;i<6;i++){f[i]=32;}    //讀入rs
		    	j=0;
				for(i=pos;i<(pos+6);i++)
		    	{
			    	if(inch[i]==32||inch[i]=='\n'||inch[i]=='\0')  {pos=i;pos++;break;}
			    	f[j]=inch[i];  j++;
	    		}
	    		for(i=0;i<6;i++){ch[i]=f[i];}
    			regtobin(ch,bin);
    			for(i=0;i<5;i++)
    			{
    				reg[i+6]=bin[i];
				}
		    }
			if(opn==13)	{	}    //jr例外
			else
			{
				for(i=0;i<6;i++){f[i]=32;}    //讀入rt
		    	j=0;
				for(i=pos;i<(pos+6);i++)
		    	{
			    	if(inch[i]==32||inch[i]=='\n'||inch[i]=='\0')  {pos=i;pos++;break;}
			    	f[j]=inch[i];  j++;
	    		}
	    		for(i=0;i<6;i++){ch[i]=f[i];}
    			regtobin(ch,bin);
    			for(i=0;i<5;i++)
    			{
    				reg[i+11]=bin[i];
				}
		    }
		    
			if(opn==9||opn==10||opn==11)    //讀入C(位移量) 
			{
				if(inch[pos]==32){}    //C=0
				else if(inch[pos]=='-')
				{
					j=0;  pos++;
    				while(inch[pos]>='0'&&inch[pos]<='9')
					{
						j=j*10;  j=j+(inch[pos]-48);
						pos++;
					}
					j=j*(-1);
				}
				else if(inch[pos]>='0'&&inch[pos]<='9')
				{
					j=(inch[pos]-48); pos++;
					while(inch[pos]>='0'&&inch[pos]<='9')
					{
						j=j*10;  j=j+(inch[pos]-48);
						pos++;
					}
				}
				inttobin(j,bin);
				for(i=0;i<5;i++)  {reg[25-i]=bin[31-i];}
			}
			
		}
		
		if(end==0)
		{
			for(i=0;i<32;i++)   //寫入程序 
			{printf("%d",reg[i]);}
			printf("\n\n");
		
			for(i=0;i<4;i++)    //轉換成二進位檔 
			{
				dim[i]=reg[i*8];
				for(j=1;j<8;j++)
				{
					dim[i]=dim[i]*2;
					dim[i]=dim[i]+reg[i*8+j];
				}
			}
			fwrite(dim,sizeof(char),4,out);
	    }
	}
	
	printf("Please enter any key to exit.");
	while(1)
	{
		char t;
		scanf("%c",&t);
		if(t!='\n')
		{break;}
	}
	free(bin);  free(ch);
	return 0;
}

