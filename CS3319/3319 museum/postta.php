<?php
include "connecttodb.php";
$imageurl = $_POST["imageurl"];
$tauserid = $_POST["tauserid"];
$firstname = $_POST["firstname"];
$lastname = $_POST["lastname"];
$studentnum = $_POST["studentnum"];
$degreetype = $_POST["degreetype"];

// Insert TA into 'ta' table
$taQuery = "INSERT INTO ta (tauserid, firstname, lastname, studentnum, degreetype, image) VALUES ('$tauserid', '$firstname', '$lastname', '$studentnum', '$degreetype', '$imageurl')";

if (mysqli_query($connection, $taQuery)) {
    // Get the TA's ID
    $taId = mysqli_insert_id($connection);

    // Insert selected courses into 'loves' table
    if (isset($_POST['courses'])) {
        $courses = $_POST['courses'];

        foreach ($courses as $course) {
            $lovesQuery = "INSERT INTO loves (ltauserid, lcoursenum) VALUES ('$tauserid', '$course')";

            if (!mysqli_query($connection, $lovesQuery)) {
                echo "Error inserting into 'loves' table: " . mysqli_error($connection);
                exit;
            }
        }
    }

    echo "TA and related courses added successfully!";
} else {
    echo "Error inserting into 'ta' table: " . mysqli_error($connection);
}

mysqli_close($connection);
?>