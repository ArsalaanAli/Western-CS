<?php
include "connecttodb.php";

$tauserid = $_POST["tauserid"];
$newImageURL = $_POST["newImageURL"];

// Update TA image URL
$updateQuery = "UPDATE ta SET image = '$newImageURL' WHERE tauserid = '$tauserid'";
$updateResult = mysqli_query($connection, $updateQuery);

if ($updateResult) {
    echo "TA image updated successfully!";
} else {
    echo "Error updating TA image: " . mysqli_error($connection);
}

mysqli_close($connection);
?>