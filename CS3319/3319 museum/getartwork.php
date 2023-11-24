<?php
 $whichMus = $_POST["order"]; //get selected museum value from the form 
$query = 'SELECT * FROM workofart WHERE whichmus = ' . $whichMus; //fill in with correct query
 $result = mysqli_query($connection, $query);
 if (!$result) {
 die("databases query on art pieces failed. ");
 }
 echo "<ul>"; //put the artwork in an unordered bulleted list
 while ($row = mysqli_fetch_assoc($result)) {
  echo "<li>";
  echo $row["artname"];
 echo " BY ";  
echo $row["artist"];
  echo  "</li>";
 }
 //figure out how to put the loop see (see step 13 below)
 echo "</ul>"; //end the bulleted list
 mysqli_free_result($result);
?>


<?php
 $sortingOrder = $_POST["order"] ? $_POST["order"] : "ASC" ; //get selected museum value from the form 
 $orderCol = $_POST["ordercol"]  ? $_POST["ordercol"] : "lastname" ;
 $query = 'SELECT * FROM ta ORDER BY ' . $orderCol . " " . $sortingOrder; //fill in with correct query
 $result = mysqli_query($connection, $query);
 if (!$result) {
 die("databases query on art pieces failed. ");
 }
 echo "<table border='1'>"; //start the table with border for visibility, you can customize as needed

echo "<tr>";
echo "<th>tauserid</th>";
echo "<th>firstname</th>";
echo "<th>lastname</th>";
echo "<th>studentnum</th>";
echo "<th>degreetype</th>";
echo "</tr>";

echo "<ul>"; //put the artwork in an unordered bulleted list
 while ($row = mysqli_fetch_assoc($result)) {
    echo "<tr>";
    echo "<td>" . $row["tauserid"] . "</td>";
    echo "<td><a href='ta_details.php?tauserid=" . $row["tauserid"] . "'>" . $row["firstname"] . "</a></td>";
    echo "<td>" . $row["lastname"] . "</td>";
    echo "<td>" . $row["studentnum"] . "</td>";
    echo "<td>" . $row["degreetype"] . "</td>";
    echo "</tr>";
 }
 //figure out how to put the loop see (see step 13 below)
 echo "</ul>"; //end the bulleted list
 mysqli_free_result($result);
?>

