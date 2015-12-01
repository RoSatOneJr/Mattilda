<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <!-- The above 3 meta tags *must* come first in the head; any other head content must come *after* these tags -->
    <title>Mattilda - Monitor</title>

    <!-- Bootstrap -->
    <link href="css/bootstrap.min.css" rel="stylesheet">
	<link href="css/sticky-footer-navbar.css" rel="stylesheet">
    <!-- HTML5 shim and Respond.js for IE8 support of HTML5 elements and media queries -->
    <!-- WARNING: Respond.js doesn't work if you view the page via file:// -->
    <!--[if lt IE 9]>
      <script src="external/html5shiv.min.js"></script>
      <script src="external/respond.min.js"></script>
    <![endif]-->
	<style>
.pull-left {
  float: left !important;
}
.pull-right {
  float: right !important;
}

body{background-color: #FFF2E5;}

.panel-body{background-color: #FFF2E5;}

iframe{
  border:0;

}

</style>
  </head>
  <body>
    <!-- Fixed navbar -->
    <nav class="navbar navbar-default navbar-fixed-top"  style = "background-color: #ffe6cc">
      <div class="container">
        <div class="navbar-header">
          <button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#navbar" aria-expanded="false" aria-controls="navbar">
            <span class="sr-only">Toggle navigation</span>
            <span class="icon-bar"></span>
            <span class="icon-bar"></span>
            <span class="icon-bar"></span>
          </button>
          <a class="navbar-brand" href="#">Mattilda</a>
        </div>
        <div id="navbar" class="collapse navbar-collapse"  style = "background-color: #ffe6cc">
          <ul class="nav navbar-nav" >
            <li  ><a href="index.php">Monitor</a></li>
          </ul>
          <ul class="nav navbar-nav" >
            <li  ><a href="esp1_monitor.php">ESP1</a></li>
          </ul>
          <ul class="nav navbar-nav" >
            <li  ><a href="esp2_monitor.php">ESP2</a></li>
          </ul>
          <ul class="nav navbar-nav" >
            <li  ><a href="leduri_monitor.php">Leduri + Nivele</a></li>
          </ul>
        </div><!--/.nav-collapse -->
      </div>
    </nav>

    <!-- Begin page content -->
    <div class="container">

	<div class="col-lg-8">
	<div class="panel panel-default">
<div class="panel-heading" style = "background-color: #ffe6cc">
<h3 class="panel-title">ESP1 Log</h3>
</div>
<div class="panel-body">
<div class="embed-responsive embed-responsive-16by9">
      <iframe id="esp1" class="embed-responsive-item" src="mattilda1.html" allowfullscreen=""></iframe>
	      <script type="text/javascript">

          //interval = setInterval(function() {$('#frame').attr('src', $('#frame').attr('src'));}, 1000);
          function pauza(){
            clearInterval(interval);

          }
          function continua(){
            interval = setInterval(function() {$('#esp1').attr('src', $('#esp1').attr('src'));}, 1000);
          }


  </script>
    </div>

<p class="pull-right"><input type="button" value="Pauza" id="butonPauza" onclick="pauza()" class="butoncss btn btn-default"></input>
    <input type="button" value="Continua" id="butonContinua" onclick="continua()" class="butoncss btn btn-default"></input></p>
</div>
</div>
<div class="panel panel-default">
<div class="panel-heading"  style = "background-color: #ffe6cc">
<h3 class="panel-title">ESP2 Log</h3>
</div>
<div class="panel-body">
<div class="embed-responsive embed-responsive-16by9">
      <iframe id="esp2" class="embed-responsive-item" src="mattilda2.html" allowfullscreen=""></iframe>
	      <script type="text/javascript">

          //interval = setInterval(function() {$('#frame').attr('src', $('#frame').attr('src'));}, 1000);
          function pauza2(){
            clearInterval(interval2);

          }
          function continua2(){
            interval2 = setInterval(function() {$('#esp2').attr('src', $('#esp2').attr('src'));}, 1000);

          }


          var esp2 = document.getElementById('frame');
          esp2.onload = function () {
            esp2.contentWindow.scrollTo(0,9999999);
          }
  </script>
    </div>

<p class="pull-right"><input type="button" value="Pauza" id="butonPauza2" onclick="pauza2()" class="butoncss btn btn-default"></input>
    <input type="button" value="Continua" id="butonContinua2" onclick="continua2()" class="butoncss btn btn-default"></input></p>
</div>
</div>
</div><!-- COL-LG-8 --><div class="col-lg-4">
<!-- ==== -->
<div class="panel panel-default">
<div class="panel-heading"  style = "background-color: #ffe6cc">
<h3 class="panel-title">Leduri</h3>
</div>
<div class="panel-body">

   <script type="text/javascript">

    //  intervalrosu = setInterval(function() {$('#framerosu').attr('src', $('#framerosu').attr('src'));}, 1000);
    //  intervalgalben = setInterval(function() {$('#framegalben').attr('src', $('#framegalben').attr('src'));}, 1000);
    //  intervalverde = setInterval(function() {$('#frameverde').attr('src', $('#frameverde').attr('src'));}, 1000);
      function pauzaleduri(){
        clearInterval(intervalrosu);
      //  clearInterval(intervalgalben);
      //  clearInterval(intervalverde);

      }

      function continualeduri(){

        intervalrosu = setInterval(function() {$('#framerosu').attr('src', $('#framerosu').attr('src'));}, 1000);
    //    intervalgalben = setInterval(function() {$('#framegalben').attr('src', $('#framegalben').attr('src'));}, 1000);
      //  intervalverde = setInterval(function() {$('#frameverde').attr('src', $('#frameverde').attr('src'));}, 1000);

      }

      var leduri = document.getElementById('frame');
      leduri.onload = function () {
        leduri.contentWindow.scrollTo(0,9999999);
      }
      </script>
	   <center>
<iframe id="framerosu" class="embed-responsive-item" width="240" height= "450" src="led.html" frame-border = "0" allowfullscreen=""></iframe><br>

  <input type="button" value="Pauza" id="butonPauza" onclick="pauzaleduri()" class="butoncss btn btn-default"></input>
  <input type="button" value="Continua" id="butonContinua" onclick="continualeduri()" class="butoncss btn btn-default"></input>
  </center>

</div>
</div>



<!-- ==== -->

<!-- ==== -->
  <div class="panel panel-default">
    <div class="panel-heading"  style = "background-color: #ffe6cc">
    <h3 class="panel-title">Actiuni leduri</h3>
    </div>
    <div class="panel-body">
    <style>
      .rosu {
        color: #dc322f;
        font-family:"Helvetica Neue", Arial, sans-serif;
        font-weight:100;
        -webkit-font-smoothing:antialiased;
          }
      .galben {
        color: #b58900;
        font-family:"Helvetica Neue", Arial, sans-serif;
        font-weight:100;
        -webkit-font-smoothing:antialiased;
      }
      .verde {
        color: #859900;
        font-family:"Helvetica Neue", Arial, sans-serif;
        font-weight:100;
        -webkit-font-smoothing:antialiased;
      }
    </style><strong>
    <p class="rosu">  LED Rosu = [Ce reprezinta ledul rosu aici] </p>
       <p class="galben"> LED Galben = [Ce reprezinta ledul galben aici] </p>
       <p class="verde"> LED Verde = [Ce reprezinta ledul verde aici] </p></strong>
    </div>
  </div>
<!-- ==== -->

<div class="panel panel-default">
 <div class="panel-heading"  style = "background-color: #ffe6cc">
 <h3 class="panel-title">Nivele</h3>
 </div>
 <div class="panel-body">
 <div class="embed-responsive embed-responsive-16by9">
       <iframe id="lift" class="embed-responsive-item" src="nivele.html" allowfullscreen=""></iframe>
         <script type="text/javascript">

           //interval = setInterval(function() {$('#frame').attr('src', $('#frame').attr('src'));}, 1000);
           function pauza3(){
             clearInterval(interval3);

           }
           function continua3(){
             interval3 = setInterval(function() {$('#lift').attr('src', $('#lift').attr('src'));}, 1000);

           }


           var lift = document.getElementById('frame');
           lift.onload = function () {
             lift.contentWindow.scrollTo(0,9999999);
           }
   </script>
   </div>
   <center>
    <input type="button" value="Pauza" id="butonPauza2" onclick="pauza3()" class="butoncss btn btn-default"></input>
     <input type="button" value="Continua" id="butonContinua2" onclick="continua3()" class="butoncss btn btn-default"></input>
   </center>
 </div>
 </div>


</div><!-- COL-LG-4 -->


	</div> <!-- CONTAINER -->





  <footer class="footer"  style = "background-color: #ffe6cc" >
    <div class="container">
      <p class="text-muted">Copyright &copy; <?php echo date("Y"); ?> <a href="https://github.com/RoSatOneJr/Mattilda">RoSatOneJr</a></p>
    </div>
  </footer>


    <script src="external/jquery.min.js"></script>
    <script src="js/bootstrap.min.js"></script>
  </body>
</html>
