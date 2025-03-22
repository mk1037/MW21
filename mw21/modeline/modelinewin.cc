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

#include "modelinewin.h"
#include "modelinearea.h"
//#include "midiclient.h"

#include "signalclient.h"
#include <iostream>
#include <gtkmm.h>

extern SignalClient * global_sclient;

ModelineWin::ModelineWin(ModelineConfig *pconfig)
{
  set_title("Modeline");
  set_border_width(0);

  modelineConfig = pconfig;
  client_thread = nullptr;
//   blink_client_thread = nullptr;
  signal_client_thread = nullptr;
  timeout_client_thread = nullptr;
  modelineAction = nullptr;
  set_default_size(modelineConfig->getModelineAreaWidth() , modelineConfig->getModelineAreaHeight() * 2);
//   std::cout << "Window height is " << modelineConfig->getModelineAreaHeight() * 2 + 5 << std::endl;
  theme_idx = 2;
  title_b = "";
  sensitive_actions_lock = false;
  m_prompt_1_theme = THEME_NEUTRAL_2;
  m_prompt_2_theme = THEME_NEUTRAL_2;
  last_loaded = 1;

  bank_1_pattern = "K1E";
  bank_2_pattern = "WR[Xx]";
  bank_3_pattern = "K3[Yy]";
  bank_1_patternRegex = Glib::Regex::create(bank_1_pattern);
  bank_2_patternRegex = Glib::Regex::create(bank_2_pattern);
  bank_3_patternRegex = Glib::Regex::create(bank_3_pattern);
  
  m_initialized = false;
  m_state = STATE_IDLE;
  //show_all_children();
  //update_widgets();
}

