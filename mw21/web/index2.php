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

require_once('library_mw2.php');

global $g_filesDir2;
global $g_playListToDisplayPath;

if( isset ( $_POST["ACTION"] )) {
  $g_action_type = trim ( $_POST["ACTION"] );
} else {
  $g_action_type = "select2";
}

if( isset ( $_POST["ITEM"] )) {
  $g_item = trim ( $_POST["ITEM"] );
} else {
  $g_item = "0000";
}

if( isset ( $_POST["DEFAULT_VOLUME"] )) {
  $g_default_volume = trim ( $_POST["DEFAULT_VOLUME"] );
} else {
  $g_default_volume = "70";
}

if( isset ( $_POST["PASSED_VOLUME"] )) {
  $g_passed_volume = trim ( $_POST["PASSED_VOLUME"] );
} else {
  $g_passed_volume = "70";
}

if( isset ( $_POST["SCROLL_TO_PLAYLIST"] )) {
  $g_if_scroll_to_playlist = trim ( $_POST["SCROLL_TO_PLAYLIST"] );
} else {
  $g_if_scroll_to_playlist = "0";
}

$g_list = new FileList($g_filesDir2);
$g_list->readFileList();

$g_action = new Actions();
$l_result = $g_action->doAction2($g_action_type, $g_item, $g_passed_volume, $g_default_volume);

$l_result = trim($l_result);
$g_action->log("Received from action2 after trim: \"" . $l_result . "\"");

if ($l_result == "LOCKED") {
   $g_action->log("Condition checked in mode2: \"" . $l_result . "\"");
//    $g_volume = $g_passed_volume;
}

$g_currentLabel = $g_list->getItem($g_item);
$g_playlist = new PlayList($g_playListToDisplayPath);
$g_playlist->readPlayList();
?>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<html>
<head>
   <meta http-equiv="content-type" content="text/html; charset=utf-8"/>
   <meta name="viewport" content="width=device-width, initial-scale=1"/>
   <title>Waves</title>
   <style type="text/css">
      #dimScreen {
        width: 100%;
        height: 100%;
        background:rgba(255,255,255,0.5); 
        position: fixed;
        top: 0;
        left: 0;
        z-index: 100; /* Just to keep it at the very top */
      }
      .id {
         background: #fbe48f;
         font-weight: bold;
         font-family: monospace;
         font-size:  20px;
      }
      .id_rand_a {
         background: #d4b44f;
         font-weight: bold;
         font-family: monospace;
         font-size:  20px;
      }
      .id_rand_b {
         background: #f4c400;
         font-weight: bold;
         font-family: monospace;
         font-size:  20px;
      }
      .playlist {
         background: #f4a430;
         font-weight: bold;
         font-family: monospace;
         font-size:  20px;
      }
      a {
         display:block;
         width: 100%;
         height: 100%;
         text-decoration: none;
      }
       button {
         border: 0;
         padding: 0;
         display: inline;
         width: 100%;
         height: 100%;
         background: none;
         text-decoration: none;
         text-align: left;
       }
      #top {
         position: fixed;
         background: #fbc43f;
         font-weight: bold;
         font-family: monospace;
         font-size:  20px;
         width: 100%;
      }
      #bottom {
         position: fixed;
         background: #fbc43f;
         font-weight: bold;
         font-family: monospace;
         font-size:  20px;
         bottom: 0;
         width: 100%;
      }
      #my_timer {
         font-weight: bold;
         font-family: monospace;
         font-size:  20px;
         background: #c73684;
         color: #FFFFFF;
       }
      .play {
         font-weight: bold;
         font-family: monospace;
         font-size:  20px;
         background: #ec5654;
         text-align: center;
      }
      .load {
         font-weight: bold;
         font-family: monospace;
         font-size:  20px;
         background: #87e684;
         text-align: center;
      }
      .menu {
         font-weight: bold;
         font-family: monospace;
         font-size:  20px;
         background: #ec5654;
         text-align: center;
      }
      .label {
         font-weight: bold;
         font-family: monospace;
         font-size:  20px;
         background: #ec5654;
         color: #FFFFFF;
      }
      .lock {
         font-weight: bold;
         font-family: monospace;
         font-size:  20px;
         background: #ec5654;
         text-align: center;
         color: #FFFFFF;
      }
      .transpo {
         font-weight: bold;
         font-family: monospace;
         font-size:  20px;
         background: #c73684;
         text-align: center;
         color: #FFFFFF;
       }
      .transpo_p {
         font-weight: bold;
         font-family: monospace;
         font-size:  20px;
         background: #c73684;
         text-align: center;
         color: #FFFFFF;
       }
      .vol_set {
         font-weight: bold;
         font-family: monospace;
         font-size:  20px;
         background: #fbe48f;
         text-align: center;
         color: #404040;
       }
      .vol {
         font-weight: bold;
         font-family: monospace;
         font-size:  20px;
         background: #8b3a23;
         color: #FFFFFF;
       }
   </style>
   <script type="text/javascript">

     function hideshow(which){
       if (!document.getElementById)
         return
       if (which.style.display=="table-row")
         which.style.display="none"
       else
         which.style.display="table-row"
     }

     function jumpToCurrent(){
       if (!document.getElementById)
         return
       var curr_elem_anchor = document.getElementById("row_" + <?php echo "\"" . sprintf("%04d", intval($g_item) - 2) . "\""; ?> );
        curr_elem_anchor.scrollIntoView(true);
     }
