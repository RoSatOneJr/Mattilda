<?php
$date1 = $_GET["date1"];
$fisier = fopen("mattilda1.html", "a") or die("Nu s-a putut deschide fisierul ! (din vina Ruxandrei)");
$div1 = "<div>";
$div2 = "</div> \n";
$span1 = '<span class="timestamp">';
$span2 = "</span>";
$span3 = '<span class="date">';


//TIME-ZONEUL TREBUIE SCHIMBAT IN OLANDA, heh, daca ajungem
//date_default_timezone_set ('Europe/Amsterdam');
date_default_timezone_set ('Europe/Bucharest');


$timp_HMS = date("H:i:s");
// $timp_GMT, $timp_GMT_val, $whitespace, $timp_HMS, $whitespace;
$timestamp = $timp_HMS.": ";
echo $timestamp;
fwrite($fisier, $div1);
fwrite($fisier, $span1);
fwrite($fisier, $timestamp);
fwrite($fisier, $span2);
fwrite($fisier, $span3);
fwrite($fisier, $date1);
fwrite($fisier, $span2);
fwrite($fisier, $div2);
fclose($fisier);

?>
