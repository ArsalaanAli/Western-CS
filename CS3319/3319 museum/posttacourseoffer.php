<?php
include "connecttodb.php";

$tauserid = $_POST["tauserid"];

$query = "SELECT hasworkedon.coid, courseoffer.term, courseoffer.year, hasworkedon.hours,
                 course.coursenum, course.coursename, loves.lcoursenum
          FROM hasworkedon
          INNER JOIN courseoffer ON hasworkedon.coid = courseoffer.coid
          INNER JOIN course ON courseoffer.whichcourse = course.coursenum
          LEFT JOIN loves ON hasworkedon.tauserid = loves.ltauserid
                         AND courseoffer.coid = loves.lcoursenum
          WHERE hasworkedon.tauserid = '$tauserid'
          ORDER BY courseoffer.year, courseoffer.term, course.coursenum";

$result = mysqli_query($connection, $query);

if ($result) {
    echo "<h2>Course Offerings for TA $tauserid</h2>";
    echo "<table border='1'>";
    echo "<tr>";
    echo "<th>Course Number</th>";
    echo "<th>Course Name</th>";
    echo "<th>Term</th>";
    echo "<th>Year Offered</th>";
    echo "<th>Hours Worked</th>";
    echo "<th>Loved/Hated</th>";
    echo "</tr>";

    while ($row = mysqli_fetch_assoc($result)) {
        echo "<tr>";
        echo "<td>" . $row["coursenum"] . "</td>";
        echo "<td>" . $row["coursename"] . "</td>";
        echo "<td>" . $row["term"] . "</td>";
        echo "<td>" . $row["year"] . "</td>";
        echo "<td>" . $row["hours"] . "</td>";

        // Check if the TA loved or hated the course
        $lovedHated = isset($row["lcoursenum"]) ? "Loved 😊" : "Hated 😞";
        echo "<td>" . $lovedHated . "</td>";

        echo "</tr>";
    }

    echo "</table>";
    mysqli_free_result($result);
} else {
    echo "Error fetching TA's course offerings: " . mysqli_error($connection);
}

mysqli_close($connection);
?>