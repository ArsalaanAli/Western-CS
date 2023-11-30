<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>TA Information</title>
    <link rel="stylesheet" href="">
</head>
<body>
    <h1>Sort TAs</h1>
    <form action="" method="post">
        <label for="ordercol">Sort by:</label>
        <select name="ordercol" id="ordercol">
            <option value="lastname">Last Name</option>
            <option value="degreetype">Degree</option>
        </select>
        <label for="order">Sorting type:</label>
        <select name="order" id="order">
            <option value="ASC">Ascending</option>
            <option value="DESC">Descending</option>
        </select>
        <button type="submit">Sort</button>
    </form>

    <?php
    if ($_SERVER["REQUEST_METHOD"] == "POST") {
      include "connecttodb.php";
      include "selectfromta.php";
    }
    ?>
</body>
</html>
