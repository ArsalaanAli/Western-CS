<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Degree Information</title>
    <link rel="stylesheet" href="">
</head>
<body>
    <h1>Degree Information</h1>
    <form action="" method="post">
        <label for="degreetype">Sort by:</label>
        <select name="degreetype" id="degreetype">
            <option value="Masters">Masters</option>
            <option value="PhD">PhD</option>
        </select>
        <button type="submit">Select</button>
    </form>

    <?php
    include "connecttodb.php";
    include "getdegreeinfo.php";
    ?>
</body>
</html>
