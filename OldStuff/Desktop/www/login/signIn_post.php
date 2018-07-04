<?php

    session_start();

      $servername = "localhost";
      $username = "root";
      $password = "";
      $dbname = "mini-ebay";

      // Create connection
      $conn = new mysqli($servername, $username, $password, $dbname);
      // Check connection
      if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
      } 

      $user = $conn->real_escape_string($_POST['username']);

      $sql = "SELECT username FROM user WHERE `userName` = '$user'";
      $result = $conn->query($sql);

      if ($result->num_rows > 0) //here is a problem
      {
        $_SESSION['username'] = $_POST['username'];
        echo 'Username and Password Found'; 
        echo $_SESSION["username"];
        header( 'Location: ../main.php' );
      }
      else
      {
        echo 'Username and Password NOT Found';
        header('Location: signIn.php');
      }
      $conn->close();
?>          