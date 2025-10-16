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

#include "displaywin.h"
#include "displayarea.h"
#include "midiclient.h"
#include <iostream>
#include <gtkmm.h>

DisplayWin::DisplayWin(DisplayConfig *pconfig)
{
  set_title("Display");
  set_border_width(0);
  displayConfig = pconfig;
  client_thread = nullptr;
  set_default_size(displayConfig->getAreaWidth() , displayConfig->getAreaHeight() * 4 );

  text_title = "";

  m_read_text_file = false;
  color_theme = 0;
  go_back = false;
  increment = true;
  inc4 = false;
  dec4 = false;
  pckbd_action = 0;
  pckbd_enabled = true;

  bank_1_pattern = "K1E";
  bank_2_pattern = "WR[Xx]";
  bank_3_pattern = "K3[Yy]";
  bank_1_patternRegex = Glib::Regex::create(bank_1_pattern);
  bank_2_patternRegex = Glib::Regex::create(bank_2_pattern);
  bank_3_patternRegex = Glib::Regex::create(bank_3_pattern);

  //show_all_children();
  //update_widgets();
}

DisplayWin::~DisplayWin()
{
  delete m_VBox;
  for (int i = 0; i < LINES_NUM; i++)
  {
    delete displayArea[i];
  }
  FT_Done_Face    ( face );
  FT_Done_FreeType( library );
  delete [] fontBuffer;

  delete client;
}

void DisplayWin::initialize()
{
  Glib::ustring face_name = displayConfig->getFontDirPrefix() + displayConfig->getFontName();
  //std::cout << "Font path is : " << face_name << std::endl;
  FT_Error error;

  error = FT_Init_FreeType( &library );
  //std::cout << "Error is " << error << std::endl;



  std::ifstream fontFile(face_name, std::ios::binary);
  int fontSize = (int)( (((float)displayConfig->getAreaHeight()) * 0.5f) );

  if (fontFile)
  {
    // Read the entire file to a memory buffer.
    fontFile.seekg(0, std::ios::end);
    std::fstream::pos_type fontFileSize = fontFile.tellg();
    fontFile.seekg(0);
    fontBuffer = new unsigned char[fontFileSize];
    fontFile.read((char *)fontBuffer, fontFileSize);

    error = FT_New_Memory_Face(library, fontBuffer, fontFileSize, 0, &face);
    //std::cout << "Error (memory face) is " << error << std::endl;
    //error = FT_New_Face( library, face_name.c_str(), 0, &face );
    //std::cout << "(config->getFontSize() << 6)" << (config->getFontSize() << 6) <<std::endl;
    FT_Set_Char_Size(face, (fontSize << 6), (fontSize << 6), 90, 90);
    //use_kerning = FT_HAS_KERNING( face );
    //if(use_kerning) std::cout << "Kerning support enabled " << std::endl;
  }

  m_VBox = new Gtk::Box(Gtk::ORIENTATION_VERTICAL);
  this->add(*m_VBox);

  for (int i = 0; i < LINES_NUM; i++)
  {
    displayArea[i] = new DisplayArea(&library, &face, color_theme);
    displayArea[i]->set_config(displayConfig);
    displayArea[i]->initialize();
    m_VBox->pack_start(*displayArea[i]);
    displayArea[i]->show();
    //displayArea[i]->render_string(left_str, right_str, (bool) (i%2));
  }
  this->signal_key_press_event().connect(sigc::mem_fun(*this, &DisplayWin::onKeyRelease), false);
  m_Dispatcher.connect(sigc::mem_fun(*this, &DisplayWin::on_notification_from_worker_thread));
  m_VBox->show();


}

void DisplayWin::set_theme(unsigned int value)
{
  color_theme = value;
}

Glib::ustring DisplayWin::get_filename(Glib::ustring path)
{
  Glib::ustring result;
  Glib::ustring::reverse_iterator rit = path.rbegin();
  int counter = 0;
  while((gunichar)'/' != *rit)
  {
    rit++;
    counter++;
  }
  return path.substr(path.length() - counter, counter);
}

