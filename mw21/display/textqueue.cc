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

#include "textqueue.h"

TextLine::TextLine()
{
  chunk_pointer = -1;
}

TextQueue::TextQueue()
{
  pointer = -1;
  line_pointer = -1;
  chunk_pointer = -1;
  group_pointer = -1;
  group_chunk_pointer = -1;
  reached_end = false;
}

void TextLine::set_hint(bool hint)
{
  is_hint = hint;
}

bool TextLine::get_hint()
{
  return is_hint;
}

int TextLine::get_size()
{
  return chunks.size();
}

int TextQueue::lines_num()
{
  return lines.size();
}

int TextQueue::get_pointer()
{
  return pointer;
}

int TextQueue::get_group_pointer()
{
  return group_pointer;
}

int TextQueue::get_group_chunk_pointer()
{
  return group_chunk_pointer;
}

int TextQueue::read_lines(Glib::ustring path, Glib::ustring p_file_name)
{
  Gio::init();
  auto f = Gio::File::create_for_path(path);

  try
  {
  auto file_stream = f->read();
  auto data_stream = Gio::DataInputStream::create(file_stream);

  std::string line;
  std::locale::global(std::locale(""));

  int last, found;
  bool is_next;
  unsigned int t_chunks_acc;

  Glib::ustring t_chunk;
  TextLine l_line_obj;

  t_chunks_acc = 0;

  while (data_stream->read_line(line))
  {
    Glib::ustring l_string;
    try
    {
      l_string = Glib::locale_to_utf8(trim(line));
    }
    catch (Glib::ConvertError &e)
    {
      std::cerr << "Glib::ConvertError " << e.what() << std::endl;
    }

    if (l_string.empty())
    {
      //std::cout << "Skipping empty line" << std::endl;
      if(t_chunks_acc > 0)
      {
        groups.push_back(t_chunks_acc);
        t_chunks_acc = 0;
      }
      continue;
    }

    //handling comment
    if (l_string.length() > 1) //comment must have at least two chars ;;
    {
      last = 0;
      do
      {
        found = (int) l_string.find((gunichar)';', last);
        if(found >= 0)
          if ( l_string.length() > found + 1 )
            if ( ';' == l_string.at( found + 1 ) )
            {
              l_string = l_string.substr(0, found);
              break;
            }
            else
              last = found + 1;
          else break;
        else break;
      }
      while(last < l_string.length());
    }

    if (l_string.empty()) continue;

    l_line_obj.clear();
    l_line_obj.set_hint(false);
    
    last = -1; //points last search start
    found = -1;
    is_next = true;

    if('~' == ((gunichar)l_string.at(0)))
    {
      l_string = l_string.substr(1, l_string.length() - 1);
      l_line_obj.set_hint(true);
    }
    if (l_string.empty())
    {
      //std::cout << "Skipping empty line" << std::endl;
      continue;
    }

    do
    {
      last++;
      found = (int) l_string.find((gunichar)'|', last);

      if(found < 0)
      {
        t_chunk = l_string.substr(last, l_string.length() - last);
        l_line_obj.push(t_chunk);
        is_next = false;
      }
      else
      {
        t_chunk = l_string.substr(last, found - last);
        last = found;

        l_line_obj.push(t_chunk);
      }
    }
    while (is_next);
    l_line_obj.escape_chars();
    lines.push_back(l_line_obj);
    t_chunks_acc += l_line_obj.get_size();
  }
  data_stream->close();
  if(groups_accumulative_value() < (unsigned int)get_size())
  {
    groups.push_back(get_size() - groups_accumulative_value());
    t_chunks_acc = 0;
  }
  reached_end = false;
  set_pointer(-1);
  return 0;
  }
  catch  (Glib::Error &err)
  {
    std::cerr << "Couldn't read file " << path << std::endl;
    set_notext(p_file_name);
  }
  return 0;
}


void TextLine::print()
{
  //std::cout << "NEW LINE" << std::endl;
  for(std::vector<Glib::ustring>::iterator it = chunks.begin(); it != chunks.end(); ++it)
  {
    if (!is_hint)
      std::cout << "<" << *it << "> ";
    else
      std::cout << "{" << *it << "} ";
  }
}

