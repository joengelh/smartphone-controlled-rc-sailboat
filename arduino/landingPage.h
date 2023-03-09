R"(
<!DOCTYPE html>
<html>
<head>
    <title>Manual and Autopilot Selection</title>
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">
    <style>
        body {
            font-family: Arial, sans-serif;
            color: white;
            background-color: #303030;
        }

        h1,
        h2 {
            color: white;
            text-align: center;
        }

        .btn-manual {
            color: black;
            background-color: #FFD700;
        }

        .btn-autopilot {
            color: black;
            background-color: #1E90FF;
        }

        .btn-danger {
            color: white;
            background-color: #dc3545;
        }

        button {
            border-radius: 10px;
        }
        
        .btn {
            width: 80%;
            height: 150px;
            margin: 0 auto;
            display: block;
            font-size: 36px;
            margin-top: 50px;
        }

        .btn-manual:hover, .btn-autopilot:hover {
            background-color: #AD9500;
        }
        
        @media (min-width: 768px) {
            .btn {
                width: 50%;
            }
        }
    </style>
</head>
<body>
    <h1>Select Operation Mode</h1>
    <div class="container-fluid">
        <div class="row">
            <div class="col-md-6 col-md-offset-3">
                <a href="/autopilot"><button type="button" class="btn btn-autopilot">Autopilot Mode</button></a>
                <a href="/manual"><button type="button" class="btn btn-manual">Manual Mode</button></a>
            </div>
        </div>
    </div>
</body>
</html>
)"