<?php if ($g_if_scroll_to_playlist == "0") { ?>
     window.onload = function() {
        var elem_anchor = document.getElementById("row_" + <?php echo "\"" . sprintf("%04d", intval($g_item) - 2) . "\""; ?> );
        elem_anchor.scrollIntoView(true);
     }
<?php } else { ?>
     window.onload = function() {
        var elem_anchor = document.getElementById("row_end_head");
        elem_anchor.scrollIntoView(true);
     }
<?php } ?>

</script>
</head>

<body lang="pl-PL" dir="ltr" style="margin:0px">
<div id="dimScreen" style="display:none">&nbsp;</div>
<!-- TOP DIV -->
  <div id="top">
    <table style="width: 100%" cellspacing="4px">
      <colgroup>
        <col span="1" style="width: 80%;">
        <col span="1" style="width: 20%;">
      </colgroup>
      <tr><td colspan="5" class="label">&nbsp;</td></tr>
      <tr>
      <!--LABEL ROW -->
        <td class="label">
<?php
print substr($g_currentLabel, 0, 15);
?>

</td>
<td class="menu" onclick="javascript:hideshow(document.getElementById('my_menu'))">
<?php print $g_default_volume; ?>
</td>
</tr><!-- LABEL ROW -->


<tr id="my_menu" style="display: none"> <!-- MENU ROW -->
<td colspan="2">
<!-- ########################################### -->
  <div>
  <table cellspacing="4px" style="font-weight: bold" width="100%">
  <col width="20%">
  <col width="20%">
  <col width="20%">
  <col width="20%">
  <col width="20%">

  <tr>
    <td colspan="5" class="vol_set">
<?php
putForm3("./index2.php", "select2", $g_item, $g_default_volume, $g_default_volume, "vol_set", "CHECK", 1);
    ?>
    </td>
  </tr>
  <tr>
    <td colspan="2" class="vol_set">CURRENT</td>
    <td colspan="1" class="vol_set">&nbsp;</td>
    <td colspan="2" class="vol_set">DEFAULT</td>
  </tr>

  <tr>
    <td class="vol_set">
<?php
putForm3("./index2.php", "current_volume2", $g_item, $g_default_volume, 100, "lock", "100");
    ?>
    </td>
    <td class="vol_set">
<?php
putForm3("./index2.php", "current_volume2", $g_item, $g_default_volume, 90, "lock", "90");
    ?>
    </td>
    <td class="vol_set">&nbsp;</td>
    <td class="vol_set">
<?php
putForm3("./index2.php", "default_volume2", $g_item, 100, 100, "lock", "100");
    ?>
    </td>
    <td class="vol_set">
<?php
putForm3("./index2.php", "default_volume2", $g_item, 90, 90, "lock", "90");
    ?>
    </td>
  </tr>


  <tr>
    <td class="vol_set">
<?php
putForm3("./index2.php", "current_volume2", $g_item, $g_default_volume, 80, "lock", "80");
    ?>
    </td>
    <td class="vol_set">
<?php
putForm3("./index2.php", "current_volume2", $g_item, $g_default_volume, 70, "vol_set", "70");
    ?>
    </td>
    <td class="vol_set">&nbsp;</td>
    <td class="vol_set">
<?php
putForm3("./index2.php", "default_volume2", $g_item, 80, 80, "lock", "80");
    ?>
    </td>
    <td class="vol_set">
<?php
putForm3("./index2.php", "default_volume2", $g_item, 70, 70, "vol_set", "70");
    ?>
    </td>
  </tr>

  <tr>
    <td class="vol_set">