bool TextQueue::has_reached_end()
{
  return reached_end;
}

void TextLine::clear()
{
  chunks.clear();
  is_hint = false;
}

void TextLine::escape_chars()
{
  int cpos = 0;
  int length;
  int lastchunk = (int) get_size() - 1;

  if ( (int) get_size() < 2) return;

  do
  {
    std::vector<Glib::ustring>::iterator it = chunks.begin();
    std::vector<Glib::ustring>::iterator cchunk = it + cpos;
    if ( cchunk->empty() )
    {
      *cchunk = *(cchunk+1);
      for (int i = cpos+1; i < lastchunk; i++)
        *(it+i) = *(it+i+1);
      chunks.erase(chunks.end() - 1);
    }
    else if ( '\\' == ( (gunichar) ( cchunk->at(cchunk->length() - 1) ) ) )
    {
      Glib::ustring tmp = *cchunk;
      tmp.replace(tmp.size() - 1, 1, "|");
      *cchunk = tmp + *(cchunk+1);
      for (int i = cpos+1; i < lastchunk; i++)
        *(it+i) = *(it+i+1);
      chunks.erase(chunks.end() - 1);
    }
    else
      cpos++;
    lastchunk = (int) get_size() - 1;
  }
  while (cpos < lastchunk);
}

void TextQueue::print()
{
  for(std::vector<TextLine>::iterator it = lines.begin(); it != lines.end(); ++it)
  {
    it->print();
    std::cout << std::endl;
  }
  std::cout << "L_POINTER: " << line_pointer << ", CH_POINTER: " << chunk_pointer << std::endl;
  std::cout << "POINTER: " << pointer << std::endl;
  std::cout << "GROUPS: ";
  for(std::vector<unsigned int>::iterator git = groups.begin(); git != groups.end(); ++git)
  {
    std::cout << " " << *git;
  }
  std::cout << std::endl;
  std::cout << "GROUP_POINTER: " << group_pointer<< ", GROUP_CH_POINTER: " << group_chunk_pointer << std::endl;
}

int TextQueue::get_size()
{
  int i = 0;
  for(std::vector<TextLine>::iterator it = lines.begin(); it != lines.end(); ++it)
  {
    i += it->get_size();
  }
  return i;
}

void TextLine::push(Glib::ustring chunk)
{
  chunks.push_back(chunk);
}

unsigned int TextQueue::get_group_size(unsigned int i)
{
  if (i >= groups.size()) return 0;
  return groups.at(i);
}

void TextQueue::set_pointer(int p_pointer)
{
  if (p_pointer < 0 || (0 == lines.size()) || reached_end)
  {
    pointer = -1;
    line_pointer = 0;
    chunk_pointer = -1;
    group_pointer = -1;
    group_chunk_pointer = -1;
    return;
  }

  if(p_pointer >= get_size())
  {
    pointer = -1;
    line_pointer = 0;
    chunk_pointer = -1;
    group_pointer = -1;
    group_chunk_pointer = -1;
    reached_end = true;
    return;
  }

  line_pointer = 0;
  group_pointer = 0;
  int copy_p_pointer = p_pointer;
  pointer = p_pointer;

  for(std::vector<TextLine>::iterator it = lines.begin(); it != lines.end(); ++it)
  {
    if(p_pointer < (it->get_size()))
    {
      chunk_pointer = p_pointer;
      break;
    }
    else
    {
      p_pointer -= it->get_size();
      line_pointer++;
    }
  }

  for(std::vector<unsigned int>::iterator git = groups.begin(); git != groups.end(); ++git)
  {
    if(copy_p_pointer < (int)(*git))
    {
      group_chunk_pointer = copy_p_pointer;
      break;
    }
    else
    {
      copy_p_pointer -= *git;
      group_pointer++;
    }
  }
}

void TextQueue::set_group_pointer(int p_pointer)
{
  if (p_pointer < 0 || (0 == groups.size()) || reached_end)
  {
    set_pointer(-1);
    return;
  }
  if((unsigned int)p_pointer >= get_groups_num())
  {
    set_pointer(-1);
    reached_end = true;
    return;
  }

  int accumulator = 0;
  std::vector<unsigned int>::iterator it = groups.begin();
  for(int i = 0; i < p_pointer+1; i++ )
  {
    accumulator += *(it+i);
  }
  set_pointer(accumulator-1);
}