int ModelineWin::initialize()
{
  client = new MidiClient();
  if(client->readBanks(modelineConfig->getDataDir()) != 0)
  {
    std::cout << "Returning from initialize()" << std::endl;
    return 1;
  }
  client->configure(modelineConfig);

  modelineAction = new ModelineAction(modelineConfig);
  Glib::ustring face_name = modelineConfig->getFontDirPrefix() + modelineConfig->getFontName();
  //std::cout << "Font path is : " << face_name << std::endl;
  FT_Error error;

  error = FT_Init_FreeType( &library );

  std::ifstream fontFile(face_name, std::ios::binary);
  int fontSize = (int)( (((float)modelineConfig->getModelineAreaHeight()) * 0.5f) );

  if (fontFile)
  {
    // Read the entire file to a memory buffer.
    fontFile.seekg(0, std::ios::end);
    std::fstream::pos_type fontFileSize = fontFile.tellg();
    fontFile.seekg(0);
    fontBuffer = new unsigned char[fontFileSize];
    fontFile.read((char *)fontBuffer, fontFileSize);

    error = FT_New_Memory_Face(library, fontBuffer, fontFileSize, 0, &face);
    FT_Set_Char_Size(face, (fontSize << 6), (fontSize << 6), 90, 90);
  }
  
  timeoutClient = new TimeoutClient(modelineConfig->getTimeout());

  // compute dimensions of the areas
  prompt_width = (unsigned int)( (((float)modelineConfig->getModelineAreaWidth()) * 0.08f) );
  side_item_width = (unsigned int)( (((float)modelineConfig->getModelineAreaWidth()) * 0.01f) );
  item_width = modelineConfig->getModelineAreaWidth() - (2 * side_item_width + prompt_width);
  
//   std::cout << "prompt_width: " << prompt_width << " side_item_width: " << side_item_width
//     << " item_width: " << item_width << std::endl;
  
  

  
  m_prompt_1 = new ModelineArea(&library, &face, prompt_width);
  m_prompt_1->set_config(modelineConfig);
  m_prompt_1->initialize(THEME_NEUTRAL_2);

  m_prev = new ModelineArea(&library, &face, side_item_width);
  m_prev->set_config(modelineConfig);
  m_prev->initialize(THEME_BANK_3);

  m_curr = new ModelineArea(&library, &face, item_width);
  m_curr->set_config(modelineConfig);
  m_curr->initialize(THEME_BANK_3);

  m_next = new ModelineArea(&library, &face, side_item_width);
  m_next->set_config(modelineConfig);
  m_next->initialize(THEME_BANK_3);


  m_sep_1 = new ModelineArea(&library, &face, prompt_width);
  m_sep_1->set_config(modelineConfig);
  m_sep_1->initialize(THEME_BLINK_1);

  m_sep_2 = new ModelineArea(&library, &face, side_item_width);
  m_sep_2->set_config(modelineConfig);
  m_sep_2->initialize(THEME_BLINK_2);

  m_sep_3 = new ModelineArea(&library, &face, item_width);
  m_sep_3->set_config(modelineConfig);
  m_sep_3->initialize(THEME_OK);

  m_sep_4 = new ModelineArea(&library, &face, side_item_width);
  m_sep_4->set_config(modelineConfig);
  m_sep_4->initialize(THEME_SEARCH);


  m_prompt_2 = new ModelineArea(&library, &face, prompt_width);
  m_prompt_2->set_config(modelineConfig);
  m_prompt_2->initialize(THEME_NEUTRAL_2);

  m_space1 = new ModelineArea(&library, &face, side_item_width);
  m_space1->set_config(modelineConfig);
  m_space1->initialize(THEME_BANK_3);

  m_curr2 = new ModelineArea(&library, &face, item_width);
  m_curr2->set_config(modelineConfig);
  m_curr2->initialize(THEME_BANK_3);

  m_space2 = new ModelineArea(&library, &face, side_item_width);
  m_space2->set_config(modelineConfig);
  m_space2->initialize(THEME_BANK_3);



  
  m_grid = new Gtk::Grid();

  if (modelineConfig->getFirstRow())
  {
    m_grid->attach(*m_prompt_1, 0, 0, 1, 1);
    m_grid->attach(*m_prev, 1, 0, 1, 1);
    m_grid->attach(*m_curr, 2, 0, 1, 1);
    m_grid->attach(*m_next, 3, 0, 1, 1);
  }
  else
  {
    m_grid->attach(*m_prompt_2, 0, 0, 1, 1);
    m_grid->attach(*m_space1, 1, 0, 1, 1);
    m_grid->attach(*m_curr2, 2, 0, 1, 1);
    m_grid->attach(*m_space2, 3, 0, 1, 1);
  }
  
  m_grid->attach(*m_sep_1, 0, 1, 1, 1);
  m_grid->attach(*m_sep_2, 1, 1, 1, 1);
  m_grid->attach(*m_sep_3, 2, 1, 1, 1);
  m_grid->attach(*m_sep_4, 3, 1, 1, 1);

  if (modelineConfig->getFirstRow() && modelineConfig->getSecondRow())
  {
    m_grid->attach(*m_prompt_2, 0, 2, 1, 1);
    m_grid->attach(*m_space1, 1, 2, 1, 1);
    m_grid->attach(*m_curr2, 2, 2, 1, 1);
    m_grid->attach(*m_space2, 3, 2, 1, 1);
  }
  
  this->add(*m_grid);


  m_prompt_1->show();
  m_prev->show();
  m_curr->show();
  m_next->show();

  m_sep_1->show();
  m_sep_2->show();
  m_sep_3->show();
  m_sep_4->show();

  if (modelineConfig->getSecondRow())
  {
    m_prompt_2->show();
    m_space1->show();
    m_curr2->show();
    m_space2->show();
  }
  
  m_Dispatcher.connect(sigc::mem_fun(*this, &ModelineWin::on_notification_from_worker_thread));
  m_timeoutDispatcher.connect(sigc::mem_fun(*this, &ModelineWin::on_notification_from_timeout_thread));
  m_signalDispatcher.connect(sigc::mem_fun(*this, &ModelineWin::on_notification_from_signal_thread));
/*
  Glib::ustring t_str = "WELCOME";
  Glib::ustring t_str2 = ">";
  Glib::ustring t_str3 = ">>";
  Glib::ustring t_str4 = "";
  m_prompt_1->render_string(t_str2, false);
  m_prev->render_string(t_str, true);
  m_curr->render_string(t_str, false);
  m_next->render_string(t_str, true);
  
  m_sep_1->render_string(t_str, false, true);
  m_sep_2->render_string(t_str, false, true);
  m_sep_3->render_string(t_str, false, true);
  m_sep_4->render_string(t_str, false, true);
  
*/
  Glib::ustring t_str3 = "WELCOME";
  Glib::ustring t_str4 = "";

  m_space1->render_string(t_str4, true);
  m_curr2->render_string(t_str3, false);
  m_space2->render_string(t_str4, true);

  m_grid->show();
  m_state = STATE_IDLE;
  m_initialized = true;
  show_all_children();
  do_logic();
  return 0;
}

