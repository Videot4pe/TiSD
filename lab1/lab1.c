#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

int division(char *d, char *m, int sizeM, int sizeD, char *result);
int main() {
  char mm[30], dd[30], rresult[30];
  char *m;
  char *d;
  char *result;

  result = rresult;
  printf("                  ------------------------------\n");

  printf("Vvedite delimoe:  ");
  d = gets(dd);
  printf("                  ------------------------------\n");

  printf("Vvedite mantissu: ");
  m = gets(mm);

  char pp[30];
  char *ppp;

  int p;
  printf("                  -----\n");
  printf("Vvedite poryadok: ");
  ppp = gets(pp);
  int sizePPP = strlen(ppp);
  //printf("%d", sizePPP);
  for (int i = 0; i < sizePPP; i++)
  {
  	if (*(ppp) == '-')
  		continue;
  	if ((*(ppp+i) == '0') || (*(ppp+i) == '1') || (*(ppp+i) == '2') || (*(ppp+i) == '3') || (*(ppp+i) == '4') || (*(ppp+i) == '5') || (*(ppp+i) == '6') || (*(ppp+i) == '7') || (*(ppp+i) == '8') || (*(ppp+i) == '9') || (*(ppp+i) == ' '))
  	{
  		continue;
  	}
  	else
  	{
  		printf("Error. Unknown symbols");
  		getch();
  		return 1;
  	}
  }
  p = atoi(ppp);
  //scanf("%d", &p);

  //printf("%d", p);

  if (abs(p) > 99999)
  {
  	printf("Overflow order");
  	getch();
  	return 1;
  }

  //puts(m);
  int sizeM = strlen(m);
  int sizeD = strlen(d);
  int y = 0;

  int zz = 0;
  if(*(m) == '-')
  {
  	zz = 1;
    for (int i = 1; i < sizeM; i++)
	{
		m[i-1] = m[i];
	}
	m[sizeM-1] = '0';
	sizeM--;
  	}

  int z = 0;
  if (*d == '-')
  {
    z = 1;
    for (int i = 1; i < sizeD; i++)
	{
		d[i-1] = d[i];
	}
	m[sizeD-1] = '0';
    sizeD--;
  }

  p = sizeD - p;

 if (m[1] == '.')
  {
	if (m[0] != '0')
	{
		p--;
		p--;
		for (int i = 2; i < sizeM; i++)
		{
			m[i-1] = m[i];
		}
		m[sizeM-1] == '0';
		sizeM--;
	}
	else
	{
		int flag = 0;
		for (int i = 2; i < sizeM; i++)
		{
			m[i-1] = m[i];
		}
		sizeM--;
		for (int i = 1; i < sizeM; i++)
		{
			m[i-1] = m[i];
		}
		while (flag == 0)
		{
			if (*(m) == '0')
			{
				for (int i = 1; i < sizeM; i++)
				{
					m[i-1] = m[i];
				}
				sizeM--;
				if (sizeM == 1)
				{
					flag = 1;
					break;
				}
			}
			else
			{
				flag = 1;
				break;
			}
		}
		sizeM--;
		p--;
		//p = p++;
	}
	//puts(m);
  }
  else
  {
	p = p - sizeM - 1;
  }

  //printf("%d", sizeM);
  int lastSymbol = 0;
  int j = 0;
  
  if ((*(d+30) == '0') || (*(d+30) == '1') || (*(d+30) == '2') || (*(d+30) == '3') || (*(d+30) == '4') || (*(d+30) == '5') || (*(d+30) == '6') || (*(d+30) == '7') || (*(d+30) == '8') || (*(d+30) == '9') || (*(d+30) == '0'))
  {
  	printf("Overflow");
  	getch();
  	return 1;
  }
  if ((*(m+30) == '0') || (*(m+30) == '1') || (*(m+30) == '2') || (*(m+30) == '3') || (*(m+30) == '4') || (*(m+30) == '5') || (*(m+30) == '6') || (*(m+30) == '7') || (*(m+30) == '8') || (*(m+30) == '9') || (*(m+30) == '0'))
  {
  	printf("Overflow order");
  	getch();
  	return 1;
  }
  int flag = 0;
  for(int i = 0; i < sizeM; i++)
  {
  	if((*(m+i) != '0') && (*(m+i) != '.'))
	{
		flag = 1;
		break;
	}
  }
  if (flag== 0)
  {
  	printf("Error. Zero division");
  	getch();
  	return 1;
  }

  //printf("%d", sizeD);
  for (int i = 0; i < sizeD; i++)
  {
  	if ((*(d+i) != '0') && (*(d+i) != '1') && (*(d+i) != '2') && (*(d+i) != '3') && (*(d+i) != '4') && (*(d+i) != '5') && (*(d+i) != '6') && (*(d+i) != '7') && (*(d+i) != '8') && (*(d+i) != '9') && (*(d+i) != '0'))
	  {
	  	printf("Unknown symbols");
	  	getch();
	  	return 1;
	  }
  }
  for (int i = 0; i < sizeM; i++)
  {
  	if ((*(m+i) != '0') && (*(m+i) != '1') && (*(m+i) != '2') && (*(m+i) != '3') && (*(m+i) != '4') && (*(m+i) != '5') && (*(m+i) != '6') && (*(m+i) != '7') && (*(m+i) != '8') && (*(m+i) != '9') && (*(m+i) != '0'))
	  {
	  	printf("Unknown symbols");
	  	getch();
	  	return 1;
	  }
  }

  if (*(d) == '0')
  {
  	printf("\nResult: \n");
  	printf("0");
  	getch();
  	return 1;
  }
  lastSymbol, j = division(d, m, sizeM, sizeD, result);
  //p = sizeD - p - y;
  int sizeR = strlen(result);
  for (int i = 0; i < sizeR; i++)
  {
    if (*(result + i) > '9' || *(result + i) < '0')
    {
      *(result + i) = '\0';
    }
  }
  
  p++;
  p++;
  p = p - j;
  if (abs(p) > 99999)
  {
  	printf("Overflow result order");
  	getch();
  	return 1;
  }
  printf("\nResult: \n");
  if ((z == 1 && z != zz) || (z == 0 && zz != z))
    printf("-");
  printf("0.");
  //if (*(result) > '9' || *(result) < '0')
    //printf("1");
  //else
  //puts(result);

 //printf("%d", lastSymbol);
  
  printf("%s", result);
  
  printf(" E %d", p);
  getch();
  return 0;
}

