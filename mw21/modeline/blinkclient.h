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

#ifndef MODELINE_BLINKCLIENT_H
#define MODELINE_BLINKCLIENT_H

#define ACTION_BLINK_SELECTED 0
#define ACTION_BLINK_SEARCH 1

#include "modelineconfig.h"

class BlinkClient
{
  public:
    BlinkClient(unsigned int p_counter, unsigned int p_period);
    ~BlinkClient();
    void blink(ModelineWin * caller, int p_action);

    
  private:
    unsigned int blinkingTime;
    unsigned int blinkingPeriod;
};


#endif //MODELINE_BLINKCLIENT_H
