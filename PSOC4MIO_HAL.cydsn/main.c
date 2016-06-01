/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>
#include <trio.h>

#define NARG 10
#define C_ENTRIES 10
#define A_ENTRIES 5
#define E_ENTRIES 20

#define SYSTICK_EACH_10_HZ  (10u)
#define SYSTICK_EACH_100_HZ (100u)
#define SYSTICK_EACH_1000_HZ (1000u)
// Define tick size  100 ms or 10s ms or 1ms
#define SYSTICK_RELOAD        (CYDEV_BCLK__SYSCLK__HZ / SYSTICK_EACH_10_HZ)
#define SYSTICK_RELOAD_100_HZ (CYDEV_BCLK__SYSCLK__HZ / SYSTICK_EACH_100_HZ)
#define SYSTICK_RELOAD_1000_HZ (CYDEV_BCLK__SYSCLK__HZ / SYSTICK_EACH_1000_HZ)

// Interrupt prototype 
CY_ISR_PROTO(SysTickIsrHandler);
typedef void (FUNC0)(void);
typedef int (FUNC1)(char *s);
typedef int (*PFUNC0)(void);
typedef void (*PFUNC)(void);
typedef int (*PFUNC1)(char *s);
typedef int (*PFUNC2)(int argc, char *argv[]);
typedef int (*FUNC3)(int n);
typedef int (*PFUNC3)(int n);
typedef void (*FUNC4)(int argc, char *argp);
//bit routines
/* test if n-th bit in x is set */
#define B_IS_SET(x, n)   (((x) & (1<<(n)))?1:0)

/* set n-th bit in x */
#define B_SET(x, n)      ((x) |= (1<<(n)))

/* unset n-th bit in x */
#define B_CLEAR(x, n)    ((x) &= ~(1<<(n)))

/* toggle n-th bit in x */
#define B_TOGGLE(x, n)   ((x) ^= (1<<(n)))

/////////////////////////////////////////////////////////////////////////////
// EVENT ROUTINES
////////////////////////////////////////////////////////////////////////////

#define V_DEEPSLEEP    1
#define V_SLEEP        2
#define V_GTICK        3
#define V_1SEC         4
#define V_SEC10        5
#define V_DODS         6
#define V_UBUT         7
#define V_CRDY         8
#define V_SENSORLED    9
#define V_IPSW        10
#define V_ADCRDY      11
#define V_10SEC       12

uint32 GEV;

#define IF_EV_SET(n)   (((GEV) & (1<<(n)))?1:0)
#define EV_SET(n)      ((GEV) |= (1<<(n)))
#define EV_CLEAR(n)    ((GEV) &= ~(1<<(n)))
#define EV_TOGGLE(n)   ((GEV) ^= (1<<(n)))

typedef struct ct 
{
char com[4];
PFUNC0 f;     //pointer to function for this item
}ctable;

ctable ctab[C_ENTRIES];

////////////////////////////////////////////////////////////////////////////////
//                      GLOBAL VARIABLES FOR IO.C                            
////////////////////////////////////////////////////////////////////////////////
char obuf[100];     // Output buffer                                         
char linebuf[100];  // Line buffer used for command line input               
char *cline;		// Points to current position in line buffer             
char *bufpos;       // Points to the current output buffer position          
char *bufbegin;     // Points to the start of the output buffer              
char *obpos;        // Points to the current output buffer position          
char *obb;          // Output buffer begin                                   

// This string contains all the printable/keyable characters used in the kernel       
const char ChkStr[] =
  {
    "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ -+*/%&|^:=()[]$\",.;<>"
  };



///////////////////////////////////////////////////////////////////////////////
//                          IO.c CODE STARTS HERE                            
///////////////////////////////////////////////////////////////////////////////

void init_io(void)
{
obb = obuf;         // Command buffering                                     
obpos = obuf;       // Command buffer position                               
cline = linebuf;    // Command line is the same as the line buffer            
}

void printbuff(void)
{
long r;
long size;
if (obpos == obb)    return;	

size = (long)(obpos - obb);
obpos=obb;
for(r=0;r<size;r++)  console_UartPutChar((long)*(obpos++));
obpos=obb;

}
/*
 * Insert newline into the output buffer
 */