ModelineWin::~ModelineWin()
{
  delete client;
  std::cout << "ModelineWin destructor" << std::endl;

  if(!m_initialized) return;

  delete m_space2;
  delete m_curr2;
  delete m_space1;
  delete m_prompt_2;

  delete m_sep_4;
  delete m_sep_3;
  delete m_sep_2;
  delete m_sep_1;

  delete m_next;
  delete m_curr;
  delete m_prev;
  delete m_prompt_1;

  delete m_grid;
  delete timeoutClient;
  delete modelineAction;

  FT_Done_Face    ( face );
  FT_Done_FreeType( library );
  delete [] fontBuffer;
}



void ModelineWin::on_quit_button_clicked()
{
  client->stop_work();
  //blinkClient->stop_work();
  //timeoutClient->stop_work();
  hide();
}
/*
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
*/


void ModelineWin::start_listen()
{
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


  signalClient = new SignalClient(modelineConfig->getInstructionPath());
  global_sclient = signalClient;
  if (signal_client_thread)
  {
    std::cout << "Can't start a signal thread while another one is running." << std::endl;
  }
  else
  {
    // Start a new worker thread.
    signal_client_thread = Glib::Threads::Thread::create(
      sigc::bind(sigc::mem_fun(signalClient, &SignalClient::listen), this));
  }

}


void ModelineWin::set_config(ModelineConfig *config)
{
  modelineConfig = config;
}

void ModelineWin::notify()
{
  m_Dispatcher.emit();
}

void ModelineWin::notify_timeout()
{
  m_timeoutDispatcher.emit();
}

void ModelineWin::notify2()
{
  m_signalDispatcher.emit();
}


void ModelineWin::on_notification_from_worker_thread()
{
  if (client_thread && client->has_stopped())
  {
    // Work is done.
    client_thread->join();
    client_thread = nullptr;
    //update_start_stop_buttons();
  }
  do_logic();
}

void ModelineWin::on_notification_from_timeout_thread()
{
  if (timeout_client_thread  && timeoutClient->has_stopped())
  {
    // Work is done.
    timeout_client_thread->join();
    timeout_client_thread = nullptr;
    sensitive_actions_lock = false;
    std::cout << "sensible_actions_lock released" << std::endl;
  }
  if (m_state == STATE_PLAYING)
  {
    m_prompt_1_theme = THEME_BLINK_2;
    m_prompt_2_theme = THEME_BLINK_2;
  }
  else if (m_state == STATE_LOADED_K1E)
  {
    m_prompt_1_theme = THEME_BLINK_1;
    m_prompt_2_theme = THEME_BLINK_1;
  }
  else if (m_state == STATE_LOADED_WRX)
  {
    m_prompt_1_theme = THEME_NEUTRAL_2;
    m_prompt_2_theme = THEME_NEUTRAL_2;
  }
  else
  {
    m_prompt_1_theme = THEME_NEUTRAL_2;
    m_prompt_2_theme = THEME_NEUTRAL_2;
  }
  update_widgets();
}

void ModelineWin::on_notification_from_signal_thread()
{
  if (signal_client_thread && signalClient->has_stopped())
  {
    // Work is done.
    signal_client_thread->join();
    signal_client_thread = nullptr;
  }
  update_widgets2(); // ???
}


