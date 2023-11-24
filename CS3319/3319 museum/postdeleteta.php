<?php
include "connecttodb.php";

$tauserid = $_POST["tauserid"];

$deleteQuery = "DELETE FROM ta WHERE tauserid = '$tauserid'";
$deleteResult = mysqli_query($connection, $deleteQuery);

if ($deleteResult) {
    echo "TA deleted successfully!";
} else {
    echo "Error deleting TA: " . mysqli_error($connection);
}

mysqli_close($connection);
?>