<?php
putForm3("./index2.php", "current_volume2", $g_item, $g_default_volume, 60, "vol_set", "60");
    ?>
    </td>
    <td class="vol_set">
<?php
putForm3("./index2.php", "current_volume2", $g_item, $g_default_volume, 50, "vol_set", "50");
    ?>
    </td>
    <td class="vol_set">&nbsp;</td>
    <td class="vol_set">
<?php
putForm3("./index2.php", "default_volume2", $g_item, 60, 60, "vol_set", "60");
    ?>
    </td>
    <td class="vol_set">
<?php
putForm3("./index2.php", "default_volume2", $g_item, 50, 50, "vol_set", "50");
    ?>
    </td>
  </tr>

  <tr>
    <td class="vol_set">
<?php
putForm3("./index2.php", "current_volume2", $g_item, $g_default_volume, 40, "vol_set", "40");
    ?>
    </td>
    <td class="vol_set">
<?php
putForm3("./index2.php", "current_volume2", $g_item, $g_default_volume, 30, "vol_set", "30");
    ?>
    </td>
    <td class="vol_set">&nbsp;</td>
    <td class="vol_set">
<?php
putForm3("./index2.php", "default_volume2", $g_item, 40, 40, "vol_set", "40");
    ?>
    </td>
    <td class="vol_set">
<?php
putForm3("./index2.php", "default_volume2", $g_item, 30, 30, "vol_set", "30");
    ?>
    </td>
  </tr>

  <tr>
    <td class="vol_set">
<?php
putForm3("./index2.php", "current_volume2", $g_item, $g_default_volume, 20, "vol_set", "20");
    ?>
    </td>
    <td class="vol_set">
<?php
putForm3("./index2.php", "current_volume2", $g_item, $g_default_volume, 10, "load", "10");
    ?>
    </td>
    <td class="vol_set">&nbsp;</td>
    <td class="vol_set">
<?php
putForm3("./index2.php", "default_volume2", $g_item, 20, 20, "vol_set", "20");
    ?>
    </td>
    <td class="vol_set">
<?php
putForm3("./index2.php", "default_volume2", $g_item, 10, 10, "load", "10");
    ?>
    </td>
  </tr>

  <tr>
    <td colspan="2" class="vol_set">
<?php
putForm3("./index2.php", "current_volume2", $g_item, $g_default_volume, 0, "load", "0");
    ?>
    </td>
    <td class="vol_set">&nbsp;</td>
    <td colspan="2" class="vol_set">
<?php
putForm3("./index2.php", "default_volume2", $g_item, 0, 0, "load", "0");
    ?>
    </td>
  </tr>
  <tr>
    <td colspan="5" class="vol_set">&nbsp;</td>
  </tr>

  <tr>
    <td class="vol_set">
<?php
putForm3("./index2.php", "overwrite2_full", $g_item, $g_default_volume, $g_default_volume, "vol_set", "FULL", 1);
    ?>
    </td>
    <td class="vol_set">
<?php
putForm3("./index2.php", "rotate2", $g_item, $g_default_volume, $g_default_volume, "vol_set", "ROTATE", 1);
    ?>
    </td>
    <td class="vol_set">
<?php
putForm3("./index2.php", "overwrite2_p3", $g_item, $g_default_volume, $g_default_volume, "vol_set", "OVR 3", 1);
    ?>
    </td>
    <td class="vol_set">
<?php
putForm3("./index2.php", "overwrite2_p2", $g_item, $g_default_volume, $g_default_volume, "vol_set", "OVR 2", 1);
    ?>
    </td>
    <td class="vol_set">
<?php
putForm3("./index2.php", "overwrite2_p1", $g_item, $g_default_volume, $g_default_volume, "vol_set", "OVR 1", 1);
    ?>
    </td>
  </tr>
  <tr>
    <td colspan="5" class="vol_set">&nbsp;</td>
  </tr>
  <tr>
<?php
print "    <td>\n";
putForm3("./index2.php", "clear2", $g_item, $g_default_volume, $g_default_volume, "vol_set", "CLEAR");
print "    </td>\n";
print "    <td>\n";
putForm3("./index2.php", "next2", $g_item, $g_default_volume, $g_default_volume, "load", "NEXT");
print "    </td>\n";
print "    <td>\n";
putForm3("./index2.php", "play2", $g_item, $g_default_volume, $g_default_volume, "load", "PLAY");
print "    </td>\n";
print "    <td class=\"label\">&nbsp;</td>\n";
print "    <td>\n";
putForm3("./index2.php", "stop2", $g_item, $g_default_volume, $g_default_volume, "play", "STOP");
print "    </td>\n";
?>
  </tr>
  <tr>
    <td colspan="5" class="label">
