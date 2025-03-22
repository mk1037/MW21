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

include_once('config.php');

class Actions {
   public function doAction($p_type, $p_item1) {
      $this->log("MW2_Action: $p_type  item1 $p_item1");
      if($p_type == "select" ) {
         return $this->select($p_item1);
      }
      if($p_type == "load" ) {
         $this->load();
      }
      if($p_type == "play" ) {
         $this->play();
      }
      if($p_type == "stop" ) {
         $this->stop();
      }
      if($p_type == "lock" ) {
         $this->lock();
      }
      if($p_type == "unlock" ) {
         $this->unlock();
      }
   }

   public function doAction2($p_type, $p_item, $p_passed_vol, $p_default_vol) {
      $this->log("MW2_Action2: $p_type item: $p_item passed volume: $p_passed_vol default volume: $p_default_vol");
      if($p_type == "select2" ) {
         $this->select2($p_item);
      }
      if($p_type == "play2" ) {
         $this->play2($p_item);
      }
      if($p_type == "stop2" ) {
         $this->stop2($p_item);
      }
      if($p_type == "next2" ) {
         $this->next2($p_item);
      }
      if($p_type == "clear2" ) {
         $this->clear2();
      }
      if($p_type == "current_volume2" ) {
         return $this->current_volume2($p_passed_vol);
      }
      if($p_type == "default_volume2" ) {
         return $this->default_volume2($p_passed_vol);
      }
      if($p_type == "overwrite2_p1" ) {
         return $this->overwrite2($p_item, 1);
      }
      if($p_type == "overwrite2_p2" ) {
         return $this->overwrite2($p_item, 2);
      }
      if($p_type == "overwrite2_p3" ) {
         return $this->overwrite2($p_item, 3);
      }
      if($p_type == "overwrite2_p4" ) {
         return $this->overwrite2($p_item, 4);
      }
      if($p_type == "overwrite2_full" ) {
         return $this->overwrite2_full($p_item);
      }
      if($p_type == "rotate2" ) {
         return $this->rotate2();
      }
      if($p_type == "lock2" ) {
         return $this->lock2();
      }
      if($p_type == "unlock2" ) {
         return $this->unlock2();
      }
   }

   public function doAction6($p_type) {
      $this->log("Action6: $p_type");
      if($p_type == "place_windows" ) {
         $this->place_windows6();
      }
   }

   public function doAction8($p_type, $p_value) {
      $this->log("Action8: $p_type value $p_value");
      if($p_type == "reconnect" ) {
         $this->reconnect8($p_value);
      }
   }

   public function log($p_string) {
      global $g_logPath;
      $log_file = fopen($g_logPath, "a");
      fwrite($log_file, date("Y-m-d H:i:s  : "));
      fwrite($log_file, $p_string . "\n");
      fclose($log_file);
   }

   public function select($p_item) {
      global $g_workingPath;
      global $g_selectTimeout;
      $exec_string = "./selectm_mw2.sh " . substr($p_item, 0, -4);
      $this->log($exec_string);
      chdir($g_workingPath . "/web");
      $l_result = shell_exec($exec_string);
      return $l_result;
   }
   public function load() {
      global $g_workingPath;
      $exec_string = "./loadm_mw2.sh";
      $this->log($exec_string);
      chdir($g_workingPath . "/web");
      $l_result = shell_exec($exec_string);
      return $l_result;
   }
   public function play() {
      global $g_workingPath;
      $exec_string = "./playm_mw2.sh";
      $this->log($exec_string);
      chdir($g_workingPath . "/web");
      $l_result = shell_exec($exec_string);
      return $l_result;
   }
   public function stop() {
      global $g_workingPath;
      $exec_string = "./stopm_mw2.sh";
      $this->log($exec_string);
      chdir($g_workingPath . "/web");
      $l_result = shell_exec($exec_string);
      return $l_result;
   }
   public function lock() {
      global $g_workingPath;
      $exec_string = "./lock_mw2.sh";
      $this->log($exec_string);
      chdir($g_workingPath . "/web");
      $l_result = shell_exec($exec_string);
      return $l_result;
   }
   public function unlock() {
      global $g_workingPath;
      $exec_string = "./unlock_mw2.sh";
      $this->log($exec_string);
      chdir($g_workingPath . "/web");
      $l_result = shell_exec($exec_string);
      return $l_result;
   }

   
   
