<?php

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

error_reporting(E_ALL);

require_once('./library_mw2.php');

global $g_dataDir;
global $g_logPath;

$g_action_type = "place_windows";

$g_action = new Actions();
$l_result = $g_action->doAction6($g_action_type);

?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<html>
<head>
   <meta http-equiv="content-type" content="text/html; charset=utf-8"/>
   <meta name="viewport" content="width=device-width, initial-scale=1"/>
   <title>Placing windows</title>
</head>

<body lang="pl-PL" dir="ltr" style="margin:0px">
Windows placed
</body>
</html>
