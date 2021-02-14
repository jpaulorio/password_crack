int skip(int a[], ulong length, int base);
int compare(char a[], int b[]);

__kernel
void passwordCrack(__global char* password, __global char* crackedPassword, ulong maxScanSize,
int passwordSize, int lastChar, int pageSize, int pageIndex)
{
	ulong wd = get_work_dim();
	ulong gs = get_global_size(0);
	ulong gi = get_global_id(0);

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
	
	skip(tempCrackPassword, start, lastChar + 1);
	
	for (ulong j = start; j < end; j++) {

		if (compare(tempPassword, tempCrackPassword) == 0) {
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