   public function select2($p_item) {
      global $g_workingPath;
      $exec_string = 'Selecting mode 2 item ' . $p_item;
      $this->log($exec_string);
   }

   public function stop2($p_item) {
      global $g_workingPath;
      $exec_string = './stopvpl2.sh';
      $this->log($exec_string);
      chdir($g_workingPath . "/web");
      exec($exec_string);
   }

   public function play2($p_item) {
      global $g_workingPath;
      global $g_filesDir2;
      global $g_logPath2;
      global $g_noRandomLimit;
      global $g_playvpl2ArgsPath;

      $exec_string = './stopvpl2.sh';
      $this->log($exec_string);
      chdir($g_workingPath . "/web");
      $stop_result = trim(shell_exec($exec_string));

      if($stop_result == "false") {
        $this->log("Stopping failure");
        return false;
      }


      $exec_string = './playlist_random.sh ' . $g_filesDir2 .  ' ' . $p_item . ' ' . $g_noRandomLimit;
      $this->log($exec_string);
      chdir($g_workingPath . "/web");
      exec($exec_string);

      $exec_string = 'echo "' . $g_filesDir2 .  ' ' . $g_logPath2 . ' break" > ' . $g_playvpl2ArgsPath;
      $this->log($exec_string);
      chdir($g_workingPath . "/web");
      exec($exec_string);

      $exec_string = './signal_playvpl2.sh';
      $this->log($exec_string);
      chdir($g_workingPath . "/web");
      exec($exec_string);

   }

   public function next2($p_item) {
      global $g_workingPath;
      $exec_string = './stopvpl2.sh next';
      $this->log($exec_string);
      chdir($g_workingPath . "/web");
      exec($exec_string);
   }

   public function clear2() {
      global $g_workingPath;
      $exec_string = './clear.sh';
      $this->log($exec_string);
      chdir($g_workingPath . "/web");
      exec($exec_string);
   }

   public function current_volume2($p_volume) {
      global $g_workingPath;
      $exec_string = './volumev2.sh ' . $p_volume;
      $this->log($exec_string);
      chdir($g_workingPath . "/web");
      $l_result = exec($exec_string);
      return $l_result;
   }

   public function default_volume2($p_volume) {
      global $g_workingPath;
      global $g_defaultVolumePath;
      $exec_string = 'echo "' . $p_volume . '" > ' . $g_defaultVolumePath;
      $this->log($exec_string);
      chdir($g_workingPath . "/web");
      $l_result = exec($exec_string);
      return $l_result;
   }

   public function overwrite2_full($p_item) {
      global $g_workingPath;
      global $g_filesDir2;
      global $g_logPath2;
      global $g_noRandomLimit;

      $exec_string = './playlist_random.sh ' . $g_filesDir2 .  ' ' . $p_item . ' ' . $g_noRandomLimit;
      $this->log($exec_string);
      chdir($g_workingPath . "/web");
      exec($exec_string);
   }

   public function overwrite2($p_item, $p_position) {
      global $g_workingPath;
      global $g_filesDir2;
      global $g_logPath2;

      $exec_string = './overwrite.sh ' . $g_filesDir2 . ' ' . $p_position . ' ' . $p_item;
      $this->log($exec_string);
      chdir($g_workingPath . "/web");
      $l_result = shell_exec($exec_string);
      return $l_result;
   }

   public function rotate2() {
      global $g_workingPath;

      $exec_string = './rotate.sh';
      $this->log($exec_string);
      chdir($g_workingPath . "/web");
      shell_exec($exec_string);
   }

   public function lock2() {
      global $g_workingPath;
      $exec_string = "./lock_mw2.sh";
      $this->log($exec_string);
      chdir($g_workingPath . "/web");
      $l_result = shell_exec($exec_string);
      return $l_result;
   }