Glib::ustring TextLine::get_left(int i)
{
  Glib::ustring result = "";
  
  if(i < 0 || (0 == chunks.size()) || (i >= (int)chunks.size()))
    return result;

  std::vector<Glib::ustring>::iterator it = chunks.begin();
  for (int j = 0; j <= i; j++)
  {
    //std::cout << *(it+j) << std::endl;
    result += *(it+j);
  }
  return result;
}

Glib::ustring TextLine::get_right(int i)
{
  Glib::ustring result = "";
  
  if((0 == chunks.size()) || (i >= (int)chunks.size()))
    return result;

  std::vector<Glib::ustring>::iterator it = chunks.begin();
  if (i < 0) i = -1;
  
  for (int j = i + 1; j < (int)chunks.size(); j++)
    result += *(it+j);
  return result;
}


FrameContent TextQueue::get_frame()
{
  FrameContent result;
  if(get_size() <=   0)
  {
    result.left[0] = "";
    result.right[0] = "---";

    result.left[1] = "";
    result.right[1] = "WELCOME";

    result.left[2] = "";
    result.right[2] = "---";

    result.left[3] = "";
    result.right[3] = "---";

    result.is_hint[0] = true;
    result.is_hint[1] = true;
    result.is_hint[2] = true;
    result.is_hint[3] = true;

    result.is_active[0] = false;
    result.is_active[1] = false;
    result.is_active[2] = false;
    result.is_active[3] = false;

    return result;
  }
  std::vector<TextLine>::iterator it = lines.begin();

  if(line_pointer % 4 == 0)
  {
    result.set_content(0, (it+line_pointer)->get_left(chunk_pointer),
                       (it+line_pointer)->get_right(chunk_pointer),
                       chunk_pointer >= 0 ? true : false,
                       (it+line_pointer)->get_hint() );
    if(line_pointer + 1 < lines_num())
    {
    result.set_content(1, (it+line_pointer+1)->get_left(-1),
                       (it+line_pointer+1)->get_right(-1),
                       false, (it+line_pointer+1)->get_hint() );
    }
    if(line_pointer + 2 < lines_num())
    {
    result.set_content(2, (it+line_pointer+2)->get_left(-1),
                       (it+line_pointer+2)->get_right(-1),
                       false, (it+line_pointer+2)->get_hint() );
    }
    if(line_pointer + 3 < lines_num())
    {
    result.set_content(3, (it+line_pointer+3)->get_left(-1),
                       (it+line_pointer+3)->get_right(-1),
                       false, (it+line_pointer+3)->get_hint() );
    }
  }

  if(line_pointer % 4 == 1)
  {
    result.set_content(0, (it+line_pointer-1)->get_left( (it+line_pointer-1)->get_size() - 1 ),
                       (it+line_pointer-1)->get_right((it+line_pointer-1)->get_size() - 1),
                       true, (it+line_pointer-1)->get_hint() );

    result.set_content(1, (it+line_pointer)->get_left(chunk_pointer),
                       (it+line_pointer)->get_right(chunk_pointer),
                       chunk_pointer >= 0 ? true : false,
                       (it+line_pointer)->get_hint() );
    if(line_pointer + 1 < lines_num())
    {
      result.set_content(2, (it+line_pointer+1)->get_left(-1),
                       (it+line_pointer+1)->get_right(-1),
                       false, (it+line_pointer+1)->get_hint() );
    }
    if(line_pointer + 2 < lines_num())
    {
      result.set_content(3, (it+line_pointer+2)->get_left(-1),
                       (it+line_pointer+2)->get_right(-1),
                       false, (it+line_pointer+2)->get_hint() );
    }
  }

  if(line_pointer % 4 == 2)
  {
    result.set_content(2, (it+line_pointer)->get_left(chunk_pointer),
                       (it+line_pointer)->get_right(chunk_pointer),
                       chunk_pointer >= 0 ? true : false,
                       (it+line_pointer)->get_hint() );
    if(line_pointer + 1 < lines_num())
    {
    result.set_content(3, (it+line_pointer+1)->get_left(-1),
                       (it+line_pointer+1)->get_right(-1),
                       false, (it+line_pointer+1)->get_hint() );
    }
    if(line_pointer + 2 < lines_num())
    {
    result.set_content(0, (it+line_pointer+2)->get_left(-1),
                       (it+line_pointer+2)->get_right(-1),
                       false, (it+line_pointer+2)->get_hint() );
    }
    if(line_pointer + 3 < lines_num())
    {
    result.set_content(1, (it+line_pointer+3)->get_left(-1),
                       (it+line_pointer+3)->get_right(-1),
                       false, (it+line_pointer+3)->get_hint() );
    }
  }

  if(line_pointer % 4 == 3)
  {
    result.set_content(2, (it+line_pointer-1)->get_left( (it+line_pointer-1)->get_size() - 1 ),
                       (it+line_pointer-1)->get_right((it+line_pointer-1)->get_size() - 1),
                       true, (it+line_pointer-1)->get_hint() );

    result.set_content(3, (it+line_pointer)->get_left(chunk_pointer),
                       (it+line_pointer)->get_right(chunk_pointer),
                       chunk_pointer >= 0 ? true : false,
                       (it+line_pointer)->get_hint() );
    if(line_pointer + 1 < lines_num())
    {
      result.set_content(0, (it+line_pointer+1)->get_left(-1),
                       (it+line_pointer+1)->get_right(-1),
                       false, (it+line_pointer+1)->get_hint() );
    }
    if(line_pointer + 2 < lines_num())
    {
      result.set_content(1, (it+line_pointer+2)->get_left(-1),
                       (it+line_pointer+2)->get_right(-1),
                       false, (it+line_pointer+2)->get_hint() );
    }
  }

/*
  for (int i = 0; i < (int)lines.size(); i++)
  {
    std::cout << "LEFT" << (it+i)->get_left(-1) << "RIGHT" << (it+i)->get_right(-1) << "ENDL" << std::endl;
  }
  */
  return result;
}

