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

#include "modelineaction.h"

ModelineAction::ModelineAction(ModelineConfig* p_config)
{
  modelineConfig = p_config;
  seq_controller_pid = -1;
}

void ModelineAction::load(Glib::ustring item)
{
  seq_controller_pid = -1;
  if(!read_sc_trap_pid()) return;
  // write instruction to seq controller instruction file
  write_instruction("LOAD\n" + item, modelineConfig->getSeqControllerInstruction());
  // send signal to display controller
  kill(seq_controller_pid, SIGUSR1);
}

void ModelineAction::play()
{
  seq_controller_pid = -1;
  if(!read_sc_trap_pid()) return;
  // write instruction to seq controller instruction file
  write_instruction("PLAY", modelineConfig->getSeqControllerInstruction());
  // send signal to display controller
  kill(seq_controller_pid, SIGUSR1);
}

void ModelineAction::stop1()
{
  seq_controller_pid = -1;
  if(!read_sc_trap_pid()) return;
  // write instruction to seq controller instruction file
  write_instruction("STOP1", modelineConfig->getSeqControllerInstruction());
  // send signal to display controller
  kill(seq_controller_pid, SIGUSR1);
}

void ModelineAction::stop2()
{
  seq_controller_pid = -1;
  if(!read_sc_trap_pid()) return;
  // write instruction to seq controller instruction file
  write_instruction("STOP2", modelineConfig->getSeqControllerInstruction());
  // send signal to display controller
  kill(seq_controller_pid, SIGUSR1);
}

void ModelineAction::arm()
{
  //std::cerr << "Arming starter" << std::endl;
  starter_pid = -1;
}

void ModelineAction::disarm()
{
  //std::cerr << "Disarming starter" << std::endl;
  starter_pid = -1;
}

bool ModelineAction::read_sc_trap_pid()
{
  Gio::init();
  auto f = Gio::File::create_for_path(modelineConfig->getSCTrapPidPath());

  try
  {
    auto file_stream = f->read();
    auto data_stream = Gio::DataInputStream::create(file_stream);

    std::string line;
    std::locale::global(std::locale(""));

    data_stream->read_line(line);
    
    if(line != "")
      seq_controller_pid = atoi(line.c_str());
    else
      return false;
  }
  catch  (Glib::Error &err)
  {
    std::cerr << "Couldn't read file " << modelineConfig->getSCTrapPidPath() << std::endl;
    return false;
  }
  std::cerr << "Sequencer controler pid is " << seq_controller_pid << std::endl;
  return true;
}


bool ModelineAction::read_starter_pid()
{
  return false;
}

int ModelineAction::write_instruction(Glib::ustring p_instr, Glib::ustring p_path)
{
  Gio::init();
  try
  {
    auto f = Gio::File::create_for_path(p_path);
    if(!f)
      std::cerr << "ModelineAction::write_instruction() Gio::File::create_for_path() returned an empty RefPtr." << std::endl;

    Glib::RefPtr<Gio::FileOutputStream> stream;

    //If the file exists already then replace it.
    //Otherwise, create it:
    if(f->query_exists())
      stream = f->replace();
    else
      stream = f->create_file();
    if(!stream)
      std::cerr << "ModelineAction::write_instruction() Gio::File::create_file() returned an empty RefPtr." << std::endl;

    const gsize bytes_read = stream->write(p_instr + "\n");
    if(bytes_read)
      std::cout << "ModelineAction::write_instruction() instruction written" << std::endl;
    else
      std::cerr << "ModelineAction::write_instruction() Gio::InputStream::write() wrote 0 bytes." << std::endl;

    stream->close();
    stream.reset(); //Stream can't be used after we have closed it.
    return 0;
  }
  catch(const Glib::Exception& ex)
  {
    std::cerr << "ModelineAction::write_instruction() Exception caught: " << ex.what() << std::endl; 
    return 1;
  }

}