void newline(void)
{

if((long)((obpos) -obb)>=(long)MAXBUF) 	printbuff();

*obpos++ = CR;
*obpos++ = LF;
*obpos = 0;
printbuff();
}


/*
 * Put character in output buffer
 */
void printc(char c)
{
  if ((long)  ((obpos) -obb) >=  (long)MAXBUF) printbuff();
  if (c == 10)
  {
   *obpos++ = LF;
   printbuff();
  }
  else
  {
    *obpos++ = c;
    *obpos = 0;
  }
}

/*
 * Put string in the output buffer
 */
void prints(char *s)
{
  long i=0;

  while(s[i])
  {
    if((long)(obpos - obb) >=  (long)MAXBUF)
      printbuff();

    if(s[i] == 10)
    {
      *obpos++ = LF;
//      *obpos++ = CR;
      i++;
	  printbuff();
    }
    else
      *obpos++ = s[i++];
  }
  *obpos = 0;
}
void backspace(void)
{
console_UartPutChar(8);
console_UartPutChar(' ');
console_UartPutChar(8);
}

void outchar(char c)
{
console_UartPutChar((long)c);
}

void tab(long n)
{
long i=0;

i= (long)(obpos-obb);
while (i<=n)   { *obpos++ = ' '; i++; }
*obpos = 0;
}

////////////////////////////////////////////////////////
// Multifunctional format printing routine
////////////////////////////////////////////////////////
void printn(char b,char s,int n,int nolz)
{
  int i = 0, tel = 0, x = 0;
  unsigned char c, ont = 0;
  long l = 0;
  char digit[12], temp = 0;
  const char digits[] = {"0123456789ABCDEF"};

  if (b == 'b')
  {
    if (s == 'w')
      tel = 15;
    else
      if(s == 'b')
        tel = 7;
      else
        tel = 3;
    for (i=tel;i>=0;i--)
    {
//	if (tel == 3)     x = 4+i;
	if (i<=7) 
		{
        	x = i;
		c = (unsigned char) n;
		}
	else 
		{
		x = i-8;
		c= (unsigned char)( n>>8);
		}
      	temp=(char)('0'+((c>>x)&1));
     	printc(temp);
    }
  }
  if (b == 'x')
  {
    if (s == 'l') tel = 7;
      if (s == 'w') tel = 3;
      if (s == 'b') tel = 1;

    for (i=tel;i>=0;i--)
    {
      l = n;
      c=(unsigned char)((l>>4*i)&0x0f);
      if (nolz == 1)
      {
        if ((c != 0) || (ont == 1) || (i == 0))
        {
          ont = 1;
          printc(digits[c]);
        }
      }
      else
      {
        printc(digits[c]);
      }
    }
  }
  if (b == 'd')
  {
    l = n;
    for (i=0;i<=9;i++)
    {
      n=l%10;
      l=l/10;
      digit[i] = (char)(n +'0');
    }
    for(i=9;i>=0;i--)
    {
      if ((digit[i] != '0') || (ont == 1) || (i == 0))
      {
        ont = 1;
        printc(digit[i]);
      }
    }
  }
}

char buf[20];

char *ntos(int n)
{
int i = 0;
unsigned char ont = 0;
long l = 0;
char digit[12];
//const char digits[] = {"0123456789ABCDEF"};
char *b;

b = buf;
  
l = n;
for (i=0;i<=9;i++)
  {
  n=l%10;
  l=l/10;
  digit[i] = (char)(n +'0');
  }
for(i=9;i>=0;i--)
  {
  if ((digit[i] != '0') || (ont == 1) || (i == 0))
    {
    ont = 1;
    *b++ = digit[i];
    }
  }
*b++ = '\0';
return buf;
}

/////////////////////////////////////////////////////////////////////
// Copy string from source to destination: replaces strncpy function.
//////////////////////////////////////////////////////////////////////
void xstrncpy(char *t, char *s, int maxlen)
{
   int teller = 0;

   while (teller <= (maxlen-1))
   {
         t[teller] = s[teller];
         teller++;
   }
}

