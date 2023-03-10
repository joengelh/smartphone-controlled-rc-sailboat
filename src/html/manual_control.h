R"(
<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no" />
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
    <script>
    function makeCall(id) {
    var xhr = new XMLHttpRequest();
    xhr.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
        // handle the response
        console.log(this.responseText);
        }
    };
    xhr.open("GET", id, true);
    xhr.send();
    }
    </script>
    <script>
    function makePost(endpoint, data) {
      var xhr = new XMLHttpRequest();
      xhr.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          // handle the response
          console.log(this.responseText);
        }
      };
      var url = window.location.origin + '/' + endpoint;
      xhr.open("POST", url, true);
      xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
      var encodedData = Object.keys(data).map(function(key) {
        return encodeURIComponent(key) + "=" + encodeURIComponent(data[key]);
      }).join("&");
      xhr.send(encodedData);
    }
    </script>
    <script>
    document.addEventListener("keydown", function(event) {
      if (event.key === "w") {
        makePost("sails", {"direction": "close"});
      } else if (event.key === "a") {
        makePost("rudder", {"direction": "left"})
      } else if (event.key === "s") {
        makePost("sails", {"direction": "open"});
      } else if (event.key === "d") {
        makePost("rudder", {"direction": "right"})
      }
    });
    </script>
    <script>
    function updateSettings() {
        var sailSetting = document.getElementById("sailSetting");
        var rudderSetting = document.getElementById("rudderSetting");

        var sailRequest = new XMLHttpRequest();
        sailRequest.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
            sailSetting.innerHTML = this.responseText;
        }
        };
        sailRequest.open("GET", "/sailSetting", true);
        sailRequest.send();

        var rudderRequest = new XMLHttpRequest();
        rudderRequest.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
            rudderSetting.innerHTML = this.responseText;
        }
        };
        rudderRequest.open("GET", "/rudderSetting", true);
        rudderRequest.send();
    }

    document.addEventListener("DOMContentLoaded", function() {
        setInterval(updateSettings, 1000);
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
            <button id="reach" type="button" class="btn btn-default" style="height: 100%; width: 100%" onclick='makePost("sails", {"direction": "close"});'>Reach</button>
            </div>
        </div>
        <div class="row" style="height: 33.33%; padding-bottom: 1em">
            <div class="col-xs-4" style="height: 100%; text-align: center">
            <button id="port" type="button" class="btn btn-default" style="height: 100%; width: 100%" onclick='makePost("rudder", {"direction": "left"})'>Port</button>
            </div>
            <div class="col-xs-4" style="height: 100%; text-align: center">
            <button id="starboard" type="button" class="btn btn-default" style="height: 100%; width: 100%" onclick='makePost("rudder", {"direction": "right"})'>Starboard</button>
            </div>
            <div class="col-xs-4" style="height: 100%; text-align: center">
            <button id="run" type="button" class="btn btn-default" style="height: 100%; width: 100%" onclick='makePost("sails", {"direction": "open"});'>Run</button>
            </div>
        </div>
        </div>
    </div>
    </body>

</html>
)"