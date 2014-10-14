/*
** malloc.h for Malloc H in /home/bellan_r/work/projet/inemajo2.0/malloc/from_scrach
** 
** Made by romain bellan
** Login   <bellan_r@epitech.net>
** 
** Started on  Mon Feb 22 14:08:52 2010 romain bellan
** Last update Thu Mar 25 17:59:45 2010 romain bellan
*/

#ifndef __MALLOC_HEADER__
#define __MALLOC_HEADER__

/* Headers Files Includes */
#include <sys/types.h>

#include <unistd.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <stdlib.h>

#ifndef PAGE_SIZE
#define PAGE_SIZE 4096
#endif

/* Structures And Variables Definition */

#ifdef __FreeBSD__
typedef size_t uint; /* racourci unsigne int size_t pour compatibilite  */
#endif

typedef struct	s_mem /* Structure de chaque case mamoire  */
{
  uint		size;
  uint		allocated_size;
  struct s_mem	*next;
}		memcase;

/* Configuration de malloc par le biais d'un fichier  */

typedef struct	s_mconf
{
  uint		maxsbrk; /* taille maximal pour utiliser sbrk */
  uint		maxalloc; /* taille maximal pour un alloc */
  uint		info; /* bit (1on,0off)*/
}		malloc_conf;

typedef struct	conf_alloc
{
  char		*name;
  char		len_name;
  char		byte;
  uint		*nbr;  
}		conf_alloc;

#define FILE_CONFIG_PATH "malloc.conf"
#define CONFINFO_MSG_ON_ERR 1
#define CONFINFO_EXIT_ON_ERR 2
#define CONFINFO_MAXSBRK 4
#define CONFINFO_MAXMALLOC 8
#define CONFINFO_CHUCK 16
#define CONFINFO_FREECHUCK 32

#define ERR_CHUCK_POINTER "libmalloc: warning: modified (chunk-) pointer\n"
#define ERR_PAGE_FREE "libmalloc: Warning: page is already free\n"
#define ERR_PAGE_NIMP "libmalloc: Warning: junk pointer, too high to make sense\n"
/* -------------  */

memcase		*memmap;
void		*first_alloc;
malloc_conf	myconf;

memcase		*find_memory(uint size);
void		byte_copy(void *from, void *to, uint size);
size_t		pow2up(size_t nb);
void		*malloc(size_t size);
void		free(void *ptr);
void            show_alloc_mem();
void		getmalloc_conf();
memcase		*find_block(void *ptr);
void		p_error(char *err);


#endif
