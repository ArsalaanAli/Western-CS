<?php
 $degreeType = $_POST["degreetype"] ? $_POST["degreetype"] : "Masters" ;
 $query = "SELECT * FROM ta WHERE degreetype = '$degreeType'";
 //fill in with correct query
 $result = mysqli_query($connection, $query);
 if (!$result) {
 die("databases query on degree type failed. ");
 }
echo "<h1>Degree Type: '$degreeType'</h1>";
echo "<table border='1'>";
echo "<tr>";
echo "<th>tauserid</th>";
echo "<th>firstname</th>";
echo "<th>lastname</th>";
echo "<th>studentnum</th>";
echo "</tr>";

echo "<ul>";
 while ($row = mysqli_fetch_assoc($result)) {
    echo "<tr>";
    echo "<td>" . $row["tauserid"] . "</td>";
    echo "<td><a href='ta_details.php?tauserid=" . $row["tauserid"] . "'>" . $row["firstname"] . "</a></td>";
    echo "<td>" . $row["lastname"] . "</td>";
    echo "<td>" . $row["studentnum"] . "</td>";
    echo "</tr>";
 }
 //figure out how to put the loop see (see step 13 below)
 echo "</ul>"; //end the bulleted list
 mysqli_free_result($result);
?>

