/*
** realloc.c for realloc in /home/bellan_r/work/projet/inemajo2.0/malloc/from_scrach
** 
** Made by romain bellan
** Login   <bellan_r@epitech.net>
** 
** Started on  Mon Feb 22 14:29:05 2010 romain bellan
** Last update Thu Mar 25 18:31:27 2010 romain bellan
*/

#include		"malloc.h"

void			*realloc(void *ptr, size_t size)
{
  memcase		*tmp;
  memcase		*new_alloc;
  extern malloc_conf	myconf;

  if (!ptr)
    return (malloc(size));
  if ((tmp = find_block(ptr)) == 0 || myconf.maxalloc < size)
    return (0);
  if (tmp->allocated_size >= pow2up(size + sizeof(memcase)))
    tmp->size = size;
  else
    {
      new_alloc = malloc(size);
      if (new_alloc)
	{
	  byte_copy(ptr, new_alloc, tmp->size);
	  free(ptr);
	}
      ptr = new_alloc;
    }
  return (ptr);
}

void			*reallocf(void *ptr, uint size)
{
  void			*res;

  if ((res = realloc(ptr, size)) == 0)
    free(ptr);
  return (res);
}
