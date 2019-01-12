this program can be used to create the memory values from a game of life situation
<form action="wandler.php" method="post">
<?php
for($j=0;$j<19;++$j) {
	echo ($j%5 == 0 && $j != 0) ? "<hr>" : "<br>";
	for($i=0;$i<30;++$i)
		echo (($i%5 == 0 && $i != 0) ? "|" : "")."<input type='checkbox' name='".$i.",".$j."' value='1'".(($_POST[$i.",".$j] == "1") ? " checked='true'" : "").">";
}
?>
<br>
<br>
<input type="submit" value=" send ">
</form>
<?php
for($j=0;$j<19;++$j)
	for($i=0;$i<30;++$i)
		if($_POST[$i.",".$j] == "1")
			$cell[$j*30+$i] = 1;

for($j=0;$j<72;++$j) {
	$value = 0;
	for($i=0;$i<8;++$i)
		if($cell[$j*8+$i] == 1)
			$value += pow(2,$i);
	if($value > 0)
		echo "golField[".$j."] = ".$value.";<br>";
}
?>
