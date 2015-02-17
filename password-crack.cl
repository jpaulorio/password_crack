int skip(int a[], ulong length, int base);
int compare(char a[], int b[]);

__kernel
void passwordCrack(__global char* password, __global char* crackedPassword, ulong maxScanSize, int passwordSize, int lastChar, int pageSize, int pageIndex)
{
	ulong wd = get_work_dim();
	ulong gs = get_global_size(0);
	ulong gi = get_global_id(0);

//if (gi == 0 && pageIndex == 0) {
	int found = 0;
	char tempPassword[6];
	int tempCrackPassword[6];
	for (int i = 0; i < 6; i++) {
		tempCrackPassword[i] = 0;
		tempPassword[i] = password[i];
	}

	ulong start = (((maxScanSize/pageSize)/gs) * gi) + ((maxScanSize/pageSize) * pageIndex);
	ulong end = start + ((maxScanSize/pageSize)/gs) - 1;

	if (maxScanSize % 2 == 1) {
		end = end + 1;
	}

	//if (gi == gs-10321) {
	//if (gi > gs-15433 && gi < gs-10320) {
	//if (gi > 245730 && gi < gs) {
		// printf("maxScanSize->%lu\n", maxScanSize);
		// printf("index->%lu\n", pageIndex);
		// printf("start->%lu\n", start);
		// printf("end->%lu\n", end);
		// printf("lastChar->%lu\n", lastChar);
		// printf("gs->%lu\n", gs);
//		printf("gi->%lu\n", gi);
		// printf("wd->%lu\n", wd);
	
	
	skip(tempCrackPassword, start, lastChar + 1);
	
	// printf("c0->%d\n",tempCrackPassword[0]);
	// printf("c1->%d\n",tempCrackPassword[1]);
	// printf("c2->%d\n",tempCrackPassword[2]);
	// printf("c3->%d\n---------\n",tempCrackPassword[3]);
	
	for (ulong j = start; j < end; j++) {

	 // printf("a0->%d\n",tempCrackPassword[0]);
	 // printf("a1->%d\n",tempCrackPassword[1]);
	 // printf("a2->%d\n",tempCrackPassword[2]);
	 // printf("a3->%d\n---------\n",tempCrackPassword[3]);
	
		//if (tempCrackPassword[0] == 122 && tempCrackPassword[1] == 122 && tempCrackPassword[2] == 122
		//	&& tempCrackPassword[3] == 122) {
		if (compare(tempPassword, tempCrackPassword) == 0) {
			//printf("j->%d-gi->%d-value->%d-start->%lu-end->%lu\n", j, gi, tempCrackPassword[3], start, end);
			found = 1;
		  	break;
		}

		tempCrackPassword[0]++;

		for (int i = 0; i < passwordSize; i++) {			
		  	if (tempCrackPassword[i] == (lastChar + 1)) {
		    	tempCrackPassword[i] = 0;
		    	tempCrackPassword[i+1]++;
		  	}        
		}
	}

	if (found == 1) {
		for (int i=0; i<passwordSize; i++) {
			crackedPassword[i] = tempCrackPassword[i];
		}
	}

	 // printf("a0->%d\n",tempCrackPassword[0]);
	 // printf("a1->%d\n",tempCrackPassword[1]);
	 // printf("a2->%d\n",tempCrackPassword[2]);
	 // printf("a3->%d\n---------\n",tempCrackPassword[3]);

//}
 }

int skip(int a[], ulong length, int base){

	ulong m = length;
	ulong n = base;
	ulong s = 0;
	int count = 0;

	while (m >= n) {
		s = m % n;
		a[count] = s;
		m = m / n;
		count++;
	}
	a[count] = m;

	return 0;
}

int compare(char a[], int b[])
{
   int c = 0;
 
   while( a[c] == b[c] )
   {
      if( a[c] == '\0' || b[c] == '\0' )
         break;
      c++;
   }
   if( a[c] == '\0' && b[c] == '\0' )
      return 0;
   else
      return -1;
}