///////////////////////////////////////////////////////////////
// Compare maxlen characters in source and destination strings.
// Replaces strncmp() result < 0 if s<t, 0 if s==t, >0 if s>t.
/////////////////////////////////////////////////////////////////
long xstrncmp(char *s, char *t, long  maxlen)
{
  long i;

  for (i=0; s[i] == t[i]; i++)
  {
        /* Note: This is tricky and easily overlooked. If s is shorter
           than t the '\0' will be compared with the next character of t
           and they will not match and an error code will be returned
           So use maxlen-1 instead */
        if (i == maxlen-1) return 0;
  }
  return (long)(s[i] - t[i]);
}


/////////////////////////////////////////////////////////////////////
// Return pointer to specified character c: replaces strchr function.
/////////////////////////////////////////////////////////////////////

char *xstrchr(char *s, char c)
{
   long i;

   for ( i=0;s[i]!='\0';i++)
   {
          if(s[i]==c) return s+i;
   }
   return 0;
}
/////////////////////////////////////////////////////////////////////
// Return pointer to specified character C, within n characters
/////////////////////////////////////////////////////////////////////

char * xstrnchr(char *s,char c,int n)
{
int x=0;
while (x<n)
	{
	if (*s == c) return s;
	s++;
	x++;
	}
return 0;
}

void pr_n_just(int n)
{

if (n < 10)         prints("     ");
else if (n < 100)   prints("    ");
else if (n <1000)   prints("   ");
else if (n <10000)  prints("  ");
else if (n <100000) prints(" ");
else prints(" ");

printd(n);
}

void pr_n_ljust(int n)
{
printd(n);

if (n < 10) prints("    ");
else if (n < 100) prints("   ");
else prints("  ");
}
///////////////////////////////////////////////////////////////////////
// Get a line from input device
///////////////////////////////////////////////////////////////////////