void DisplayWin::read_from_textpath()
{
  std::cout << "Read from textpath!!!" << std::endl;
  Gio::init();
  auto f = Gio::File::create_for_path(displayConfig->getTextPointerPath());
  try
  {
  auto file_stream = f->read();
  auto data_stream = Gio::DataInputStream::create(file_stream);

  std::string line;
  std::locale::global(std::locale(""));

  Glib::ustring t_path = "";

  data_stream->read_line(line);
  try
  {
    t_path = Glib::locale_to_utf8(trim(line));
  }
  catch (Glib::ConvertError &e)
  {
    std::cerr << "Glib::ConvertError " << e.what() << std::endl;
  }

  data_stream->close();
  if(t_path.length() == 0)
  {
    queue.set_notextpath();
    return;
  }
  //int found = (int) t_path.find((gunichar)'/', 0);
  //logic to be checked
  std::cout << "Will read file \"" << t_path << "\"" << std::endl;
  std::cout << "At zero is  " << t_path.at(0) << std::endl;
  std::cout << "Char is  " << (gunichar)'/' << std::endl;

  if(t_path.at(0) != (gunichar)'/')
  {
    if(bank_1_patternRegex->match(t_path))
      t_path = displayConfig->getDataDir() + "/bank_1/text/" + t_path + ".txt";
    else if(bank_2_patternRegex->match(t_path))
      t_path = displayConfig->getDataDir() + "/bank_2/text/" + t_path + ".txt";
    else
      t_path = displayConfig->getDataDir() + "/bank_3/text/" + t_path + ".txt";
  }
//   std::cout << "Will read file " << t_path << std::endl;
  text_title = get_filename(t_path);
  queue.clear();
  queue.read_lines(t_path, text_title);
  }
  catch  (Glib::Error &err)
  {
    std::cerr << "Couldn't read file " << displayConfig->getTextPointerPath() << std::endl;
    queue.set_notextpath();
  }
}

void DisplayWin::start_listen()
{
  //Create port and run listener
  client = new MidiClient( displayConfig->getChannel(),
                          displayConfig->getNoteGEQ(), displayConfig->getNoteLT(),
                          displayConfig->getVelGEQ(), displayConfig->getVelLT(),
                          displayConfig->getCtrlNum4Fw(), displayConfig->getCtrlVal4Fw(),
                          displayConfig->getCtrlNum4Bw(), displayConfig->getCtrlVal4Bw(),
                          displayConfig->getCtrlNumGroupSel(),
                          displayConfig->getNoteRead(), displayConfig->getVelRead(),
                          displayConfig->getNoteBack(), displayConfig->getVelBack(),
                          displayConfig->getNoteTheme1(), displayConfig->getVelTheme1(),
                          displayConfig->getNoteTheme2(), displayConfig->getVelTheme2(),
                          displayConfig->getNoteTheme3(), displayConfig->getVelTheme3(),
                          displayConfig->getNotePCKbdEnable(), displayConfig->getNotePCKbdDisable(),
                          displayConfig->getNoteHome(), displayConfig->getVelHome(),
                          false);
  client->open_client();
  if(!client->get_client_success_info())
  {
    std::cout << "Couldn't open sequencer!" << std::endl;
  }
  client->new_port_write();
  if(client->get_port() < 0)
  {
    std::cout << "Couldn't open port write!" << std::endl;
  }

  if (client_thread)
  {
    std::cout << "Can't start a worker thread while another one is running." << std::endl;
  }
  else
  {
    // Start a new worker thread.
    client_thread = Glib::Threads::Thread::create(
      sigc::bind(sigc::mem_fun(client, &MidiClient::listen), this));
  }
}

void DisplayWin::set_config(DisplayConfig *config)
{
  displayConfig = config;
}

void DisplayWin::set_pointer(int i)
{
  queue.set_pointer(i);
}

void DisplayWin::read_lines(Glib::ustring path)
{
  queue.read_lines(path, get_filename(path));
}

int DisplayWin::get_pointer()
{
  return queue.get_pointer();
}

void DisplayWin::render_frame()
{
  frame = queue.get_frame();
  //frame.print();
  //queue.print();

//   for (int i = 0; i < LINES_NUM; i++)
//   {
//     m_VBox->remove(*displayArea[i]);
//     delete displayArea[i];
//   }

  for (int i = 0; i < LINES_NUM; i++)
  {
//     displayArea[i] = new DisplayArea(&library, &face, color_theme);
//     displayArea[i]->set_config(displayConfig);
    displayArea[i]->set_color_theme(color_theme);
    displayArea[i]->initialize();
//     m_VBox->pack_start(*displayArea[i]);
    displayArea[i]->render_string(frame.left[i], frame.right[i], frame.is_active[i], frame.is_hint[i]);
    displayArea[i]->show();
  }
}

