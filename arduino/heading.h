R"(
<!DOCTYPE html>
<html>
  <head>
    <meta charset="UTF-8">
    <title>Set Boat Heading</title>
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

      .btn-manual {
        color: black;
        background-color: #dc3545;
      }

      .btn-waypoint {
        color: black;
        background-color: #106f0a;
      }

      .btn-heading {
        color: black;
        background-color: #FFD700;
      }

      .btn-danger {
        color: white;
        background-color: #dc3545;
      }

      button {
        border-radius: 20px;
      }

      .btn-container {
        display: flex;
        justify-content: center;
        align-items: center;
      }

      .btn {
        width: 35%;
        height: 200px;
        margin: 0 10px;
        font-size: 36px;
      }

      .heading-display {
        display: flex;
        justify-content: center;
        align-items: center;
        height: 400px;
        font-size: 100px;
      }
    </style>
  </head>
  <body>
    <div class="container">
      <h1>Set Boat Heading</h1>
      <div class="heading-display">0&deg;</div>
      <div class="btn-container">
        <button class="btn btn-danger" id="minus-10">-10&deg;</button>
        <button class="btn btn-danger" id="minus-1">-1&deg;</button>
        <button class="btn btn-waypoint" id="plus-1">+1&deg;</button>
        <button class="btn btn-waypoint" id="plus-10">+10&deg;</button>
      </div>
    </div>

    <script src="./js/jquery.js"></script>
    <script>
      const headingDisplay = document.querySelector('.heading-display');
      const minus10Button = document.getElementById('minus-10');
      const minus1Button = document.getElementById('minus-1');
      const plus1Button = document.getElementById('plus-1');
      const plus10Button = document.getElementById('plus-10');

      let heading = 0;

      function updateHeadingDisplay() {
        headingDisplay.textContent = `${heading}${String.fromCharCode(176)}`;
      }

      function setHeading(change) {
        heading += change;

        updateHeadingDisplay();
      }

      minus10Button.addEventListener('click', () => setHeading(-10));
      minus1Button.addEventListener('click', () => setHeading(-1));
      plus1Button.addEventListener('click', () => setHeading(1));
      plus10Button.addEventListener('click', () => setHeading(10));
    </script>
  </body>
</html>
)"