int getline(void)
{
  uint32 c;

  c = console_UartGetChar();

  switch(c)
  {
    case     0x0: return(-1);     
    case  0x100 : return(-1); /* Nothing entered */

        case 27 : return(-2); /* Escape key      */

        case 1  : return(-3); /* <Ctrl A> key    */

        case 8  : /* <Backspace>     */
                       *cline-- = (char)0;
                       *cline = (char)0;
                        backspace();
                        return(0);

        default : /* <Enter>: line ready to be processed */
                  if ((c == CR) | (c == LF))
                  {    
			       *cline = NULC;
			       cline = linebuf;
                   return(1);
                  }
                   /* If valid character, print and put character in line buffer */
                  if(xstrchr((char *)ChkStr,(char)c)!=NULC)
                  {
                    *cline++ = (char)c;
			        *cline = NULC;
                    console_UartPutChar(c);
                    return(0);
                  }
                  else
                    return (-1);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////
// Command line section
/////////////////////////////////////////////////////////////////////////////////////////
typedef struct{
    uint32 secs;
    uint32 load;
    uint8  ev;
    uint8  inuse;
    FUNC0 *f;
    uint32 count;
} after;

typedef struct ont{
uint8  inuse;
uint16 event;
PFUNC f;
uint8  rflag;
 uint32 count;
} ontab;

ontab ontable[E_ENTRIES];
after aftertab_1S[A_ENTRIES];
after aftertab_1M[A_ENTRIES];

int argc;
char *argv[NARG];        

int do_after(void)
{
uint8 i;
    
prints("\r\nAfter tables\r\n");
prints("1 sec after table\r\n");
prints("Item Used EVnr  Secs   Load    Count\r\n");
for (i=0;i<A_ENTRIES-1;i++)
    {
    if (aftertab_1S[i].inuse ==1) 
        {
        printd(i); prints("    "); 
        printd(aftertab_1S[i].inuse);  prints("    "); 
        printbx0(aftertab_1S[i].ev);   prints("  ");
        pr_n_just(aftertab_1S[i].secs);
        pr_n_just(aftertab_1S[i].load); 
        pr_n_just(aftertab_1S[i].count);
        prints("\r\n");
        }
    }  
prints("msec after table\r\n");
for (i=0;i<A_ENTRIES-1;i++)
    {
    if (aftertab_1M[i].inuse == 1) 
        {
        printd(i); prints("     "); 
        printd(aftertab_1M[i].inuse);prints("     "); 
        printbx0(aftertab_1M[i].ev);   prints("     ");
        pr_n_just(aftertab_1M[i].secs); prints("     ");
        pr_n_just(aftertab_1M[i].load); prints("     ");
        pr_n_just(aftertab_1M[i].count);
        prints("\r\n");
        }
    }      
return 0;
}

int do_onevent(void)
{
uint8 i;
    
prints("\r\nOn Event Table\r\n");
prints("Nr  Inuse Rflag Event Count\r\n");
for (i=0;i<C_ENTRIES-1;i++)
    {
    if (ontable[i].inuse == 1) 
        {
        pr_n_ljust(i); 
        pr_n_ljust(ontable[i].inuse);  
        pr_n_ljust(ontable[i].rflag);  
        pr_n_just(ontable[i].event); 
        pr_n_just(ontable[i].count);  
        prints("\r\n");
        }
    }  

return 0;
}

int do_help(void)
{
uint8 i;
uint8 j;
    
prints("\r\nCommands are : \r\n");
for (i=0;i<C_ENTRIES;i++)
    {
    if (ctab[i].f != 0) 
        {
        printd(i);
        prints("   ");
        for (j=0;j<4;j++) printc(ctab[i].com[j]);
        prints("\r\n");
        }
    }  
return 0;
}


int do_exit(void)
{
prints("Bye Bye");
newline();
return 0;
}

/////////////////////////////////////////////////////////////////////////////
// mkparam turns a command string into a set of tokens and initialises arc and argv[]
// which are global
/////////////////////////////////////////////////////////////////////////////
void mkparam(char *line)
{
int qflag;
char *cp;
//clear buffer before use
for(argc = 0;argc < NARG;argc++) argv[argc] = 0;
for(argc = 0;argc < NARG;) 
    {
    while(*line == ' ' || *line == '\t') line++; /* Skip leading white space */
    if(*line == '\0') break; /* Empty command line */
    if(*line == CR) break; /* End of command line */
    qflag = 0;  /* Quote flag, if a quote is detected this flag is set */     
    /* Check for quoted token: string detection */
    if(*line == '"')  
        {
        line++;   /* Suppress quote */
        qflag = 1;
        }
    argv[argc++] = line; /* Beginning of token */
    /* Find terminating delimiter */
    if(qflag) 
        {
        /* Find quote, it must be present */
        if((cp = xstrchr(line,'"')) == NULC) 
            {
            //Error message: error in command line 
            return ;             
            }
        *cp++ = '\0';
        line = cp;
        }
    else {
        /* Find space or tab. If not present then we've already found the last token. */
        if((cp = xstrchr(line,' ')) == NULC && (cp = xstrchr(line,'\t')) == NULC) {break;}
        *cp++ = '\0';
        line = cp;
        }
    }
}


int do_command(char *s)
{
FUNC0 f;
int rc=0;
uint8 i;
    
mkparam(s); //s now points to first param which is 0 terminated

for (i=0;i<=C_ENTRIES;i++)
{
if (xstrncmp(argv[0],ctab[i].com, 4)==0)  { rc = ctab[i].f(); break;}   
}
prints("\r\nNMON> ");
printbuff();
return rc; //success
}

void loadctab(char *com,PFUNC0 f)
{
uint8 i;

for (i=0;i<C_ENTRIES;i++)
    {
    if (ctab[i].f == 0) 
        {
        xstrncpy(ctab[i].com,com,4);
        ctab[i].f = f;
        break;
        }
    }  
}

void initctab()
{
loadctab("help",do_help);
loadctab("exit",do_exit);
loadctab("after",do_after);
loadctab("onev",do_onevent);
}


////////////////////////////////////////////////////////////////////////////////////////////
// End of IO.c 
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
// Low level HW BIOS routines dependent on TopDesign
/////////////////////////////////////////////////////////////////////////////////////////////
uint8 toggle=0;     // toggle for led flash;
int64 ltime;        // linux time
uint32 wdcount =0;  // counter for Watch Dog timer
uint32 sticks = 0;  // seconds
uint32 msticks = 0;  // global 1 ms ticks
uint8 lticks =0;    // local ticks

void afterMS(int32 msecs, int8 ev, int8 lflag,FUNC0 *f );
void afterS(int32 msecs, int8 ev, int8 lflag,FUNC0 *f );

//////////////////////////////////////////////////////////////
// ADC measurement 
///////////////////////////////////////////////////////////////
// this routine is etup for using ADC in triggeed mode
// it takes samples readings over all configured channels
// throws away the biggest and the lowest and avergaes the rest
// It assumes that the lastchannel si the injected channel and 
// is connected to the die temp sensor

uint32 sa = 0;
int16 gres[9];

void do_measure(int16 samples, int16 chans)
{
int16 m[9];
int16 v[9];
int16 min[9];
int16 max[9];
int16 res[9];

uint8 i = 0;
uint8 j;

for (j=0;j<=chans;j++) 
    {
    m[j]= 0;
    v[j] = 0;
    res[j] = 0;
    min[j] = 2200;
    max[j] = 0;
    }

ADC_1_Start();
for (i=0;i<samples;i++)
    {
    ADC_1_EnableInjection();
    ADC_1_StartConvert();
    ADC_1_IsEndConversion(ADC_1_WAIT_FOR_RESULT);
    for (j=0;j<chans;j++) 
        {
        m[j] = ADC_1_GetResult16((uint32)j);   
        if (j==chans-1) 
            {
            v[j] = (int16) coretemp_CountsTo_Celsius((int32)m[j]);
            //v[j] = m[j];
            }
        else 
            {
            v[j] = ADC_1_CountsTo_mVolts((uint32)j, m[j]);
            if (v[j] > max[j]) max[j] = v[j];
            if (v[j] < min[j]) min[j] = v[j];
            }
        res[j] = res[j]+v[j];
        }
    }
ADC_1_Stop();
//prints("Result = "); printd(sa);
for (j=0;j<chans;j++) 
    {
    if (j<chans-1)
        {
        res[j] = res[j] - max[j];
        res[j] = res[j] - min[j];
        res[j] = res[j] /(samples -2);
        //prints("Result = "); printd(sa);prints(" ");printd(j);prints(" | "); printd(res[j]);prints(" | "); printd(max[j]);prints(" | "); printd(min[j]);prints("\r\n");
        }
    else res[j] = res[j]/ samples;
    gres[j] = res[j];
    if (gres[j]<0) gres[j]=0;
    res[j] = 0;
    min[j] = 2200;
    max[j] = 0;
    }
//prints("       >");
    EV_SET(V_ADCRDY);
sa++;
}


///////////////////////////////////////////////////////////////
// LED control section
// for board led (port 4.4) and GPIO1 sensor led (port 5.4) 
//////////////////////////////////////////////////////////////
void boardledoff(void)
{
P4_4_Write(1);      
}

void boardled_flash(void)
{
P4_4_Write(0);   
afterMS(100,0,0,boardledoff);
}

void sensorled_toggle()
{
if (toggle==0) toggle=1;
else toggle = 0;

gpio1_led_Write(toggle);     
}

void sensorledoff()
{
gpio1_led_Write(0);     
}

void sensorled_flash()
{
gpio1_led_Write(1);  
afterMS(50,0,0,sensorledoff);
}

/////////////////////////////////////////////////////////////////  
// Interrupts handlers
////////////////////////////////////////////////////////////////

CY_ISR(UBUT_isr)
{
EV_SET(V_UBUT); 
P7_1_ClearInterrupt();
ubut_ClearPending();
}

CY_ISR(CRDY_isr)
{
EV_SET(V_CRDY);  
uint32 source = 0;

source = console_GetRxInterruptSourceMasked();
console_ClearRxInterruptSource(source);

}

////////////////////////////////////////////////////////
// 1 SEC timer interrupt
// Used for the AFTER table
// and ISEC event
///////////////////////////////////////////////////////


void init_after()
{
uint8 i;
    
    for (i=0;i<A_ENTRIES-1;i++)
    {
    aftertab_1S[i].inuse = 0;
    aftertab_1M[i].inuse = 0;
    }
    
    
}
///////////////////////////////////////////////////////
// 1 Hz interrupt and after table
// creates delayed Events that fire after so many seconds
// can be repetitive or 1 shot
///////////////////////////////////////////////////////
CY_ISR(sticks_isr)
{
uint8 i=0;
   
sticks++;
EV_SET(V_1SEC);  
for (i=0;i<=A_ENTRIES-1;i++)
  {
  if (aftertab_1S[i].inuse == 1)
    {
    aftertab_1S[i].secs --;
    if (aftertab_1S[i].secs <= 0)
    {
        if (aftertab_1S[i].ev == 0) aftertab_1S[i].f();
        else EV_SET(aftertab_1S[i].ev);
        aftertab_1S[i].count++;
        if (aftertab_1S[i].load >= 1 )aftertab_1S[i].secs = aftertab_1S[i].load; 
        else aftertab_1S[i].inuse = 0;
        }
    }
  }
}
//////////////////////////////////////////////////////////////
// SECONDS elayed events
// ev_after routine provides a delayed event facility
// event can be a oneshot or reptitive depending on the lflag 
// value ; 1 = repeat and 0 = oneshot
/////////////////////////////////////////////////////////////

void afterS(int32 secs, int8 ev, int8 lflag, FUNC0 *f)
{
uint8 i;
//uint8 u=0;
    
for (i=0;i<A_ENTRIES-1;i++)
  {
  if (aftertab_1S[i].inuse == 0)
    {
    //u=i;
    aftertab_1S[i].secs = secs;
    if (ev == 0) aftertab_1S[i].f = f;
    else aftertab_1S[i].ev = ev;
    if (lflag == 1) aftertab_1S[i].load = secs;
    else aftertab_1S[i].load = 0;
    aftertab_1S[i].inuse = 1;
    break;
    }
  }
//prints("After S tab ");printd(u); prints(" \r\n");
}

//////////////////////////////////////////////////////////////
// set up a 100 HZ tick from SYSTICK interrupt handler
// This sets the EV_GTICKS event
// IT sets the EV_SEC10 event
// It manages the fast after table
// Entries in the after table count down until 0 and then the EV will be set
// if the load value is > 0 0 the counter will be reloaded.
// Otherwise the enrtry is dropped an can be reused.
////////////////////////////////////////////////////////////
void ticker(void)
{
uint8 i=0;
    
msticks++;
if (lticks == 100) { lticks = 0; EV_SET(V_SEC10);}
lticks++;
EV_SET(V_GTICK);
 
for (i=0;i<=A_ENTRIES-1;i++)
  {
  if (aftertab_1M[i].inuse == 1)
    {
    aftertab_1M[i].secs --;
    if (aftertab_1M[i].secs <=0) 
        { 
        if (aftertab_1M[i].ev == 0) { aftertab_1M[i].f(); aftertab_1M[i].count++;}
        else EV_SET(aftertab_1M[i].ev);
        if (aftertab_1M[i].load >= 1 )aftertab_1M[i].secs = aftertab_1M[i].load; 
        else aftertab_1M[i].inuse = 0;
        }
    }
  }
}

void afterMS(int32 msecs, int8 ev, int8 lflag,FUNC0 *f )
{
uint8 i;
//uint8 u=0;;
    
for (i=0;i<5;i++)
  {
  if (aftertab_1M[i].inuse == 0)
    {
    //u=i;
    aftertab_1M[i].secs = msecs;
    if (ev==0) {aftertab_1M[i].f = f;aftertab_1M[i].ev = 0;}
    else {aftertab_1M[i].ev = ev ; aftertab_1M[i].f = 0;}  
    if (lflag == 1) aftertab_1M[i].load = msecs;
    else aftertab_1M[i].load = 0;
    aftertab_1M[i].inuse = 1;
    break;
    }
  }
//prints("After MS tab ");printd(u); prints(" \r\n");
}


void addto_systic_handler(cySysTickCallback f)
{
uint32 i;

for (i = 0u; i < CY_SYS_SYST_NUM_OF_CALLBACKS; ++i)
  {
  if (CySysTickGetCallback(i) == NULL)
    {
    /* Set callback */
    CySysTickSetCallback(i,f);
    break;
    }
  }
}

//////////////////////////////////////////////////////////////
// WDT interrupt and deep sleep support
/////////////////////////////////////////////////////////////
CY_ISR(WDT_isr)
{
/* Clear interrupts state */
CySysWdtClearInterrupt(CY_SYS_WDT_COUNTER1_INT);
CyIntClearPending(9);
//disable timers
CySysWdtDisable(CY_SYS_WDT_COUNTER0_MASK |CY_SYS_WDT_COUNTER1_MASK |CY_SYS_WDT_COUNTER2_MASK );
wdcount++;   
}

//////////////////////////////////////////////////
// GOTO and RECOVER DEEP SLEEP
/////////////////////////////////////////////////
// SET deep sleep period using cascaded counters
// GOTO deepsleep and recover from it
/////////////////////////////////////////////////
// DEEP SLEEP 
// WDT counter 0 is set to count in seconds by using a count of 32000 and 
//is then casacded with Counter 1 to count the seconds. This is the input 
// parameter
// Max delay is 65,536 secs or 18.2 hours
// 1 min    60
// 10 min   600
// 30 min   1,800
// 1 hr     3,600
// 10 hr    36,000
// 12 hr    43,200
///////////////////////////////////////////////////////////////////////
void set_deepsleep(secs)
{
// disable all counters
CySysWdtDisable(CY_SYS_WDT_COUNTER0_MASK |CY_SYS_WDT_COUNTER1_MASK |CY_SYS_WDT_COUNTER2_MASK );
CyDelay(1);
//set up 1 HZ roll over on timer 0
CySysWdtWriteMode(CY_SYS_WDT_COUNTER0,CY_SYS_WDT_MODE_NONE);
CySysWdtWriteMatch(CY_SYS_WDT_COUNTER0,32000);
CySysWdtWriteClearOnMatch(CY_SYS_WDT_COUNTER0, 1u);

// Place timer 0 and 1 in Cascade
CySysWdtWriteCascade(CY_SYS_WDT_CASCADE_01);

/* Set WDT int after so many seconds*/
CySysWdtWriteMatch(CY_SYS_WDT_COUNTER1,secs);
CySysWdtWriteMode(CY_SYS_WDT_COUNTER1,CY_SYS_WDT_MODE_INT);
CySysWdtWriteClearOnMatch(CY_SYS_WDT_COUNTER1, 1u);
	
/* Enable WDT counters 0 and 1 */
CySysWdtEnable(CY_SYS_WDT_COUNTER0_MASK|CY_SYS_WDT_COUNTER1_MASK);
//CySysWdtEnable(CY_SYS_WDT_COUNTER0_MASK);
CyDelay(1);
}

void goto_deepsleep(int32 t)
{
//EV_CLEAR(V_DEEPSLEEP); 
//EV_CLEAR(V_SLEEP); 
set_deepsleep(t); 
//prints("Deep Sleep "); printd(t);prints("s\r\n");
CyDelay(10); 
CySysPmDeepSleep();
// Restore various resources
CySysTickStart();
//Timer_1_Start();
}

uint8 swval;
uint8 swreg;

void checkip()
{
swval = switches_Read();
if (swval != swreg) { EV_SET(V_IPSW); swreg = swval;}
}

uint8 b;

void lcd_on()
{
LCD_UartPutChar(0xAA);LCD_UartPutChar(0x11);
}

void lcd_off()
{
LCD_UartPutChar(0xAA);LCD_UartPutChar(0x12);
}

void lcd_clear()
{
LCD_UartPutChar(0xAA);LCD_UartPutChar(0x10);
}

void lcd_disp(char *s)
{
LCD_UartPutChar(0xAA);LCD_UartPutChar(0x10);
LCD_UartPutChar(0xAA);LCD_UartPutChar(0x25);
LCD_UartPutString(s);
LCD_UartPutChar(0x0D);	    
}

///////////////////////////////////////////////////
//writes to the 2nd row and col pos
///////////////////////////////////////////////////
void lcd_put(uint8 r, uint8 c,char *s,int16 v)
{
LCD_UartPutChar(0xAA);LCD_UartPutChar(0x20);// Set cursor position
LCD_UartPutChar(r);LCD_UartPutChar(c);// Row / Column
LCD_UartPutChar(0xAA);LCD_UartPutChar(0x25);// Start writing
LCD_UartPutString("        "); // clear part line
LCD_UartPutChar(0x0D);	

LCD_UartPutChar(0xAA);LCD_UartPutChar(0x20);// Set cursor position
LCD_UartPutChar(r);LCD_UartPutChar(c);// Row / Column
LCD_UartPutChar(0xAA);LCD_UartPutChar(0x25);// Start writing
LCD_UartPutString(s);
LCD_UartPutString(ntos(v));
LCD_UartPutChar(0x0D);	
}

void lcd_posclear(uint8 r, uint8 c, char *s)
{
LCD_UartPutChar(0xAA);LCD_UartPutChar(0x20);// Set cursor position
LCD_UartPutChar(r);LCD_UartPutChar(c);// Row / Column
LCD_UartPutChar(0xAA);LCD_UartPutChar(0x25);// Start writing
LCD_UartPutString(s); // clear part line
LCD_UartPutChar(0x0D);	
}

void on_event(uint16 ev, PFUNC f, uint8 rflag)
{
uint8 i;

for (i=0;i<C_ENTRIES;i++)
  {
  if (ontable[i].inuse == 0)
    {
    ontable[i].event = ev;
    ontable[i].f = f;
    ontable[i].rflag = rflag;
    ontable[i].inuse = 1;
    break;
    }
  }
}

void pclear_lcd()
{
lcd_posclear(1,8,"        ");   
}

void sw_disp(void){
lcd_put(1,0,"SW: ",(uint8)swval);   
}

void start_measure()
{
do_measure(8,2);
}

void ubut_disp(void)
{
lcd_put(1,8,"UBUT",0);   
}

void measure_disp(void)
{
lcd_put(0,0,"Temp:",gres[1]); 
lcd_put(0,8,"T:",sticks);   
}

void do_line(void)
{
uint8 r=0;
    
if ((r = getline())==1) do_command(cline);    
}

int main()
{
uint8 i = 0;
    
init_after();
///////////////////////////////////////////////
// Set up basic CORTEX system clock for 100 Hz
// ticker is 1 of 5 possibe handlers 
//////////////////////////////////////////////
CySysTickStart();
CySysTickSetReload(SYSTICK_RELOAD_1000_HZ);
addto_systic_handler(ticker);
addto_systic_handler(checkip);
//////////////////////////////////////////////////
// Set up console communcation and UART
// Initialise basic STDIO and print/string library
/////////////////////////////////////////////////
console_Init();
console_Enable();
console_Start();
crdy_StartEx(CRDY_isr);

init_io(); 
/////////////////////////////////////////////////
//Init LCD port
////////////////////////////////////////////////
LCD_Init();
LCD_Enable();
LCD_Start();
LCD_UartPutChar(0xAA);LCD_UartPutChar(0x01);


////////////////////////////////////////////////
// Install the WDT interrupt for Deepsleep
////////////////////////////////////////////////
wdog_StartEx(WDT_isr);
////////////////////////////////////////////////
// Start bseconds timer
////////////////////////////////////////////////
sectimer_Init();
sectimer_Enable();
sectimer_SetInterruptMode(sectimer_STATUS_TC_INT_MASK);
sectimer_Start();
sticks_StartEx(sticks_isr);
ubut_StartEx(UBUT_isr);


///////////////////////////////////////////////  
en5v_gpio0_Write(1u);
en33v_gpio1_Write(1u);
CyGlobalIntEnable; /* Enable global interrupts. */
initctab();

//create a 5 sec delayed event for sensor led
afterS(5,V_SENSORLED,1,0);
afterS(10,V_10SEC,1,0);
//Load the input switch register
swreg = switches_Read();

lcd_off();
CyDelay(1000);
lcd_on();
lcd_disp("Welcome PSOC4MIO");
prints("\n\rWelcome PSOC4MIO BIOS\r\n");
prints("NMON> ");printbuff();
CyDelay(2000);
lcd_clear();


on_event(V_1SEC, start_measure,0);
on_event(V_1SEC, boardled_flash,1);

on_event(V_10SEC, pclear_lcd,1);
on_event(V_IPSW, sw_disp,1);
on_event(V_SENSORLED, sensorled_flash,1);

on_event(V_ADCRDY, measure_disp,1);
on_event(V_UBUT, ubut_disp,1);
on_event(V_CRDY, do_line,1);


for(;;)
    {
    i=0;
    for (i=0;i<C_ENTRIES;i++)
        {   
        if (IF_EV_SET(ontable[i].event)) 
            {  
            ontable[i].f();
            ontable[i].count++;
            if (ontable[i].rflag == 1) EV_CLEAR(ontable[i].event);
            }
        }  
    CySysPmSleep();  
    }
}

/* [] END OF FILE */
