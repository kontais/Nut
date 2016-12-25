
#include<stdio.h>
int main()
{
	int i, py,vir_addr,vir;
	printf("please input a number of 12 bits");
	scanf("%d",&vir_addr);
		vir=vir_addr>>8;
		py=vir&15;
  		printf("%d",py);
		vir_addr=vir_addr<<4;
		vir=vir_addr>>8;
		py=vir&15;
  		printf("%d",py);
return 0;	
	
}




int query_mapping(struct plm4_entry *plm4, uint64_t virt_addr, uint64_t *phy_addr, int *flag)
{
//change the method ,for example:high 16 000
	int i,k;
	uint64_t py,vir;
	vir_addr=vir_addr&0x0000ffffffffffff;   //remove high 16 bits
//get after plm4,pdpte,pde,pte address
//flag is used to represent whether the pages are present.	
	k=39;
	for(i=0;i<4;i++)
	{	
		flag=&phy_addr.p;
		if((*flag)==0)
			create_newtable();
		else{
			vir=vir_addr>>k;
			py=vir&0x1ff;
			phy_addr=phy_addr+py;
			k=k-9;
		}
	}
//get phy_addr 
	flag=&phy_addr.p;
	if((*flag)==0)
		create_newtable();
	else{
		py=vir_addr&0xfff;
		phy_addr=phy_addr+py;	
	}
}