void TextQueue::clear()
{
  lines.clear();
  groups.clear();
  pointer = -1;
  line_pointer = -1;
  chunk_pointer = -1;
  reached_end = false;
}

unsigned int TextQueue::get_groups_num()
{
  return groups.size();
}

unsigned int TextQueue::groups_accumulative_value()
{
  unsigned int result = 0;
  for(std::vector<unsigned int>::iterator git = groups.begin(); git != groups.end(); ++git)
  {
    result += *git;
  }
  return result;
}

void TextQueue::unset_reached_end()
{
  reached_end = false;
}

void TextQueue::set_notext(Glib::ustring p_file_name)
{
  clear();
  TextLine line1;
  line1.push(Glib::ustring("!!! MISSING TEXT !!!"));
  TextLine line2;
  line2.push(p_file_name);
  TextLine line3;
  line3.push(Glib::ustring("---"));
  TextLine line4;
  line4.push(Glib::ustring("---"));

  lines.push_back(line1);
  lines.push_back(line2);
  lines.push_back(line3);
  lines.push_back(line4);
  set_pointer(-1);
}

void TextQueue::set_notextpath()
{
  clear();
  TextLine line1;
  line1.push(Glib::ustring("!!! NO TEXT-PATH FILE !!!"));
  TextLine line2;
  line2.push(Glib::ustring("---"));
  TextLine line3;
  line3.push(Glib::ustring("---"));
  TextLine line4;
  line4.push(Glib::ustring("---"));

  lines.push_back(line1);
  lines.push_back(line2);
  lines.push_back(line3);
  lines.push_back(line4);
  set_pointer(-1);
}

std::string ltrim( std::string str ) {
    return std::regex_replace( str, std::regex("^\\s+"), std::string("") );
}

std::string rtrim( std::string str ) {
    return std::regex_replace( str, std::regex("\\s+$"), std::string("") );
}

std::string trim( std::string str ) {
    return ltrim( rtrim( str ) );
}
