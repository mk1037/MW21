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

if( isset ( $_POST["ACTION"] )) {
  $g_action_type = trim ( $_POST["ACTION"] );
} else {
  $g_action_type = "select";
}

if( isset ( $_POST["ITEM"] )) {
  $g_item = trim ( $_POST["ITEM"] );
} else {
  $g_item = "0000";
}

if( isset ( $_POST["ITEM_NR"] )) {
  $g_item_nr = trim ( $_POST["ITEM_NR"] );
} else {
  $g_item_nr = "0000";
}

$g_list = new FileList($g_dataDir . "/bank_3/text/");
$g_list->readFileList();

$g_action = new Actions();
$l_result = $g_action->doAction($g_action_type, $g_item);

$l_result = trim($l_result);
$g_action->log("Received from action2 after trim: \"" . $l_result . "\"");


$g_currentLabel = $g_item;

?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<html>
<head>
   <meta http-equiv="content-type" content="text/html; charset=utf-8"/>
   <meta name="viewport" content="width=device-width, initial-scale=1"/>
   <title>K3 BANK</title>
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
         background: #C5B0C9;
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
         background: #75507B;
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
      .stop {
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
      .play {
         font-weight: bold;
         font-family: monospace;
         font-size:  20px;
         background: #27e6c4;
         text-align: center;
      }
      .lock {
         font-weight: bold;
         font-family: monospace;
         font-size:  20px;
         background: #a73684;
         text-align: center;
      }
      .unlock {
         font-weight: bold;
         font-family: monospace;
         font-size:  20px;
         background: #27e6c4;
         text-align: center;
      }
      .menu {
         font-weight: bold;
         font-family: monospace;
         font-size:  20px;
         background: #D4D4D4;
         text-align: center;
      }
      .label {
         font-weight: bold;
         font-family: monospace;
         font-size:  20px;
         background: #5C0084;
         color: #FFFFFF;
      }
      .vol_set {
         font-weight: bold;
         font-family: monospace;
         font-size:  20px;
         background: #C5B0C9;
         text-align: center;
         color: #404040;
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

     window.onload = function() {
        var elem_anchor = document.getElementById("row_" + <?php echo "\"" . sprintf("%04d", intval($g_item_nr) - 1) . "\""; ?> );
        elem_anchor.scrollIntoView(true);
     }
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
      <tr><!--LABEL ROW -->
        <td class="label">
<?php
print $g_item_nr . "_" . substr(substr($g_currentLabel, 0, -4), 0, 15);
?>

</td>
<td class="menu" onclick="javascript:hideshow(document.getElementById('my_menu'))">
<?php print "MENU"; ?>
</td>
</tr><!-- LABEL ROW -->


<tr id="my_menu" style="display: none"> <!-- MENU ROW -->
<td colspan="2">
<!-- ########################################### -->
  <div>
  <table cellspacing="4px" style="font-weight: bold" width="100%">
  <col width="30%">
  <col width="10%">
  <col width="30%">
  <col width="30%">

  <tr>
    <td colspan="4" class="vol_set">&nbsp;</td>
  </tr>

  <tr>
    <td class="vol_set">
    <?php
       putForm2("./index_bank_3.php", "load", $g_item, $g_item_nr, "load", "LOAD");
    ?>
    </td>
    <td class="vol_set">&nbsp;</td>
    <td class="vol_set">
    <?php
       putForm2("./index_bank_3.php", "play", $g_item, $g_item_nr, "play", "PLAY");
    ?>
    </td>
    <td class="vol_set">
    <?php
       putForm2("./index_bank_3.php", "stop", $g_item, $g_item_nr, "stop", "STOP");
    ?>
    </td>
  </tr>

  <tr>
    <td colspan="4" class="vol_set">&nbsp;</td>
  </tr>

  <tr>
    <td class="vol_set">
    <?php
       putForm2("./index_bank_3.php", "lock", $g_item, $g_item_nr, "lock", "LOCK");
    ?>
    </td>
    <td class="vol_set">&nbsp;</td>
    <td class="vol_set">
    <?php
       putForm2("./index_bank_3.php", "unlock", $g_item, $g_item_nr, "unlock", "UNLOCK");
    ?>
    </td>
    <td class="vol_set">&nbsp;</td>
  </tr>

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
  <tr id="row_-0001">    <td class="id">-1</td><td class="id">abc</td>    </tr>

  
  
  
<?php

$l_title_class = "id";
$l_title_counter = 0;

foreach($g_list->getFileList() as $l_item) {
$l_tempIndex = sprintf("%04d", $l_title_counter);//printf 00...
$l_tempTitle = substr(substr($l_item, 0, -4), 0, 15);

print "  <tr id=\"row_" . $l_tempIndex . "\">\n";
print "   <td class=\"" . $l_title_class . "\">\n";
putForm2("./index_bank_3.php", "select", $l_item, $l_tempIndex, "id", $l_tempIndex);
print "   </td><td class=\"" . $l_title_class . "\">" . $l_tempTitle . "</td>\n";
print "  </tr>\n";

$l_title_counter++;
}
?>

</table>
<!-- END OF LIST -->
</body>
</html>
