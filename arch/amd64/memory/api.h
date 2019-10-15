/**********************************************************************
  Copyright (C) 2017-Present Tyler Cromwell <tjc6185@gmail.com>

  This file is part of Mantle.

  Mantle is free software: you can redistribute it and/or modify
  it under Version 2 of the terms of the GNU General Public License
  as published by the Free Software Foundation.

  Mantle is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY of FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Mantle.
  If not, see <http://www.gnu.org/licenses/old-licenses/gpl-2.0.html>
**********************************************************************/

#ifndef MEMORY_API_H
#define MEMORY_API_H

// Kernel headers
#include <kernel/types.h>

extern void paging_configure(size_t memory, ulong_t pages);
extern void paging_pageinfo(void);

#endif