<?php
$led_rosu_state = $_GET["ledrosu"];
$led_galben_state = $_GET["ledgalben"];
$led_verde_state = $_GET["ledverde"];
$fisier = fopen("led.html", "w") or die("Nu s-a putut deschide fisierul ! (din vina Ruxandrei)");
//$ledgalben = fopen("ledgalben.html", "w") or die("Nu s-a putut deschide fisierul ! (din vina Ruxandrei)");
//$ledverde = fopen("ledverde.html", "w") or die("Nu s-a putut deschide fisierul ! (din vina Ruxandrei)");
$tag_rosu_1='<img src="leduri/led_rosu_';
$tag_rosu_2='.png" alt="led_rosu">';
$tag_galben_1='<img src="leduri/led_galben_';
$tag_galben_2='.png" alt="led_galben">';
$tag_verde_1='<img src="leduri/led_verde_';
$tag_verde_2='.png" alt="led_verde">';
$center_1 = "<center>";
$center_2 = "</center>";
$div1 = "<div>";
$div2 = "</div>";


fwrite($fisier, $center_1);
fwrite($fisier, $div1);
fwrite($fisier, $tag_rosu_1);
fwrite($fisier, $led_rosu_state);
fwrite($fisier, $tag_rosu_2);
fwrite($fisier, $div2);
fwrite($fisier, $div1);
fwrite($fisier, $tag_galben_1);
fwrite($fisier, $led_galben_state);
fwrite($fisier, $tag_galben_2);
fwrite($fisier, $div2);
fwrite($fisier, $div1);
fwrite($fisier, $tag_verde_1);
fwrite($fisier, $led_verde_state);
fwrite($fisier, $tag_verde_2);
fwrite($fisier, $div2);
fwrite($fisier, $center_2);
fclose($fisier)
?>
