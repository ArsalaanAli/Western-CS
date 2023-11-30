<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Assign TA to Course Offering</title>
    <link rel="stylesheet" href="">
</head>
<body>
    <h1>Assign TA to Course Offering</h1>
    <form action="assign_ta_to_course_process.php" method="post">
        <label for="tauserid">Select TA User ID:</label>
        <br>
        <select name="tauserid" id="tauserid">
            <?php
            include "connecttodb.php";

            // Assuming 'ta' table has 'tauserid' column
            $query = "SELECT tauserid FROM ta";
            $result = mysqli_query($connection, $query);

            while ($row = mysqli_fetch_assoc($result)) {
                echo "<option value='" . $row['tauserid'] . "'>" . $row['tauserid'] . "</option>";
            }

            mysqli_free_result($result);
            mysqli_close($connection);
            ?>
        </select>
        <br>

        <label for="coid">Select Course Offering ID (coid):</label>
        <br>
        <select name="coid" id="coid">
            <?php
            include "connecttodb.php";

            // Assuming 'ta' table has 'tauserid' column
            $query = "SELECT coid FROM courseoffer";
            $result = mysqli_query($connection, $query);

            while ($row = mysqli_fetch_assoc($result)) {
                echo "<option value='" . $row['coid'] . "'>" . $row['coid'] . "</option>";
            }

            mysqli_free_result($result);
            mysqli_close($connection);
            ?>
        </select>
        <br>

        <label for="hours">Enter Number of Hours:</label>
        <br>
        <input type="number" name="hours" required>
        <br>

        <button type="submit">Assign TA to Course Offering</button>
    </form>
</body>
</html>