bool DisplayWin::onKeyRelease(GdkEventKey* event)
{
  //this action must be done even if keyboard is disabled
  if (event->keyval == GDK_KEY_f)
  {
    displayConfig->readConfig("/tmp/mw2_config", true);
    client->set_theme(color_theme);
    render_frame();

    set_title_label();
    return false;
  }

  //std::cout << event->keyval << ' ' << event->hardware_keycode << ' ' << event->state << std::endl;
  if(pckbd_enabled != true) return false;

  if (event->keyval == GDK_KEY_Left || event->keyval == GDK_KEY_Up || event->keyval == GDK_KEY_BackSpace)
  {
    if(!queue.has_reached_end())
      queue.set_pointer(queue.get_pointer() - 1);
    else
    {
      queue.unset_reached_end();
      queue.set_pointer(queue.get_size() - 1);
    }
    frame = queue.get_frame();
    render_frame();
  }

  if (event->keyval == GDK_KEY_Right || event->keyval == GDK_KEY_Down || event->keyval == GDK_KEY_space || event->keyval == GDK_KEY_KP_Add)
  {
    render_next_frame();
  }

  if (event->keyval == GDK_KEY_KP_Enter)
  {
    render_4fw();
  }

  if (event->keyval == GDK_KEY_KP_Insert || event->keyval == GDK_KEY_KP_0)
  {
    render_4bw();
  }

  if (event->keyval == GDK_KEY_Page_Up)
  {
    if(!queue.has_reached_end())
      queue.set_group_pointer(queue.get_group_pointer() - 1);
    else
    {
      queue.unset_reached_end();
      queue.set_group_pointer(queue.get_groups_num() - 1);
    }
    frame = queue.get_frame();
    render_frame();
  }

  if (event->keyval == GDK_KEY_Page_Down)
  {
    queue.set_group_pointer(queue.get_group_pointer() + 1);
    frame = queue.get_frame();
    render_frame();
  }

  if (event->keyval == GDK_KEY_End)
  {
    queue.set_pointer(queue.get_size());
    frame = queue.get_frame();
    render_frame();
  }
  if (event->keyval == GDK_KEY_Home || event->keyval == GDK_KEY_Escape)
  {
    queue.unset_reached_end();
    queue.set_pointer(-1);
    frame = queue.get_frame();
    render_frame();
  }

  if (event->keyval == GDK_KEY_o)
  {
    on_choose_file_clicked();
  }

  if (event->keyval == GDK_KEY_r)
  {
    //std::cout << "r presssed" << std::endl;
    read_from_textpath();
    frame = queue.get_frame();
    render_frame();
  }


  if (event->keyval == GDK_KEY_z)
  {
    color_theme = 0;
    client->set_theme(color_theme);
    render_frame();
  }

  if (event->keyval == GDK_KEY_x)
  {
    color_theme = 1;
    client->set_theme(color_theme);
    render_frame();
  }

  if (event->keyval == GDK_KEY_c)
  {
    color_theme = 2;
    client->set_theme(color_theme);
    render_frame();
  }

  set_title_label();
  return false;
}

void DisplayWin::on_choose_file_clicked()
{
  std::cout << "Choosing file" << std::endl;
  Gtk::FileChooserDialog dialog("Please choose a file",
          Gtk::FILE_CHOOSER_ACTION_OPEN);
  dialog.set_transient_for(*this);

  dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
  dialog.add_button("_Open", Gtk::RESPONSE_OK);

  int result = dialog.run();

  switch(result)
  {
    case(Gtk::RESPONSE_OK):
    {
      std::cout << "Open clicked." << std::endl;

      //Notice that this is a std::string, not a Glib::ustring.
      std::string filename = dialog.get_filename();
      std::cout << "File selected: " <<  filename << std::endl;
      write_textpath(filename);
      break;
    }
    case(Gtk::RESPONSE_CANCEL):
    {
      std::cout << "Cancel clicked." << std::endl;
      break;
    }
    default:
    {
      std::cout << "Unexpected button clicked." << std::endl;
      break;
    }
  }
}

void DisplayWin::render_next_frame()
{
  queue.set_pointer(queue.get_pointer() + 1);
  frame = queue.get_frame();
  //frame.print();
  render_frame();
}

void DisplayWin::render_previous_frame()
{
  if(!queue.has_reached_end())
    queue.set_pointer(queue.get_pointer() - 1);
  else
  {
    queue.unset_reached_end();
    queue.set_pointer(queue.get_size() - 1);
  }
  frame = queue.get_frame();
  render_frame();
}

void DisplayWin::render_4fw()
{
  queue.set_pointer(queue.get_pointer() + 2);
  frame = queue.get_frame();
  //frame.print();
  render_frame();
}

void DisplayWin::render_4bw()
{
  if(!queue.has_reached_end())
    queue.set_pointer(queue.get_pointer() - 2);
  else
  {
    queue.unset_reached_end();
    if((queue.get_size() % 2) == 0)
      queue.set_pointer(queue.get_size() - 1);
    else
      queue.set_pointer(queue.get_size() - 2);
  }
  frame = queue.get_frame();
  render_frame();
}

