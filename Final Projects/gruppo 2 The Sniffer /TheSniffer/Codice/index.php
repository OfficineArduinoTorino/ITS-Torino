<?php
error_reporting(0);

$db_sniffer=new mysqli("localhost","root","","sniffer") or die("Sniffer- ".$db_sniffer->errno().": ".$db_sniffer->error());

$j=array("B","KB","MB","GB","TB");

$sql="SELECT `id`,`ip`,`volume`,`speed` FROM `sniffex`";
$result=$db_sniffer->query($sql);

echo"<html xmlns='http://www.w3.org/1999/xhtml' xml:lang='it' lang='it'>
	<head>
		<title>Sniffer</title>
		<meta charset='utf-8'/>
		<meta name='viewport' content='width=device-width'/> 
		<link rel='stylesheet' href='./common.css'/>
	</head>
	<body onLoad='setTimeout(\"window.location.reload(true)\",1000);'>
		<div id='header'>
			SNIFFER 
		</div>
		<div id='content'>
			<br>
			<table>
				<tr>
					<th>IP</th>
					<th>Traffic volume</th>
					<th>Traffic speed</th>
				</tr>
";
while ($x=$result->fetch_array(MYSQL_ASSOC))
{
	$i=intval(log($x["volume"],1024));
	$i1=intval(log($x["speed"],1024));
	echo "				<tr>
					<td>".$x["ip"]."</td>
					<td>";
	echo sprintf("%.2f",$x["volume"]/pow(1024,$i));
	echo " ".$j[$i]."</td>
					<td>";
	echo sprintf("%.2f",$x["speed"]/pow(1024,$i1));
	echo " ".$j[$i1]."/s</td>
				</tr>
";
}
$sql="SELECT SUM(`volume`) AS `totalvolume`,SUM(`speed`) AS `totalspeed` FROM `sniffex`";
$result=$db_sniffer->query($sql);
$x=$result->fetch_array(MYSQL_ASSOC);

$i=intval(log($x["totalvolume"],1024));
$i1=intval(log($x["totalspeed"],1024));

echo "				<tr>
					<td>Total</td>
					<td>";
echo sprintf("%.2f",$x["totalvolume"]/pow(1024,$i));
echo " ".$j[$i]."</td>
				<td>";
echo sprintf("%.2f",$x["totalspeed"]/pow(1024,$i1));
echo " ".$j[$i1]."/s</td>
				</tr>
			</table>
			<br>
		</div>
		<div id='footer'> 
			Cuccolini Paolo &nbsp; | &nbsp; Di Tommaso Riccardo &nbsp; | &nbsp; Lizza Matteo
		</div>
	</body>
</html>";

$db_sniffer->close();

?>