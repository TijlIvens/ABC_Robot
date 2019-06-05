
<?php
$sensorvalue = 0;
$sensorvalue2 = 0;
$sensorvalue3 = 0;
$motor1 = 0;
$motor2 = 0;
$file = fopen("/home/pi/Documents/python/test_data.csv", "r", ","); //this line see readme
while (($row = fgetcsv($file, "0", ",")) !== FALSE) 
{
	//echo $row[0];
	//echo " value";
	//echo $row[1];
	//echo '<br>';
	//echo "==============";
	//echo '<br>';
	$string = $row[0];
	$compare = substr($string, 0, 6);
	if($row[0] == "sensor1")
	{
	$sensorvalue = $row[1];
	}
	
	if($row[0] == "sensor2")
	{
	$sensorvalue2 = $row[1];
	}
	
	if($row[0] == "sensor3")
	{
	$sensorvalue3 = $row[1];
	}
	
	if($compare == "motor1")
	{
	$motor1 = $row[1];
	}
	
	if($compare == "motor2")
	{
	$motor2 = $row[1];
	}
	
}
echo "sensor1 = ";
echo $sensorvalue;
echo " | sensor2 = ";
echo $sensorvalue2;
echo " | sensor3 = ";
echo $sensorvalue3;
echo " |  motor1 = ";
echo $motor1;
echo " |  motor2 = ";
echo $motor2;
?>



<?php 
$sec = 5;
$page = "index.php";
?>
<html>
    <head>
    <meta http-equiv="refresh" content="<?php echo $sec?>;URL='<?php echo $page?>'">
    </head>
    <p id="bottom">bottom of the page</p>
    <script>
    	
    function bottom() {
    document.getElementById( 'bottom' ).scrollIntoView();
	};
	bottom();
	
    </script>
</html>
