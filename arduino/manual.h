R"(
<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no" />
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">
    <style>
      body {
        font-family: Arial, sans-serif;
        color: white;
        background-color: #303030;
      }
      h1, h2 {
        color: white;
        text-align: center;
      }
      .btn-default {
        color: black;
        background-color: white;
      }
      .btn-primary {
        color: white;
        background-color: #007bff;
      }
      .btn-danger {
        color: white;
        background-color: #dc3545;
      }
      button {
        border-radius: 10px;
      }
      #port {
        background-color: red;
        color: white;
      }
      #starboard {
        background-color: green;
        color: white;
      }
      #reach {
        background-color: orange;
        color: white;
      }
      #run {
        background-color: blue;
        color: white;
      }
    </style>
  </head>
  <head>
	<title>Boat Control</title>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.0/jquery.min.js"></script>
    <script>
      $(document).ready(function() {
        setInterval(function() {
          $.get("/sailSetting", function(data) {
            $("#sailSetting").html(data);
          });
          $.get("/rudderSetting", function(data) {
            $("#rudderSetting").html(data);
          });
        }, 1000);
      });
    </script>
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>
    <script> function makeAjaxCall(url){$.ajax({"url": url})}</script>
    <script>
    document.addEventListener("keydown", function(event) {
      if (event.key === "w") {
        makeAjaxCall("reach");
      } else if (event.key === "a") {
        makeAjaxCall("port");
      } else if (event.key === "s") {
        makeAjaxCall("run");
      } else if (event.key === "d") {
        makeAjaxCall("starboard");
      }
    });
    </script>
  </head>
  <body>
    <h1>Boat Control</h1>
    <h2>Sail Setting: <span id="sailSetting"><?php echo $sailSetting; ?></span></h2>
    <h2>Rudder Setting: <span id="rudderSetting"><?php echo $rudderSetting; ?></span></h2>
    <div class="container-fluid">
      <div class="col-xs-12" style="height: 100vh">
        <div class="row" style="height: 33.33%; padding-top: 1em; padding-bottom: 1em">
          <div class="col-xs-8"></div>
          <div class="col-xs-4" style="text-align: center; height: 100%">
            <button id="reach" type="button" class="btn btn-default" style="height: 100%; width: 100%" onclick='makeAjaxCall("reach")'>Reach</button>
          </div>
        </div>
        <div class="row" style="height: 33.33%; padding-bottom: 1em">
          <div class="col-xs-4" style="height: 100%; text-align: center">
            <button id="port" type="button" class="btn btn-default" style="height: 100%; width: 100%" onclick='makeAjaxCall("port")'>Port</button>
          </div>
          <div class="col-xs-4" style="height: 100%; text-align: center">
            <button id="starboard" type="button" class="btn btn-default" style="height: 100%; width: 100%" onclick='makeAjaxCall("starboard")'>Starboard</button>
          </div>
          <div class="col-xs-4" style="height: 100%; text-align: center">
            <button id="run" type="button" class="btn btn-default" style="height: 100%; width: 100%" onclick='makeAjaxCall("run")'>Run</button>
          </div>
        </div>
      </div>
    </div>
  </body>
</html>
)"
