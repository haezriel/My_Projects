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

      $sql = "insert into user values($_POST[userid],'$_POST[firstName]','$_POST[lastName]','$_POST[email]','$_POST[address]','$_POST[username]')";

      if ($conn->query($sql) === TRUE) {
        echo "New record created successfully";
  
        // Set session variables
        $_SESSION['username'] = $_POST['username'];
        echo $_SESSION["userids"];
      } 
      else {
          echo "Error: " . $sql . "<br>" . $conn->error;
      }

      $conn->close();
      header( 'Location: ../main.php' );
?>          