<?php
    date_default_timezone_set("Asia/Kolkata");
    if(file_exists("temp.txt"))
    {
        $file = fopen("temp.txt","r+");
        $default=fgets($file);
        if($default=="")
        {
            $default="0";
        }
    }
    else
    {
        $file = fopen("temp.txt","w+");
        $default="0";
    }
    rewind($file);
    if(file_exists("time.txt"))
    {
        $timefile = fopen("time.txt","r+");
    }
    else
    {
        $timefile = fopen("time.txt","w+");
        $default="0";
    }
    if(isset($_GET['temp'])&&isset($_GET['authkey'])&&$_GET['authkey']=="AuthenticationKey")
    {
        file_put_contents("time.txt","");
        fwrite($timefile,date("Y-m-d")." ".date("h:i:s"));
        $temp = $_GET['temp'];
        fwrite($file,$temp);
        rewind($file);
        $value = fgets($file);
        echo $value;
    }
    else
    {
        $currentTime = date_create(date("Y-m-d")." ".date("h:i:s"));
        $lastRequestTime = date_create(fgets($timefile));
        $timeDifference = date_diff($currentTime,$lastRequestTime);
        $timeDifferenceInMinutes = ($timeDifference->i);
        if($timeDifferenceInMinutes>=1)
        {
            file_put_contents("temp.txt","");
            $default="0";
        }
        $temp=$default;
        fwrite($file,$temp);
        rewind($file);
        $value = fgets($file);
        echo $value;
    }
    fclose($file);
    fclose($timefile);
?>