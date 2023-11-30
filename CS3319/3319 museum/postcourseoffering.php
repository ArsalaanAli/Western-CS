<?php
include "connecttodb.php";

$course = $_POST["course"];
$startYear = $_POST["startYear"];
$endYear = $_POST["endYear"];

$query = "SELECT coid, numstudent, term, year
          FROM courseoffer
          WHERE whichcourse = '$course'
          AND year BETWEEN '$startYear' AND '$endYear'
          ORDER BY year";

$result = mysqli_query($connection, $query);

if ($result) {
    echo "<h2>Course Offerings for Course $course</h2>";
    echo "<table border='1'>";
    echo "<tr>";
    echo "<th>Course Offering ID</th>";
    echo "<th>Number of Students</th>";
    echo "<th>Term</th>";
    echo "<th>Year Offered</th>";
    echo "</tr>";

    while ($row = mysqli_fetch_assoc($result)) {
        echo "<tr>";
        echo "<td>" . $row["coid"] . "</td>";
        echo "<td>" . $row["numstudent"] . "</td>";
        echo "<td>" . $row["term"] . "</td>";
        echo "<td>" . $row["year"] . "</td>";
        echo "</tr>";
    }

    echo "</table>";
    mysqli_free_result($result);
} else {
    echo "Error fetching course offerings: " . mysqli_error($connection);
}

mysqli_close($connection);
?>