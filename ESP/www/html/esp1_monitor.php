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


          var esp1 = document.getElementById('esp1');
          esp1.onload = function () {
            esp1.contentWindow.scrollTo(0,9999999);
          }
  </script>
    </div>

<p class="pull-right"><input type="button" value="Pauza" id="butonPauza" onclick="pauza()" class="butoncss btn btn-default"></input>
    <input type="button" value="Continua" id="butonContinua" onclick="continua()" class="butoncss btn btn-default"></input></p>
</div>
</div>
</div><!-- COL-LG-8 -->


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
