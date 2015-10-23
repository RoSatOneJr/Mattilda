<html>
<head>
<script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jquery/1.4.2/jquery.min.js"></script>
</head>
<body>

    <iframe id="frame" src="mattilda.html" width="1280" height="720"></iframe>


    <script type="text/javascript">

        $(document).ready(function() {
            setInterval(function() {
                $('#frame').attr('src', $('#frame').attr('src'));
                return false;
            }, 1000);
        });

    </script>
</body>