void ModelineWin::do_logic()
{
  client->get_data(&current_item, 0, &prev_item, &next_item, &action, &theme_idx, &character);

  // lock sensitive keys
  if(action == ACTION_STOP_1 ||
     action == ACTION_STOP_2 ||
     action == ACTION_PLAY ||
     action == ACTION_LOAD_1 ||
     action == ACTION_LOAD_2 ||
     action == ACTION_ARM ||
     action == ACTION_DISARM
  )
  {
    if(sensitive_actions_lock)
    {
      std::cout << "Sensitive actions locked ... do nothing " << std::endl;
      return;
    }
    sensitive_actions_lock = true;
    //create thread timeout client
    if (timeout_client_thread)
    {
      std::cout << "Can't start a timeout thread while another one is running." << std::endl;
    }
    else
    {
      // Start a new timeout thread.
      timeout_client_thread = Glib::Threads::Thread::create(
        sigc::bind(sigc::mem_fun(timeoutClient, &TimeoutClient::countdown), this));
      //do action
      std::cout << "Doing sensitive action ... " << std::endl;
      if(action == ACTION_LOAD_1)
      {
        last_loaded = 1;
        modelineAction->load(current_item);
      }
      if(action == ACTION_LOAD_2)
      {
        last_loaded = 2;
        modelineAction->load(title_b);
      }
      if(action == ACTION_PLAY)
      {
        modelineAction->play();
      }
      if(action == ACTION_STOP_1)
      {
        modelineAction->stop1();
      }
      if(action == ACTION_ARM)
      {
        if ( m_state == STATE_LOADED_K1E )
          modelineAction->arm();
      }
      if(action == ACTION_DISARM)
      {
        modelineAction->disarm();
      }
    }

  }
  if (action == ACTION_INFO_OK)
  {
    m_prompt_2_theme = THEME_OK;
  }
  if (action == ACTION_INFO_SEARCH)
  {
    m_prompt_2_theme = THEME_SEARCH;
  }
  if (action == ACTION_INFO_CLEAR)
  {
    m_prompt_2_theme = THEME_NEUTRAL_2;
  }

  std::cout << "-------------------------------------------------" << std::endl;
  std::cout << "update_widgets(): " << std::endl;
  std::cout << "prev_item: " << prev_item << std::endl;
  std::cout << "curr_item: " << current_item << std::endl;
  std::cout << "next_item: " << next_item << std::endl;
  std::cout << "action   : " << action << std::endl;
  std::cout << "theme_idx: " << theme_idx << std::endl;
  std::cout << "character: " << character << std::endl;
  update_widgets();
}

void ModelineWin::update_widgets()
{
  Glib::ustring t_str = "Empty slot for ";
  Glib::ustring t_str2 = ">";
  Glib::ustring t_str3 = ">>";
  Glib::ustring t_str4 = "";

  m_prompt_1->initialize(m_prompt_1_theme);
  m_prompt_2->initialize(m_prompt_2_theme);
  if(theme_idx >= 0)
  {
    m_prev->initialize(theme_idx);
    m_curr->initialize(theme_idx);
    m_next->initialize(theme_idx);
  }

  m_prompt_1->render_string(t_str2, false);
  m_prev->render_string(prev_item, true);
  
  if(character != 0)
  {
    Glib::ustring message = "Empty slot for ";
    switch(character)
    {
      case 'A':
        message += Glib::ustring("A");
        break;
      case 'B':
        message += Glib::ustring("B");
        break;
      case 'C':
        message += Glib::ustring("C");
        break;
      case 'D':
        message += Glib::ustring("D");
        break;
      case 'E':
        message += Glib::ustring("E");
        break;
      case 'F':
        message += Glib::ustring("F");
        break;
      case 'G':
        message += Glib::ustring("G");
        break;
      case 'H':
        message += Glib::ustring("H");
        break;
      case 'I':
        message += Glib::ustring("I");
        break;
      case 'J':
        message += Glib::ustring("J");
        break;
      case 'K':
        message += Glib::ustring("K");
        break;
      case 'L':
        message += Glib::ustring("L");
        break;
      case 'M':
        message += Glib::ustring("M");
        break;
      case 'N':
        message += Glib::ustring("N");
        break;
      case 'O':
        message += Glib::ustring("O");
        break;
      case 'P':
        message += Glib::ustring("P");
        break;
      case 'R':
        message += Glib::ustring("R");
        break;
      case 'S':
        message += Glib::ustring("S");
        break;
      case 'T':
        message += Glib::ustring("T");
        break;
      case 'U':
        message += Glib::ustring("U");
        break;
      case 'W':
        message += Glib::ustring("W");
        break;
      case 'Z':
        message += Glib::ustring("Z");
        break;
      default:
        break;
    }
    m_curr->render_string(message, false);
  }
  else
  {
    Glib::ustring to_display = current_item.substr(0, current_item.length() - 6);
    m_curr->render_string(to_display, false);
  }

  m_next->render_string(next_item, true);

  m_prompt_2->render_string(t_str3, false);
}