int division(char *d, char *m, int sizeM, int sizeD, char *result)
{
  int rescount = 0;
  int lastValue = 0;
  int lastSymbol = 0;
  int f = 1;
  int i = 0;
  int h = 0;
  while(f == 1)
  {
  	//puts(d);
  	//printf("\n%d\n", sizeD);
  	if (rescount >= 31)
        break;
    for (int y = 0; y < sizeD; y++)
    {
      f = 0;
      if (*(d+y) != '0')
      {
        f = 1;
        break;
      }
    }
    if (f == 0)
    	break;
    //printf("%d", sizeD);
    int l = 0;
    int u = 0;
    if (*(d+u)=='0')
      while(*(d+u)=='0')
      {
        u++;
        if (u >= sizeD)
            break;
      }
    i = u;
    //printf("%d\n", i);
    int last = lastValue;
    lastValue = i;
    //printf("%d ", sizeD);
    while (i-lastValue < sizeM-1)
    {
      //printf("%d %d", i, lastValue);
      i++;
      if (i >= sizeD)
      {
        *(d+i) = '0';
        lastSymbol++;
        sizeD++;
        //printf("%d\n", sizeD);
      }
    }
    //i--;
    int flag = 0;
    //printf("\n%d\n", lastValue);
    //puts(d);

    for(int j = lastValue; j < i+1; j++)
    {
      if (*(d+j) > *(m+l))
        break;
      else if(*(d+j) < *(m+l))
      {
      	if (rescount == 0)
      		h = 1;
        if (i < sizeD - 1)
        {
          i++;
          *(d+lastValue+1) = *(d+lastValue+1) + *(d+lastValue)*10 - '0'*10;
          *(d+lastValue) = '0';
          lastValue++;
        }
        else
        {
          i++;
          *(d+i) = '0';
          sizeD++;
          *(d+lastValue+1) = *(d+lastValue+1) + *(d+lastValue)*10 - '0'*10;
          *(d+lastValue) = '0';
          lastValue++;
        }
        break;
      }
      l++;
    }
    //puts(d);
    if (rescount > 0)
    {
      int pr = i;
      //printf("\n%d, %d\n", pr, last);
      while ((pr - last - sizeM) > 0)
      {
		if (rescount < 31)
		{
			*(result+rescount) = '0';
			rescount++;
		}
        pr--;
      }
    }
    int res = 0;
    //printf("%d%d\n", i, lastValue);
    //puts(d);
    while (flag == 0)
    {
    //puts(d);
      int h = sizeM-1;
      int k = i;
      for (h; h > -1; h--)
      {
        if (*(d+k) < *(m+h))
        {
          int u = k - 1;
          while (*(d+u) == '0' && u > 0)
          {
            u--;
          }
          if (*(d+u) != '0')
          {
	          *(d+u) = *(d+u) - 1 + 0;
	          for(u = u+1; u < k; u++)
	          {
	            *(d+u) = *(d+u) + 9;
	          }
	          *(d+k) = *(d+k) + 10;
	      }
	      else
	      {
	      	break;
	      }
        }
        *(d+k) = *(d+k) - *(m+h) + '0';
        k--;
      }
      res++;
      //printf("%s\n", d);
      int o = 0;
      int j = lastValue;
      for(0; o < sizeM; o++)
      {
        if(*(d+j) < *(m+o))
        {
          flag = 1;
          break;
        }
        else if (*(d+j) > *(m+o))
        {
          break;
        }
        j++;
      }
    }
	if (rescount < 31)
	{
		*(result+rescount) = res + '0';
		rescount++;
	}
    i--;
  }
  
  if (rescount > 30)
  {
  	//printf("\n%d\n", *(result+lastSymbol-1));
  	rescount = 30;
  	if (*(result + rescount) > '4')
  	{
  		int i = 1;
  		for (i; *(result+rescount-i) == '9'; i++)
  		{
  			*(result + rescount - i) = '0';
  		}
  		*(result+rescount-i) = *(result+rescount-i) + 1;
  	}
  	*(result+30) = ' ';
  }
  return rescount, h;
}