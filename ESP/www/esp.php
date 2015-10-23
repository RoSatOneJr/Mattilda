<?php

$ayycopy = $_GET["ayy"];
$lmaocopy = $_GET["lmao"];
$fisier = fopen("mattilda.html", "a") or die("Nu s-a putut deschide fisierul ! (din vina Ruxandrei)");
$div1 = "<div>";
$div2 = "</div> \n";


fwrite($fisier, $div1);
fwrite($fisier, $ayycopy);
fwrite($fisier, $div2);
fclose($fisier);

?>
