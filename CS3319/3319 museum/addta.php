<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Add TA</title>
    <link rel="stylesheet" href="">
</head>
<body>
    <h1>Add TA</h1>
    <form action="postta.php" method="post">
        <label for="tauserid">TA User ID:</label>
        <input type="text" name="tauserid" required>
        <br>
        <br>    
        <label for="firstname">First Name:</label>
        <input type="text" name="firstname" required>
        <br>
        <br>
        <label for="lastname">Last Name:</label>
        <input type="text" name="lastname" required>
        <br>
        <br>
        <label for="studentnum">Student Number:</label>
        <input type="text" name="studentnum" required>
        <br>
        <br>
        <label for="imageurl">Image URL:</label>
        <input type="text" name="imageurl">
        <br>
        <br>
        <label for="degreetype">Degree Type:</label>
        <select name="degreetype" id="degreetype">
            <option value="Masters">Masters</option>
            <option value="PhD">PhD</option>
        </select>
        <br>
        <br>
        <label for="courses">Select Courses (hold Ctrl to select multiple):</label>
        <br>
        <br>
        <select name="courses[]" id="courses" multiple>
            <?php
             include "connecttodb.php";
            // Assuming you have a 'courses' table with 'coursenum' and 'coursename' columns
            $courseQuery = "SELECT * FROM course";
            $courseResult = mysqli_query($connection, $courseQuery);

            while ($courseRow = mysqli_fetch_assoc($courseResult)) {
                echo "<option value='" . $courseRow['coursenum'] . "'>" . $courseRow['coursename'] . "</option>";
            }

            mysqli_free_result($courseResult);
            ?>
        </select>
        <br>
        <br>
        <button type="submit">Add TA</button>
    </form>
</body>
</html>