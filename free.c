/*
** free.c for Free in /home/bellan_r/work/projet/inemajo2.0/malloc/from_scrach
** 
** Made by romain bellan
** Login   <bellan_r@epitech.net>
** 
** Started on  Mon Feb 22 14:26:33 2010 romain bellan
** Last update Thu Mar 25 17:42:26 2010 cyprien diot-
*/

#include		"malloc.h"

void			free(void *ptr)
{
  memcase		*mem_to_free;
  extern malloc_conf	myconf;

  if (!ptr)
    return ;
  if (myconf.info & CONFINFO_CHUCK)
      mem_to_free = find_block(ptr);
  else
      mem_to_free = (memcase *)((size_t)ptr - sizeof(memcase));
  if (!mem_to_free || (!(myconf.info & CONFINFO_FREECHUCK) && mem_to_free !=
		       (memcase *)((size_t)ptr - sizeof(memcase))))
    return ;
  else if (mem_to_free && mem_to_free->size == 0)
      p_error(ERR_PAGE_FREE);  
  else if (myconf.info & CONFINFO_FREECHUCK && mem_to_free !=
	   (memcase *)((size_t)ptr - sizeof(memcase)))
      mem_to_free->size = 0;
  else
    mem_to_free->size = 0;
}
