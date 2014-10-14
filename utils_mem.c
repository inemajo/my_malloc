/*
** utils_mem.c for  in /nfs/export/malloc-2
** 
** Made by cyprien diot-
** Login   <diot-_c@epitech.net>
** 
** Started on  Thu Mar 25 18:12:14 2010 cyprien diot-
** Last update Thu Mar 25 18:12:50 2010 cyprien diot-
*/

#include "malloc.h"

memcase			*find_block(void *ptr)
{
  extern memcase	*memmap;
  extern void		*first_alloc;
  memcase		*tmp;

  if (memmap == 0)
    return (0);
  tmp = memmap;
  if ((size_t)ptr > memmap->allocated_size + (size_t)memmap ||
      (size_t)ptr < (size_t)first_alloc)
    {
      p_error(ERR_PAGE_NIMP);
      return (0);
    }
  while (tmp)
    {
      if (ptr >= (void *)tmp && 
	  (size_t)ptr <= (size_t)tmp + tmp->allocated_size)
	{
	  if ((memcase *)ptr - 1 != tmp)
	    p_error(ERR_CHUCK_POINTER);
	  return (tmp);
	}
      tmp = tmp->next;
    }
  return (0);
}

static memcase			*prepare_find(memcase *tmp, size_t size)
{
  memcase			*new;

  new = (memcase *)((size_t)tmp + pow2up(tmp->size + sizeof(memcase)));
  new->size = size;
  new->allocated_size = tmp->allocated_size - pow2up(tmp->size + sizeof(memcase));
  tmp->allocated_size -= new->allocated_size;
  new->next = tmp;
  return (new);
}

memcase			*find_memory(uint size)
{
  extern memcase	*memmap;
  memcase		*tmp;
  memcase		*new;
  memcase		*sav;

  tmp = memmap;
  sav = 0;
  while (tmp)
    {
      if (tmp->size == 0 && tmp->allocated_size >= pow2up(size + sizeof(memcase)))
	return (tmp);
      else if ((int)tmp->allocated_size - (int)pow2up(tmp->size + sizeof(memcase)) -
	       (int)pow2up(size + sizeof(memcase)) >= 0)
	{
	  new = prepare_find(tmp, size);
	  if (sav)
	    sav->next = new;
	  else
	    memmap = new;
	  return (new);
	}
      sav = tmp;
      tmp = tmp->next;
    }
  return (0);
}
