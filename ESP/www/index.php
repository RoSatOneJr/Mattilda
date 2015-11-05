<html>
<head>
<script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jquery/1.4.2/jquery.min.js"></script>
</head>

<style>

body {
    background-color: #fdf6e3;
}

iframe{
  border-color: #eee8d5;
  border-style: solid;
  border-width: 3px;
  border-radius: 25px;

}

.butoncss {
	-moz-box-shadow:inset 0px 0px 0px 0px #ffffff;
	-webkit-box-shadow:inset 0px 0px 0px 0px #ffffff;
	box-shadow:inset 0px 0px 0px 0px #ffffff;
	background:-webkit-gradient(linear, left top, left bottom, color-stop(0.05, #FFFEFB), color-stop(1, #FFF2E5));
	background:-moz-linear-gradient(top, #FFFEFB 5%, #FFF2E5 100%);
	background:-webkit-linear-gradient(top, #FFFEFB 5%, #FFF2E5 100%);
	background:-o-linear-gradient(top, #FFFEFB 5%, #FFF2E5 100%);
	background:-ms-linear-gradient(top, #FFFEFB 5%, #FFF2E5 100%);
	background:linear-gradient(to bottom, #FFFEFB 5%, #FFF2E5 100%);
	filter:progid:DXImageTransform.Microsoft.gradient(startColorstr='#FFFEFB', endColorstr='#FFF2E5',GradientType=0);
	background-color:#FFFEFB;
	-moz-border-radius:2px;
	-webkit-border-radius:2px;
	border-radius:2px;
	border:1px solid #dcdcdc;
	display:inline-block;
	cursor:pointer;
	color:#666666;
	font-family:Trebuchet MS;
	font-size:15px;
	font-weight:bold;
	padding:10px 16px;
	text-decoration:none;
}
.butoncss:active {
	position:relative;
	top:1px;
}

</style>
<body>
 <center>
    <iframe id="frame" src="mattilda.html" width="1000" height="600" scrolling="yes" frameBorder="1"></iframe>


    <script type="text/javascript">

          interval = setInterval(function() {$('#frame').attr('src', $('#frame').attr('src'));}, 500);


          function pauza(){
            clearInterval(interval);

          }
          function continua(){
            interval = setInterval(function() {$('#frame').attr('src', $('#frame').attr('src'));}, 500);

          }

          var myIframe = document.getElementById('frame');
          myIframe.onload = function () {
            myIframe.contentWindow.scrollTo(0,9999999);
          }
  </script>


  </script>
    <div>

    <input type="button" value="Pauza" id="butonPauza" onclick="pauza()" class="butoncss"></input>
    <input type="button" value="Continua" id="butonContinua" onclick="continua()" class="butoncss"></input>
  </div>
</center>
</body>
</style>
