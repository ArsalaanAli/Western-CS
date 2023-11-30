<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>View Course Offering TAs</title>
    <link rel="stylesheet" href="">
</head>
<body>
    <h1>View Course Offering TAs</h1>

    <form action="postcourseofferta.php" method="post">
        <label for="coid">Select Course Offering ID (coid):</label>
        <select name="coid" id="coid">
            <?php
            include "connecttodb.php";

            // Assuming 'ta' table has 'tauserid' column
            $query = "SELECT coid, whichcourse FROM courseoffer";
            $result = mysqli_query($connection, $query);

            while ($row = mysqli_fetch_assoc($result)) {
                echo "<option value='" . $row['coid'] . "'>" . $row['coid'] . "</option>";
            }

            mysqli_free_result($result);
            mysqli_close($connection);
            ?>
        </select>
        <button type="submit">Show TAs for Course Offering</button>
    </form>

</body>
</html>