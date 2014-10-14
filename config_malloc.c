/*
** config_malloc.c for Config_malloc in /home/bellan_r/work/projet/inemajo2.0/malloc/from_scrach
** 
** Made by romain bellan
** Login   <bellan_r@epitech.net>
** 
** Started on  Wed Feb 24 15:45:57 2010 romain bellan
** Last update Thu Mar 25 18:19:08 2010 romain bellan
*/

#include "malloc.h"

conf_alloc confmalloc[]={
  {"msg_on_err", 11, CONFINFO_MSG_ON_ERR, 0},
  {"exit_on_err", 12, CONFINFO_EXIT_ON_ERR, 0},
  {"maxsbrk:", 8, CONFINFO_MAXSBRK, &(myconf.maxsbrk)},
  {"maxalloc:", 9, CONFINFO_MAXMALLOC, &(myconf.maxalloc)},
  {"chuck_pointer_gest:", 19, CONFINFO_CHUCK, 0},
  {"free_chuck_pointer:", 19, CONFINFO_FREECHUCK, 0},
  {0, 0, 0, 0}
};

static int		get_nbr(char *s, char cut)
{
  int			i;
  int			pow;
  uint			res;

  res = 0;
  pow = 1;
  i = 0;
  while (s[i] != cut)
    ++i;
  while (i)
    {
      --i;
      res = res + ((s[i] - '0') * pow);
      pow = pow * 10;
    }
  return (res);
}

static int 		strfind(char *s, char *find)
{
  int			i;

  i = 0;
  while (s[i] && find[i] && s[i] == find[i])
    ++i;
  if (!find[i])
    return (1);
  return (0);
}

static int		getconffile(char *buffer)
{
  extern malloc_conf	myconf;
  int			fd;
  register int		len_read;

  myconf.info = 0;
  myconf.maxsbrk = 0;
  myconf.maxalloc = 0;
  fd = open(FILE_CONFIG_PATH, O_RDONLY);
  if (fd == -1)
    {
      myconf.info = CONFINFO_CHUCK | CONFINFO_MSG_ON_ERR;
      myconf.maxsbrk = 0;
      myconf.maxalloc = 2147483647;
      return (-1);
    }
  len_read = read(fd, buffer, 4096);
  close(fd);
  return (len_read);
}

void			getmalloc_conf()
{
  extern malloc_conf	myconf;
  char			buffer[4096];
  int			len_read;
  register int		i_buffer;
  int			i_conf;

  if ((len_read = getconffile(buffer)) == -1)
    return ;
  for (i_buffer = 0; i_buffer < len_read; ++i_buffer)
    {
      i_conf = 0;
      while (confmalloc[i_conf].name && 
	     !strfind(buffer + i_buffer, confmalloc[i_conf].name))
	++i_conf;
      if (confmalloc[i_conf].name)
	{
	  i_buffer += confmalloc[i_conf].len_name;
	  if (confmalloc[i_conf].nbr)
	    {
	      myconf.info |= confmalloc[i_conf].byte;
	      *(confmalloc[i_conf].nbr) = get_nbr(buffer + i_buffer, '\n');
	    }
	  else if (strfind(buffer + i_buffer, "yes"))
	    myconf.info |= confmalloc[i_conf].byte;
	}
      while (buffer[i_buffer] != '\n' && i_buffer < len_read)
	++i_buffer;
    }
}
