<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1 ,maximum-scale=1">
    <link rel="shortcut icon" type="img/png" href="favicon.png">
    <title>Mini Project</title>
    <link rel="stylesheet" href="style.css"/>
</head>
<body>
    <main>
        <div id="Light 1">
            <h1 id="light1">Light 1 :<h2 class="light1"><?php
            include("light1.php");
            ?></h2></h1>
            <button class="btn1" id="btn">Turn Off</button>
        </div>
        <div id="Light 2">
            <h1 id="light2">Light 2 :<h2 class="light2"><?php
            include("light2.php");
            ?></h2></h1>
            <button class="btn2" id="btn">Turn Off</button>
        </div>
        <div id="Fan 1">
            <h1 id="fan1">Fan 1 :<h2 class="fan1"><?php
            include("fan1.php");
            ?></h2></h1>
            <button class="fanbtn1" id="btn">Turn Off</button>
        </div>
        <div id="Light 3">
            <h1 id="light3">Light 3 :<h2 class="light3"><?php
            include("light3.php");
            ?></h2></h1>
            <button class="btn3" id="btn">Turn Off</button>
        </div>
        <div id="dropdown">
            <h1 id="currentspeed">Current Speed : <?php include("fanspeed.php");?></h1>
            <button class="fanbtn" id="setfanspeed">Set Fan Speed</button>
            <ul id="fanspeedlist">
                <li><button class="fanbtn" id="fanspeed0">0</button></li>
                <li><button class="fanbtn" id="fanspeed1">1</button></li>
                <li><button class="fanbtn" id="fanspeed2">2</button></li>
                <li><button class="fanbtn" id="fanspeed3">3</button></li>
                <li><button class="fanbtn" id="fanspeed4">4</button></li>
                <li><button class="fanbtn" id="fanspeed5">5</button></li>
            </ul>
        </div> 
        <div class="input"><h1 id="input">Current Temperature : <?php include("temp.php"); ?></h1></div>   
    </main>
    <script src="project.js"></script>
</body>
</html>