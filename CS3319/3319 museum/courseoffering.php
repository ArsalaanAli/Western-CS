<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>View Course Offerings</title>
    <link rel="stylesheet" href="">
</head>
<body>
    <h1>View Course Offerings</h1>

    <form action="postcourseoffering.php" method="post">
        <label for="course">Select Course:</label>
        <br>
        <select name="course" id="course">
            <?php
            include "connecttodb.php";

            // Assuming 'courses' table has 'coursenum' and 'coursename' columns
            $query = "SELECT * FROM course";
            $result = mysqli_query($connection, $query);

            while ($row = mysqli_fetch_assoc($result)) {
                echo "<option value='" . $row['coursenum'] . "'>" . $row['coursenum'] . ": " . $row['coursename'] . "</option>";
            }

            mysqli_free_result($result);
            mysqli_close($connection);
            ?>
        </select>
        <br>

        <label for="startYear">Start Year:</label>
        <br>
        <input type="number" name="startYear" required>
        <br>

        <label for="endYear">End Year:</label>
        <br>
        <input type="number" name="endYear" required>
        <br>

        <button type="submit">Show Course Offerings</button>
    </form>
</body>
</html>