void DisplayWin::set_title_label()
{
  std::ostringstream ssIn2, gIndex, chIndex, gSize, gNum;

  ssIn2 << queue.get_size();
  Glib::ustring strOut2 = ssIn2.str();

  gIndex << queue.get_group_pointer() + 1;
  Glib::ustring gIndexStr = gIndex.str();

  chIndex << queue.get_group_chunk_pointer() + 1;
  Glib::ustring chIndexStr = chIndex.str();

  gSize << queue.get_group_size(queue.get_group_pointer());
  Glib::ustring gSizeStr = gSize.str();

  gNum << queue.get_groups_num();
  Glib::ustring gNumStr = gNum.str();

  if(queue.get_pointer() >= 0)
  {
    std::ostringstream ssIn1;
    ssIn1 << (queue.get_pointer() + 1);
    Glib::ustring strOut1 = ssIn1.str();
    set_title("Display " + text_title + " " + strOut1 + "/" + strOut2 + " T: " + chIndexStr + "/" + gSizeStr + " GROUP #" + gIndexStr );
  }
  else
  {
    if (queue.has_reached_end())
      set_title("Display " + text_title + " " + "END/" + strOut2 + " T: " + gSizeStr + "/" + gSizeStr + " GROUP #" + gNumStr );
    else
      set_title("Display " + text_title + " " + "BEGIN/" + strOut2 + " T: " + "0/" + gSizeStr + " GROUP #" + "0" );
  }
}

void DisplayWin::update_widgets(bool only_refresh)
{
  //std::cout << "In update widgets" << std::endl;
  if(only_refresh)
  {
    render_frame();
    set_title_label();
    return;
  }
  unsigned int t_theme_id = color_theme;

  client->get_data(&m_read_text_file, &color_theme, &go_back, &increment, &inc4, &dec4, &home, &pckbd_action, &select_group, &group);

  if(t_theme_id != color_theme)
  {
    //std::cout << "Changing colour" << std::endl;
    render_frame();
    set_title_label();
    return;
  }
  if(m_read_text_file)
  {
    std::cout << "Update widgets with m_read_text_file == true !!!" << std::endl;
    m_read_text_file = false;
    read_from_textpath();
    render_frame();
    set_title_label();
    return;
  }
  if(go_back)
  {
    go_back = false;
    render_previous_frame();
    set_title_label();
    return;
  }
  if(home)
  {
    home = false;
    queue.unset_reached_end();
    queue.set_pointer(-1);
    frame = queue.get_frame();
    render_frame();
    set_title_label();
    return;
  }
  if(select_group)
  {
    queue.unset_reached_end();
    queue.set_group_pointer((int)group - 1);
    frame = queue.get_frame();
    render_frame();
    set_title_label();
    return;
  }
  if(pckbd_action == 1)
  {
    pckbd_enabled = true;
    return;
  }
  if(pckbd_action == 2)
  {
    pckbd_enabled = false;
    return;
  }
  if(inc4)
  {
    render_4fw();
    set_title_label();
    return;
  }
  if(dec4)
  {
    render_4bw();
    set_title_label();
    return;
  }
  if (increment)
    render_next_frame();
  else
    render_frame();
  set_title_label();
}

void DisplayWin::on_quit_button_clicked()
{
  client->stop_work();
  hide();
}

void DisplayWin::write_textpath(std::string p_textpath)
{
  Gio::init();
  try
  {

    auto f = Gio::File::create_for_path(displayConfig->getTextPointerPath());
    if(!f)
      std::cerr << "Gio::File::create_for_path() returned an empty RefPtr." << std::endl;

    Glib::RefPtr<Gio::FileOutputStream> stream;

    //If the file exists already then replace it.
    //Otherwise, create it:
    if(f->query_exists())
      stream = f->replace();
    else
      stream = f->create_file();
    if(!stream)
      std::cerr << "Gio::File::create_file() returned an empty RefPtr." << std::endl;

    const gsize bytes_read = stream->write(p_textpath + "\n");

    if(bytes_read)
      std::cout << "File contents written: " << p_textpath << std::endl;
    else
      std::cerr << "Gio::InputStream::write() wrote 0 bytes." << std::endl;

    stream->close();
    stream.reset(); //Stream can't be used after we have closed it.
    read_from_textpath();
    update_widgets(true);
    return;
  }
  catch(const Glib::Exception& ex)
  {
    std::cerr << "Exception caught: " << ex.what() << std::endl;
  }
}

void DisplayWin::notify()
{
  m_Dispatcher.emit();
}

void DisplayWin::on_notification_from_worker_thread()
{
  if (client_thread && client->has_stopped())
  {
    // Work is done.
    client_thread->join();
    client_thread = nullptr;
    //update_start_stop_buttons();
  }
  update_widgets();
}
