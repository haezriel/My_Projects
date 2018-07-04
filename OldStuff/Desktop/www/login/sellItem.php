<!DOCTYPE html>
<!--[if lt IE 7]> <html class="lt-ie9 lt-ie8 lt-ie7" lang="en"> <![endif]-->
<!--[if IE 7]> <html class="lt-ie9 lt-ie8" lang="en"> <![endif]-->
<!--[if IE 8]> <html class="lt-ie9" lang="en"> <![endif]-->
<!--[if gt IE 8]><!--> <html lang="en"> <!--<![endif]-->
<head>
  <meta charset="utf-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1">
  <title>Mini-Ebay</title>
  <link rel="stylesheet" href="css/style.css">
  <!--[if lt IE 9]><script src="//html5shim.googlecode.com/svn/trunk/html5.js"></script><![endif]-->
</head>
<body>
  <form method="post" action="./item_post.php" class="login">

    <p>
      <label for="itemid">Item ID:</label>
      <input type="text" name="itemid" id="itemid" value="">
    </p>
    <p>
      <label for="status">Status:</label>
      <input type="text" name="status" id="status" value="">
    </p>
    <p>
      <label for="postTime">Post Time:</label>
      <input type="text" name="postTime" id="postTime" value="">
    </p>
    <p>
      <label for="userID">User ID:</label>
      <input type="text" name="userID" id="userID" value="">
    </p>
    <p>
      <label for="description">Description:</label>
      <input type="password" name="description" id="description" value="">
    </p>
    <p>
      <label for="buyPrice">Buy Price:</label>
      <input type="text" name="buyPrice" id="buyPrice" value="">
    </p>
    <p>
      <label for="minPrice">Min Price:</label>
      <input type="text" name="minPrice" id="minPrice" value="">
    </p>
    <p class="login-submit">
      <button type="submit" class="login-button">Submit</button>
    </p>
  </form>
</body>
</html>