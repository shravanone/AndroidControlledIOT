<?php
    if(file_exists("fan1.txt"))
    {
        $file = fopen("fan1.txt","r+");
        $default=fread($file,1);
        if($default=="")
        {
            $default="0";
        }
    }
    else
    {
        $file = fopen("fan1.txt","w+");
        $default="0";
    }
    rewind($file);
    if(isset($_GET['bool']))
    {
        $bool = $_GET['bool'];
        if($bool=="0"||$bool=="1")
        {
            fwrite($file,$bool);
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
        $bool=$default;
        fwrite($file,$bool);
        rewind($file);
        $value = fgets($file);
        echo $value;
    }
    fclose($file);
?>