<html>
<head>
<script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jquery/1.4.2/jquery.min.js"></script>
</head>

<style>

body {
    background-color: #EFF0F0;
}

iframe{
  border-color: 000000;
  border-style: dotted;
  border-width: 3px;

}

.butoncss {
	-moz-box-shadow:inset 0px 0px 0px 0px #ffffff;
	-webkit-box-shadow:inset 0px 0px 0px 0px #ffffff;
	box-shadow:inset 0px 0px 0px 0px #ffffff;
	background:-webkit-gradient(linear, left top, left bottom, color-stop(0.05, #f9f9f9), color-stop(1, #e9e9e9));
	background:-moz-linear-gradient(top, #f9f9f9 5%, #e9e9e9 100%);
	background:-webkit-linear-gradient(top, #f9f9f9 5%, #e9e9e9 100%);
	background:-o-linear-gradient(top, #f9f9f9 5%, #e9e9e9 100%);
	background:-ms-linear-gradient(top, #f9f9f9 5%, #e9e9e9 100%);
	background:linear-gradient(to bottom, #f9f9f9 5%, #e9e9e9 100%);
	filter:progid:DXImageTransform.Microsoft.gradient(startColorstr='#f9f9f9', endColorstr='#e9e9e9',GradientType=0);
	background-color:#f9f9f9;
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

    <iframe id="frame" src="mattilda.html" width="1000" height="600" scrolling="yes" frameBorder="1"></iframe>


    <script type="text/javascript">

          interval = setInterval(function() {$('#frame').attr('src', $('#frame').attr('src'));}, 250);


          function pauza(){
            clearInterval(interval);

          }
          function continua(){
            interval = setInterval(function() {$('#frame').attr('src', $('#frame').attr('src'));}, 250);

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
</body>
</style>
