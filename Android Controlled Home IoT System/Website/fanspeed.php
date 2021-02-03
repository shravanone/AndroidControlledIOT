<?php
    if(file_exists("fanspeed.txt"))
    {
        $file = fopen("fanspeed.txt","r+");
        $default=fread($file,1);
        if($default=="")
        {
            $default="0";
        }
    }
    else
    {
        $file = fopen("fanspeed.txt","w+");
        $default="0";
    }
    rewind($file);
    if(isset($_GET['fanspeed']))
    {
        $fanspeed = $_GET['fanspeed'];
        if($fanspeed=="0"||$fanspeed=="1"||$fanspeed=="2"||$fanspeed=="3"||$fanspeed=="4"||$fanspeed=="5")
        {
            fwrite($file,$fanspeed);
            rewind($file);
            $value = fgets($file);
            echo $value;
        }
        else
        {
            echo "Error";
        }
    }
    else
    {
        $fanspeed=$default;
        fwrite($file,$fanspeed);
        rewind($file);
        $value = fgets($file);
        echo $value;
    }
    fclose($file);
?>