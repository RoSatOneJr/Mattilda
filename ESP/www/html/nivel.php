<?php
$nivel = $_GET["nivel"];
$fisier = fopen("nivele.html", "w") or die("Nu s-a putut deschide fisierul ! (din vina Ruxandrei)");
$img1 = '<center><img src="nivele/indicator_brate_';
$img2 = '.png" width="200" height="150"></center>';

fwrite($fisier, $img1);
fwrite($fisier, $nivel);
fwrite($fisier, $img2);
fclose($fisier);

?>
