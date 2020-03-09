/* Licensed Materials - Property of IBM */
/* (c) Copyright IBM Corporation 2009, 2011. All Rights Reserved. */

#define OSE_SIGDESC_STRPOOL_32

#include <sigdesc.h>
#define O(s,m) ((U16) ((U32) ((char *) & (((s *)0) -> m))))

#include <ose.h>
#include "oseev.sig"

static const char ose_string_pool[] =
{
/*    0 */	'S','I','G','S','E','L','E','C','T','\0',
/*   10 */	'O','S','_','A','T','T','A','C','H','_','S','I','G','\0',
/*   24 */	'R','H','A','P','S','O','D','Y','_','S','I','G','N','A','L','\0',
/*   40 */	's','i','g','N','o','\0',
/*   46 */	'e','v','_','d','a','t','a','\0',
/*   54 */	'%','x','\0',
/*   57 */	'R','H','A','P','S','O','D','Y','_','S','I','G','\0',
'\0'
};

static const S16 ose_index_pool[] =
{
0
};

static const ose_enumdesc ose_enum_pool[] =
{
{ 0, N_A_ }
};

static const ose_vardesc ose_vardesc_tab[] =
{
/*   0 */
{
	0,
	sizeof(SIGSELECT),
	0,
	N_A_,
	N_A_,
	T_U_LONG,
	0,
	0,
},
/*   1 */
{
	24,
	sizeof(struct RHAPSODY_SIGNAL),
	0,
	N_A_,
	2,
	T_STRUCT,
	0|FLAG_US_FIRST|FLAG_US_LAST,
	0,
},
/*   2 */
{
	40,
	sizeof(SIGSELECT ),
	O(struct RHAPSODY_SIGNAL, sigNo),
	N_A_,
	N_A_,
	T_U_LONG,
	0|FLAG_US_FIRST,
	0,
},
/*   3 */
{
	46,
	sizeof(void *),
	O(struct RHAPSODY_SIGNAL, ev_data),
	N_A_,
	54,
	T_POINTER,
	0|FLAG_US_LAST,
	0,
},
{ 0,0,0,N_A_,N_A_,N_A_, FLAG_US_FIRST|FLAG_US_LAST, 0 }
};

static const ose_sigdesc ose_sigdesc_tab[] =
{
	{10,  (252)	, 0},
	{57,  (222) , 1}
};

ose_symdesc ose_symbols =
{
	2,
	1,
	ose_sigdesc_tab,
	ose_vardesc_tab,
	ose_enum_pool,
	ose_string_pool,
	ose_index_pool,
	sizeof(ose_sigdesc_tab),
	sizeof(ose_vardesc_tab),
	sizeof(ose_enum_pool),
	sizeof(ose_string_pool),
	sizeof(ose_index_pool)
};
