<?php
 $query = "select * from museum";
 $result = mysqli_query($connection,$query);
 if (!$result) {
 die("databases query failed.");
 }
 while ($row = mysqli_fetch_assoc($result)) {
 echo "<option value='" . $row["musID"] . "'>"; 
 	echo $row["musname"];
echo "</option>";
 }
 mysqli_free_result($result);
?>
