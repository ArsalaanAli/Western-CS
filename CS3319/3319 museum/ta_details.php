<?php
include "connecttodb.php";

// Retrieve tauserid from URL parameter
$tauserid = $_GET['tauserid'];

// Query to get TA details based on tauserid
// Query to get TA details, loved courses, and hated courses in a single query
$query = "
    SELECT ta.*, loves.lcoursenum AS love_course, hates.hcoursenum AS hate_course
    FROM ta
    LEFT JOIN loves ON ta.tauserid = loves.ltauserid
    LEFT JOIN hates ON ta.tauserid = hates.htauserid
    WHERE ta.tauserid = '$tauserid'
";
$result = mysqli_query($connection, $query);

if (!$result) {
    die("Database query failed.");
}

// Display TA details
echo "<h2>TA Details</h2>";

if ($row = mysqli_fetch_assoc($result)) {
    // Display the image or placeholder
    if ($row['image']) {
        echo "<img src='" . $row['image'] . "' alt='TA Image'>";
    } else {
        // Placeholder image if 'image' is NULL
        echo "<img src='https://st3.depositphotos.com/6672868/13701/v/450/depositphotos_137014128-stock-illustration-user-profile-icon.jpg' alt='Placeholder Image'>";
    }
    echo "<p><strong>TA ID:</strong> " . $row['tauserid'] . "</p>";
    echo "<p><strong>First Name:</strong> " . $row['firstname'] . "</p>";
    echo "<p><strong>Last Name:</strong> " . $row['lastname'] . "</p>";
    echo "<p><strong>Student Number:</strong> " . $row['studentnum'] . "</p>";
    echo "<p><strong>Degree Type:</strong> " . $row['degreetype'] . "</p>";
} else {
    echo "No details found for the selected TA.";
}
// Display courses the TA loves
echo "<h3>Courses the TA Loves</h3>";

if ($row['love_course']) {
    echo "<ul>";
    do {
        echo "<li>" . $row['love_course'] . "</li>";
    } while ($row = mysqli_fetch_assoc($result));
    echo "</ul>";
} else {
    echo "The TA has not specified any loved courses.";
}

// Display courses the TA hates
echo "<h3>Courses the TA Hates</h3>";

if ($row['hate_course']) {
    echo "<ul>";
    do {
        echo "<li>" . $row['hate_course'] . "</li>";
    } while ($row = mysqli_fetch_assoc($result));
    echo "</ul>";
} else {
    echo "The TA has not specified any hated courses.";
}

// Close the database connection
mysqli_free_result($result);
mysqli_close($connection);
?>