int ModelineWin::write_pid()
{
  Gio::init();
  try
  {
    pid_t pid = getpid();
    std::cout << "Will be writing pid " << pid << " to " << modelineConfig->getPidPath() << std::endl;

    auto f = Gio::File::create_for_path(modelineConfig->getPidPath());
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

    char *mypid = NULL;
    if (asprintf(&mypid, "%jd", (intmax_t) pid) != -1)
    {
      const gsize bytes_read = stream->write(mypid);
      free(mypid); // cleanup when done.

      if(bytes_read)
        std::cout << "File contents written: " << getpid() << std::endl;
      else
        std::cerr << "Gio::InputStream::write() wrote 0 bytes." << std::endl;
    }
    const gsize bytes_read = stream->write("\n");
    if(bytes_read)
      std::cout << "File contents written: " << "<newline>" << std::endl;
    else
      std::cerr << "Gio::InputStream::write() wrote 0 bytes." << std::endl;
    stream->close();
    stream.reset(); //Stream can't be used after we have closed it.
    return 0;
  }
  catch(const Glib::Exception& ex)
  {
    std::cerr << "Exception caught: " << ex.what() << std::endl; 
    return 1;
  }
}

// it doeas also some logic
void ModelineWin::update_widgets2()
{
  std::cout << "Here is modeline update_widgets2()" << std::endl;
  Glib::ustring t_title;
  signalClient->get_data(&t_title);
  Glib::ustring t_emptyString = "";
  
  if(t_title.length() == 0) return;
  
  //it means that signal came after starting seq
  if(t_title == "PLAY")
  {
    m_state = STATE_PLAYING;
    m_prompt_1->initialize(THEME_BLINK_2);
    m_prompt_2->initialize(THEME_BLINK_2);
  }

  //it means that signal came after stopping some seq
  if(t_title == "STOP")
  {
    m_state = STATE_IDLE;
    m_prompt_1->initialize(THEME_NEUTRAL_1);
    m_prompt_2->initialize(THEME_NEUTRAL_1);
    if (timeout_client_thread)
    {
      std::cout << "Can't start a timeout thread while another one is running." << std::endl;
    }
    else
    {
      // Start a new timeout thread.
      timeout_client_thread = Glib::Threads::Thread::create(
        sigc::bind(sigc::mem_fun(timeoutClient, &TimeoutClient::countdown), this));
    }
  }
  
  //it means that signal came after loading >
  if(t_title == "K1E" || t_title == "K3Y" || t_title == "WRX")
  {
    if (last_loaded == 1)
    {
      m_prompt_1->initialize(THEME_BLINK_1);
      m_prompt_2->initialize(THEME_NEUTRAL_2);
    }
    else
    {
      m_prompt_1->initialize(THEME_NEUTRAL_2);
      m_prompt_2->initialize(THEME_BLINK_1);
    }
    if(t_title == "K1E")
      m_state = STATE_LOADED_K1E;
    if(t_title == "WRX")
      m_state = STATE_LOADED_WRX;
    if(t_title == "K3Y")
      m_state = STATE_LOADED_K3Y;
  }

  std::cout << "The title " << t_title << std::endl;
  
  // if it is title proposition
  if(t_title.length() > 6)
  {
    title_b = t_title;
    if (m_state == STATE_PLAYING)
    {
      m_prompt_1->initialize(THEME_BLINK_2);
      m_prompt_2->initialize(THEME_BLINK_2);
    }
    else
    {
      if (m_state == STATE_LOADED_K1E)
      {
        m_prompt_1->initialize(THEME_BLINK_1);
        m_prompt_2->initialize(THEME_BLINK_1);
      }
      else
      {
        m_prompt_1->initialize(THEME_NEUTRAL_2);
        m_prompt_2->initialize(THEME_NEUTRAL_2);
      }
    }

    if (bank_1_patternRegex->match(title_b))
    {
      m_curr2->initialize(THEME_BANK_1);
      m_space1->initialize(THEME_BANK_1);
      m_space2->initialize(THEME_BANK_1);
    }
    else if (bank_2_patternRegex->match(title_b))
    {
      m_curr2->initialize(THEME_BANK_2);
      m_space1->initialize(THEME_BANK_2);
      m_space2->initialize(THEME_BANK_2);
    }
    else
    {
      m_curr2->initialize(THEME_BANK_3);
      m_space1->initialize(THEME_BANK_3);
      m_space2->initialize(THEME_BANK_3);
    }
    m_space1->render_string(t_emptyString, false);
    Glib::ustring to_display = title_b.substr(0, title_b.length() - 6);
    m_curr2->render_string(to_display, false);
    //m_curr2->render_string(title_b, false);
    m_space2->render_string(t_emptyString, false);
  }
  
  Glib::ustring t_prompt1 = ">";
  m_prompt_1->render_string(t_prompt1, false);
  Glib::ustring t_prompt2 = ">>";
  m_prompt_2->render_string(t_prompt2, false);
}

