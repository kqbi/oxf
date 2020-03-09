/*******************************************************************************
 * Licensed Materials - Property of IBM
 * (c) Copyright IBM Corporation 2008, 2014. All Rights Reserved.
 *
 * Note to U.S. Government Users Restricted Rights:  
 * Use, duplication or disclosure restricted by GSA ADP Schedule 
 * Contract with IBM Corp.
 *******************************************************************************/
//
//  file name   :   $Source: R:/StmOO/Master/cg/LangCpp/oxf/rcs/NuInit.c $
//  file version:   $Revision: 1.4 $1.0
//
//  purpose:        Nucleus PLUS C++ adaptor for Rhapsody

//
//  author(s):      
//                  
//  date started:  
//  date changed:   $Date: 2007/03/08 16:55:59 $
//  last change by: $Author: ilgiga $
//
//  (c) Copyright Telelogic 2000, 2007
//

#if ((!defined lint) && (!defined OM_NO_RCS_ID))
static char *rcsid="$Id: NuInit.c 1.4 2007/03/08 16:55:59 ilgiga Exp $";
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef NU_OMTRACER
#include <nucleus.h>
#include <uart.h>
#include <stdio.h>
#include <sys/types.h>
#endif

extern void __init(void);
extern int main(int, char **, char **);
extern char __DATA_ROM[], __DATA_RAM[], __DATA_END[], __BSS_START[], __BSS_END[];
extern char __SP_INIT[];
extern char *__argv[], *__env[];
extern void *TCD_System_Stack;

void init_serial_OMTRACER(void);
int __inchar(void);
int __outchar( int c, int last );
int outerrorchar( int c, int last );
int __inedit(void);
int __outedit( int c, int last );
int __outerror( int c, int last );


char **environ;	// used by getenv(), putenv()

int __init_main(void);

//
// DiabData function that is overloaded to prevent the calling of constructors.
// We can't call constructors yet because we don't have a valid Nucleus memory
// pool defined. Constructors now get called in the Application_Initialize()
// function via __init() in NuAppInit.cpp
//
static int init_main_guts(void)
{
  int argc;
  
  // move initialized data from ROM to RAM if defined at
  // different locations
  if (__DATA_ROM != __DATA_RAM)
  {
    memcpy(__DATA_RAM,__DATA_ROM,__DATA_END-__DATA_RAM);
  }

  // clear uninitialized data
  if (__BSS_START != __BSS_END) 
  {
    memset(__BSS_START,0,__BSS_END-__BSS_START);
  }
  
  // check how many arguments we have
  for(argc = 0; __argv[argc] != NULL; argc++) ;
  
  environ = __env;
  
  // prepare to call the main function
  return argc ;
}

//
// DiabData function.
//
int __init_main(void)
{
  int argc = init_main_guts() ;
  return main(argc,__argv,__env) ;
}

//
// These are DiabData functions that we must overload for two reasons:
//  1. There is no filesystem available
//  2. The omtracer.cfg and omanimator.cfg files may exist, but we can't
//  give the compiler the option of using them - again there is now filesystem
//  so we must fail the calls. The OXF framework *WILL* try to open these files.
//
int __lseek(int fildes, unsigned long offset, int whence) 
{
  return 0;
}

int __open(const char *path, int oflag, ...) 
{
  return -1;
}



#ifdef NU_OMTRACER

//
// Setup the serial port on SMC1 for tracing.
//
static UNSIGNED_CHAR   user_SMC;
UART_INIT uart[2];
void init_serial_OMTRACER(void)
{
  VOID      (*old_lisr)(INT);
  
  //
  // Turn buffering off for stdin and stdout
  //
  setvbuf( stdin, NULL, _IONBF, 0 );
  setvbuf( stdout, NULL, _IONBF, 0 );

  //
  // Initialize the serial port
  //
  user_SMC = SMC1;
  uart[user_SMC].smc_port = SMC1;
  uart[user_SMC].baud_rate = 115000;
  uart[user_SMC].read = uart[user_SMC].write = 0;
  uart[user_SMC].mode = SMC_NORMAL_MODE;
  NU_Register_LISR(SMC1_VECTOR, UART_LISR, &old_lisr);
  UART_Init_Port(&(uart[user_SMC]));  
}

//
// The following functions are defined by the DiabData compiler for use in character based
// i/o using the "simple" library. We overload these functions to redirect characters to and
// from the serial port to support tracing.
//
int __inchar(void)
{
  int ch;
  
  ch = UART_Get_Char( user_SMC );
  if ( ch == BUF_EMPTY )
  {
	return( -2 ); /* No character available */
  }

  return( ch );
}

int __outchar( int c, int last )
{
  if (c == '\n') // leave as a separate case so it can be easily changed where needed
  {
	UART_Put_Char( user_SMC, '\r' ); // This is how to handle newlines for a TTY device.
	UART_Put_Char( user_SMC, '\n' ); // These lines can be changed for different terminal types.
  }
  else
  {
	UART_Put_Char( user_SMC, c );
  }
  return( 0 );
}

int outerrorchar( int c, int last )
{
  __outchar( c, last );
  return( 0 );
}

int __inedit(void)
{
  int ch;
  static int last_was_cr;

  if ( last_was_cr )
  {
    last_was_cr = 0;
    return( -1 );
  }

  while( ( ch = __inchar() ) == BUF_EMPTY );

  if ( ch == '\r' || ch == '\n' )
  {
    ch = '\n';
    last_was_cr = 1;
  }

  if ( ch > 0 )
  {
    __outedit( ch, 1 );
  }

  return( ch );
}

int __outedit( int c, int last )
{
  __outchar( c, last );
  return( 0 );
}

int __outerror( int c, int last )
{
  __outchar( c, last );
  return( 0 );
}

#endif