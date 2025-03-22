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

#ifndef MODELINE_ACTION_H
#define MODELINE_ACTION_H

#include "modelineconfig.h"

class ModelineAction
{
  public:
    ModelineAction(ModelineConfig * p_config);
    void play();
    void load(Glib::ustring item);
    void stop1();
    void stop2();
    void arm();
    void disarm();
  private:
    ModelineConfig * modelineConfig;
    int seq_controller_pid;
    int starter_pid;
    bool read_sc_trap_pid();
    bool read_starter_pid();
    int write_instruction(Glib::ustring p_instruction, Glib::ustring p_path);
};

#endif // MODELINE_ACTION_H
