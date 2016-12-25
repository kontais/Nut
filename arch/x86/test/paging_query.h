
int query_mapping(struct plm4_entry *plm4, uint64_t virt_addr, uint64_t *phy_addr, int *flag)
{
//change the method ,for example:high 16 000
	int i,k;
	uint64_t py,vir;
	vir_addr=vir_addr&0x0000ffffffffffff;   //remove high 16 bits
//get the begain phy_addr of pdpte_entry
//plm4.p is the flag which judges weather the paging is present
	if(plm4.p==0){
		printf("false to query!\n");
		return 0;
	}
	else{
		vir=vir_addr>>39;
		py=vir&0x1ff;
		plm4=plm4+py;
	}
//get the begain phy_addr of pde_entry
	if(plm4.p==0){
		printf("false to query!\n");
		return 0;
	}
	else{
		vir=vir_addr>>30;
		py=vir&0x1ff;
		plm4=plm4+py;
	}
//get the begain phy_addr of pte_entry
	if(plm4.p==0){
		printf("false to query!\n");
		return 0;
	}
	else{
		vir=vir_addr>>21;
		py=vir&0x1ff;
		plm4=plm4+py;
	}
//get the begain phy_addr of pte4k_entry
	if(plm4.p==0){
		printf("false to query!\n");
		return 0;
	}
	else{
		vir=vir_addr>>12;
		py=vir&0x1ff;
		plm4=plm4+py;
	}
//get phy_addr 
	if((plm4.p)==0){
		printf("false to query!\n");
		return 0;
	}
	else{
		py=vir_addr&0xfff;
		plm4=plm4+py;	
	}
//get the final flag and phy_addr
	*phy_addr=*plm4;
	return 0;
}





