&nbsp;
    </td>
  </tr>

<?php
global $g_displayLocking;
if($g_displayLocking) {
?>
  <tr>
    <td class="lock">
<?php putForm3("./index2.php", "lock2", $g_item, $g_default_volume, $g_default_volume, "lock", "LOCK"); ?>
    </td>
    <td class="lock">
&nbsp;
    </td>
    <td class="lock">
<?php putForm3("./index2.php", "unlock2", $g_item, $g_default_volume, $g_default_volume, "lock", "UNLOCK"); ?>
    </td>
    <td colspan="2" class="lock">
&nbsp;
    </td>
  </tr>
  <tr>
    <td colspan="5" class="lock">
&nbsp;
    </td>
  </tr>
<?php
}
?>

  </table>
</div>
<!-- ########################################### -->
</td>
</tr> <!-- MENU ROW -->




  </table>
  </div>
<!-- END OF TOP DIV -->






<!-- LIST -->
<table style="width: 100%;" cellspacing="4px">
  <colgroup>
    <col span="1" style="width: 20%;">
    <col span="1" style="width: 80%;">
  </colgroup>
  <tr id="row_-002">    <td class="id">-2</td><td class="id">abc2</td>    </tr>
  <tr id="row_-001">    <td class="id">-1</td><td class="id">abc</td>    </tr>

<?php
$l_title_class = "id";
$l_title_counter = 0;
global $g_noRandomLimit;

foreach($g_list->getFileList() as $l_item) {
$l_tempIndex = substr($l_item, 0, 4);
$l_tempTitle = substr(substr($l_item, 5), 0, 24);

print "  <tr id=\"row_" . $l_tempIndex . "\">\n";
print "   <td class=\"" . $l_title_class . "\">\n";
putForm3("./index2.php", "select2", $l_tempIndex, $g_default_volume, $g_default_volume, $l_title_class, $l_tempIndex);
print "   </td><td class=\"" . $l_title_class . "\">" . $l_tempTitle . "</td>\n";
print "  </tr>\n";

  $l_title_counter++;
  if ($l_title_counter >= $g_noRandomLimit) {
    if (($l_title_counter / 10) % 2 == 1) {
      $l_title_class="id_rand_a";
    } else {
      $l_title_class="id_rand_b";
    }
  }
}
?>
  <tr id="row_end_head"><td class="playlist" onclick="javascript:jumpToCurrent()">----</td><td class="playlist">-----------------------</td>    </tr>
  <tr id="row_end"><td class="playlist" onclick="javascript:jumpToCurrent()">----</td><td class="playlist">------ PLAYLIST -------</td>    </tr>

<!-- CURRENT PLAYLIST -->
<?php
foreach($g_playlist->getPlayList() as $l_plitem) {
$l_tempIndex = substr($l_plitem, 0, 4);
$l_tempTitle = substr(substr($l_plitem, 5), 0, 24);

print "  <tr id=\"row_end\">\n";
print "   <td class=\"playlist\" onclick=\"javascript:jumpToCurrent()\">" . $l_tempIndex . "</td><td class=\"playlist\">" . $l_tempTitle . "</td>\n";
print "  </tr>\n";

}
?>

<!-- END OF CURRENT PLAYLIST -->

  <tr id="row_end">    <td class="playlist" onclick="javascript:jumpToCurrent()">----</td><td class="playlist">-----------------------</td>    </tr>
  <tr id="row_end">    <td class="playlist" onclick="javascript:jumpToCurrent()">----</td><td class="playlist">-----------------------</td>    </tr>
  <tr id="row_end">    <td class="playlist" onclick="javascript:jumpToCurrent()">----</td><td class="playlist">-----------------------</td>    </tr>

</table>
<!-- END OF LIST -->

<!-- BOTTOM DIV -->
  <div id="bottom">
    <table style="width: 100%" cellspacing="4px">
      <colgroup>
        <col span="1" style="width: 50%;">
        <col span="1" style="width: 50%;">
      </colgroup>

      <tr>
        <td colspan="2" class="label">
&nbsp;

        </td>
      </tr>

      <tr>
        <td colspan="2" class="label">
&nbsp;
<!--          <img src="./graphics/label.png"></img> -->
        </td>
      </tr>
    </table>
  </div>
<!-- END OF BOTTOM DIV -->
</body>
</html>
