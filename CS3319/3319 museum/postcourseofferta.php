<?php
include "connecttodb.php";

$coid = $_POST["coid"];

$query = "SELECT ta.tauserid, ta.firstname, ta.lastname, courseoffer.whichcourse, course.coursename
          FROM ta
          INNER JOIN hasworkedon ON ta.tauserid = hasworkedon.tauserid
          INNER JOIN courseoffer on courseoffer.coid = hasworkedon.coid
          INNER JOIN course on courseoffer.whichcourse = course.coursenum
          WHERE hasworkedon.coid = '$coid'";

$result = mysqli_query($connection, $query);

if ($result) {
    echo "<h2>TAs for Course Offering $coid </h2>";
    echo "<table border='1'>";
    echo "<tr>";
    echo "<th>User ID</th>";
    echo "<th>First Name</th>";
    echo "<th>Last Name</th>";
    echo "<th>Course Number</th>";
    echo "<th>Course Name</th>";
    echo "</tr>";

    while ($row = mysqli_fetch_assoc($result)) {
        echo "<tr>";
        echo "<td>" . $row["tauserid"] . "</td>";
        echo "<td>" . $row["firstname"] . "</td>";
        echo "<td>" . $row["lastname"] . "</td>";
        echo "<td>" . $row["whichcourse"]  . "</td>";
        echo "<td>" . $row["coursename"]  . "</td>";
        echo "</tr>";
    }

    echo "</table>";
    mysqli_free_result($result);
} else {
    echo "Error fetching TAs for course offering: " . mysqli_error($connection);
}

mysqli_close($connection);
?>

<!-- sudo mysql -nvvf --verbose -pcs3319 <  inputscript.sql  > outputscript1.txt 2>&1 -->