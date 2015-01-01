__kernel
void passwordCrack(__global char* password, __global char* crackedPassword, int maxScanSize, int passwordSize, int lastChar)
{
	int gs = get_global_size(0);
	int gi = get_global_id(0);

//if (gi == 1) {
	int found = 0;
	int tempCrackPassword[4];

	int start = (maxScanSize/gs) * gi;
	int end = start + (maxScanSize / gs) - 1;

	if (maxScanSize % 2 == 1) {
		end = end + 1;
	}

	// printf("start->%d\n", start);
	// printf("end->%d\n", end);
	// printf("lastChar->%d\n", lastChar);

	skip(tempCrackPassword, start, lastChar);
	
	// printf("c0->%d\n",tempCrackPassword[0]);
	// printf("c1->%d\n",tempCrackPassword[1]);
	// printf("c2->%d\n---------\n",tempCrackPassword[2]);

	for (int j = start; j < end; j++) {
	
		if (compare(password,tempCrackPassword) == 0) {
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

	 // printf("a0->%d\n",crackedPassword[0]);
	 // printf("a1->%d\n",crackedPassword[1]);
	 // printf("a2->%d\n---------\n",crackedPassword[2]);

//}
 }

int skip(int a[], int length, int lastChar){
	int result = length / (lastChar+1);
	int mod = length % (lastChar+1);
	int count = 0;

	while (result > 0) {
		// printf("count->%d\n",count);
		// printf("result->%d\n",result);
		// printf("mod->%d\n",mod);
		a[count] += mod;

		mod = result % (lastChar+1);
		result = result / (lastChar+1);
		count++;
	}
	a[count] += mod;	

	// printf("count->%d\n",count);
	// printf("result->%d\n",result);
	// printf("mod->%d\n",mod);
	// printf("a0->%d\n",a[0]);
	// printf("a1->%d\n",a[1]);
	// printf("a2->%d\n",a[2]);

	return 0;
}

int strlen(char a[]) {
	int result = 0;
	while (a[result] != '\0') {
		result++;
	}
	return result;
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