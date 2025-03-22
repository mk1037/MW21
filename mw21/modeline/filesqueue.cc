/*
 * Copyright (C) 2017-2025 Marek Momot
 *
 * This file is part of MW21.
 *
 * MW21 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * MW21 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with MW21.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "filesqueue.h"
#include <dirent.h>
#include <algorithm>

FilesQueue::FilesQueue()
{
  items.clear();
  pointer = 0;
  filenamePattern = "^[a-zA-Z0-9_\\-]+\\.txt$";
  filenamePatternRegex = Glib::Regex::create(filenamePattern);
}

int FilesQueue::readDir(Glib::ustring p_absDir)
{
  DIR *dp;
  struct dirent *dirp;
  if((dp = opendir(p_absDir.c_str())) == NULL)
  {
    std::cout << "Error(" << errno << ") opening " << p_absDir << std::endl;
    return 1;
  }

  Glib::ustring t_name;
  while ((dirp = readdir(dp)) != NULL)
  {
    t_name = Glib::ustring(dirp->d_name);
    if(t_name.length() < 7) continue;
    if(!filenamePatternRegex->match(t_name))
    {
      std::cout << "Filename " << t_name << " doesn't match pattern ..." << std::endl;
      closedir(dp);
      return 1;
    }
    items.push_back(t_name.substr(0, t_name.length() - 4));
  }
  closedir(dp);
  
  std::sort(items.begin(), items.end());
  
  return 0;
}

Glib::ustring FilesQueue::getItem(int p_idx) const
{
  if(items.size() > 0 && p_idx >=0 && p_idx < (int) items.size()) return items.at(p_idx);
  return "";
}

void FilesQueue::increase()
{
  if(pointer + 1 < (int) items.size()) pointer++;
}

void FilesQueue::decrease()
{
  if(pointer > 0) pointer--;
}

void FilesQueue::print()
{
  for ( std::vector<Glib::ustring>::iterator it = items.begin(); it < items.end(); it++ )
  {
    std::cout << *it << std::endl;
  }
  std::cout << "pointer is " << pointer << std::endl;
}

char FilesQueue::setAtChar(char p_char)
{
  p_char = tolower(p_char);
  if( p_char < 'a' || p_char > 'z' ) p_char = 'a';

  unsigned int t_counter = 0;
  for( std::vector<Glib::ustring>::iterator it = items.begin(); it < items.end(); it++)
  {
    if((gunichar) tolower(it->at(0)) == (gunichar) tolower(p_char))
    {
      pointer = t_counter;
      return (char) 0;
    }
    t_counter++;
  }
  //pointer = -1;
  return toupper(p_char);
}

void FilesQueue::setAtIndex(unsigned int p_index)
{
  std::vector<Glib::ustring>::iterator it = items.begin();

  if( p_index >= (unsigned int) items.size())
    pointer = (int) items.size() - 1;
  else
    pointer = (int) p_index;
}

char FilesQueue::decreaseChar()
{
  gunichar current_char = tolower((gunichar) items.at(pointer).at(0));
  unsigned int t_counter = 0;
  for( std::vector<Glib::ustring>::iterator it = items.begin() + pointer; it >= items.begin(); it--)
  {
    if (tolower((gunichar) it->at(0)) != current_char)
    {
      pointer -= t_counter;
      return (char) 0;
    }
    t_counter++;
  }
  return toupper((char)'A');
}

char FilesQueue::increaseChar()
{
  gunichar current_char = tolower((gunichar) items.at(pointer).at(0));
  unsigned int t_counter = 0;
  for( std::vector<Glib::ustring>::iterator it = items.begin() + pointer; it < items.end(); it++)
  {
    if (tolower((gunichar) it->at(0)) != current_char)
    {
      pointer += t_counter;
      return (char) 0;
    }
    t_counter++;
  }
  return toupper((char)'Z');
}

int FilesQueue::getPointer() const
{
  return pointer;
}
