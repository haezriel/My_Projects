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
  <form method="post" action="./signUp_post.php" class="login">

    <p>
      <label for="userid">User ID:</label>
      <input type="text" name="userid" id="userid" value="">
    </p>
    <p>
      <label for="firstName">First Name:</label>
      <input type="text" name="firstName" id="firstName" value="Wade">
    </p>
    <p>
      <label for="lastName">Last Name:</label>
      <input type="text" name="lastName" id="lastName" value="Wilson">
    </p>
    <p>
      <label for="email">Email:</label>
      <input type="text" name="email" id="email" value="">
    </p>
    <p>
      <label for="address">Address:</label>
      <input type="password" name="address" id="address" value="">
    </p>
    <p>
      <label for="username">Username:</label>
      <input type="text" name="username" id="username" value="">
    </p>
    <p class="login-submit">
      <button type="submit" class="login-button">Login</button>
    </p>
  </form>
</body>
</html>