   public function unlock2() {
      global $g_workingPath;
      $exec_string = "./unlock_mw2.sh";
      $this->log($exec_string);
      chdir($g_workingPath . "/web");
      $l_result = shell_exec($exec_string);
      return $l_result;
   }

   public function place_windows6() {
      global $g_workingPath;
      $exec_string = './place_windows.sh';
      $this->log($exec_string);
      chdir($g_workingPath . "/web");
      exec($exec_string);
   }

   public function reconnect8($p_value) {
      global $g_workingPath;
      $exec_string = './reconnect.sh ' . $p_value;
      $this->log($exec_string);
      chdir($g_workingPath . "/web");
      exec($exec_string);
   }

}

class FileList {
   public $f_fileList = array();
   public $f_listSize;
   public $f_currentId = -1;

   public function __construct($p_fileDir) {
      $this->fileDir = $p_fileDir;
   }

   public function readFileList() {
      $this->f_fileList = array();
      $this->f_fileList = array_slice(scandir($this->fileDir),2);
      $this->f_listSize = sizeOf($this->f_fileList);
      if ($this->f_currentId == -1) {$this->f_currentId = 0;}
   }

   public function getFileList() {
      return $this->f_fileList;
   }

   public function getSize() {
      return $this->f_listSize;
   }

   public function getCurrent() {
      return $this->f_currentId;
   }

   public function getItem($index) {
      foreach ($this->f_fileList as $l_item) {
         if(substr($l_item, 0, 4) == $index) {
            return $l_item;
         }
      }
   }
}

class PlayList {
   public $f_playList = array();
   public $f_playListPath;
   public $f_playListSize;

   public function __construct($p_playlistPath) {
      $this->f_playListPath = $p_playlistPath;
   }

   public function readPlayList() {
      $this->f_playList = array();
      if ($file = fopen($this->f_playListPath, "r")) {
         while(!feof($file)) {
            $textperline = trim(fgets($file));
            if ($textperline != "") {
               array_push($this->f_playList, $textperline);
            }
         }
         fclose($file);
      }
      $this->f_playListSize = sizeOf($this->f_playList);
   }

   public function getPlayList() {
      return $this->f_playList;
   }

   public function getSize() {
      return $this->f_playListSize;
   }

   public function getItem($index) {
      foreach ($this->f_playList as $l_item) {
         if(substr($l_item, 0, 4) == $index) {
            return $l_item;
         }
      }
   }
}


function putForm2($p_actionFile, $p_type, $p_item, $p_item_nr, $p_buttonClass, $p_buttonText) {
   print "<form action=\"" . $p_actionFile . "\" method=\"post\" style=\"display: inline;\">\n";
   print "<input type=\"hidden\" name=\"ACTION\" value=\"" . $p_type . "\" />\n";
   print "<input type=\"hidden\" name=\"ITEM\" value=\"" . $p_item . "\" />\n";
   print "<input type=\"hidden\" name=\"ITEM_NR\" value=\"" . $p_item_nr . "\" />\n";
   print "<button class=\"" . $p_buttonClass . "\">" . $p_buttonText . "</button>\n";
   print "</form>\n";
}

function putForm3($p_actionFile, $p_type, $p_item, $p_default_volume, $p_passed_volume, $p_buttonClass, $p_buttonText, $p_scroll_to_playlist = "0") {
   print "      <form action=\"" . $p_actionFile . "\" method=\"post\" style=\"display: inline;\">\n";
   print "        <input type=\"hidden\" name=\"ACTION\" value=\"" . $p_type . "\" />\n";
   print "        <input type=\"hidden\" name=\"ITEM\" value=\"" . $p_item . "\" />\n";
   print "        <input type=\"hidden\" name=\"DEFAULT_VOLUME\" value=\"" . $p_default_volume . "\" />\n";
   print "        <input type=\"hidden\" name=\"PASSED_VOLUME\" value=\"" . $p_passed_volume . "\" />\n";
   print "        <input type=\"hidden\" name=\"SCROLL_TO_PLAYLIST\" value=\"" . $p_scroll_to_playlist . "\" />\n";
   print "        <button class=\"" . $p_buttonClass . "\">" . $p_buttonText . "</button>\n";
   print "      </form>\n";
}

?>
