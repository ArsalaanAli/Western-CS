<!DOCTYPE html>
<html>
<head>
	<title>Worldwide Museums</title>
	<link rel="stylesheet" type="text/css" href="museum.css">
	<link href="https://fonts.googleapis.com/css?family=Mali" rel="stylesheet">
</head>
<body>
<script src="museum.js"></script>
<?php
 include "connecttodb.php";
?>
<h1>Museums of the World </h1>
Select your museum:
<form action="" method="post">
<select name="pickamuseum" id="pickamuseum">
  <option value="1">Select Here</option>
  <?php
  include "getmuseum.php";
  ?>
</select>
</form>
<hr>
<?php
 include "connecttodb.php";
 include "getartwork.php";
?>
<hr>
<img src="http://www.csd.uwo.ca/~lreid/blendedcs3319/flippedclassroom/four/kids.png" width="216" height="260">
</body>
</html>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Sort TAs</title>
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
    include "connecttodb.php";
    include "selectfromta.php";
    ?>
</body>
</html>
