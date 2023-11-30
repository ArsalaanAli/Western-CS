<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>View TA's Course Offerings</title>
    <link rel="stylesheet" href="">
</head>
<body>
    <h1>View TA's Course Offerings</h1>

    <form action="posttacourseoffer.php" method="post">
        <label for="tauserid">Select TA:</label>
        <br>
        <select name="tauserid" id="tauserid">
            <?php
            include "connecttodb.php";

            // Assuming 'ta' table has 'tauserid' column
            $query = "SELECT tauserid, firstname, lastname FROM ta";
            $result = mysqli_query($connection, $query);

            while ($row = mysqli_fetch_assoc($result)) {
                echo "<option value='" . $row['tauserid'] . "'>" . $row['firstname'] . " " . $row['lastname'] . "</option>";
            }

            mysqli_free_result($result);
            mysqli_close($connection);
            ?>
        </select>
        <br>

        <button type="submit">Show TA's Course Offerings</button>
    </form>
</body>
</html>